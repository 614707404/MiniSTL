#ifndef DAVIS_LIST_H
#define DAVIS_LIST_H
#include "davis_iterator.h"
#include "davis_allocate.h"
#include "davis_type_traits.h"
#include "davis_construct.h"
namespace davis
{
    template <class _Tp>
    struct List_Node
    {
        List_Node* _M_prev;
        List_Node* _M_next;
        _Tp _M_data;
    };
    template <class _Tp, class _Ref, class _Ptr>
    struct List_iterator
    {
        typedef _Tp                                             value_type;
        typedef _Ref                                            reference;
        typedef _Ptr                                            pointer;
        typedef size_t                                          size_type;
        typedef ptrdiff_t                                       difference_type;
        typedef davis::bidirectional_iterator_tag               iterator_category;
        typedef List_iterator<_Tp, _Tp &, _Tp *>                iterator;
        typedef List_iterator<_Tp, const _Tp &, const _Tp *>    const_iterator;
        typedef List_Node<_Tp>                                  _Node;
        typedef List_iterator<_Tp, _Ref, _Ptr>                  _Self;

        _Node* _M_node;

        List_iterator(){}
        List_iterator(const _Node* x) : _M_node(x) {}
        List_iterator(const _Self& x) : _M_node(x._M_node){}

        void _M_incr() { _M_node = _M_node->next; }
        void _M_decr() { _M_node = _M_node->prev; }

        reference operator*()   {   return  _M_node->_M_data;   }
        pointer operator->()    {   return &(operator*());  }
        bool operator==(const _Self& x) const
        {
            return _M_node==x._M_node;
        }
        bool operator!=(const _Self& x) const
        {
            return _M_node!=x._M_node;
        }
        _Self& operator++()
        {
            this->_M_incr();
            return *this;
        }
        _Self operator++(int)
        {
            _Self __tmp = *this;
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

    template <class _Tp, class _Alloc = davis::allocator<_Tp>>
    class list
    {
    // Member types
    public:
        typedef _Tp                                             value_type;
        typedef _Alloc                                          allocator_type;
        typedef value_type&                                     reference;
        typedef const value_type &                              const_reference;
        typedef value_type*                                     pointer;
        typedef const value_type *                              const_pointer;
        typedef List_iterator<_Tp, _Tp &, _Tp *>                iterator;
        typedef List_iterator<_Tp, const _Tp &, const _Tp *>    const_iterator;
        // TODO reverse_itrator
        // typedef reverse_iterator<iterator>                   reverse_iterator;
        // typedef reverse_iterator<const_iterator>             const_reverse_iterator;
        typedef size_t                                          size_type;
        typedef ptrdiff_t                                       difference_type;
        typedef List_Node<_Tp>                                  _Node;
    // Data
    protected:
        _Node* _M_node;
        allocator_type _M_allocator;

    // Member functions
    protected:
        _Node* _M_get_node() { return _M_allocator.allocate(1); }
        void _M_put_node(_Node *p) { return _M_allocator.deallocate(p,1); }
        template <class _Integer>
        void _M_assign_dispatch(_Integer n, _Integer val, davis::__true_type);
        template <class _InputIterator>
        void _M_assign_dispatch(_InputIterator first, _InputIterator last, davis::__false_type);
        void _M_fill_assign(size_type n, const _Tp& val);
        _Node *_M_create_node(const value_type& x);
        void _M_fill_insert(iterator pos, size_type n, const _Tp& x);
        template <class _Integer>
        void _M_insert_dispatch(iterator pos, _Integer n, _Integer x,davis::__true_type);
        template <class _InputIterator>
        void _M_insert_dispatch(iterator pos,_InputIterator first, _InputIterator last,davis::__false_type);
        void transfer(iterator position, iterator first, iterator last);

    public:
        // constructor
        explicit list(const allocator_type& alloc = allocator_type());
        explicit list(size_type n);
        list(size_type n, const value_type& val,
             const allocator_type& alloc = allocator_type());
        template <class _InputIterator>
        list(_InputIterator first, _InputIterator last,
             const allocator_type& alloc = allocator_type());
        list(const list<_Tp,_Alloc>& x);
        list(const list<_Tp,_Alloc>& x, const allocator_type& alloc);
        
        // TODO move constructor
        //  list(list&& x);
        //  list(list&& x, const allocator_type& alloc);
        // TODO initializer list
        //  list(initializer_list<value_type> il,
        //       const allocator_type& alloc = allocator_type());

        // destructor
        ~list();

        // operator=
        list& operator=(const list& x);
        // TODO move
        //  list& operator=(list&& x);
        // TODO initializer list
        //  list& operator=(initializer_list<value_type> il);

        // Iterators
        iterator begin() noexcept { return _M_node->_M_next; }
        const_iterator begin() const noexcept { return _M_node->_M_next; };
        iterator end() noexcept { return _M_node; }
        const_iterator end() const noexcept { return _M_node; }
        const_iterator cbegin() const noexcept { return _M_node->_M_next; }
        const_iterator cend() const noexcept { return _M_node; }
        //TODO reverse_iterator
        // reverse_iterator rbegin() noexcept;
        // const_reverse_iterator rbegin() const noexcept;
        // reverse_iterator rend() nothrow;
        // const_reverse_iterator rend() const nothrow;
        // const_reverse_iterator crbegin() const noexcept;
        // const_reverse_iterator crend() const noexcept;

        // Capacity
        size_type size() const noexcept;
        bool empty() const noexcept { return _M_node->_M_next=_M_node; }
        size_type max_size() const noexcept { return static_cast<size_type>(-1)}
        
        // Element access
        reference front() { return *begin(); }
        const_reference front() const { return *begin(); }
        reference back() { return *end(); }
        const_reference back() const { return *end(); }

        // Modifiers
        template <class _InputIterator>
        void assign(_InputIterator first, _InputIterator last);
        void assign(size_type n, const value_type& val);
        // TODO initializer_list 
        void assign(initializer_list<value_type> il);
        // TODO emplace
        template <class... _Args>
        void emplace_front(_Args&&... args);
        void push_front(const value_type& val);
        // TODO &&
        void push_front(value_type&& val);
        void pop_front();
        // TODO &&
        template <class... _Args>
        void emplace_back(_Args&&... args);
        void push_back(const value_type& val);
        // TODO &&
        void push_back(value_type&& val);
        void pop_back();
        // TODO emplace
        template <class... _Args>
        iterator emplace(const_iterator position, _Args&&... args);
        iterator insert(const_iterator position, const value_type& val);
        iterator insert(const_iterator position, size_type n, const value_type& val);
        template <class _InputIterator>
        iterator insert(const_iterator position, _InputIterator first, _InputIterator last);
        // TODO && 
        iterator insert(const_iterator position, value_type&& val);
        // TODO initializer_list
        iterator insert(const_iterator position, initializer_list<value_type> il);
        iterator erase(const_iterator position);
        iterator erase(const_iterator first, const_iterator last);
        void swap(list& x);
        void resize(size_type n);
        void resize(size_type n, const value_type& val);
        void clear() noexcept;

        // Operations
        void splice(const_iterator position, list& x);
        void splice(const_iterator position, list& x, const_iterator i);
        void splice(const_iterator position, list& x,
                    const_iterator first, const_iterator last);
        void remove(const value_type& val);
        template <class _Predicate>
        void remove_if(_Predicate pred);
        void unique();
        template <class _BinaryPredicate>
        void unique(_BinaryPredicate binary_pred);
        void merge(list& x);
        template <class Compare>
        void merge(list& x, Compare comp);
        void sort();
        template <class _Compare>
        void sort(_Compare comp);
        void reverse() noexcept;

        //TODO &&
        void merge(list&& x);
        template <class Compare>
        void merge(list&& x, Compare comp);
        //TODO &&
        void splice(const_iterator position, list&& x);
        void splice(const_iterator position, list&& x, const_iterator i);
        void splice(const_iterator position, list&& x,
                    const_iterator first, const_iterator last);
        // Observers
        allocator_type get_allocator() const noexcept { return _M_allocator; }
    };
    
    template<class _Tp,class _Alloc>
    list<_Tp,_Alloc>::list(const allocator_type& alloc = allocator_type()):_M_node(0),_M_allocator(alloc)
    {
        _M_node=_M_get_node();
        _M_node->_M_next = _M_node;
        _M_node->_M_prev = _M_node;
    }
    template <class _Tp, class _Alloc>
    list<_Tp, _Alloc>::list(size_type n) : _M_node(0), _M_allocator(allocator_type())
    {
        insert(begin(),n,_Tp());
    }
    template <class _Tp, class _Alloc>
    list<_Tp, _Alloc>::list(size_type n, const value_type& val,
        const allocator_type& alloc = allocator_type()) : _M_node(0), _M_allocator(alloc)
    {
        insert(begin(), n, val);
    }
    template <class _Tp, class _Alloc>
    template <class _InputIterator>
    list<_Tp, _Alloc>::list(_InputIterator first, _InputIterator last,
        const allocator_type& alloc = allocator_type()) : _M_node(0), _M_allocator(alloc)
    {
        insert(begin(),first,last);
    }
    template <class _Tp, class _Alloc>
    list<_Tp, _Alloc>::list(const list<_Tp, _Alloc>& x):_M_node(0), _M_allocator(get_allocator())
    {
        insert(begin(), x.begin(), x.end());
    }
    template <class _Tp, class _Alloc>
    list<_Tp, _Alloc>::list(const list<_Tp, _Alloc>& x, const allocator_type& alloc) : _M_node(0), _M_allocator(alloc)
    {
        insert(begin(), x.begin(), x.end());
    }
    template <class _Tp, class _Alloc>
    list<_Tp,_Alloc>::~list()
    {
        clear();
        _M_put_node(_M_node);
    }
    template <class _Tp, class _Alloc>
    list<_Tp, _Alloc>::list<_Tp, _Alloc>& operator=(const list<_Tp, _Alloc>& x)
    {
        if(this!=&x)
        {
            iterator first=begin();
            iterator last=end();
            const_iterator first2 = x.begin();
            const_iterator last2 = x.end();
            for (; fisrt != last && first2 != last2;++first,++first2)
            {
                *first=*first2;
            }
            if(first==last)
            {
                insert(last,fisrt2,last2);
            }
            else
            {
                erase(first,last);
            }
        }
        return *this;
    }
    template <class _Tp, class _Alloc>
    list<_Tp, _Alloc> size_type list<_Tp, _Alloc> size() const noexcept
    {
        size_type result;
        //TODO std::distance
        std::distance(begin(),end(),result);
        return result;
    }
    template <class _Tp, class _Alloc>
    template <class _InputIterator>
    void list<_Tp, _Alloc>::assign(_InputIterator first, _InputIterator last)
    {
        typedef typename davis::_Is_integer<_Tp>::_Integral _Integral;
        _M_assign_dispatch(__first, __last, _Integral());
    }
    template <class _Tp, class _Alloc>
    void list<_Tp, _Alloc>::assign(size_type n, const value_type &val)
    {
        _M_fill_assign(n,val);
    }
    template <class _Tp, class _Alloc>
    void list<_Tp, _Alloc>::push_front(const value_type& val)
    {
        insert(begin(),val);
    }
    template <class _Tp, class _Alloc>
    void list<_Tp, _Alloc>::pop_front()
    {
        erase(begin());
    }
    template <class _Tp, class _Alloc>
    void list<_Tp, _Alloc>::push_back(const value_type& val)
    {
        insert(end(),val);
    }
    template <class _Tp, class _Alloc>
    void list<_Tp, _Alloc>::pop_back()
    {
        erase(end());
    }
    template <class _Tp, class _Alloc>
    list<_Tp, _Alloc>::iterator 
        list<_Tp, _Alloc>::insert(const_iterator position, const value_type& val)
    {
        _Node* tmp = _M_create_node(val);
        tmp->_M_next = position._M_node;
        tmp->_M_prev = position._M_node->_M_prev;
        position._M_node->_M_prev->_M_next=tmp;
        position._M_node->_M_prev=tmp;
        return tmp;
    }
    template <class _Tp, class _Alloc>
    list<_Tp, _Alloc>::iterator 
        list<_Tp, _Alloc>::insert(const_iterator position, size_type n, const value_type& val)
    {
        _M_fill_insert(__pos, __n, __x);
    }
    template <class _Tp, class _Alloc>
    template <class _InputIterator>
    list<_Tp, _Alloc>::iterator
        list<_Tp, _Alloc>::insert(const_iterator position, _InputIterator first, _InputIterator last)
    {
        typedef typename davis::_Is_integer<_Tp>::_Integral _Integral;
        _M_insert_dispatch(position, first, last, _Integral());
    }
    template <class _Tp, class _Alloc>
    list<_Tp, _Alloc>::iterator list<_Tp, _Alloc>::erase(const_iterator position)
    {
        _Node* prev_node = position._M_node->_M_prev;
        _Node* next_node = position._M_node->_M_next;
        prev_node._M_node->_M_next = next_node;
        next_node._M_node->_M_prev = prev_node;
        _Node* curr_node = position._M_node;
        davis::destroy(&curr_node->_M_data);
        _M_put_node(curr_node);
        return iterator()
    }
    template <class _Tp, class _Alloc>
    list<_Tp, _Alloc>::iterator list<_Tp, _Alloc>::erase(const_iterator first, const_iterator last)
    {
        while(first!=last)
        {
            erase(first++);
        }
        return last;
    }
    template <class _Tp, class _Alloc>
    void list<_Tp, _Alloc>::swap(list<_Tp, _Alloc>& x)
    {
        // TODO std::swap
        std::swap(_M_node,x._M_node);
    }
    template <class _Tp, class _Alloc>
    void list<_Tp, _Alloc>::resize(size_type n)
    {
        resize(n,_Tp());
    }
    template <class _Tp, class _Alloc>
    void list<_Tp, _Alloc>::resize(size_type n, const value_type& val)
    {
        iterator it=begin();
        size_type len=0;
        for(;it!=end()&&len<n;it++,len++){}
        if(len==n)
        {
            erase(it,end());
        }
        else
        {
            insert(end(),n-len,val);
        }
    }
    template <class _Tp, class _Alloc>
    void list<_Tp, _Alloc>::clear() noexcept
    {
        _Node* curr_node = _M_node->next;
        while(curr_node!=_M_node)
        {
            _Node* tmp = curr_node;
            curr_node = curr_node->_M_next;
            davis::destroy(&tmp->_M_data);
            _M_put_node(tmp);
        }
        _M_node->_M_next = _M_node;
        _M_node->_M_prev = _M_node;
    }
    template <class _Tp, class _Alloc>
    void list<_Tp, _Alloc>::splice(const_iterator position, list &x)
    {
        if(!x.empty())
        {
            transfer(position,x.begin(),x.end());
        }
    }
    template <class _Tp, class _Alloc>
    void list<_Tp, _Alloc>::splice(const_iterator position, list &x, const_iterator i)
    {
        iterator j=i;
        ++j;
        if (i == position || j == position) return;
        transfer(position, i, j);
    }
    template <class _Tp, class _Alloc>
    void list<_Tp, _Alloc>::splice(const_iterator position, list &x,
                                   const_iterator first, const_iterator last)
    {
        if(first!=last)
        {
            transfer(position,first, last);
        }
    }
    template <class _Tp, class _Alloc>
    void list<_Tp, _Alloc>::remove(const value_type &val)
    {
        iterator it=begin();
        while(it!=end())
        {
            iterator nxt=it;
            nxt++;
            if(*it==val){
                erase(it);
            }
            it=nxt;
        }
    }
    template <class _Tp, class _Alloc>
    template <class _Predicate>
    void list<_Tp, _Alloc>::remove_if(_Predicate pred)
    {
        iterator it = begin();
        while (it != end())
        {
            iterator nxt = it;
            nxt++;
            if (pred(*it) == val)
            {
                erase(it);
            }
            it = nxt;
        }
    }
    template <class _Tp, class _Alloc>
    void list<_Tp, _Alloc>::unique()
    {
        iterator it=begin();
        if(it==end()) return;
        iterator nxt=it;
        while(++nxt!=end())
        {
            if(*nxt==*it){
                erase(nxt);
            }else{
                it=nxt;
            }
            nxt=it;
        }
    }
    template <class _Tp, class _Alloc>
    template <class _BinaryPredicate>
    void list<_Tp, _Alloc>::unique(_BinaryPredicate binary_pred)
    {
        iterator it = begin();
        if (it == end())
            return;
        iterator nxt = it;
        while (++nxt != end())
        {
            if (binary_pred(*nxt, *it))
            {
                erase(nxt);
            }
            else
            {
                it = nxt;
            }
            nxt = it;
        }
    }
    template <class _Tp, class _Alloc>
    void list<_Tp, _Alloc>::merge(list &x)
    {
        iterator first1 = begin();
        iterator last1 = end();
        iterator first2 = __x.begin();
        iterator last2 = __x.end();
        while (first1 != last1 && first2 != last2)
            if (*first2 < *first1)
            {
                iterator next = first2;
                transfer(first1, first2, ++next);
                first2 = next;
            }
            else
                ++first1;
        if (first2 != last2)
            transfer(last1, first2, last2);
    }
    template <class _Tp, class _Alloc>
    template <class Compare>
    void list<_Tp, _Alloc>::merge(list &x, Compare comp)
    {
        iterator first1 = begin();
        iterator last1 = end();
        iterator first2 = __x.begin();
        iterator last2 = __x.end();
        while (first1 != last1 && first2 != last2)
            if (comp(*first2, *first1))
            {
                iterator next = first2;
                transfer(first1, first2, ++next);
                first2 = next;
            }
            else
                ++first1;
        if (first2 != last2)
            transfer(last1, first2, last2);
    }
    //TODO quick sort
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
    template <class _Tp, class _Alloc>
    template <class _Compare>
    void list<_Tp, _Alloc>::sort(_Compare comp)
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
                    __counter[__i].merge(__carry,comp);
                    __carry.swap(__counter[__i++]);
                }
                __carry.swap(__counter[__i]);
                if (__i == __fill)
                    ++__fill;
            }

            for (int __i = 1; __i < __fill; ++__i)
                __counter[__i].merge(__counter[__i - 1],comp);
            swap(__counter[__fill - 1]);
        }
    }
    template <class _Tp, class _Alloc>
    void list<_Tp, _Alloc>::reverse() noexcept
    { 
        _Node* tmp = this->_M_node;
        do
        {
            //TODO std::swap
            std::swap(tmp->_M_next, tmp->_M_prev);
            tmp = tmp->_M_prev; 
        } while (tmp != this->_M_node);
    }
    template <class _Tp, class _Alloc>
    template <class _Integer>
    void list<_Tp, _Alloc>::_M_assign_dispatch(_Integer n, _Integer val, davis::__true_type)
    {
        _M_fill_assign((size_type)__n, (_Tp)__val);
    }
    template <class _Tp, class _Alloc>
    template <class _InputIterator>
    void list<_Tp, _Alloc>::_M_assign_dispatch(_InputIterator first, _InputIterator last, davis::__false_type)
    {
        iterator it1=begin();
        iterator it2=end();
        for(;it1!=it2&&first!=last;it1++,first++)
        {
            *it1=*first;
        }
        if(first==last)
        {
            erase(it1,it2);
        }
        else{
            insert(it1,first,last);
        }
    }
    template <class _Tp, class _Alloc>
    void list<_Tp, _Alloc>::_M_fill_assign(size_type n, const _Tp &val)
    {
        iterator it=begin();
        for(;it!=end()&&n>0;it++,n--)
        {
            *it=val;
        }
        if(n>0){
            insert(end(),n,val);
        }else{
            erase(it,end());
        }
    }
    template <class _Tp, class _Alloc>
    _Node* list<_Tp, _Alloc>::_M_create_node(const value_type& x)
    {
        _Node* p=_M_get_node();
        try{
            davis::construct(&p->_M_data,x);
        }catch(...){
            _M_put_node(p);
        }
        return p;
    }
    template <class _Tp, class _Alloc>
    void list<_Tp, _Alloc>::_M_fill_insert(iterator pos, size_type n, const _Tp &x)
    {
        for (; n > 0; n--)
        {
            insert(pos, x);
        }
    }
    template <class _Tp, class _Alloc>
    template <class _Integer>
    void list<_Tp, _Alloc>::_M_insert_dispatch(iterator pos, _Integer n, _Integer x, davis::__true_type)
    {
        _M_fill_insert(__pos, (size_type)__n, (_Tp)__x);
    }
    template <class _Tp, class _Alloc>
    template <class _InputIterator>
    void list<_Tp, _Alloc>::_M_insert_dispatch(iterator pos, _InputIterator first, _InputIterator last, davis::__false_type)
    {
        for (; first != last; ++fisrt)
        {
            insert(position, *fisrt);
        }
    }
    template <class _Tp, class _Alloc>
    void list<_Tp, _Alloc>::transfer(iterator position, iterator first, iterator last)
    {
        last._M_node->_M_prev->_M_next = position._M_node;
        first._M_node->_M_prev->_M_next = __last._M_node;
        position._M_node->_M_prev->_M_next = first._M_node;

        // Splice [first, last) into its new position.
        _List_node_base *tmp = position._M_node->_M_prev;
        position._M_node->_M_prev = last._M_node->_M_prev;
        last._M_node->_M_prev = first._M_node->_M_prev;
        first._M_node->_M_prev = tmp;
    }

    // Non-member function overloads
    template <class _Tp, class _Alloc>
    bool operator==(const list<_Tp, _Alloc> &lhs, const list<_Tp, _Alloc> &rhs)
    {
        typedef typename list<_Tp, _Alloc>::const_iterator const_iterator;
        const_iterator it1=lhs.begin();
        const_iterator it2=rhs.begin();
        const_iterator end1=lhs.end();
        const_iterator end2=rhs.end();
        while(it1!=end1&&it2!=end2&&*it1==*it2)
        {
            ++it1;
            ++it2;
        }
        return it1==end1&&it2==end2;
    }
    template <class _Tp, class _Alloc>
    bool operator<(const list<_Tp, _Alloc> &lhs, const list<_Tp, _Alloc> &rhs)
    {
        // TODO std::lexicographical_compare
        return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }
    template <class _Tp, class _Alloc>
    bool operator!=(const list<_Tp, _Alloc> &lhs, const list<_Tp, _Alloc> &rhs)
    {
        return !(lhs == rhs);
    }
    template <class _Tp, class _Alloc>
    bool operator>(const list<_Tp, _Alloc> &lhs, const list<_Tp, _Alloc> &rhs)
    {
        return rhs < lhs;
    }
    template <class _Tp, class _Alloc>
    bool operator<=(const list<_Tp, _Alloc> &lhs, const list<_Tp, _Alloc> &rhs)
    {
        return !(lhs>rhs);
    }
    
    template <class _Tp, class _Alloc>
    bool operator>=(const list<_Tp, _Alloc> &lhs, const list<_Tp, _Alloc> &rhs)
    {
        return !(lhs<rhs);
    }
    // TODO relational operators (list)
    template <class _Tp, class _Alloc>
    void swap(list<_Tp, _Alloc> &x, list<_Tp, _Alloc> &y)
    {
        x.swap(y);
    }
} // namespace davis
#endif