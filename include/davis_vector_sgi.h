#ifndef _DAVIS_VECTOR_SGI_H
#define _DAVIS_VECTOR_SGI_H
#include "davis_allocate.h"
#include "davis_uninitialized.h"
#include "davis_construct.h"
namespace davis
{
    template <class _Tp, class _Alloc>
    class _Vector_base
    {
    public:
        typedef _Alloc allocator_type;
        allocator_type get_allocator() const { return allocator_type(); }

        _Vector_base(const _Alloc &__x)
            : _M_start(0), _M_finish(0), _M_end_of_storage(0)  {}

        _Vector_base(size_t __n, const _Alloc &__x)
            : _M_start(0), _M_finish(0), _M_end_of_storage(0)
        {
            _M_start = _M_allocate(__n);
            _M_finish = _M_start;
            _M_end_of_storage = _M_start + __n;
        }

        ~_Vector_base() { _M_deallocate(_M_start, _M_end_of_storage - _M_start); }

    protected:
        _Tp *_M_start;         
        _Tp *_M_finish;        
        _Tp *_M_end_of_storage;
        
        davis::allocator<_Tp> _M_data_allocator;

        _Tp *_M_allocate(size_t __n)
        {
            return _M_data_allocator.allocate(__n);
        }
        void _M_deallocate(_Tp *__p, size_t __n)
        {
            _M_data_allocator.deallocate(__p, __n);
        }
    };

    template <class _Tp, class _Alloc = davis::allocator<_Tp>>
    class vector : protected _Vector_base<_Tp, _Alloc>
    {
    private:
        typedef _Vector_base<_Tp, _Alloc> _Base;

    public:
        typedef _Tp                             value_type;
        typedef value_type*                     pointer;
        typedef const value_type*               const_pointer;
        typedef value_type*                     iterator;
        typedef const value_type*               const_iterator;
        typedef value_type&                     reference;
        typedef const value_type&               const_reference;
        typedef size_t                          size_type;
        typedef ptrdiff_t                       difference_type;

        typedef typename _Base::allocator_type           allocator_type;
        allocator_type get_allocator() const { return _Base::get_allocator(); }

    protected:
        using _Base::_M_allocate;
        using _Base::_M_deallocate;
        using _Base::_M_end_of_storage;
        using _Base::_M_finish;
        using _Base::_M_start;

    //构造函数
    public:
        //构造函数
        explicit vector(const allocator_type &__a = allocator_type()) : _Base(__a) {}
        vector(size_type __n, const _Tp &__value,
               const allocator_type &__a = allocator_type())
            : _Base(__n, __a)
        {
            _M_finish = davis::uninitialized_fill_n(_M_start, __n, __value);
        }

        explicit vector(size_type __n)
            : _Base(__n, allocator_type())
        {
            _M_finish = davis::uninitialized_fill_n(_M_start, __n, _Tp());
        }

        // 拷贝构造，构造拥有 __x 内容的容器
        vector(const vector<_Tp, _Alloc> &__x)
            : _Base(__x.size(), __x.get_allocator())
        {
            _M_finish = davis::uninitialized_copy(__x.begin(), __x.end(), _M_start);
        }

        ~vector() { davis::destroy(_M_start, _M_finish); }

    public:
        iterator begin() { return _M_start; }
        const_iterator begin() const { return _M_start; }
        iterator end() { return _M_finish; }
        const_iterator end() const { return _M_finish; }

        size_type size() const { return static_cast<size_type>(end() - begin()); }
        size_type capacity() const { return static_cast<size_type>(_M_end_of_storage - begin()); }
        bool empty() const { return begin() == end(); }
        size_type max_size() const { return size_type(-1) / sizeof(_Tp); }

        reference front() { return *begin(); }
        const_reference front() const { return *begin(); }
        reference back() { return *(end() - 1); }
        const_reference back() const { return *(end() - 1); }

        //对外开放的容器标准接口
        void push_back(const _Tp& __val);
        void push_back();
        void pop_back();

        
        iterator insert(iterator __position, const _Tp& __val);
        iterator insert(iterator __position);

        template <class _InputIterator>
        void insert(iterator __pos, _InputIterator __first, _InputIterator __last)
        {
            typedef typename davis::_Is_integer<_InputIterator>::_Integral _Integral;
            _M_insert_dispatch(__pos,__first,__last,_Integral());
        }

        template <class _Integer>
        void _M_insert_dispatch(iterator __pos, _Integer __n, _Integer __val, __true_type)
        {
            _M_fill_insert(__pos, (size_type)__n, (_Tp)__val);
        }

        template <class _InputIterator>
        void _M_insert_dispatch(iterator __pos, _InputIterator __first, _InputIterator __last, __false_type)
        {
            _M_range_insert(__pos, __first, __last, davis::iterator_category(__first));
        }

        //TODO reverse_iterater
        void reverse(size_type __n);

        //TODO 实现以下成员函数，包括辅助函数。并且重载运算符
        void assign(size_type __n,const _Tp& __val);

        iterator erase(iterator __position);
        iterator erase(iterator __first,iterator __last);

        void resize(size_type __new_size, const _Tp& __x);
        void resize(size_type __new_size);
        void clear();

    //操作符重载
    public:
        reference operator[](size_type __n) { return *(begin() + __n); }
        const_reference operator[](size_type __n) const { return *(begin() + __n); }

    //容器内部使用的辅助函数
    protected:
        void _M_insert_aux(iterator __position, const _Tp &__x);
        void _M_insert_aux(iterator __position);
        void __M_fill_insert(iterator __pos, size_type __n, const _Tp& __val);

        template <class _InputIterator>
        void _M_range_insert(iterator __pos,_InputIterator __first, _InputIterator __last,input_iterator_tag);

        template <class _ForwardIterator>
        void _M_range_insert(iterator __pos,_ForwardIterator __first, _ForwardIterator __last,forward_iterator_tag);


    };

    //
    template <class _Tp, class _Alloc>
    void vector<_Tp, _Alloc>::push_back(const_reference __x)
    {
        if (_M_finish != _M_end_of_storage)
        {
            davis::construct(_M_finish, __x);
            ++_M_finish;
        }
        else
        {
            _M_insert_aux(end(), __x);
        }
    }

    template <class _Tp, class _Alloc>
    void vector<_Tp, _Alloc>::push_back()
    {
        if (_M_finish != _M_end_of_storage)
        {
            davis::construct(_M_finish);
            ++_M_finish;
        }
        else
        {
            _M_insert_aux(end());
        }
    }

    template <class _Tp, class _Alloc>
    void vector<_Tp, _Alloc>::pop_back()
    {
        --_M_finish;
        davis::destroy(_M_finish);
    }

    template <class _Tp, class _Alloc>
    _Tp* vector<_Tp, _Alloc>::insert(iterator __position, const _Tp &__val)
    {
        size_type __n=__position-begin();
        if (_M_finish != _M_end_of_storage && __position==end())
        {
            davis::construct(_M_finish, __val);
            ++_M_finish;
        }
        else
        {
            _M_insert_aux(end(), __val);
        }
        return begin()+__n;
    }

    template <class _Tp, class _Alloc>
    _Tp* vector<_Tp, _Alloc>::insert(iterator __position)
    {
        size_type __n = __position - begin();
        if (_M_finish != _M_end_of_storage && __position == end())
        {
            davis::construct(_M_finish);
            ++_M_finish;
        }
        else
        {
            _M_insert_aux(end());
        }
        return begin() + __n;
    }
    template <class _Tp, class _Alloc>
    _Tp* vector<_Tp, _Alloc>::erase(iterator __position)
    {
        if(__position+1!=end())
        {
            std::copy(__position + 1, end(), __position);
        }
        --_M_finish;
        davis::destroy(_M_finish); 
        return __position;
    }
    template <class _Tp, class _Alloc>
    _Tp* vector<_Tp, _Alloc>::erase(iterator __first, iterator __last)
    {
        iterator __i=std::copy(__last,_M_finish,__first);
        for(;__i!=_M_finish;__i++)
        {
            davis::destroy(__i);
        }
        _M_finish = _M_finish - (__last - __first);
        return __first;
    }
    template <class _Tp, class _Alloc>
    void vector<_Tp, _Alloc>::resize(size_type __new_size, const _Tp &__x)
    {
        if(__new_size<size())
        {
            erase(begin()+__new_size,end());
        }
        else{
            insert(end(),__new_size-size(),__x);
        }

    }

    template <class _Tp, class _Alloc>
    void vector<_Tp, _Alloc>::resize(size_type __new_size)
    {
        resize(__new_size,_Tp());
    }

    template <class _Tp, class _Alloc>
    void vector<_Tp, _Alloc>::clear()
    {
        erase(begin(),end());
    }
    //辅助函数实现
    template <class _Tp, class _Alloc>
    void vector<_Tp, _Alloc>::_M_insert_aux(iterator __position, const _Tp &__x)
    {
        if(_M_finish!=_M_end_of_storage)
        {
            construct(_M_finish, *(_M_finish - 1));
            ++_M_finish;
            _Tp __x_copy = __x;
            //TODO
            std::copy_backward(__position, _M_finish - 2, _M_finish - 1);
            *__position = __x_copy;
        }
        else{
            const size_type __old_size = size();
            size_type __new_size = __old_size == 0 ? 1 : 2 * __old_size;
            iterator __new_start = _M_allocate(__new_size);
            iterator __new_finish = __new_start ;
            try
            {
                
                __new_finish = davis::uninitialized_copy(_M_start, __position, __new_start);
                construct(__new_finish, __x);
                ++__new_finish;
                __new_finish = davis::uninitialized_copy(__position, _M_finish, __new_finish);
            }
            catch (...)
            {
                davis::destroy(__new_start, __new_finish);
                _M_deallocate(__new_start, __new_size);
                throw;
            }
            davis::destroy(begin(), end());
            _M_deallocate(_M_start, _M_end_of_storage - _M_start);
            _M_start = __new_start;
            _M_finish = __new_finish;
            _M_end_of_storage = _M_start + __new_size;
        }
    }


    template <class _Tp, class _Alloc>
    void vector<_Tp,_Alloc>::__M_fill_insert(iterator __pos, size_type __n, const _Tp &__x)
    {
        if(__n!=0){
            if(size_type(_M_end_of_storage-_M_finish)>=__n)
            {
                _Tp __x_copy=__x;
                const size_type __element_cnt = _M_finish - __pos ;
                iterator __old_finish = _M_finish; 
                if (__element_cnt > __n)
                {
                    davis::uninitialized_copy(_M_finish-__n,_M_finish,_M_finish);
                    _M_finish+=__n;
                    std::copy_backward(__pos,__old_finish-__n,__old_finish);
                    std::fill(__pos,__pos+__n,__x_copy);
                }
                else
                {
                    davis::uninitialized_fill_n(_M_finish,__n-__element_cnt,__x_copy);
                    _M_finish += __n - __element_cnt;
                    davis::uninitialized_copy(__pos, __old_finish, _M_finish);
                    _M_finish += __element_cnt;
                    std::fill(__pos, __old_finish, __x_copy);
                }
            }
            else
            {
                const size_type __old_size = size();
                size_type __new_size = __old_size + std::max(__old_size,__n);
                iterator __new_start = _M_allocate(__new_size);
                iterator __new_finish = __new_start;
                try
                {
                    __new_finish = davis::uninitialized_copy(_M_start, __pos, __new_start);
                    __new_finish = davis::uninitialized_fill_n(__new_finish, __n, __x);
                    __new_finish = davis::uninitialized_copy(__pos, _M_finish, __new_finish);
                }
                catch (...)
                {
                    davis::destroy(__new_start, __new_finish);
                    _M_deallocate(__new_start, __new_size);
                    throw;
                }
                davis::destroy(begin(), end());
                _M_deallocate(_M_start, _M_end_of_storage - _M_start);
                _M_start = __new_start;
                _M_finish = __new_finish;
                _M_end_of_storage = _M_start + __new_size;
            }
        }
    }

    template <class _Tp, class _Alloc>
    template <class _InputIterator>
    void vector<_Tp,_Alloc>::_M_range_insert(iterator __pos, _InputIterator __first, _InputIterator __last, input_iterator_tag)
    {
        for(;__first!=__last;++__first)
        {
            __pos=insert(__pos,*__first);
            ++__pos;
        }
    }

    template <class _Tp, class _Alloc>
    template <class _ForwardIterator>
    void vector<_Tp, _Alloc>::_M_range_insert(iterator __pos, _ForwardIterator __first, _ForwardIterator __last, forward_iterator_tag)
    {
        if (__first != __last)
        {
            size_type __n = davis::distance(__first,__last);
            if (size_type(_M_end_of_storage - _M_finish) >= __n)
            {
                const size_type __element_cnt = _M_finish - __pos;
                iterator __old_finish = _M_finish;
                if (__element_cnt > __n)
                {
                    davis::uninitialized_copy(_M_finish - __n, _M_finish, _M_finish);
                    _M_finish += __n;
                    std::copy_backward(__pos, __old_finish - __n, __old_finish);
                    std::copy(__first, __last , __pos);
                }
                else
                {
                    _ForwardIterator __mid = __first;
                    advance(__mid, __element_cnt);

                    davis::uninitialized_copy(__mid, __last, _M_finish);
                    _M_finish += __n - __element_cnt;
                    davis::uninitialized_copy(__pos, __old_finish, _M_finish);
                    _M_finish += __element_cnt;
                    std::copy(__first, __mid, __pos);
                }
            }
            else
            {
                const size_type __old_size = size();
                size_type __new_size = __old_size + std::max(__old_size, __n);
                iterator __new_start = _M_allocate(__new_size);
                iterator __new_finish = __new_start;
                try
                {
                    __new_finish = davis::uninitialized_copy(_M_start, __pos, __new_start);
                    __new_finish = davis::uninitialized_copy(__first, __last, __new_finish);
                    __new_finish = davis::uninitialized_copy(__pos, _M_finish, __new_finish);
                }
                catch (...)
                {
                    davis::destroy(__new_start, __new_finish);
                    _M_deallocate(__new_start, __new_size);
                    throw;
                }
                davis::destroy(begin(), end());
                _M_deallocate(_M_start, _M_end_of_storage - _M_start);
                _M_start = __new_start;
                _M_finish = __new_finish;
                _M_end_of_storage = _M_start + __new_size;
            }
        }
    }
}

#endif