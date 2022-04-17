#ifndef _DAVIS_LIST_H
#define _DAVIS_LIST_H
#include "davis_allocate.h"
namespace DAVIS
{
    struct _List_Node_base
    {
        _List_Node_base* _M_prev;
        _List_Node_base* _M_next;
    };

    template <class _Tp>
    struct _List_Node : public _List_Node_base
    {
        _Tp _M_data;
    };

    struct _List_iterator_base
    {
        typedef size_t                          size_type;
        typedef ptrdiff_t                       difference_type;
        typedef bidirectional_iterator_tag      iterator_category;

        _List_Node_base* _M_node;

        _List_iterator_base(_List_Node_base *__x) : _M_node(__x) {}
        _List_iterator_base(){}

        void _M_incr() { _M_node = _M_node->next; }
        void _M_decr() { _M_node = _M_node->prev; }

        bool operator==(const _List_iterator_base& __x) const
        {
            return _M_node == __x._M_node;
        }

        bool operator!=(const _List_iterator_base& __x) const
        {
            return _M_node != __x._M_node;
        }
    };

    template <class _Tp ,class _Ref ,class _Ptr>
    struct _List_iterator : public _List_iterator_base
    {
        typedef _List_iterator<_Tp,_Tp&,_Tp*>                       iterator;
        typedef _List_iterator<_Tp,const _Tp&,const _Tp*>           const_iterator;
        typedef _List_iterator<_Tp,_Ref,_Ptr>                       _Self;

        typedef _Tp                                                 value_type;
        typedef _Ref                                                reference;
        typedef _Ptr                                                pointer; 

        typedef _List_Node<_Tp>                                     _Node;

        _List_iterator(){}
        _List_iterator(const _Node* __x) : _List_iterator_base(__x) {}
        _List_iterator(const iterator& __x) : _List_iterator_base(__x._M_node){}

        reference operator*() const {return ((_Node*)_M_node)->_M_data;}
        pointer operator->() const {return &(operator*());}

        _Self& operator++()
        {
            this->_M_incr();
            return *this;
        }
        _Self operator++(int)
        {
            _Self __tmp=*this;
            this->_M_incr();
            return __tmp;
        }

        _Self& operator--()
        {
            this->_M_decr();
            return *this;
        }

        _Self operator--(int)
        {
            _Self __tmp = *this;
            this->_M_decr();
            return __tmp;
        }
    };

    template <class _Tp, class _Alloc>
    class _List_base
    {
    public:
        typedef _Alloc allocator_type;
        allocator_type get_allocator() const {return allocator_type();}
        _List_base(const allocator_type&)
        {
            _M_node = _M_get_node();
            _M_node->_M_next = _M_node;
            _M_node->_M_prev = _M_node;
        }

        ~_List_base()
        {
            clear();
            _M_put_node(_M_node);
        }

        void clear()

    protected : 
        _List_Node<_Tp>* _M_get_node()
        {
            return _M_data_allocator.allocate(sizeof(_List_Node<_Tp>)); 
        }
        void _M_put_node(_List_Node<_Tp>* __p)
        {
            _M_data_allocator.deallocate(__p, sizeof(_List_Node<_Tp>));
        }

    protected:
        _List_Node<_Tp>* _M_node;
        DAVIS::allocator<_Tp> _M_data_allocator;
    }

    template <class _Tp, class _Alloc = DAVIS::allocator<_Tp>>
    class list : protected _List_base<_Tp,_Alloc>
    {
    private:
        typedef _List_base<_Tp, _Alloc>     _Base;
    public:
        typedef _Tp                         value_type;
        typedef value_type *                pointer;
        typedef const value_type *          const_pointer;
        typedef value_type &                reference;
        typedef const value_type &          const_reference;
        typedef size_t                      size_type;
        typedef ptrdiff_t                   difference_type;

        typedef _List_Node<_Tp>                                 _Node;
        typedef _List_iterator<_Tp, _Tp &, _Tp *>               iterator;
        typedef _List_iterator<_Tp, const _Tp &, const _Tp *>   const_iterator;

        typedef typename _Base::allocator_type  allocator_type;
        allocator_type get_allocator() const { return _Base::get_allocator(); }
    
    protected:
        using _Base::_M_put_node;
        using _Base::_M_get_node;
        using _Base::_M_node;

    protected:
        _Node* _M_create_node(const _Tp& __x)
        {
            _Node* __p=_M_get_node();
            try
            {
                DAVIS::construct(&__p->_M_data,__x);
            }
            catch(...)
            {
                _M_put_node(__p);
                throw;
            }
            return __p;
        }
        _Node *_M_create_node()
        {
            _Node *__p = _M_get_node();
            try
            {
                DAVIS::construct(&__p->_M_data);
            }
            catch (...)
            {
                _M_put_node(__p);
                throw;
            }
            return __p;
        }

    public:
        explicit list(const allocator_type& __a = allocator_type()):_Base(__a){}

        iterator begin() { return (_Node *)(_M_node->_M_next); }
        const_iterator begin() const { return (_Node *)(_M_node->_M_next); }

        iterator end() { return _M_node; }
        const_iterator end() const { return _M_node; }

        //TODO 逆迭代器部分

        bool empty() { return _M_node->_M_next == _M_node; }
        size_type size() { return static_cast<size_type>(DAVIS::distance(begin(), end())); }
        size_type max_size() { return size_type(-1); }

        reference front() {return *begin();}
        const_reference front() const { return *begin(); }

        reference back() { return *(--end()); }
        const_reference back() const { return *(--end()); }

        //TODO still std
        void swap(list<_Tp,_Alloc>& __x){    std::swap(_M_node,__x._M_node);    }

        //insert
        iterator insert(iterator __pos,const _Tp& __x);
        iterator insert(iterator __pos);
        void insert(iterator __pos, size_type __n, const _Tp &__x);
        void insert(iterator __pos, size_type __n);

        template <class _Integer>
        void _M_insert_dispatch(iterator __pos, _Integer __n, _Integer __x,
                                __true_type)
        {
            insert(__pos, (size_type)__n, (_Tp)__x);
        }

        template <class _InputIterator>
        void _M_insert_dispatch(iterator __pos,
                                _InputIterator __first, _InputIterator __last,
                                __false_type)
        {
            for (; __first != __last; ++__first)
                insert(__position, *__first);
        }

        template <class _InputIterator>
        void insert(iterator __pos, _InputIterator __first, _InputIterator __last)
        {
            typedef typename _Is_integer<_InputIterator>::_Integral _Integral;
            _M_insert_dispatch(__pos, __first, __last, _Integral());
        }

        

        //push kind functions
        void push_back()    {   insert(end());}
        void push_back(const _Tp& __x)  {   insert(end(),__x);}
        void push_front()   {   insert(begin());}
        void push_front(const _Tp& __x) {   insert(being(),__x);}

        //erase kind functions
        iterator erase(iterator __position);
        iterator erase(iterator __first,iterator __last);

        //resize
        void resize(size_type __new_size, const _Tp& __x);
        void resize(size_type __new_size);

        //pop
        void pop_front() { erase(begin()); }
        void pop_back() {
            // iterator __tmp = end();
            erase(--end());
        }

        //构造函数
        list(size_type __n,const _Tp& __value, 
            const allocator_type& __a = allocator_type()):_Base(__a){
                insert(begin(),__n,__value);
        }
        explicit list(size_type __n) : _Base(allocator_type())
        {
            insert(begin(), __n, _Tp());
        }

        template <class _InputIterator>
        list(_InputIterator __first, _InputIterator __last,
            const allocator_type& __a = allocator_type()):_Base(__a):_Base(__a){
            insert(begin(),__first,__last);
        }
        
        list(const list<_Tp,_Alloc>& __x):_Base(allocator_type()){
            insert(begin(),__x.begin(),__x.end());
        }

        ~list() {}

        list<_Tp, _Alloc> &operator=(const list<_Tp, _Alloc> &__x);

        //assign
        void assign(size_type __n,const _Tp& __val) {   _M_fill_assign(__n,__val);   }
        void _M_fill_assign(size_type __n, const _Tp &__val);

        template <class _InputIterator>
        void assign(_InputIterator __first, _InputIterator __last)
        {
            typedef typename _Is_integer<_InputIterator>::_Integral _Integral;
            _M_assign_dispatch(__first, __last, _Integral());
        }

        template <class _Integer>
        void _M_assign_dispatch(_Integer __n, _Integer __val, __true_type)
        {
            _M_fill_assign((size_type)__n, (_Tp)__val);
        }

        template <class _InputIterator>
        void _M_assign_dispatch(_InputIterator __first, _InputIterator __last,__false_type);
    
    protected:
        void transfer(iterator __position, iterator __first, iterator __last){
            __last._M_node->_M_prev->_M_next = __position._M_node;
            __first._M_node->_M_prev->_M_next = __last._M_node;
            __position._M_node->_M_prev->_M_next = __first._M_node;

            _List_node_base *__tmp = __position._M_node->_M_prev;
            __position._M_node->_M_prev = __last._M_node->_M_prev;
            __last._M_node->_M_prev = __first._M_node->_M_prev;
            __first._M_node->_M_prev = __tmp;
        }
    public:
        void splice(iterator __position, list &__x){
            if(!__x.empty()){
                transfer(__position,__x.begin(),__x.end());
            }
        }
        void splice(iterator __position, list &, iterator __i){
            iterator __j = __i;
            ++__j;
            if (__position == __i || __position == __j)
                return;
            this->transfer(__position, __i, __j);
        }
        void splice(iterator __position, list &, iterator __first, iterator __last){
            if(__first!=__last){
                transfer(__position, __first, __last);
            }
        }
        void remove(const _Tp &__value);
        void unique();
        void merge(list &__x);
        void reverse();
        void sort();
    };


    template <class _Tp, class _Alloc>
    typename list<_Tp, _Alloc>::iterator 
        list<_Tp, _Alloc>::insert(iterator __pos, const _Tp &__x)
    {
        _Node *__tmp = _M_create_node(__x);
        __tmp->_M_next = __pos._M_node;
        __tmp->_M_prev = __pos._M_node->prev;
        __pos._M_node->prev->next = __tmp;
        __pos._M_node->prev = __tmp;
        return __tmp;
    }

    template <class _Tp, class _Alloc>
    typename list<_Tp, _Alloc>::iterator
        list<_Tp, _Alloc>::insert(iterator __pos)
    {
        return insert(__pos, _Tp());
    }

    template <class _Tp, class _Alloc>
    void list<_Tp, _Alloc>::insert(iterator __pos, size_type __n, const _Tp &__x)
    {
        for(;__n;__n--)
        {
            insert(__pos,__x);
        }
    }
    template <class _Tp, class _Alloc>
    void list<_Tp, _Alloc>::insert(iterator __pos, size_type __n)
    {
        insert(__pos,__n,_Tp());
    }


    template <class _Tp, class _Alloc>
    typename list<_Tp, _Alloc>::iterator
        list<_Tp, _Alloc>::erase(iterator __position)
    {
        _List_Node_base* node_next = __position._M_node->_M_next;
        _List_Node_base* node_prev = __position._M_node->_M_prev;
        node_next->_M_prev = node_prev;
        node_prev->_M_next = node_next;
        _Node* __n = (_Node*)__position._M_node;
        DAVIS::destory(&__n->_M_data);
        _M_put_node(__n);
        return iterator((_Node*)node_next);
    }

    template <class _Tp, class _Alloc>
    typename list<_Tp, _Alloc>::iterator
        list<_Tp, _Alloc>::erase(iterator __first, iterator __last)
    {
        while(__first!=__last)
        {
            this->erase(__first++);
        }
        return __last;
    }


    template <class _Tp, class _Alloc>
    void list<_Tp, _Alloc>::resize(size_type __new_size, const _Tp &__x)
    {
        iterator __i = begin();
        size_type __len=0;
        while(__i!=end()&&__len<__new_size)
        {
            __i++;
            __len++;
        }
        if(__len==__new_size)
        {
            erase(__i,end());
        }
        else{
            insert(end(),__new_size-__len,__x);
        }
    }

    template <class _Tp, class _Alloc>
    void list<_Tp, _Alloc>::resize(size_type __new_size)
    {
        this->resize(__new_size,_Tp());
    }

    template <class _Tp, class _Alloc>
    list<_Tp, _Alloc>& list<_Tp, _Alloc>::operator=(const list<_Tp, _Alloc>& __x)
    {
        if (this != &__x)
        {
            iterator __first1=begin();
            iterator __last1=end();
            const_iterator __first2=__x.begin();
            const_iterator __last2=__x.end();
            while(__first1!=__last1&&__first2!=__last2)
            {
                *__first1++ = *__first2++;
            }
            if(__first2==__last2)
            {
                erase(__first1,__last1);
            }
            else
            {
                insert(__first1,__first2,__last2);
            }
        }
        return *this;
    }

    template <class _Tp, class _Alloc>
    void list<_Tp, _Alloc>::_M_fill_assign(size_type __n, const _Tp &__val)
    {
        iterator __i=begin();
        for(;__i!=end()&&__n>0;__i++,__n--)
        {
            *__i=__val;
        }
        if(__n>0){
            insert(end(),__n,__val);
        }else{
            erase(__i,end());
        }
    }

    template <class _Tp, class _Alloc>
    template <class _InputIterator>
    void list<_Tp, _Alloc>::_M_assign_dispatch(_InputIterator __first2, _InputIterator __last2,
                                              __false_type)
    {
        iterator __first1=begin();
        iterator __last1=end();
        while(__first1!=__last1&&__first2!=__last2)
        {
            *__first1++=*__first2++;
        }
        if(__first2==__last2)
        {
            erase(__first1,__last1);
        }
        else{
            insert(__last1,__first2,__last2);
        }

    }
    template <class _Tp, class _Alloc>
    void list<_Tp, _Alloc>::remove(const _Tp &__value)
    {
        iterator __first=begin();
        iterator __last=end();
        while(__first!=__last){
            iterator __next=__first;
            __next++;
            if(*__first==__value){
                erase(__first);
            }
            __first=__next;
        }
    }
    template <class _Tp, class _Alloc>
    void list<_Tp, _Alloc>::unique()
    {
        iterator __first = begin();
        iterator __last = end();
        if(__first==__last) return;
        iterator __next=__first;
        while(__next!=__last){
            if(*__next==*__first){
                erase(__next);
            }else{
                __first=__next;
            }
            __next=__first;
        }
    }
    template <class _Tp, class _Alloc>
    void list<_Tp, _Alloc>::merge(list& __x)
    {
        iterator __first1=begin();
        iterator __last1=end();
        iterator __first2=__x.begin();
        iterator __last2=__x.end();
        while(__first1!=__last1&&__first2!=__last2)
        {
            if(*__first2<*__first1){
                iterator __next = __first2;
                transfer(__first1,__first2,++__next);
                __first2=__next;
            }else{
                __first1++;
            }
        }
        if(__first2!=__last2){
            transfer(__last1,__first2,__last2);
        }
    }

    inline void __List_base_reverse(_List_node_base *__p)
    {
        _List_node_base *__tmp = __p;
        do
        {
            std::swap(__tmp->_M_next, __tmp->_M_prev);
            __tmp = __tmp->_M_prev; // Old next node is now prev.
        } while (__tmp != __p);
    }

    template <class _Tp, class _Alloc>
    void list<_Tp, _Alloc>::reverse()
    {
        __List_base_reverse(this->_M_node);
    }

    //TODO sort
    template <class _Tp, class _Alloc>
    void list<_Tp, _Alloc>::sort()
    {
        if (_M_node->_M_next != _M_node && _M_node->_M_next->_M_next != _M_node)
        {
            list<_Tp, _Alloc> __carry;
            list<_Tp, _Alloc> __counter[64];
            int __fill = 0;
            while (!empty())
            {
                __carry.splice(__carry.begin(), *this, begin());
                int __i = 0;
                while (__i < __fill && !__counter[__i].empty())
                {
                    __counter[__i].merge(__carry);
                    __carry.swap(__counter[__i++]);
                }
                __carry.swap(__counter[__i]);
                if (__i == __fill)
                    ++__fill;
            }

            for (int __i = 1; __i < __fill; ++__i)
                __counter[__i].merge(__counter[__i - 1]);
            swap(__counter[__fill - 1]);
        }
    }
}


#endif