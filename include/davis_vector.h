#ifndef _DAVIS_VECTOR_H
#define _DAVIS_VECTOR_H
#include "davis_allocate.h"
#include "davis_uninitialized.h"
#include "davis_construct.h"
namespace DAVIS
{
    template <class _Tp, class _Alloc>
    class _Vector_base
    {
    public:
        typedef _Alloc allocator_type;
        allocator_type get_allocator() const { return allocator_type(); }


        _Vector_base(const _Alloc &)
            : _M_start(0), _M_finish(0), _M_end_of_storage(0) {}

        _Vector_base(size_t __n, const _Alloc &)
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
        //TODO _M_data_allocator应该要如何赋值
        DAVIS::allocator<_Tp> _M_data_allocator;

        _Tp *_M_allocate(size_t __n)
        {
            return _M_data_allocator.allocate(__n);
        }
        void _M_deallocate(_Tp *__p, size_t __n)
        {
            _M_data_allocator.deallocate(__p, __n);
        }
    };

    template <class _Tp, class _Alloc = DAVIS::allocator<_Tp>>
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

    protected:
        void _M_insert_aux(iterator __position, const _Tp &__x);
        void _M_insert_aux(iterator __position);

    public:
        iterator begin() { return _M_start; }
        const_iterator begin() const { return _M_start; }
        iterator end() { return _M_finish; }
        const_iterator end() const { return _M_finish; }

        size_type size() const { return static_cast<size_type>(end() - begin()); }
        size_type capacity() const { return static_cast<size_type>(_M_end_of_storage - begin()); }
        bool empty() const { return begin() == end(); }
        size_type max_size() const { return size_type(-1) / sizeof(_Tp); }

        reference operator[](size_type __n) { return *(begin() + __n); }
        const_reference operator[](size_type __n) const { return *(begin() + __n); }


        //构造函数
        explicit vector(const allocator_type &__a = allocator_type()) : _Base(__a) {}
        vector(size_type __n, const _Tp &__value,
               const allocator_type &__a = allocator_type())
            : _Base(__n, __a)
        {
            _M_finish = DAVIS::uninitialized_fill_n(_M_start, __n, __value);
        }

        explicit vector(size_type __n)
            : _Base(__n, allocator_type())
        {
            _M_finish = DAVIS::uninitialized_fill_n(_M_start, __n, _Tp());
        }

        // 拷贝构造，构造拥有 __x 内容的容器
        vector(const vector<_Tp, _Alloc> &__x)
            : _Base(__x.size(), __x.get_allocator())
        {
            _M_finish = DAVIS::uninitialized_copy(__x.begin(), __x.end(), _M_start);
        }

        ~vector() { DAVIS::destroy(_M_start, _M_finish); }

        reference front() { return *begin(); }
        const_reference front() const { return *begin(); }
        reference back() { return *(end() - 1); }
        const_reference back() const { return *(end() - 1); }


        void push_back(const _Tp & __x)
        {
            if (_M_finish != _M_end_of_storage)
            {
                DAVIS::construct(_M_finish, __x);
                ++_M_finish;
            }
            else
            {
                _M_insert_aux(end(), __x);
            }
        }

        void pop_back()
        {
            --_M_finish;
            DAVIS::destroy(_M_finish);
        }

        
    };
}

#endif