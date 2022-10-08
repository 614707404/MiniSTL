#ifndef DAVIS_VECTOR_H
#define DAVIS_VECTOR_H
#include "davis_allocate.h"
#include "davis_construct.h"
#include "davis_uninitialized.h"
#include "davis_iterator.h"
namespace davis
{
    template <class _Tp, class _Alloc = davis::allocator<_Tp> >
    class vector
    {
        // Member Type
    public:
        typedef _Tp                                 value_type;
        typedef _Alloc                              allocator_type;
        typedef value_type&                         reference;
        typedef const value_type&                   const_reference;
        typedef value_type*                         pointer;
        typedef const value_type*                   const_pointer;
        typedef value_type*                         iterator;
        typedef const value_type*                   const_iterator;
        // TODO reverse_itrator
        // typedef reverse_iterator<iterator>          reverse_iterator;
        // typedef reverse_iterator<const_iterator>    const_reverse_iterator;
        typedef size_t                              size_type;
        typedef ptrdiff_t                           difference_type;

    // Data
    protected:
        iterator _M_start;
        iterator _M_finish;
        iterator _M_end_of_storage;
        allocator_type _M_allocator;

    // Member Functions
    protected:
        // use allocator
        _Tp* _M_allocate(size_type __n)
        {
            return _M_allocator.allocate(__n);
        }
        void _M_deallocate(_Tp* __p, size_type __n)
        {
            if(__p)
                _M_allocator.deallocate(__p,__n);
        }

        
        void _M_range_check(size_type n) const;
        
        void _M_fill_assign(size_type n, const value_type& val);
        template <class _Integer>
        void _M_assign_dispatch(_Integer n, _Integer val, __true_type)
        {
            _M_fill_assign((size_type)n, (_Tp)val);
        }
        template <class _InputIter>
        void _M_assign_dispatch(_InputIter first, _InputIter last, __false_type)
        {
            _M_assign_aux(first, last, davis::iterator_category(first));
        }
        template <class _InputIterator>
        void _M_assign_aux(_InputIterator first, _InputIterator last,
                           input_iterator_tag);
        template <class _ForwardIterator>
        void _M_assign_aux(_ForwardIterator first, _ForwardIterator last,
                           forward_iterator_tag);

        void _M_insert_aux(iterator position, const _Tp &x);
        void _M_insert_aux(iterator position);
        void _M_fill_insert(iterator pos, size_type n, const _Tp &x);
        template <class _ForwardIterator>
        iterator _M_allocate_and_copy(size_type n, _ForwardIterator first,
                                      _ForwardIterator last);
        template <class _Integer>
        void _M_initialize_aux(_Integer n, _Integer value, davis::__true_type)
        {
            _M_start = _M_allocate(n);
            _M_end_of_storage = _M_start + n;
            _M_finish = davis::uninitialized_fill_n(_M_start, n, value);
        }

        template <class _InputIterator>
        void _M_initialize_aux(_InputIterator first, _InputIterator last,
                               davis::__false_type)
        {
            _M_range_initialize(first, last, davis::iterator_category(first));
        }
        template <class _InputIterator>
        void _M_range_initialize(_InputIterator __first,
                                 _InputIterator __last, davis::input_iterator_tag)
        {
            for (; __first != __last; ++__first)
                push_back(*__first);
        }

        template <class _ForwardIterator>
        void _M_range_initialize(_ForwardIterator __first,
                                 _ForwardIterator __last, davis::forward_iterator_tag)
        {
            size_type __n = davis::distance(__first, __last);
            _M_start = _M_allocate(__n);
            _M_end_of_storage = _M_start + __n;
            // TODO std
            _M_finish = std::uninitialized_copy(__first, __last, _M_start);
        }
        template <class _Integer>
        void _M_insert_dispatch(iterator __pos, _Integer __n, _Integer __val,
                                __true_type)
        {
            _M_fill_insert(__pos, (size_type)__n, (_Tp)__val);
        }

        template <class _InputIterator>
        void _M_insert_dispatch(iterator __pos,
                                _InputIterator __first, _InputIterator __last,
                                __false_type)
        {
            _M_range_insert(__pos, __first, __last, davis::iterator_category(__first));
        }
        template <class _InputIterator>
        void _M_range_insert(iterator __pos,
                             _InputIterator __first, _InputIterator __last,
                             davis::input_iterator_tag);

        template <class _ForwardIterator>
        void _M_range_insert(iterator __pos,
                             _ForwardIterator __first, _ForwardIterator __last,
                             davis::forward_iterator_tag);

    public:
        // constructors
        // default constructor
        explicit vector(const allocator_type& __alloc = allocator_type());
        // fill constructor
        explicit vector(size_type __n);
        vector(size_type __n, const value_type& __val,
               const allocator_type& __alloc = allocator_type());
        // range constructor
        template <class _InputIterator>
        vector(_InputIterator first, _InputIterator last,
               const allocator_type& alloc = allocator_type());
        // copy constructor (and copying with allocator)
        vector(const vector& x);
        vector(const vector& x, const allocator_type& alloc);
        // TODO move constructor (and moving with allocator)
        // vector(vector&& x);
        // vector(vector&& x, const allocator_type& alloc);
        // TODO initializer list constructor
        // vector(initializer_list<value_type> il,
        //        const allocator_type& alloc = allocator_type());

        // destructor
        ~vector();

        // operator=
        vector& operator=(const vector& x);

        // TODO move 
        // vector& operator=(vector&& x);
        // TODO initializer_list
        // vector& operator=(initializer_list<value_type> il);

        // Iterators
        iterator begin() noexcept {return _M_start;}
        const_iterator begin() const noexcept {return _M_start;}
        iterator end() noexcept {return _M_finish;}
        const_iterator end() const noexcept {return _M_finish;}
        const_iterator cbegin() const noexcept {return _M_start;}
        const_iterator cend() const noexcept {return _M_finish;}

        // TODO reverse 
        // rbegin
        // rend
        // crbegin
        // crend

        // Capacity
        
        size_type size() const noexcept {return static_cast<size_type>(end()-begin());}
        size_type max_size() const noexcept { return static_cast<size_type>(-1) / sizeof(_Tp); }
        size_type capacity() const noexcept { return static_cast<size_type>(_M_end_of_storage - begin()); }
        bool empty() const noexcept {return begin()==end();}
        void resize(size_type n);
        void resize(size_type n, const value_type &val);
        // Requests that the vector capacity be at least enough to contain n elements
        void reserve(size_type n);
        void shrink_to_fit();

        // Element access
        reference front() {return *begin();}
        const_reference front() const {return *begin();}
        reference back() {return *(end()-1);}
        const_reference back() const {return *(end()-1);}
        reference operator[](size_type n);
        const_reference operator[](size_type n) const;
        reference at(size_type n);
        const_reference at(size_type n) const;
        value_type* data() noexcept;
        const value_type* data() const noexcept;

        // Modifiers
        template <class _InputIterator>
        void assign(_InputIterator first, _InputIterator last);
        void assign(size_type n, const value_type &val);
        // TODO void assign(initializer_list<value_type> il);

        void push_back(value_type &val);
        void push_back(const value_type &val);
        void pop_back();

        iterator insert(iterator position, const value_type &val);
        iterator insert(iterator position, size_type n, const value_type &val);
        template <class _InputIterator>
        iterator insert(iterator position, _InputIterator first, _InputIterator last);
        //TODO iterator insert(iterator position, value_type &&val);
        //TODO iterator insert(iterator position, initializer_list<value_type> il);
        
        iterator erase(iterator position);
        iterator erase(iterator first, iterator last);
        
        void swap(vector<_Tp,_Alloc>& x);
        
        void clear() noexcept;
        
        template <class... Args>
        iterator emplace(const_iterator position, Args&&... args);
        
        template <class... Args>
        void emplace_back(Args&&... args);

        // Allocator
        // get_allocator
        allocator_type get_allocator() const noexcept {return _M_allocator;}
    };

    template <class _Tp, class _Alloc>
    vector<_Tp, _Alloc>::vector(const allocator_type& __alloc)
        : _M_start(0), _M_finish(0), _M_end_of_storage(0), _M_allocator(__alloc) {}

    template <class _Tp, class _Alloc>
    vector<_Tp, _Alloc>::vector(size_type __n)
        : _M_start(0), _M_finish(0), _M_end_of_storage(0), _M_allocator(allocator_type())
    {
        _M_start=_M_allocate(__n); 
        _M_finish=_M_start;
        _M_end_of_storage=_M_start+__n;
        _M_finish = davis::uninitialized_fill_n(_M_start,__n, _Tp());
    }
    template <class _Tp, class _Alloc>
    vector<_Tp, _Alloc>::vector(size_type __n, const value_type& __val,
                                const allocator_type& __alloc)
        : _M_start(0), _M_finish(0), _M_end_of_storage(0), _M_allocator(__alloc)
    {
        _M_start = _M_allocate(__n);
        _M_finish = _M_start;
        _M_end_of_storage = _M_start + __n;
        _M_finish =davis::uninitialized_fill_n(_M_start, __n, __val);
    }
    template <class _Tp, class _Alloc>
    template <class _InputIterator>
    vector<_Tp, _Alloc>::vector(_InputIterator first, _InputIterator last,
                                const allocator_type &alloc )
        : _M_start(0), _M_finish(0), _M_end_of_storage(0), _M_allocator(alloc)
    {
        typedef typename _Is_integer<_InputIterator>::_Integral _Integral;
        _M_initialize_aux(first, last, _Integral());
    }
    template <class _Tp, class _Alloc>
    vector<_Tp, _Alloc>::vector(const vector &x)
        : _M_start(0), _M_finish(0), _M_end_of_storage(0), _M_allocator(x.get_allocator())
    {
        _M_start = _M_allocate(x.size());
        _M_finish = _M_start;
        _M_end_of_storage = _M_start + x.size();
        _M_finish = std::uninitialized_copy(x.begin(), x.end(), _M_start);
    }
    template <class _Tp, class _Alloc>
    vector<_Tp, _Alloc>::vector(const vector &x, const allocator_type &alloc)
        : _M_start(0), _M_finish(0), _M_end_of_storage(0), _M_allocator(alloc)
    {
        _M_start = _M_allocate(x.size());
        _M_finish = _M_start;
        _M_end_of_storage = _M_start + x.size();
        _M_finish = std::uninitialized_copy(x.begin(), x.end(), _M_start);
    }
    template <class _Tp, class _Alloc>
    vector<_Tp,_Alloc>::~vector()
    {
        davis::destroy(_M_start,_M_finish);
    }

    template <class _Tp, class _Alloc>
    vector<_Tp,_Alloc>& 
        vector<_Tp,_Alloc>::operator=(const vector<_Tp,_Alloc>& __x)
    {
        if (&__x != this)
        {
            const size_type __xlen = __x.size();
            if (__xlen > capacity())
            {
                iterator __tmp = _M_allocate_and_copy(__xlen, __x.begin(), __x.end());
                davis::destroy(_M_start, _M_finish);
                _M_deallocate(_M_start, _M_end_of_storage - _M_start);
                _M_start = __tmp;
                _M_end_of_storage = _M_start + __xlen;
            }
            else if (size() >= __xlen)
            {
                // TODO std::copy 
                iterator __i = std::copy(__x.begin(), __x.end(), begin());
                davis::destroy(__i, _M_finish);
            }
            else
            {
                // TODO std::copy
                std::copy(__x.begin(), __x.begin() + size(), _M_start);
                std::uninitialized_copy(__x.begin() + size(), __x.end(), _M_finish);
            }
            _M_finish = _M_start + __xlen;
        }
        return *this;
    }
    template <class _Tp, class _Alloc>
    void vector<_Tp, _Alloc>::resize(size_type new_size)
    {
        resize(new_size, _Tp());
    }
    template <class _Tp, class _Alloc>
    void vector<_Tp, _Alloc>::resize(size_type new_size, const value_type &val)
    {
        if (new_size<size())
        {
            erase(begin()+new_size,end());
        }
        else
        {
            insert(end(),new_size-size(),val);
        }
    }
    template <class _Tp, class _Alloc>
    void vector<_Tp, _Alloc>::reserve(size_type n)
    {
        if(capacity()<n)
        {
            const size_type old_size = size();
            iterator tmp = _M_allocate_and_copy(n, _M_start, _M_finish);
            davis::destroy(_M_start, _M_finish);
            _M_deallocate(_M_start, _M_end_of_storage - _M_start);
            _M_start = tmp;
            _M_finish = _M_start + old_size;
            _M_end_of_storage = _M_start + n;
        }
    }
    template <class _Tp, class _Alloc>
    void vector<_Tp, _Alloc>::shrink_to_fit()
    {
        if(capacity()>size())
        {
            const size_type old_size = size();
            iterator tmp = _M_allocate_and_copy(old_size, _M_start, _M_finish);
            davis::destroy(_M_start, _M_finish);
            _M_deallocate(_M_start, _M_end_of_storage - _M_start);
            _M_start = tmp;
            _M_finish = _M_start + old_size;
            _M_end_of_storage = _M_finish;
        }
    }
    template <class _Tp, class _Alloc>
    typename vector<_Tp, _Alloc>::reference 
        vector<_Tp, _Alloc>::operator[](size_type n)
    {
        return *(begin() + n);
    }
    template <class _Tp, class _Alloc>
    typename vector<_Tp, _Alloc>::const_reference 
        vector<_Tp, _Alloc>::operator[](size_type n) const
    {
        return *(begin() + n);
    }
    template <class _Tp, class _Alloc>
    typename vector<_Tp, _Alloc>::reference 
        vector<_Tp, _Alloc>::at(size_type n)
    {
        _M_range_check(n);
        return (*this)[n];
    }
    template <class _Tp, class _Alloc>
    typename vector<_Tp, _Alloc>::const_reference 
        vector<_Tp, _Alloc>::at(size_type n) const
    {
        _M_range_check(n);
        return (*this)[n];
    }
    template <class _Tp, class _Alloc>
    typename vector<_Tp, _Alloc>::value_type *
        vector<_Tp, _Alloc>::data() noexcept
    {
        return static_cast<value_type*>(begin());
    }
    template <class _Tp, class _Alloc>
    const typename vector<_Tp, _Alloc>::value_type *
        vector<_Tp, _Alloc>::data() const noexcept
    {
        return static_cast<value_type *>(begin());
    }
    template <class _Tp, class _Alloc>
    template <class _InputIterator>
    void vector<_Tp, _Alloc>::assign(_InputIterator first, _InputIterator last)
    {
        typedef typename _Is_integer<_InputIterator>::_Integral _Integral;
        _M_assign_dispatch(first, last, _Integral());
    }
    template <class _Tp, class _Alloc>
    void vector<_Tp, _Alloc>::assign(size_type n, const value_type& val)
    {
        _M_fill_assign(n, val);
    }
    template <class _Tp, class _Alloc>
    void vector<_Tp, _Alloc>::push_back(value_type &val)
    {
        if (_M_finish != _M_end_of_storage)
        {
            davis::construct(_M_finish, val);
            ++_M_finish;
        }
        else
        {
            _M_insert_aux(_M_finish, val);
        }
    }
    template <class _Tp, class _Alloc>
    void vector<_Tp, _Alloc>::push_back(const value_type &val)
    {
        if (_M_finish != _M_end_of_storage)
        {
            davis::construct(_M_finish, val);
            ++_M_finish;
        }
        else
        {
            _M_insert_aux(_M_finish, val);
        }
    }
    template <class _Tp, class _Alloc>
    void vector<_Tp, _Alloc>::pop_back()
    {
        --_M_finish;
        davis::destroy(_M_finish);
    }
    template <class _Tp, class _Alloc>
    typename vector<_Tp, _Alloc>::iterator 
        vector<_Tp, _Alloc>::insert(iterator position, const value_type &val)
    {
        size_type n = position - begin();
        if (_M_finish != _M_end_of_storage && position == end())
        {
            davis::construct(_M_finish, val);
            ++_M_finish;
        }
        else
        {
            _M_insert_aux(position, val);
        }
        return begin() + n;
    }
    template <class _Tp, class _Alloc>
    typename vector<_Tp, _Alloc>::iterator 
        vector<_Tp, _Alloc>::insert(iterator __position, size_type __n, const value_type& __val)
    {
        _M_fill_insert(__position,__n,__val);
        return __position;
    }
    template <class _Tp, class _Alloc>
    template <class _InputIterator>
    typename vector<_Tp, _Alloc>::iterator 
        vector<_Tp, _Alloc>::insert(iterator position, _InputIterator first, _InputIterator last)
    {
        typedef typename davis::_Is_integer<_InputIterator>::_Integral _Integral;
        _M_insert_dispatch(position, first, last, _Integral());
        return position;
    }
    // TODO
    // template <class _Tp, class _Alloc>
    // typename vector<_Tp, _Alloc>::iterator
    //     vector<_Tp, _Alloc>::insert(iterator position, value_type&& val)
    // {
    //
    // }
    template <class _Tp, class _Alloc>
    void vector<_Tp, _Alloc>::swap(vector<_Tp,_Alloc> &x)
    {
        //TODO std::swap
        std::swap(_M_start,x._M_start);
        std::swap(_M_finish, x._M_finish);
        std::swap(_M_end_of_storage, x._M_end_of_storage);
    }
    template <class _Tp, class _Alloc>
    void vector<_Tp, _Alloc>::clear() noexcept
    {
        erase(begin(),end());
    }
    template <class _Tp, class _Alloc>
    template <class... Args>
    typename vector<_Tp, _Alloc>::iterator
        vector<_Tp, _Alloc>::emplace(const_iterator position, Args &&...args)
    {
        // TODO
    }
    template <class _Tp, class _Alloc>
    template <class... Args>
    void vector<_Tp, _Alloc>::emplace_back(Args &&...args)
    {
        // TODO
    }
    template <class _Tp, class _Alloc>
    template <class _ForwardIterator>
    typename vector<_Tp, _Alloc>::iterator
        vector<_Tp, _Alloc>::_M_allocate_and_copy(size_type n, _ForwardIterator fisrt, _ForwardIterator last)
    {
        iterator result = _M_allocate(n);
        try
        {
            davis::uninitialized_copy(fisrt,last,result);
            return result;
        }
        catch(...)
        {
            _M_deallocate(result, n);
        }
        return result;
    }
    template <class _Tp, class _Alloc>
    void vector<_Tp, _Alloc>::_M_range_check(size_type n) const
    {
        if(n>=this->size())
        {
            std::range_error("vector");
        }
    }
    template <class _Tp, class _Alloc>
    void vector<_Tp, _Alloc>::_M_fill_assign(size_type n, const value_type &val)
    {
        if (n > capacity())
        {
            vector<_Tp, _Alloc> tmp(n,val, get_allocator());
            tmp.swap(*this);
        }
        else if (n > size())
        {
            //TODO std::fill
            std::fill(begin(), end(), val);
            
            _M_finish = davis::uninitialized_fill_n(_M_finish, n - size(), val);
        }
        else
            //TODO std::fill_n
            erase(std::fill_n(begin(), n, val), end());
    }
    template <class _Tp, class _Alloc>
    template <class _InputIterator>
    void vector<_Tp, _Alloc>::_M_assign_aux(_InputIterator first, _InputIterator last,
                                            davis::input_iterator_tag)
    {
        iterator cur=begin();
        for(;first!=last&&cur!=end();++first,++cur)
        {
            *cur=*first;
        }
        if(first==last)
        {
            erase(cur,end());
        }
        else
        {
            insert(end(),first,last);
        }
    }
    template <class _Tp, class _Alloc>
    template <class _ForwardIterator>
    void vector<_Tp, _Alloc>::_M_assign_aux(_ForwardIterator first, _ForwardIterator last,
                                            davis::forward_iterator_tag)
    {
        size_type len = distance(first,last);

        if (len > capacity())
        {
            iterator tmp = _M_allocate_and_copy(len, first, last);
            destroy(_M_start, _M_finish);
            _M_deallocate(_M_start, _M_end_of_storage - _M_start);
            _M_start = tmp;
            _M_end_of_storage = _M_finish = _M_start + len;
        }
        else if (size() >= len)
        {
            // TODO std::destroy
            iterator new_finish = std::copy(first, last, _M_start);
            davis::destroy(new_finish, _M_finish);
            _M_finish = new_finish;
        }
        else
        {
            _ForwardIterator mid = first;
            // TODO std::advance
            std::advance(mid, size());
            // TODO std::copy
            std::copy(first, mid, _M_start);
            _M_finish = uninitialized_copy(mid, last, _M_finish);
        }
    }
    template <class _Tp, class _Alloc>
    void vector<_Tp, _Alloc>::_M_insert_aux(iterator position, const _Tp &x)
    {
        if (_M_finish != _M_end_of_storage)
        {
            davis::construct(_M_finish, *(_M_finish - 1));
            ++_M_finish;
            _Tp x_copy = x;
            //TODO std::copy_backward
            std::copy_backward(position, _M_finish - 2, _M_finish - 1);
            *position = x_copy;
        }
        else
        { // 没有备用空间
            const size_type old_size = size();
            const size_type len = old_size != 0 ? 2 * old_size : 1;
            iterator new_start = _M_allocate(len);
            iterator new_finish = new_start;
            try
            {
                new_finish = davis::uninitialized_copy(_M_start, position, new_start);
                davis::construct(new_finish, x);
                ++new_finish;
                new_finish = davis::uninitialized_copy(position, _M_finish, new_finish);
            }
            catch(...){
                
                davis::destroy(new_start, new_finish);
                _M_deallocate(new_start, len);
            }
            
            davis::destroy(begin(), end());
            _M_deallocate(_M_start, _M_end_of_storage - _M_start);
            _M_start = new_start;
            _M_finish = new_finish;
            _M_end_of_storage = new_start + len;
        }
    }
    template <class _Tp, class _Alloc>
    void vector<_Tp, _Alloc>::_M_insert_aux(iterator position)
    {
        _M_insert_aux(position,_Tp());
    }
    template <class _Tp, class _Alloc>
    void vector<_Tp, _Alloc>::_M_fill_insert(iterator position, size_type n, const _Tp &x)
    {
        if (n != 0)
        {
            if (size_type(_M_end_of_storage - _M_finish) >= n)
            {
                _Tp x_copy = x;
                const size_type elems_after = _M_finish - position;
                iterator old_finish = _M_finish;
                if (elems_after > n)
                {
                    davis::uninitialized_copy(_M_finish - n, _M_finish, _M_finish);
                    _M_finish += n;   
                    //TODO std::copy_backward
                    std::copy_backward(position, old_finish - n, old_finish); 
                    std::fill(position, position + n, x_copy); 
                }
                else
                {
                    davis::uninitialized_fill_n(_M_finish, n - elems_after, x_copy);
                    _M_finish += n - elems_after;
                    davis::uninitialized_copy(position, old_finish, _M_finish); 
                    _M_finish += elems_after;
                    //TODO std::fill
                    std::fill(position, old_finish, x_copy); // 填充
                }
            }
            else
            {
                const size_type old_size = size();
                const size_type len = old_size + std::max(old_size, n);
                iterator new_start = _M_allocate(len);
                iterator new_finish = new_start;
                try
                {
                    new_finish = davis::uninitialized_copy(_M_start, position, new_start); 
                    new_finish = davis::uninitialized_fill_n(new_finish, n, x);
                    new_finish = davis::uninitialized_copy(position, _M_finish, new_finish);
                }
                catch(...)
                {
                    davis::destroy(new_start, new_finish);
                    _M_deallocate(new_start, len);
                }
                davis::destroy(_M_start, _M_finish);
                _M_deallocate(_M_start, _M_end_of_storage - _M_start);
                _M_start = new_start;
                _M_finish = new_finish;
                _M_end_of_storage = new_start + len;
            }
        }
    }
    template <class _Tp, class _Alloc>
    typename vector<_Tp, _Alloc>::iterator 
    vector<_Tp, _Alloc>::erase(iterator __position)
    {
        if (__position + 1 != end())
            std::copy(__position + 1, _M_finish, __position); // 全局函数
        --_M_finish;
        davis::destroy(_M_finish);
        return __position;
    }
    template <class _Tp, class _Alloc>
    typename vector<_Tp, _Alloc>::iterator
    vector<_Tp, _Alloc>::erase(iterator __first, iterator __last)
    {
        iterator __i = std::copy(__last, _M_finish, __first);
        davis::destroy(__i, _M_finish);
        _M_finish = _M_finish - (__last - __first);
        return __first;
    }
    template <class _Tp, class _Alloc>
    template <class _InputIterator>
    void
    vector<_Tp, _Alloc>::_M_range_insert(iterator __pos,
                                         _InputIterator __first,
                                         _InputIterator __last,
                                         davis::input_iterator_tag)
    {
        for (; __first != __last; ++__first)
        {
            __pos = insert(__pos, *__first);
            ++__pos;
        }
    }

    template <class _Tp, class _Alloc>
    template <class _ForwardIterator>
    void
    vector<_Tp, _Alloc>::_M_range_insert(iterator __position,
                                         _ForwardIterator __first,
                                         _ForwardIterator __last,
                                         davis::forward_iterator_tag)
    {
        if (__first != __last)
        {
            size_type __n = davis::distance(__first, __last);
            if (size_type(_M_end_of_storage - _M_finish) >= __n)
            {
                const size_type __elems_after = _M_finish - __position;
                iterator __old_finish = _M_finish;
                if (__elems_after > __n)
                {
                    davis::uninitialized_copy(_M_finish - __n, _M_finish, _M_finish);
                    _M_finish += __n;
                    std::copy_backward(__position, __old_finish - __n, __old_finish);
                    std::copy(__first, __last, __position);
                }
                else
                {
                    _ForwardIterator __mid = __first;
                    davis::advance(__mid, __elems_after);
                    davis::uninitialized_copy(__mid, __last, _M_finish);
                    _M_finish += __n - __elems_after;
                    std::uninitialized_copy(__position, __old_finish, _M_finish);
                    _M_finish += __elems_after;
                    std::copy(__first, __mid, __position);
                }
            }
            else
            {
                const size_type __old_size = size();
                const size_type __len = __old_size + std::max(__old_size, __n);
                iterator __new_start = _M_allocate(__len);
                iterator __new_finish = __new_start;
                try
                {
                    __new_finish = std::uninitialized_copy(_M_start, __position, __new_start);
                    __new_finish = std::uninitialized_copy(__first, __last, __new_finish);
                    __new_finish = std::uninitialized_copy(__position, _M_finish, __new_finish);
                }
                catch(...)
                {
                    davis::destroy(__new_start, __new_finish);
                    _M_deallocate(__new_start, __len);
                }

                davis::destroy(_M_start, _M_finish);
                _M_deallocate(_M_start, _M_end_of_storage - _M_start);
                _M_start = __new_start;
                _M_finish = __new_finish;
                _M_end_of_storage = __new_start + __len;
            }
        }
    }
    // Non-member function overloads
    // relational operators
    template <class _Tp, class _Alloc>
    inline bool operator==(const vector<_Tp, _Alloc> &lhs, const vector<_Tp, _Alloc> &rhs)
    {
        return lhs.size() == rhs.size() &&
            //TODO algorithm std::equal
            std::equal(lhs.begin(),lhs.end(),rhs.begin());
    }
    template <class _Tp, class _Alloc>
    inline bool operator!=(const vector<_Tp, _Alloc> &lhs, const vector<_Tp, _Alloc> &rhs)
    {
        return !(lhs==rhs);
    }
    template <class _Tp, class _Alloc>
    inline bool operator<(const vector<_Tp, _Alloc> &lhs, const vector<_Tp, _Alloc> &rhs)
    {
        // TODO algorithm std::lexicographical_compare
        return std::lexicographical_compare(lhs.begin(),lhs.end(),
                                        rhs.begin(),rhs.end());
    }
    template <class _Tp, class _Alloc>
    inline bool operator>(const vector<_Tp, _Alloc> &lhs, const vector<_Tp, _Alloc> &rhs)
    {
        return rhs<lhs;
    }
    template <class _Tp, class _Alloc>
    inline bool operator<=(const vector<_Tp, _Alloc> &lhs, const vector<_Tp, _Alloc> &rhs)
    {
        return !(lhs>rhs);
    }
    
    template <class _Tp, class _Alloc>
    inline bool operator>=(const vector<_Tp, _Alloc> &lhs, const vector<_Tp, _Alloc> &rhs)
    {
        return !(lhs<rhs);
    }
    // swap
    template <class _Tp, class _Alloc>
    void swap(vector<_Tp, _Alloc> &x, vector<_Tp, _Alloc> &y)
    {
        x.swap(y);
    }

    // Template specializations
    // TODO vector<bool>
    // template <class _Alloc>
    // class vector<bool, _Alloc>;
} // namespace davis

#endif