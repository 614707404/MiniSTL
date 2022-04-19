#ifndef DAVIS_DEQUE_SGI_H
#define DAVIS_DEQUE_SGI_H

namespace DAVIS
{
    inline size_t __deque_buf_size(size_t __size)
    {
        return __size < 512 ? size_t(512 / __size) : size_t(1);
    }

    template <class _Tp,class _Ref,class _Ptr>
    struct _Deque_iterator
    {
        typedef _Deque_iterator<_Tp, _Tp&, _Tp*>                  iterator;
        typedef _Deque_iterator<_Tp,const _Tp&,const _Tp*>        const_iterator;
        static size_t _S_buffer_size() { return __deque_buf_size(sizeof(_Tp)); }

        typedef random_access_iterator_tag          iterator_category; // Random access iterator
        typedef _Tp                                 value_type;
        typedef _Ptr                                pointer;
        typedef _Ref                                reference;
        typedef size_t                              size_type;
        typedef ptrdiff_t                           difference_type;

        //pointer of pointer
        typedef _Tp**                               _Map_pointer;

        typedef _Deque_iterator                     _Self;

        _Tp *           _M_cur;          
        _Tp *           _M_first;        
        _Tp *           _M_last;         
        _Map_pointer    _M_node;

        //construct
        _Deque_iterator(_Tp* __x, _Map_pointer __y)
            : _M_cur(__x), _M_first(*__y),
              _M_last(*__y + _S_buffer_size()), _M_node(__y) {}
        _Deque_iterator() : _M_cur(0), _M_first(0), _M_last(0), _M_node(0) {}
        _Deque_iterator(const iterator &__x)
            : _M_cur(__x._M_cur), _M_first(__x._M_first),
              _M_last(__x._M_last), _M_node(__x._M_node) {}

        reference operator*() const {return *_M_cur;}
        pointer operator->() const {return _M_cur;}

        //两个迭代器相减
        difference_type operator-(const _Self& __x) const {
            return difference_type(_S_buffer_size()) * (_M_node - __x._M_node - 1) +
                   (_M_cur - _M_first) + (__x._M_last - __x._M_cur);
        }

        void _M_set_node(_Map_pointer __new_node)
        {
            _M_node = __new_node;
            _M_first = *__new_node;
            _M_last = _M_first + difference_type(_S_buffer_size());
        }

        _Self& operator++(){
            ++_M_cur;
            if(_M_cur==_M_last)
            {
                _M_set_node(_M_node+1);
                _M_cur=_M_first;
            }
            return *this;
        }
        _Self operator++(int){
            _Self __tmp=*this;
            ++*this;
            return __tmp;
        }

        _Self &operator--()
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
            _Self __tmp = *this;
            --*this;
            return __tmp;
        }

        _Self& operator+=(difference_type __n)
        {
            difference_type __offset = __n + (_M_cur-_M_first);
            if(__offset>=0&&__offset<difference_type(_S_buffer_size())){
                _M_cur+=__n;
            }else{
                difference_type __node_offset =
                    __offset > 0 ? __offset / -difference_type((-__offset - 1) / _S_buffer_size()) - 1 : 
                        -difference_type((-__offset - 1) / _S_buffer_size()) - 1 ;
                _M_set_node(_M_node+__node_offset);
                _M_cur = _M_first + (__offset - __node_offset * difference_type(_S_buffer_size()));
            }
            return *this;
        }

        _Self operator+(difference_type __n) const
        {
            _Self __tmp = *this;
            return __tmp += __n;
        }
        _Self& operator-=(difference_type __n) { return *this += -__n; }
        _Self operator-(difference_type __n) const
        {
            _Self __tmp = *this;
            return __tmp -= __n;
        }

        reference operator[](difference_type __n) const { return *(*this + __n); }

        bool operator==(const _Self& __x) const { return __x._M_cur == _M_cur;}
        bool operator!=(const _Self &__x) const { return !(*this == __x); }
        bool operator<(const _Self& __x) const{
            return __x._M_node==_M_node?
                (_M_cur<__x._M_cur):(_M_node<__x._M_node);
        } 
        bool operator>(const _Self& __x)const {return *this<__x;}
        bool operator>=(const _Self &__x) const {return !(*this < __x);}
        bool operator<=(const _Self &__x) const {return !(*this > __x);}
    };

    template <class _Tp, class _Alloc>
    class _Deque_base
    {
    public:
        typedef _Deque_iterator<_Tp ,_Tp&,_Tp*>                 iterator;
        typedef _Deque_iterator<_Tp ,const _Tp& ,const _Tp*>    const_iterator;

        typedef _Alloc                                          allocator_type;
        allocator_type get_allocator() const {   return allocator_type();    }

        _Deque_base(const allocator_type &, size_t __num_elements)
            : _M_map(0), _M_map_size(0), _M_start(), _M_finish()
        {
            _M_initialize_map(__num_elements);
        }
        _Deque_base(const allocator_type &)
            : _M_map(0), _M_map_size(0), _M_start(), _M_finish() {}
        ~_Deque_base();

    protected:
        void _M_initialize_map(size_t);
        void _M_create_nodes(_Tp** __nstart, _Tp** __nfinish);
        void _M_destroy_nodes(_Tp** __nstart, _Tp** __nfinish);
        enum {   _S_initial_map_size = 8     };

    protected:
        _Tp** _M_map;
        size_t _M_map_size;
        iterator _M_start;
        iterator _M_finish;

        DAVIS::allocator<_Tp> _M_data_allocator;

        _Tp *_M_allocate_node()
        {   return _M_data_allocator.allocate(__deque_buf_size(sizeof(_Tp)));   }
        void _M_deallocate_node(_Tp *__p) 
        {   _M_data_allocator.deallocate(__p, __deque_buf_size(sizeof(_Tp)));   }
        _Tp** _M_allocate_map(size_t __n)
        {   return _M_data_allocator.allocate(__n); }
        void _M_deallocate_map(_Tp **__p, size_t __n)
        {   _M_data_allocator.deallocate(__p, __n); }
    };
    template <class _Tp, class _Alloc>
    _Deque_base<_Tp, _Alloc>::~_Deque_base()
    {
        if (_M_map)
        {
            _M_destroy_nodes(_M_start._M_node, _M_finish._M_node + 1);
            _M_deallocate_map(_M_map, _M_map_size);
        }
    }

    template <class _Tp, class _Alloc>
    void _Deque_base<_Tp, _Alloc>::_M_initialize_map(size_t __num_elements)
    {
        //__num_nodes 指map中指针的数量
        size_t __num_nodes =
            __num_elements / __deque_buf_size(sizeof(_Tp)) + 1;
        
        _M_map_size = max((size_t)_S_initial_map_size, __num_nodes + 2);
        _M_map = _M_allocate_map(_M_map_size);

        _Tp **__nstart = _M_map + (_M_map_size - __num_nodes) / 2;
        _Tp **__nfinish = __nstart + __num_nodes;

        try
        {
            _M_create_nodes(__nstart, __nfinish);
        }
        catch(...)
        {
            _M_deallocate_map(_M_map, _M_map_size);
            _M_map = 0, _M_map_size = 0;
        }
        
        _M_start._M_set_node(__nstart);
        _M_finish._M_set_node(__nfinish - 1);
        _M_start._M_cur = _M_start._M_first;
        _M_finish._M_cur = _M_finish._M_first +
                           __num_elements % __deque_buf_size(sizeof(_Tp));
    }

    template <class _Tp, class _Alloc>
    void _Deque_base<_Tp, _Alloc>::_M_create_nodes(_Tp** __nstart, _Tp** __nfinish)
    {
        _Tp** __cur;
        try
        {
            for (__cur = __nstart; __cur < __nfinish; ++__cur)
                *__cur = _M_allocate_node();
        }
        catch(...){
            _M_destroy_nodes(__nstart, __cur);
        }
    }
    template <class _Tp, class _Alloc>
    void _Deque_base<_Tp, _Alloc>::_M_destroy_nodes(_Tp **__nstart, _Tp **__nfinish)
    {
        for (_Tp **__n = __nstart; __n < __nfinish; ++__n)
            _M_deallocate_node(*__n);
    }

    template <class _Tp, class _Alloc=DAVIS::allocator<_Tp>>
    class deque : protected _Deque_base<_Tp,_Alloc>
    {
        typedef _Deque_base<_Tp,_Alloc>             _Base;
    public:
        typedef _Tp                                 value_type;
        typedef value_type *                        pointer;
        typedef const value_type *                  const_pointer;
        typedef value_type &                        reference;
        typedef const value_type &                  const_reference;
        typedef size_t                              size_type;
        typedef ptrdiff_t                           difference_type;

        typedef typename _Base::allocator_type      allocator_type;
        allocator_type get_allocator() const { return _Base::get_allocator(); }

    public:
        typedef _Base::iterator                     iterator;
        typedef _Base::const_iterator               const_iterator;

        //TODO reverse iterator

    protected:
        typedef pointer*                            _Map_pointer;
        static size_t _S_buffer_size() { return __deque_buf_size(sizeof(_Tp)); }

    protected:
        using _Base::_M_allocate_map;
        using _Base::_M_allocate_node;
        using _Base::_M_create_nodes;
        using _Base::_M_deallocate_map;
        using _Base::_M_deallocate_node;
        using _Base::_M_destroy_nodes;
        using _Base::_M_initialize_map;

        using _Base::_M_finish;
        using _Base::_M_map;
        using _Base::_M_map_size;
        using _Base::_M_start;

    public:
        iterator begin() { return _M_start; }
        const_iterator begin() const { return _M_start; }
        iterator end() { return _M_finish; }
        const_iterator end() const { return _M_finish; }

        //TODO rbegin rend

        reference operator[](size_type __n)
        {
            return _M_start[difference_type(__n)];
        }

        const_reference operator[](size_type __n) const
        {
            return _M_start[difference_type(__n)];
        }

        reference front(){  return *_M_start;}
        reference back(){
            iterator __tmp=_M_finish;
            --__tmp;
            return *__tmp;
        }
        const_reference front() const { return *_M_start; }
        const_reference back() const
        {
            const_iterator __tmp = _M_finish;
            --__tmp;
            return *__tmp;
        }
        size_type size() const {  return _M_finish-_M_start;  }
        bool empty() const {  return _M_start==_M_finish; }
        size_type max_size() const { return size_type(-1); }

    public:
        explicit deque(const allocator_type &__a = allocator_type())
            : _Base(__a, 0) {}
        deque(const deque &__x) : _Base(__x.get_allocator(), __x.size())
        {
            uninitialized_copy(__x.begin(), __x.end(), _M_start);
        }
        deque(size_type __n, const value_type &__value,
              const allocator_type &__a = allocator_type()) : _Base(__a, __n)
        {
            _M_fill_initialize(__value);
        }
        explicit deque(size_type __n) : _Base(allocator_type(), __n)
        {
            _M_fill_initialize(value_type());
        }
        //TODO 

    };
}

#endif