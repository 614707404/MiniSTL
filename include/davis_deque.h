#ifndef DAVIS_DEQUE_H
#define DAVIS_DEQUE_H
#include "davis_iterator.h"
#include "davis_type_traits.h"
#include "davis_construct.h"
#include "davis_allocate.h"
#include "davis_uninitialized.h"
namespace davis
{
    inline size_t __deque_buf_size(size_t size)
    {
        return size < 512 ? size_t(512 / size) : size_t(1);
    }
    template <class _Tp, class _Ref, class _Ptr>
    struct deque_iterator
    {
        typedef deque_iterator<_Tp, _Tp &, _Tp *>                                   iterator;
        typedef deque_iterator<_Tp, const _Tp &, const _Tp *>                       const_iterator;

        typedef davis::random_access_iterator_tag                                   iterator_category;
        typedef _Tp                                                                 value_type;
        typedef _Ptr                                                                pointer;
        typedef _Ref                                                                reference;
        typedef size_t                                                              size_type;
        typedef ptrdiff_t                                                           difference_type;
        typedef _Tp **                                                              _Map_pointer;
        typedef deque_iterator                                                      _Self;
        static size_t _S_buffer_size() { return __deque_buf_size(sizeof(_Tp)); }

        _Tp* _M_cur;          
        _Tp* _M_first;        
        _Tp* _M_last;         
        _Map_pointer _M_node;

        deque_iterator(_Tp* x, _Map_pointer y)
            : _M_cur(x), _M_first(*y),
              _M_last(*y + _S_buffer_size()), _M_node(y) {}
        deque_iterator() : _M_cur(0), _M_first(0), _M_last(0), _M_node(0) {}
        deque_iterator(const iterator& x)
            : _M_cur(x._M_cur), _M_first(x._M_first),
              _M_last(x._M_last), _M_node(x._M_node) {}

        reference operator*() const { return *_M_cur; }
        pointer operator->() const { return _M_cur; }

        difference_type operator-(const _Self& x) const
        {
            return difference_type(_S_buffer_size()) * (_M_node - x._M_node - 1) +
                   (_M_cur - _M_first) + (x._M_last - x._M_cur);
        }

        _Self& operator++()
        {
            ++_M_cur; 
            if (_M_cur == _M_last)
            {                            
                _M_set_node(_M_node + 1); 
                _M_cur = _M_first;        
            }
            return *this;
        }
        _Self operator++(int)
        {
            _Self tmp=*this;
            ++*this;
            return tmp;
        }
        _Self& operator--()
        {
            if (_M_cur == _M_first)
            {
                _M_set_node(_M_node - 1);
                _M_cur = _M_last;
            }
            --_M_cur;
            return *this;
        }
        _Self operator--(int)
        {
            _Self tmp = *this;
            --*this;
            return tmp;
        }
        _Self& operator+=(difference_type n)
        {
            difference_type offset = n + (_M_cur - _M_first);
            if (offset >= 0 && offset < difference_type(_S_buffer_size()))
                _M_cur += n; 
            else
            { 
                difference_type node_offset =
                    offset > 0 ? offset / difference_type(_S_buffer_size())
                                 : -difference_type((-offset - 1) / _S_buffer_size()) - 1;
                _M_set_node(_M_node + node_offset); // 切换到正确的节点(缓冲区)
                _M_cur = _M_first +                   // 切换到正确的元素
                         (offset - node_offset * difference_type(_S_buffer_size()));
            }
            return *this;
        }
        _Self operator+(difference_type n) const
        {
            _Self tmp = *this;
            return tmp += n;
        }
        _Self& operator-=(difference_type n) { return *this += -n; }
        _Self operator-(difference_type n) const
        {
            _Self tmp = *this;
            return tmp -= n;
        }
        reference operator[](difference_type n) const { return *(*this + n); }

        bool operator==(const _Self &x) const { return _M_cur == x._M_cur; }
        bool operator!=(const _Self &x) const { return !(*this == x); }
        bool operator<(const _Self &x) const
        {
            return (_M_node == x._M_node) ? (_M_cur < x._M_cur) : (_M_node < x._M_node);
        }
        bool operator>(const _Self &x) const { return x < *this; }
        bool operator<=(const _Self &x) const { return !(x < *this); }
        bool operator>=(const _Self &x) const { return !(*this < x); }
        void _M_set_node(_Map_pointer new_node)
        {
            _M_node = new_node;
            _M_first = *new_node;
            _M_last = _M_first + difference_type(_S_buffer_size());
        }
    };
    // TODO 这个函数是做什么的？
    template <class _Tp, class _Ref, class _Ptr>
    inline deque_iterator<_Tp, _Ref, _Ptr>
    operator+(ptrdiff_t n, const deque_iterator<_Tp, _Ref, _Ptr>& x)
    {
        return x + n;
    }
    template <class _Tp, class _Ref, class _Ptr>
    inline davis::random_access_iterator_tag
    iterator_category(const deque_iterator<_Tp, _Ref, _Ptr> &)
    {
        return davis::random_access_iterator_tag();
    }

    template <class _Tp, class _Ref, class _Ptr>
    inline _Tp* value_type(const deque_iterator<_Tp, _Ref, _Ptr> &) { return 0; }

    template <class _Tp, class _Ref, class _Ptr>
    inline ptrdiff_t* distance_type(const deque_iterator<_Tp, _Ref, _Ptr> &)
    {
        return 0;
    }

    template <class _Tp, class _Alloc = davis::allocator<_Tp>>
    class deque
    {
    // Member types
    public:
        typedef _Tp                                                 value_type;
        typedef _Alloc                                              allocator_type;
        typedef value_type &                                        reference;
        typedef const value_type &                                  const_reference;
        typedef value_type *                                        pointer;
        typedef const value_type *                                  const_pointer;
        typedef deque_iterator<_Tp, _Tp &, _Tp *>                   iterator;
        typedef deque_iterator<_Tp, const _Tp &, const _Tp *>       const_iterator;
        // TODO reverse_itrator
        // typedef reverse_iterator<iterator>                       reverse_iterator;
        // typedef reverse_iterator<const_iterator>                 const_reverse_iterator;
        typedef size_t                                              size_type;
        typedef ptrdiff_t                                           difference_type;
    protected:
        typedef pointer*                                            _Map_pointer;
        static size_t _S_buffer_size() { return __deque_buf_size(sizeof(_Tp)); }
        // Data
    protected:
        iterator _M_start;
        iterator _M_finish;
        _Map_pointer _M_map;
        size_t _M_map_size;
        allocator_type _M_allocator;
        davis::allocator<_Tp*> _M_map_allocator;
        // Member functions
    protected:
        enum {  _S_initial_map_size = 8 };
        pointer _M_allocate_node(){ return _M_allocator.allocate(__deque_buf_size(sizeof(_Tp)));}
        void _M_deallocate_node(pointer p) { _M_allocator.deallocate(p, __deque_buf_size(sizeof(_Tp)));}

        _Map_pointer _M_allocate_map(size_type n) { return _M_map_allocator.allocate(n); }
        void _M_deallocate_map(_Map_pointer p, size_type n) { _M_map_allocator.deallocate(p, n); }

        void _M_initialize_map(size_type);
        void _M_create_nodes(_Map_pointer nstart, _Map_pointer nfinish);
        void _M_destroy_nodes(_Map_pointer nstart, _Map_pointer nfinish);
        void _M_range_check(size_type n) const ;
        void _M_fill_initialize(const value_type &value);
        template <class _Integer>
        void _M_initialize_dispatch(_Integer n, _Integer x, davis::__true_type);
        template <class _Integer>
        void _M_initialize_dispatch(_Integer n, _Integer x, davis::__false_type);
        void _M_fill_assign(size_type n, const _Tp &val);
        template <class _Integer>
        void _M_assign_dispatch(_Integer n, _Integer val, davis::__true_type);
        template <class _InputIterator>
        void _M_assign_dispatch(_InputIterator first, _InputIterator last, davis::__false_type);
        template <class _InputIterator>
        void _M_assign_aux(_InputIterator first, _InputIterator last,davis::input_iterator_tag);
        template <class _ForwardIterator>
        void _M_assign_aux(_ForwardIterator first, _ForwardIterator last,davis::forward_iterator_tag);
        void _M_push_back_aux(const value_type &);
        void _M_push_back_aux();
        void _M_push_front_aux(const value_type &);
        void _M_push_front_aux();
        void _M_pop_back_aux();
        void _M_pop_front_aux();
        iterator _M_insert_aux(iterator pos, const value_type &x);
        iterator _M_insert_aux(iterator pos);
        void _M_insert_aux(iterator pos, size_type n, const value_type &x);
        template <class _ForwardIterator>
        void _M_insert_aux(iterator __pos,
                           _ForwardIterator __first,
                           _ForwardIterator __last,
                           size_type __n);
        template <class _Integer>
        void _M_insert_dispatch(iterator pos, _Integer n, _Integer x,
                                davis::__true_type);
        template <class _InputIterator>
        void _M_insert_dispatch(iterator pos,
                                _InputIterator first, _InputIterator last,
                                davis::__false_type);
        template <class _InputIterator>
        void _M_range_initialize(_InputIterator first, _InputIterator last,
                                 davis::input_iterator_tag);

        template <class _ForwardIterator>
        void _M_range_initialize(_ForwardIterator first, _ForwardIterator last,
                                 davis::forward_iterator_tag);
        void _M_reserve_map_at_back(size_type nodes_to_add = 1)
        {
            if (nodes_to_add + 1 > _M_map_size - (_M_finish._M_node - _M_map))
                _M_reallocate_map(nodes_to_add, false);
        }

        void _M_reserve_map_at_front(size_type nodes_to_add = 1)
        {
            if (nodes_to_add > size_type(_M_start._M_node - _M_map))
                _M_reallocate_map(nodes_to_add, true);
        }
        void _M_new_elements_at_front(size_type new_elements);
        void _M_new_elements_at_back(size_type new_elements);
        void _M_reallocate_map(size_type nodes_to_add, bool add_at_front);
        iterator _M_reserve_elements_at_front(size_type n);

        iterator _M_reserve_elements_at_back(size_type n);
        void _M_fill_insert(iterator pos, size_type n, const value_type &x);

    public:
        explicit deque(const allocator_type& alloc = allocator_type());
        explicit deque(size_type n);
        deque(size_type n, const value_type& val,const allocator_type& alloc = allocator_type());
        template <class _InputIterator>
        deque(_InputIterator first, _InputIterator last,const allocator_type& alloc = allocator_type());
        deque(const deque& x);
        deque(const deque& x, const allocator_type& alloc);
    
        ~deque();
        deque& operator=(deque &x);
        
        // Iterators
        iterator begin() noexcept { return _M_start; }
        const_iterator begin() const noexcept { return _M_start; }
        iterator end() noexcept { return _M_finish; }
        const_iterator end() const noexcept { return _M_finish; }
        const_iterator cbegin() const noexcept { return _M_start; }
        const_iterator cend() const noexcept { return _M_finish; }
       

        // Capacity
        size_type size() const noexcept  { return _M_finish - _M_start; }
        size_type max_size() const noexcept { return static_cast<size_type>(-1); }
        bool empty() const noexcept { return _M_start == _M_finish; }
        void resize(size_type n);
        void resize(size_type n, const value_type& val);
        
        void shrink_to_fit();

        // Element access
        reference operator[](size_type n) { return _M_start[difference_type(n)]; }
        const_reference operator[](size_type n) const { return _M_start[difference_type(n)]; }
        reference at(size_type n) { _M_range_check(n); return (*this)[difference_type(n)]; }
        const_reference at(size_type n) const { _M_range_check(n); return (*this)[difference_type(n)]; }
        reference front() { return *begin(); }
        const_reference front() const { return *begin(); }
        reference back() { return *(end()-1); }
        const_reference back() const { return *(end()-1); }

        // Modifiers
        template <class _InputIterator>
        void assign(_InputIterator first, _InputIterator last);
        void assign(size_type n, const value_type& val);
        void push_back(const value_type& val);
        void push_front(const value_type& val);
        void pop_back();
        void pop_front();
        iterator insert(iterator position, const value_type& val);
        iterator insert(iterator position, size_type n, const value_type& val);
        template <class _InputIterator>
        iterator insert(iterator position, _InputIterator first, _InputIterator last);
        template <class _InputIterator>
        void insert(iterator __pos, _InputIterator __first, _InputIterator __last,
                    input_iterator_tag);

        template <class _ForwardIterator>
        void insert(iterator __pos,
                    _ForwardIterator __first, _ForwardIterator __last,
                    forward_iterator_tag);
        iterator erase(iterator position);
        iterator erase(iterator first, iterator last);
        void swap(deque& x);
        void clear() noexcept;

        // Allocator
        allocator_type get_allocator() const noexcept { return _M_allocator; }

        // TODO reverse_iterator
        // reverse_iterator rbegin() noexcept;
        // const_reverse_iterator rbegin() const noexcept;
        // reverse_iterator rend() noexcept;
        // const_reverse_iterator rend() const noexcept;
        // const_reverse_iterator crbegin() const noexcept;
        // const_reverse_iterator crend() const noexcept;
        // TODO &&
        // deque(deque &&x);
        // deque(deque &&x, const allocator_type &alloc);
        // deque &operator=(deque &&x);
        // template <class... _Args>
        // iterator emplace(const_iterator position, _Args &&...args);
        // template <class... _Args>
        // void emplace_front(_Args &&...args);
        // template <class... _Args>
        // void emplace_back(_Args &&...args);
        // iterator insert(const_iterator position, value_type &&val);
        // void push_front(value_type &&val);
        // void push_back(value_type &&val);
        // TODO initializer_list
        // deque(initializer_list<value_type> il, const allocator_type &alloc = allocator_type());
        // deque &operator=(initializer_list<value_type> il);
        // iterator insert(const_iterator position, initializer_list<value_type> il);
        // void assign(initializer_list<value_type> il);
    };

    template <class _Tp, class _Alloc>
    deque<_Tp, _Alloc>::deque(const allocator_type &alloc) 
        : _M_map(0), _M_map_size(0), _M_start(), _M_finish(), _M_allocator(alloc)
    {
        _M_initialize_map(0);
    }
    template <class _Tp, class _Alloc>
    deque<_Tp, _Alloc>::deque(size_type n)
        : _M_map(0), _M_map_size(0), _M_start(), _M_finish(), _M_allocator(allocator_type())
    {
        _M_initialize_map(n);
        _M_fill_initialize(value_type());
    }
    template <class _Tp, class _Alloc>
    deque<_Tp, _Alloc>::deque(size_type __n, const value_type &__val, const allocator_type &__alloc)
        : _M_map(0), _M_map_size(0), _M_start(), _M_finish(), _M_allocator(__alloc)
    {
        _M_initialize_map(__n);
        _M_fill_initialize(__val);
    }
    template <class _Tp, class _Alloc>
    template <class _InputIterator>
    deque<_Tp, _Alloc>::deque(_InputIterator first, _InputIterator last, const allocator_type &alloc)
        : _M_map(0), _M_map_size(0), _M_start(), _M_finish(), _M_allocator(alloc)
    {
        typedef typename davis::_Is_integer<_InputIterator>::_Integral _Integral;
        _M_initialize_dispatch(first, last, _Integral());
    }
    template <class _Tp, class _Alloc>
    deque<_Tp, _Alloc>::deque(const deque& x)
        : _M_map(0), _M_map_size(0), _M_start(), _M_finish(), _M_allocator(x.get_allocator())
    {
        _M_initialize_map(x.size());
        davis::uninitialized_copy(x.begin(), x.end(), _M_start);
    }
    template <class _Tp, class _Alloc>
    deque<_Tp, _Alloc>::deque(const deque& x, const allocator_type& alloc)
        : _M_map(0), _M_map_size(0), _M_start(), _M_finish(), _M_allocator(alloc)
    {
        _M_initialize_map(x.size());
        davis::uninitialized_copy(x.begin(), x.end(), _M_start);
    }
    template <class _Tp, class _Alloc>
    deque<_Tp, _Alloc>::~deque()
    {   
        
        davis::destroy(_M_start, _M_finish);
        if (_M_map)
        {
            _M_destroy_nodes(_M_start._M_node, _M_finish._M_node + 1);
            _M_deallocate_map(_M_map, _M_map_size);
        }
        
    }
    template <class _Tp, class _Alloc>
    deque<_Tp, _Alloc>&
        deque<_Tp, _Alloc>::operator=(deque<_Tp, _Alloc> &x)
    {
        if(&x!=this)
        {
            size_type len=size();
            if(len>=x.size())
            {
                erase(std::copy(x.begin(),x.end(),_M_start),_M_finish);
            }
            else
            {
                iterator mid = x.begin() + difference_type(len);
                std::copy(x.begin(), mid, _M_start);
                insert(_M_finish, mid, x.end());
            }
        }
        return *this;
    }
    template <class _Tp, class _Alloc>
    void deque<_Tp, _Alloc>::resize(size_type n)
    {
        resize(n,_Tp());
    }
    template <class _Tp, class _Alloc>
    void deque<_Tp, _Alloc>::resize(size_type n, const value_type &val)
    {
        size_type len=size();
        if(len>=n)
        {
            erase(begin()+n,end());
        }
        else
        {
            insert(end(),n-len,val);
        }
    }
    template <class _Tp, class _Alloc>
    void deque<_Tp, _Alloc>::shrink_to_fit()
    {
        // TODO shrink_to_fit
    }

    // Modifiers
    template <class _Tp, class _Alloc>
    template <class _InputIterator>
    void deque<_Tp, _Alloc>::assign(_InputIterator first, _InputIterator last)
    {
        typedef typename davis::_Is_integer<_InputIterator>::_Integral _Integral;
        _M_assign_dispatch(first, last, _Integral());
    }
    template <class _Tp, class _Alloc>
    void deque<_Tp, _Alloc>::assign(size_type n, const value_type &val)
    {
        _M_fill_assign(n, val);
    }
    template <class _Tp, class _Alloc>
    void deque<_Tp, _Alloc>::push_back(const value_type &val)
    {
        if (_M_finish._M_cur != _M_finish._M_last - 1)
        {
            davis::construct(_M_finish._M_cur, val);
            ++_M_finish._M_cur;
        }
        else
            _M_push_back_aux(val);
    }
    template <class _Tp, class _Alloc>
    void deque<_Tp, _Alloc>::push_front(const value_type &val)
    {
        if (_M_start._M_cur != _M_start._M_first)
        {
            davis::construct(_M_start._M_cur - 1,val);
            --_M_start._M_cur;
        }
        else
            _M_push_front_aux(val);
    }
    template <class _Tp, class _Alloc>
    void deque<_Tp, _Alloc>::pop_back()
    {
        if (_M_finish._M_cur != _M_finish._M_first)
        {
            --_M_finish._M_cur;
            davis::destroy(_M_finish._M_cur);
        }
        else
            _M_pop_back_aux();
    }
    template <class _Tp, class _Alloc>
    void deque<_Tp, _Alloc>::pop_front()
    {
        if (_M_start._M_cur != _M_start._M_last - 1)
        {
            davis::destroy(_M_start._M_cur);
            ++_M_start._M_cur;
        }
        else
            _M_pop_front_aux();
    }
    template <class _Tp, class _Alloc>
    typename deque<_Tp, _Alloc>::iterator 
        deque<_Tp, _Alloc>::insert(iterator position, const value_type &val)
    {
        if (position._M_cur == _M_start._M_cur)
        {
            push_front(val);
            return _M_start;
        }
        else if (position._M_cur == _M_finish._M_cur)
        {
            push_back(val);
            iterator tmp = _M_finish;
            --tmp;
            return tmp;
        }
        else
        {
            return _M_insert_aux(position, val);
        }
    }
    template <class _Tp, class _Alloc>
    typename deque<_Tp, _Alloc>::iterator 
        deque<_Tp, _Alloc>::insert(iterator position, size_type n, const value_type &val)
    {
        _M_fill_insert(position, n, val);
        return position;
    }
    template <class _Tp, class _Alloc>
    template <class _InputIterator>
    typename deque<_Tp, _Alloc>::iterator 
        deque<_Tp, _Alloc>::insert(iterator position, _InputIterator first, _InputIterator last)
    {
        typedef typename davis::_Is_integer<_InputIterator>::_Integral _Integral;
        _M_insert_dispatch(position, first, last, _Integral());
        return position;
    }
    template <class _Tp, class _Alloc>
    typename deque<_Tp, _Alloc>::iterator 
        deque<_Tp, _Alloc>::erase(iterator position)
    {
        iterator next = position;
        ++next;
        difference_type index = position - _M_start;
        if (size_type(index) < (this->size() >> 1))
        {
            std::copy_backward(_M_start, position, next);
            pop_front();
        }
        else
        {
            std::copy(next, _M_finish, position);
            pop_back();
        }
        return _M_start + index;
    }
    template <class _Tp, class _Alloc>
    typename deque<_Tp, _Alloc>::iterator 
        deque<_Tp, _Alloc>::erase(iterator first, iterator last)
    {
        if (first == _M_start && last == _M_finish)
        {
            clear();
            return _M_finish;
        }
        else
        {
            difference_type n = last - first;
            difference_type elems_before = first - _M_start;
            if (elems_before < difference_type((this->size() - n) / 2))
            {
                std::copy_backward(_M_start, first, last);
                iterator new_start = _M_start + n;
                davis::destroy(_M_start, new_start);
                _M_destroy_nodes(new_start._M_node, _M_start._M_node);
                _M_start = new_start;
            }
            else
            {
                std::copy(last, _M_finish, first);
                iterator new_finish = _M_finish - n;
                davis::destroy(new_finish, _M_finish);
                _M_destroy_nodes(new_finish._M_node + 1, _M_finish._M_node + 1);
                _M_finish = new_finish;
            }
            return _M_start + elems_before;
        }
    }
    template <class _Tp, class _Alloc>
    void deque<_Tp, _Alloc>::swap(deque &x)
    {
        //TODO std::swap
        std::swap(_M_start, x._M_start);
        std::swap(_M_finish, x._M_finish);
        std::swap(_M_map, x._M_map);
        std::swap(_M_map_size, x._M_map_size);
    }
    template <class _Tp, class _Alloc>
    void deque<_Tp, _Alloc>::clear() noexcept
    {
        for (_Map_pointer node = _M_start._M_node + 1;
             node < _M_finish._M_node;
             ++node)
        {
            davis::destroy(*node, *node + _S_buffer_size());
            _M_deallocate_node(*node);
        }

        if (_M_start._M_node != _M_finish._M_node)
        {
            davis::destroy(_M_start._M_cur, _M_start._M_last);
            davis::destroy(_M_finish._M_first, _M_finish._M_cur);
            _M_deallocate_node(_M_finish._M_first);
        }
        else
            davis::destroy(_M_start._M_cur, _M_finish._M_cur);

        _M_finish = _M_start;
    }
    template <class _Tp, class _Alloc> // int
    void deque<_Tp, _Alloc>::_M_initialize_map(size_type num_elements) //500 
    {
        size_type num_nodes = num_elements / __deque_buf_size(sizeof(_Tp)) + 1; //4
        _M_map_size = std::max((size_type)_S_initial_map_size, num_nodes + 2); //8
        _M_map = _M_allocate_map(_M_map_size); 

        _Tp** nstart = _M_map + (_M_map_size - num_nodes) / 2; //0+2
        _Tp** nfinish = nstart + num_nodes; // 2 + 4 

        try
        {
            _M_create_nodes(nstart, nfinish);
        }
        catch(...)
        {
            _M_deallocate_map(_M_map, _M_map_size);
            _M_map = 0;
            _M_map_size = 0;
        }
        _M_start._M_set_node(nstart);
        _M_finish._M_set_node(nfinish - 1);
        _M_start._M_cur = _M_start._M_first;
        _M_finish._M_cur = _M_finish._M_first + num_elements % __deque_buf_size(sizeof(_Tp));
    }
    template <class _Tp, class _Alloc>
    void deque<_Tp, _Alloc>::_M_create_nodes(_Map_pointer nstart, _Map_pointer nfinish)
    {
        _Tp** cur;
        try
        {
            for (cur = nstart; cur < nfinish; ++cur)
                *cur = _M_allocate_node();
        }
        catch(...)
        {
            _M_destroy_nodes(nstart, cur);
        }
    }
    template <class _Tp, class _Alloc>
    void deque<_Tp, _Alloc>::_M_destroy_nodes(_Map_pointer nstart, _Map_pointer nfinish)
    {
        for (_Tp **n = nstart; n < nfinish; ++n)
            _M_deallocate_node(*n);
    }
    template <class _Tp, class _Alloc>
    void deque<_Tp, _Alloc>::_M_range_check(size_type n) const
    {
        if (n >= this->size())
            std::range_error("deque");
    }
    template <class _Tp, class _Alloc>
    void deque<_Tp, _Alloc>::_M_fill_initialize(const value_type& value)
    {
        _Map_pointer cur;
        try
        {
            for (cur = _M_start._M_node; cur < _M_finish._M_node; ++cur)
                davis::uninitialized_fill(*cur, *cur + _S_buffer_size(), value);
            davis::uninitialized_fill(_M_finish._M_first, _M_finish._M_cur, value);
        }
        catch(...)
        {
            davis::destroy(_M_start, iterator(*cur, cur));
        }
    }
    template <class _Tp, class _Alloc>
    template <class _Integer>
    void deque<_Tp, _Alloc>::_M_initialize_dispatch(_Integer n, _Integer x, davis::__true_type)
    {
        _M_initialize_map(n);
        _M_fill_initialize(x);
    }
    template <class _Tp, class _Alloc>
    template <class _Integer>
    void deque<_Tp, _Alloc>::_M_initialize_dispatch(_Integer first, _Integer last, davis::__false_type)
    {
        _M_range_initialize(first, last, davis::iterator_category(first));
    }
    template <class _Tp, class _Alloc>
    void deque<_Tp, _Alloc>::_M_fill_assign(size_type n, const _Tp & val)
    {
        if (n > size())
        {
            //TODO std::fill
            std::fill(begin(), end(), val);
            insert(end(), n - size(), val);
        }
        else
        {
            erase(begin() + n, end());
            std::fill(begin(), end(), val);
        }
    }
    template <class _Tp, class _Alloc>
    template <class _Integer>
    void deque<_Tp, _Alloc>::_M_assign_dispatch(_Integer n, _Integer val, davis::__true_type)
    {
        _M_fill_assign((size_type)n, (_Tp)val);
    }
    template <class _Tp, class _Alloc>
    template <class _InputIterator>
    void deque<_Tp, _Alloc>::_M_assign_dispatch(_InputIterator first, _InputIterator last, davis::__false_type)
    {
        _M_assign_aux(first, last, davis::iterator_category(first));
    }
    template <class _Tp, class _Alloc>
    template <class _InputIterator>
    void deque<_Tp, _Alloc>::_M_assign_aux(_InputIterator first, _InputIterator last, davis::input_iterator_tag)
    {
        iterator cur = begin();
        for (; first != last && cur != end(); ++cur, ++first)
            *cur = *first;
        if (first == last)
            erase(cur, end());
        else
            insert(end(), first, last);
    }
    template <class _Tp, class _Alloc>
    template <class _ForwardIterator>
    void deque<_Tp, _Alloc>::_M_assign_aux(_ForwardIterator first, _ForwardIterator last, davis::forward_iterator_tag)
    {
        size_type len = davis::distance(first, last);
        if (len > size())
        {
            _ForwardIterator mid = first;
            davis::advance(mid, size());
            //TODO std::copy
            std::copy(first, mid, begin());
            insert(end(), mid, last);
        }
        else
            erase(std::copy(first, last, begin()), end());
    }
    template <class _Tp, class _Alloc>
    void deque<_Tp, _Alloc>::_M_push_back_aux(const value_type & val)
    {
        value_type v_copy = val;
        _M_reserve_map_at_back();
        *(_M_finish._M_node + 1) = _M_allocate_node();
        try
        {
            davis::construct(_M_finish._M_cur, v_copy);
            _M_finish._M_set_node(_M_finish._M_node + 1);
            _M_finish._M_cur = _M_finish._M_first;
        }
        catch(...){
            _M_deallocate_node(*(_M_finish._M_node + 1));
        }
    }
    template <class _Tp, class _Alloc>
    void deque<_Tp, _Alloc>::_M_push_back_aux()
    {
        _M_push_back_aux(value_type());
    }
    template <class _Tp, class _Alloc>
    void deque<_Tp, _Alloc>::_M_push_front_aux(const value_type & val)
    {
        value_type v_copy = val;
        _M_reserve_map_at_front();
        *(_M_start._M_node - 1) = _M_allocate_node();
        try
        {
            _M_start._M_set_node(_M_start._M_node - 1);
            _M_start._M_cur = _M_start._M_last - 1;
            davis::construct(_M_start._M_cur, v_copy);
        }
        catch(...)
        {
            ++_M_start;
            _M_deallocate_node(*(_M_start._M_node - 1));
        }
    }
    template <class _Tp, class _Alloc>
    void deque<_Tp, _Alloc>::_M_push_front_aux()
    {
        _M_reserve_map_at_front();
        *(_M_start._M_node - 1) = _M_allocate_node();
        try
        {
            _M_start._M_set_node(_M_start._M_node - 1);
            _M_start._M_cur = _M_start._M_last - 1;
            davis::construct(_M_start._M_cur);
        }
        catch (...)
        {
            ++_M_start;
            _M_deallocate_node(*(_M_start._M_node - 1));
        }
    }
    template <class _Tp, class _Alloc>
    void deque<_Tp, _Alloc>::_M_pop_back_aux()
    {
        _M_deallocate_node(_M_finish._M_first);
        _M_finish._M_set_node(_M_finish._M_node - 1);
        _M_finish._M_cur = _M_finish._M_last - 1;
        davis::destroy(_M_finish._M_cur);
    }
    template <class _Tp, class _Alloc>
    void deque<_Tp, _Alloc>::_M_pop_front_aux()
    {
        davis::destroy(_M_start._M_cur);
        _M_deallocate_node(_M_start._M_first);
        _M_start._M_set_node(_M_start._M_node + 1);
        _M_start._M_cur = _M_start._M_first;
    }
    template <class _Tp, class _Alloc>
    typename deque<_Tp, _Alloc>::iterator 
        deque<_Tp, _Alloc>::_M_insert_aux(iterator pos, const value_type &x)
    {
        difference_type index = pos - _M_start;
        value_type x_copy = x;
        if (size_type(index) < this->size() / 2)
        {
            push_front(front());
            iterator front1 = _M_start;
            ++front1;
            iterator front2 = front1;
            ++front2;
            pos = _M_start + index;
            iterator pos1 = pos;
            ++pos1;
            //TODO std::copy
            std::copy(front2, pos1, front1);
        }
        else
        {
            push_back(back());
            iterator back1 = _M_finish;
            --back1;
            iterator back2 = back1;
            --back2;
            pos = _M_start + index;
            std::copy_backward(pos, back2, back1);
        }
        *pos = x_copy;
        return pos;
    }
    template <class _Tp, class _Alloc>
    typename deque<_Tp, _Alloc>::iterator deque<_Tp, _Alloc>::_M_insert_aux(iterator pos)
    {
        difference_type index = pos - _M_start;
        if (index < size() / 2)
        {
            push_front(front());
            iterator front1 = _M_start;
            ++front1;
            iterator front2 = front1;
            ++front2;
            pos = _M_start + index;
            iterator pos1 = pos;
            ++pos1;
            copy(front2, pos1, front1);
        }
        else
        {
            push_back(back());
            iterator back1 = _M_finish;
            --back1;
            iterator back2 = back1;
            --back2;
            pos = _M_start + index;
            copy_backward(pos, back2, back1);
        }
        *pos = value_type();
        return pos;
    }
    //TODO std
    template <class _Tp, class _Alloc>
    void deque<_Tp, _Alloc>::_M_insert_aux(iterator pos, size_type n, const value_type &x)
    {
        const difference_type elems_before = pos - _M_start;
        size_type length = this->size();
        value_type x_copy = x;
        if (elems_before < difference_type(length / 2))
        {
            iterator new_start = _M_reserve_elements_at_front(n);
            iterator old_start = _M_start;
            pos = _M_start + elems_before;
            try
            {
                if (elems_before >= difference_type(n))
                {
                    iterator start_n = _M_start + difference_type(n);
                    std::uninitialized_copy(_M_start, start_n, new_start);
                    _M_start = new_start;
                    std::copy(start_n, pos, old_start);
                    std::fill(pos - difference_type(n), pos, x_copy);
                }
                else
                {
                    davis::__uninitialized_copy_fill(_M_start, pos, new_start,
                                              _M_start, x_copy);
                    _M_start = new_start;
                    std::fill(old_start, pos, x_copy);
                }
            }
            catch(...){
                _M_destroy_nodes(new_start._M_node, _M_start._M_node);
            }
        }
        else
        {
            iterator new_finish = _M_reserve_elements_at_back(n);
            iterator old_finish = _M_finish;
            const difference_type elems_after =
                difference_type(length) - elems_before;
            pos = _M_finish - elems_after;
            try
            {
                if (elems_after > difference_type(n))
                {
                    iterator finish_n = _M_finish - difference_type(n);
                    std::uninitialized_copy(finish_n, _M_finish, _M_finish);
                    _M_finish = new_finish;
                    std::copy_backward(pos, finish_n, old_finish);
                    std::fill(pos, pos + difference_type(n), x_copy);
                }
                else
                {
                    davis::__uninitialized_fill_copy(_M_finish, pos + difference_type(n),
                                              x_copy, pos, _M_finish);
                    _M_finish = new_finish;
                    std::fill(pos, old_finish, x_copy);
                }
            }
            catch(...)
            {
                _M_destroy_nodes(_M_finish._M_node + 1,
                                 new_finish._M_node + 1);
            }
        }
    }
    template <class _Tp, class _Alloc>
    template <class _ForwardIterator>
    void deque<_Tp, _Alloc>::_M_insert_aux(iterator __pos,
                                           _ForwardIterator __first,
                                           _ForwardIterator __last,
                                           size_type __n)
    {
        const difference_type __elemsbefore = __pos - _M_start;
        size_type __length = size();
        if (__elemsbefore < __length / 2)
        {
            iterator __new_start = _M_reserve_elements_at_front(__n);
            iterator __old_start = _M_start;
            __pos = _M_start + __elemsbefore;
            try
            {
                if (__elemsbefore >= difference_type(__n))
                {
                    iterator __start_n = _M_start + difference_type(__n);
                    davis::uninitialized_copy(_M_start, __start_n, __new_start);
                    _M_start = __new_start;
                    std::copy(__start_n, __pos, __old_start);
                    std::copy(__first, __last, __pos - difference_type(__n));
                }
                else
                {
                    _ForwardIterator __mid = __first;
                    davis::advance(__mid, difference_type(__n) - __elemsbefore);
                    __uninitialized_copy_copy(_M_start, __pos, __first, __mid,
                                              __new_start);
                    _M_start = __new_start;
                    std::copy(__mid, __last, __old_start);
                }
            }
            catch(...){
                _M_destroy_nodes(__new_start._M_node, _M_start._M_node);
            }
        }
        else
        {
            iterator __new_finish = _M_reserve_elements_at_back(__n);
            iterator __old_finish = _M_finish;
            const difference_type __elemsafter =
                difference_type(__length) - __elemsbefore;
            __pos = _M_finish - __elemsafter;
            try
            {
                if (__elemsafter > difference_type(__n))
                {
                    iterator __finish_n = _M_finish - difference_type(__n);
                    davis::uninitialized_copy(__finish_n, _M_finish, _M_finish);
                    _M_finish = __new_finish;
                    std::copy_backward(__pos, __finish_n, __old_finish);
                    std::copy(__first, __last, __pos);
                }
                else
                {
                    _ForwardIterator __mid = __first;
                    davis::advance(__mid, __elemsafter);
                    davis::__uninitialized_copy_copy(__mid, __last, __pos, _M_finish, _M_finish);
                    _M_finish = __new_finish;
                    std::copy(__first, __mid, __pos);
                }
            }
            catch(...){
                _M_destroy_nodes(_M_finish._M_node + 1,
                                  __new_finish._M_node + 1);
            }
        }
    }
    template <class _Tp, class _Alloc>
    template <class _Integer>
    void deque<_Tp, _Alloc>::_M_insert_dispatch(iterator pos, _Integer n, _Integer x,
                                                davis::__true_type)
    {
        _M_fill_insert(pos, (size_type)n, (value_type)x);
    }
    template <class _Tp, class _Alloc>
    template <class _InputIterator>
    void deque<_Tp, _Alloc>::_M_insert_dispatch(iterator pos,
                                                _InputIterator first, _InputIterator last,
                                                davis::__false_type)
    {
        insert(pos, first, last, davis::iterator_category(first));
    }
    template <class _Tp, class _Alloc>
    template <class _InputIterator>
    void deque<_Tp, _Alloc>::_M_range_initialize(_InputIterator first, _InputIterator last,
                                                 davis::input_iterator_tag)
    {
        _M_initialize_map(0);
        try
        {
            for (; first != last; ++first)
                push_back(*first);
        }
        catch(...){
            clear();
        }
    }

    template <class _Tp, class _Alloc>
    template <class _ForwardIterator>
    void deque<_Tp, _Alloc>::_M_range_initialize(_ForwardIterator first, _ForwardIterator last,
                                                 davis::forward_iterator_tag)
    {
        size_type n = davis::distance(first, last);
        _M_initialize_map(n);

        _Map_pointer cur_node;
        try
        {
            for (cur_node = _M_start._M_node;
                 cur_node < _M_finish._M_node;
                 ++cur_node)
            {
                _ForwardIterator mid = first;
                advance(mid, _S_buffer_size());
                uninitialized_copy(first, mid, *cur_node);
                first = mid;
            }
            uninitialized_copy(first, last, _M_finish._M_first);
        }
        catch(...)
        {
            destroy(_M_start, iterator(*cur_node, cur_node));
        }
    }
    template <class _Tp, class _Alloc>
    void deque<_Tp, _Alloc>::_M_new_elements_at_front(size_type __new_elements)
    {
        size_type new_nodes = (__new_elements + _S_buffer_size() - 1) / _S_buffer_size();
        _M_reserve_map_at_front(new_nodes);
        size_type i;
        try
        {
            for (i = 1; i <= new_nodes; ++i)
                *(_M_start._M_node - i) = _M_allocate_node();
        }
        catch (...)
        {
            for (size_type j = 1; j < i; ++j)
                _M_deallocate_node(*(_M_start._M_node - j));
            throw;
        }
    }
    template <class _Tp, class _Alloc>
    void deque<_Tp, _Alloc>::_M_new_elements_at_back(size_type __new_elements)
    {
        size_type new_nodes = (__new_elements + _S_buffer_size() - 1) / _S_buffer_size();
        _M_reserve_map_at_back(new_nodes);
        size_type i;
        try
        {
            for (i = 1; i <= new_nodes; ++i)
                *(_M_finish._M_node + i) = _M_allocate_node();
        }
        catch (...)
        {
            for (size_type j = 1; j < i; ++j)
                _M_deallocate_node(*(_M_finish._M_node + j));
            throw;
        }
    }
    template <class _Tp, class _Alloc>
    void deque<_Tp, _Alloc>::_M_reallocate_map(size_type nodes_to_add, bool add_at_front)
    {
        size_type old_num_nodes = _M_finish._M_node - _M_start._M_node + 1;
        size_type new_num_nodes = old_num_nodes + nodes_to_add;

        _Map_pointer new_nstart;
        if (_M_map_size > 2 * new_num_nodes)
        {
            new_nstart = _M_map + (_M_map_size - new_num_nodes) / 2 + (add_at_front ? nodes_to_add : 0);
            if (new_nstart < _M_start._M_node)
            //TODO std
                std::copy(_M_start._M_node, _M_finish._M_node + 1, new_nstart);
            else
                std::copy_backward(_M_start._M_node, _M_finish._M_node + 1,
                              new_nstart + old_num_nodes);
        }
        else
        {
            size_type new_map_size =
                _M_map_size + std::max(_M_map_size, nodes_to_add) + 2;

            _Map_pointer new_map = _M_allocate_map(new_map_size);
            new_nstart = new_map + (new_map_size - new_num_nodes) / 2 + (add_at_front ? nodes_to_add : 0);
            std::copy(_M_start._M_node, _M_finish._M_node + 1, new_nstart);
            _M_deallocate_map(_M_map, _M_map_size);

            _M_map = new_map;
            _M_map_size = new_map_size;
        }

        _M_start._M_set_node(new_nstart);
        _M_finish._M_set_node(new_nstart + old_num_nodes - 1);
    }
    template <class _Tp, class _Alloc>
    typename deque<_Tp, _Alloc>::iterator 
        deque<_Tp, _Alloc>::_M_reserve_elements_at_front(size_type n)
    {
        size_type vacancies = _M_start._M_cur - _M_start._M_first;
        if (n > vacancies)
            _M_new_elements_at_front(n - vacancies);
        return _M_start - difference_type(n);
    }
    template <class _Tp, class _Alloc>
    typename deque<_Tp, _Alloc>::iterator 
        deque<_Tp, _Alloc>::_M_reserve_elements_at_back(size_type n)
    {
        size_type vacancies = (_M_finish._M_last - _M_finish._M_cur) - 1;
        if (n > vacancies)
            _M_new_elements_at_back(n - vacancies);
        return _M_finish + difference_type(n);
    }
    template <class _Tp, class _Alloc>
    void deque<_Tp, _Alloc>::_M_fill_insert(iterator pos, size_type n, const value_type &x)
    {
        if (pos._M_cur == _M_start._M_cur)
        {
            iterator new_start = _M_reserve_elements_at_front(n);
            try
            {
                uninitialized_fill(new_start, _M_start, x);
                _M_start = new_start;
            }
            catch(...)
            {
                _M_destroy_nodes(new_start._M_node, _M_start._M_node);
            }
            
        }
        else if (pos._M_cur == _M_finish._M_cur)
        {
            iterator new_finish = _M_reserve_elements_at_back(n);
            try
            {
                uninitialized_fill(_M_finish, new_finish, x);
                _M_finish = new_finish;
            }
            catch(...){
                _M_destroy_nodes(_M_finish._M_node + 1,new_finish._M_node + 1);
            }
        }
        else
            _M_insert_aux(pos, n, x);
    }
    template <class _Tp, class _Alloc>
    template <class _InputIterator>
    void deque<_Tp, _Alloc>::insert(iterator __pos, _InputIterator __first, _InputIterator __last,
                                    davis::input_iterator_tag)
    {
        std::copy(__first, __last, std::inserter(*this, __pos));
    }
    template <class _Tp, class _Alloc>
    template <class _ForwardIterator>
    void deque<_Tp, _Alloc>::insert(iterator __pos,
                                    _ForwardIterator __first, _ForwardIterator __last,
                                    davis::forward_iterator_tag)
    {
        size_type __n = davis::distance(__first, __last);
        if (__pos._M_cur == _M_start._M_cur)
        {
            iterator __new_start = _M_reserve_elements_at_front(__n);
            try
            {
                davis::uninitialized_copy(__first, __last, __new_start);
                _M_start = __new_start;
            }
            catch(...)
            {
                _M_destroy_nodes(__new_start._M_node, _M_start._M_node);
            };
        }
        else if (__pos._M_cur == _M_finish._M_cur)
        {
            iterator __new_finish = _M_reserve_elements_at_back(__n);
            try
            {
                davis::uninitialized_copy(__first, __last, _M_finish);
                _M_finish = __new_finish;
            }
            catch(...)
            {
                _M_destroy_nodes(_M_finish._M_node + 1,
                                 __new_finish._M_node + 1);
            }
        }
        else
            _M_insert_aux(__pos, __first, __last, __n);
    }
    // Non-member function overloads
    template <class _Tp, class _Alloc>
    inline bool operator==(const deque<_Tp, _Alloc> &x,
                           const deque<_Tp, _Alloc> &y)
    {
        return x.size() == y.size() &&
               std::equal(x.begin(), x.end(), y.begin());
    }

    template <class _Tp, class _Alloc>
    inline bool operator<(const deque<_Tp, _Alloc> &x,
                          const deque<_Tp, _Alloc> &y)
    {
        return std::lexicographical_compare(x.begin(), x.end(),
                                            y.begin(), y.end());
    }
    template <class _Tp, class _Alloc>
    inline bool operator!=(const deque<_Tp, _Alloc> &x,
                           const deque<_Tp, _Alloc> &y)
    {
        return !(x == y);
    }

    template <class _Tp, class _Alloc>
    inline bool operator>(const deque<_Tp, _Alloc> &x,
                          const deque<_Tp, _Alloc> &y)
    {
        return y < x;
    }

    template <class _Tp, class _Alloc>
    inline bool operator<=(const deque<_Tp, _Alloc> &x,
                           const deque<_Tp, _Alloc> &y)
    {
        return !(y < x);
    }
    template <class _Tp, class _Alloc>
    inline bool operator>=(const deque<_Tp, _Alloc> &x,
                           const deque<_Tp, _Alloc> &y)
    {
        return !(x < y);
    }
    template <class _Tp, class _Alloc>
    inline void swap(deque<_Tp, _Alloc> &x, deque<_Tp, _Alloc> &y)
    {
        x.swap(y);
    }
    // relational operators for deque
    // swap Exchanges the contents of two deque containers
} // namespace davis



#endif