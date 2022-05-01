#ifndef DAVIS_RBTREE_H
#define DAVIS_RBTREE_H
#include "davis_iterator.h"
#include "davis_allocate.h"
#include "davis_construct.h"
namespace davis
{
    typedef bool __rbtree_color_type;
    const __rbtree_color_type __rbtree_red = false;
    const __rbtree_color_type __rbtree_black = true;
    template <class _Tp>
    struct __rbtree_node
    {
        typedef __rbtree_color_type color_type;
        typedef __rbtree_node<_Tp> *pointer;
        color_type _M_color;
        pointer _M_parent;
        pointer _M_left;
        pointer _M_right;
        _Tp _M_value;
        static pointer minimum(pointer __x)
        {
            while (__x->_M_left != nullptr)
                __x = __x->_M_left;
            return __x;
        }
        static pointer maximum(pointer __x)
        {
            while (__x->_M_right != nullptr)
                __x = __x->_M_right;
            return __x;
        }
    };

    template <class _Tp>
    inline void rbtree_rotate_left(__rbtree_node<_Tp> *__x, __rbtree_node<_Tp> *&__root)
    {
        __rbtree_node<_Tp> *__y = __x->_M_right;
        __x->_M_right = __y->_M_left;
        if (__y->_M_left != nullptr)
        {
            __y->_M_left->_M_parent = __x;
        }
        __y->_M_parent = __x->_M_parent;
        if (__x == __root)
        {
            __root = __y;
        }
        else if (__x == __x->_M_parent->_M_left)
        {
            __x->_M_parent->_M_left = __y;
        }
        else
        {
            __x->_M_parent->_M_right = __y;
        }
        __y->_M_left = __x;
        __x->_M_parent = __y;
    }
    template <class _Tp>
    inline void rbtree_rotate_right(__rbtree_node<_Tp> *__x, __rbtree_node<_Tp> *&__root)
    {
        __rbtree_node<_Tp> *__y = __x->_M_left;
        __x->_M_left = __y->_M_right;
        if (__y->_M_right != nullptr)
        {
            __y->_M_right->_M_parent = __x;
        }
        __y->_M_parent = __x->_M_parent;
        if (__x == __root)
        {
            __root = __y;
        }
        else if (__x == __x->_M_parent->_M_left)
        {
            __x->_M_parent->_M_left = __y;
        }
        else
        {
            __x->_M_parent->_M_right = __y;
        }
        __x->_M_parent = __y;
        __y->_M_right = __x;
    }
    template <class _Tp>
    inline void rbtree_rebalance(__rbtree_node<_Tp> *__x, __rbtree_node<_Tp> *&__root)
    {
        __x->_M_color = __rbtree_red;
        while (__x != __root && __x->_M_parent->_M_color == __rbtree_red)
        {
            if (__x->_M_parent == __x->_M_parent->_M_parent->_M_left)
            {
                __rbtree_node<_Tp> *__y = __x->_M_parent->_M_parent->_M_right;
                if (__y && __y->_M_color == __rbtree_red)
                {
                    __y->_M_color = __rbtree_black;
                    __x->_M_parent->_M_color = __rbtree_black;
                    __x->_M_parent->_M_parent->_M_color = __rbtree_red;
                    __x = __x->_M_parent->_M_parent;
                }
                else
                {
                    if (__x == __x->_M_parent->_M_right)
                    {
                        __x = __x->_M_parent;
                        rbtree_rotate_left(__x, __root);
                    }
                    __x->_M_parent->_M_color = __rbtree_black;
                    __x->_M_parent->_M_parent->_M_color = __rbtree_red;
                    rbtree_rotate_right(__x->_M_parent->_M_parent, __root);
                }
            }
            else
            {
                __rbtree_node<_Tp> *__y = __x->_M_parent->_M_parent->_M_left;
                if (__y && __y->_M_color == __rbtree_red)
                {
                    __y->_M_color = __rbtree_black;
                    __x->_M_parent->_M_color = __rbtree_black;
                    __x->_M_parent->_M_parent->_M_color = __rbtree_red;
                    __x = __x->_M_parent->_M_parent;
                }
                else
                {
                    if (__x == __x->_M_parent->_M_left)
                    {
                        __x = __x->_M_parent;
                        rbtree_rotate_right(__x, __root);
                    }
                    __x->_M_parent->_M_color = __rbtree_black;
                    __x->_M_parent->_M_parent->_M_color = __rbtree_red;
                    rbtree_rotate_left(__x->_M_parent->_M_parent, __root);
                }
            }
        }
        __root->_M_color = __rbtree_black;
    }
    template <class _Tp>
    inline __rbtree_node<_Tp>* rbtree_rebalance_for_erase(__rbtree_node<_Tp>* __z,
                                                     __rbtree_node<_Tp>*& __root,
                                                     __rbtree_node<_Tp>*& __leftmax,
                                                     __rbtree_node<_Tp>*& __rightmax)
    {
        __rbtree_node<_Tp>* __y=__z;
        __rbtree_node<_Tp>* __x=nullptr;
        __rbtree_node<_Tp>* __x_parent=nullptr;
        if(__y->_M_left==nullptr){
            __x=__y->_M_right;
        }else if(__y->_M_right==nullptr){
            __x=__y->_M_left;
        }else{
            __y=__y->_M_right;
            while(__y->_M_left){
                __y=__y->_M_left;
            }
            __x=__y->_M_right;
        }
        if(__y==__z){
            __x_parent=__y->_M_parent;
            if(__x){
                __x->_M_parent=__x_parent;
            }
            if(__z==__root){
                __root=__x;
            }else if(__y==__x_parent->_M_left){
                __x_parent->_M_left=__x;
            }else{
                __x_parent->_M_right=__x;
            }
            if(__z==__leftmax){
                if(__z->_M_right==nullptr){
                    __leftmax = __z->_M_parent;
                }else{
                    __leftmax = __rbtree_node<_Tp>::minimum(__x);
                }
            }
            if(__z==__rightmax){
                if(__z->_M_left==nullptr){
                    __rightmax = __z->_M_parent;
                }else{
                    __rightmax = __rbtree_node<_Tp>::maximun(__x);
                }
            }
        }else{
            __z->_M_left->_M_parent=__y;
            __y->_M_left=__z->_M_left;
            if(__y!=__z->_M_right){
                __x_parent = __y->_M_parent;
                if(__x){
                    __x->_M_parent=__y->_M_parent;
                }
                __y->_M_parent->_M_left = __x;
                __y->_M_right = __z->_M_right;
                __z->_M_right->_M_parent = __y;
            }
            else
                __x_parent = __y;
            if (__root == __z)
                __root = __y;
            else if (__z->_M_parent->_M_left == __z)
                __z->_M_parent->_M_left = __y;
            else
                __z->_M_parent->_M_right = __y;
            __y->_M_parent = __z->_M_parent;
            std::swap(__y->_M_color, __z->_M_color);
            __y = __z;
        }
        if (__y->_M_color != __rbtree_red)
        {
            while (__x != __root && (__x == 0 || __x->_M_color == __rbtree_black))
                if (__x == __x_parent->_M_left)
                {
                    _Rb_tree_node_base *__w = __x_parent->_M_right;
                    if (__w->_M_color == _S_rb_tree_red)
                    {
                        __w->_M_color = _S_rb_tree_black;
                        __x_parent->_M_color = _S_rb_tree_red;
                        _Rb_tree_rotate_left(__x_parent, __root);
                        __w = __x_parent->_M_right;
                    }
                    if ((__w->_M_left == 0 ||
                         __w->_M_left->_M_color == _S_rb_tree_black) &&
                        (__w->_M_right == 0 ||
                         __w->_M_right->_M_color == _S_rb_tree_black))
                    {
                        __w->_M_color = _S_rb_tree_red;
                        __x = __x_parent;
                        __x_parent = __x_parent->_M_parent;
                    }
                    else
                    {
                        if (__w->_M_right == 0 ||
                            __w->_M_right->_M_color == _S_rb_tree_black)
                        {
                            if (__w->_M_left)
                                __w->_M_left->_M_color = _S_rb_tree_black;
                            __w->_M_color = _S_rb_tree_red;
                            _Rb_tree_rotate_right(__w, __root);
                            __w = __x_parent->_M_right;
                        }
                        __w->_M_color = __x_parent->_M_color;
                        __x_parent->_M_color = _S_rb_tree_black;
                        if (__w->_M_right)
                            __w->_M_right->_M_color = _S_rb_tree_black;
                        _Rb_tree_rotate_left(__x_parent, __root);
                        break;
                    }
                }
                else
                { // same as above, with _M_right <-> _M_left.
                    _Rb_tree_node_base *__w = __x_parent->_M_left;
                    if (__w->_M_color == _S_rb_tree_red)
                    {
                        __w->_M_color = _S_rb_tree_black;
                        __x_parent->_M_color = _S_rb_tree_red;
                        _Rb_tree_rotate_right(__x_parent, __root);
                        __w = __x_parent->_M_left;
                    }
                    if ((__w->_M_right == 0 ||
                         __w->_M_right->_M_color == _S_rb_tree_black) &&
                        (__w->_M_left == 0 ||
                         __w->_M_left->_M_color == _S_rb_tree_black))
                    {
                        __w->_M_color = _S_rb_tree_red;
                        __x = __x_parent;
                        __x_parent = __x_parent->_M_parent;
                    }
                    else
                    {
                        if (__w->_M_left == 0 ||
                            __w->_M_left->_M_color == _S_rb_tree_black)
                        {
                            if (__w->_M_right)
                                __w->_M_right->_M_color = _S_rb_tree_black;
                            __w->_M_color = _S_rb_tree_red;
                            _Rb_tree_rotate_left(__w, __root);
                            __w = __x_parent->_M_left;
                        }
                        __w->_M_color = __x_parent->_M_color;
                        __x_parent->_M_color = _S_rb_tree_black;
                        if (__w->_M_left)
                            __w->_M_left->_M_color = _S_rb_tree_black;
                        _Rb_tree_rotate_right(__x_parent, __root);
                        break;
                    }
                }
            if (__x)
                __x->_M_color = _S_rb_tree_black;
        }
        return __y;
    }

    template <class _Tp,class _Ref,class _Ptr>
    struct __rbtree_iterator 
    {
        typedef _Tp                                             value_type;
        typedef _Ref                                            reference;
        typedef _Ptr                                            pointer;
        typedef __rbtree_iterator<_Tp,_Tp&,_Tp*>                iterator;
        typedef __rbtree_iterator<_Tp,const _Tp&,const _Tp*>    const_iterator;
        typedef davis::bidirectional_iterator_tag               iterator_category;
        typedef ptrdiff_t                                       difference_type;
        typedef __rbtree_node<_Tp> *                            link_type;
        typedef __rbtree_iterator<_Tp,_Ref,_Ptr>                _Self;

        link_type _M_node;

        void _M_increment(){
            if(_M_node->_M_right!=nullptr){
                _M_node=_M_node->_M_right;
                while(_M_node->_M_left!=nullptr){
                    _M_node=_M_node->_M_left;
                }
            }else{
                link_type __y = _M_node->_M_parent;
                while(_M_node==__y->_M_right){
                    _M_node=__y;
                    __y=__y->_M_parent;
                }
                if(_M_node->_M_right!=__y){
                    _M_node=__y;
                }
            }
        }
        void _M_decrement(){
            if(_M_node->_M_color==__rbtree_red&&_M_node->_M_parent->_M_parent==_M_node){
                _M_node=_M_node->_M_right;
            }else if(_M_node->_M_left!=nullptr){
                link_type __y = _M_node->_M_left;
                while(__y->_M_right!=nullptr){
                    __y = __y->_M_right;
                }
                _M_node = __y;
            }else{
                link_type __y = _M_node->_M_parent;
                while(_M_node == __y->_M_left){
                    _M_node = __y;
                    __y = _M_node->_M_parent;
                }
                _M_node = __y;
            }
        }

        __rbtree_iterator(){}
        __rbtree_iterator(link_type* __x){ _M_node=__x; }
        __rbtree_iterator(const iterator& __it){ _M_node=__it._M_node; }

        reference operator*() const { return _M_node->_M_value; }
        pointer operator->() const { return &(operator*()); }

        _Self& operator++(){
            _M_increment();
            return *this;
        }
        _Self operator++(int){
            _Self __tmp=this;
            _M_increment();
            return __tmp;
        }
        _Self& operator--(){
            _M_decrement();
            return *this;
        }
        _Self operator--(int){
            _Self __tmp=this;
            _M_decrement();
            return __tmp;
        }
    };
    template <class _Tp, class _Ref, class _Ptr>
    inline bool operator==(const __rbtree_iterator<_Tp, _Ref, _Ptr>& __x,
                           const __rbtree_iterator<_Tp, _Ref, _Ptr>& __y){
        return __x._M_node == __y._M_node;
    }
    template <class _Tp, class _Ref, class _Ptr>
    inline bool operator!=(const __rbtree_iterator<_Tp, _Ref, _Ptr>& __x,
                           const __rbtree_iterator<_Tp, _Ref, _Ptr>& __y){
        return __x._M_node != __y._M_node;
    }
    template <class _Key,class _Value,class _KeyofValue,class _Compare,
        class _Alloc=davis::allocator<__rbtree_node<_Value>>>
    class rbtree{
    protected:
        typedef __rbtree_node<_Value>                   rbtree_node;
        typedef __rbtree_color_type                     color_type;

    public:
        typedef _Key                                    key_type;
        typedef _Value                                  value_type;
        typedef value_type*                             pointer;
        typedef const value_type*                       const_pointer;
        typedef value_type&                             reference;
        typedef const value_type&                       const_reference;
        typedef rbtree_node*                            link_type;
        typedef size_t                                  size_type;
        typedef ptrdiff_t                               difference_type;
        typedef _Alloc                                  allocator_type;
        
    protected:
        link_type _M_get_node() { return _M_allocator.allocate(1); }
        void _M_put_node(link_type __p) { _M_allocator.deallocate(__p,1); }
        link_type _M_create_node(const value_type& __x){
            link_type __tmp = _M_get_node();
            try{
                davis::construct(&__tmp->_M_value,__x);
            }catch(...){
                _M_put_node(__tmp);
            }
            return __tmp;
        }
        link_type _M_clone_node(link_type __p){
            link_type __tmp = _M_create_node(__p->_M_value);
            __tmp->_M_color = __p->_M_color;
            __tmp->_M_left = 0;
            __tmp->_M_right = 0;
            return __tmp;
        }
        void _M_destory_node(link_type __p){
            davis::destroy(&__p->_M_value);
            _M_put_node(__p);
        }
     
    protected:
        allocator_type _M_allocator;
        link_type _M_header;
        size_type _M_node_count;
        _Compare _M_key_compare;

        link_type& _M_root() const{  return _M_header->_M_parent; }
        link_type& _M_leftmost() const{  return _M_header->_M_left; }
        link_type& _M_rightmost() const{  return _M_header->_M_right; }

        static link_type& _S_left(link_type __x){  return __x->_M_left;  }
        static link_type& _S_right(link_type __x){  return __x->_M_right;  }
        static link_type& _S_parent(link_type __x){  return __x->_M_parent; }
        static reference _S_value(link_type __x){  return __x->_M_value; }
        static const key_type& _S_key(link_type __x) { return _KeyofValue()(value(__x)); }
        static color_type& _S_color(link_type __x){ return __x->_M_color; }

        static link_type _S_minimum(link_type __x) { return __rbtree_node<value_type>::minimum(__x); }
        static link_type _S_maximum(link_type __x) { return __rbtree_node<value_type>::maximum(__x); }

    public:
        typedef __rbtree_iterator<value_type,reference,pointer>                 iterator;
        typedef __rbtree_iterator<value_type,const_reference,const_pointer>     const_iterator;
        // TODO reverse_iterator

    private:
        iterator _M_insert(link_type __x, link_type __y, const value_type& __v);
        link_type _M_copy(link_type __x, link_type __p);
        void _M_erase(link_type __x);
    public:
        rbtree():_M_allocator(allocator_type()),_M_header(0),_M_key_compare(),_M_node_count(0){
            _M_empty_initialize();
        }
        rbtree(const _Compare& __comp) 
            : _M_allocator(allocator_type()), _M_header(0), _M_key_compare(__comp), _M_node_count(0){
            _M_empty_initialize();
        }
        rbtree(const _Compare& __comp, const allocator_type& __a) 
            : _M_allocator(__a), _M_header(0),_M_key_compare(__comp), _M_node_count(0){
            _M_empty_initialize();
        }
        rbtree(const rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc> &__x)
            : _M_allocator(__x.get_allocator()), _M_header(0), 
            _M_key_compare(__x._M_key_compare), _M_node_count(0){
                if(__x->_M_root()==nullptr){
                    _M_empty_initialize();
                }else{
                    _S_color(_M_header) = __rbtree_red;
                    _M_root() = _M_copy(__x->_M_root,_M_header);
                    _M_leftmost() = _S_minimum(_M_header);
                    _M_rightmost() = _S_maximum(_M_header);
                }
                _M_node_count=__x._M_node_count;
        }
        ~rbtree(){clear();}
        rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc>&
            operator=(const rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc> &__x);
        allocator_type get_allocator() { return _M_allocator; }

    private:
        void _M_empty_initialize(){
            _M_header = _M_get_node();
            _S_color(_M_header) = __rbtree_red;
            _M_root() = 0;
            _M_leftmost() = _M_header;
            _M_rightmost() = _M_header;
        }
    public:
        _Compare key_comp() const { return _M_key_compare; }
        iterator begin() { return _M_leftmost(); } 
        const_iterator begin() const { return _M_leftmost(); }
        const_iterator cbegin() const { return _M_leftmost(); }
        iterator end() { return _M_header; } 
        const_iterator end() const { return _M_header; }
        const_iterator cend() const { return _M_header; }
        // TODO reverse iterator
        bool empty() { return _M_node_count==0; }
        size_type size() { return _M_node_count; }
        size_type max_size() { return  size_type(-1); }
        void swap(rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc>& __t){
            std::swap(_M_header, __t._M_header);
            std::swap(_M_key_compare, __t._M_key_compare);
            std::swap(_M_node_count, __t._M_node_count);
        }

    public:
        pair<iterator, bool> insert_unique(const value_type& __x);
        iterator insert_equal(const value_type& __x);

        iterator insert_unique(iterator __position, const value_type& __x);
        iterator insert_equal(iterator __position, const value_type& __x);

        template <class _InputIterator>
        void insert_unique(_InputIterator __first, _InputIterator __last);
        template <class _InputIterator>
        void insert_equal(_InputIterator __first, _InputIterator __last);

        void erase(iterator __position);
        size_type erase(const key_type& __x);
        void erase(iterator __first, iterator __last);
        void erase(const key_type* __first, const key_type* __last);

        void clear()
        {
            if (_M_node_count != 0)
            {
                _M_erase(_M_root());
                _M_leftmost() = _M_header;
                _M_root() = 0;
                _M_rightmost() = _M_header;
                _M_node_count = 0;
            }
        }
    public:
        iterator find(const key_type &__x);
        const_iterator find(const key_type &__x) const;
        size_type count(const key_type &__x) const;
        iterator lower_bound(const key_type &__x);
        const_iterator lower_bound(const key_type &__x) const;
        iterator upper_bound(const key_type &__x);
        const_iterator upper_bound(const key_type &__x) const;
        pair<iterator, iterator> equal_range(const key_type &__x);
        pair<const_iterator, const_iterator> equal_range(const key_type &__x) const;

    public:
        bool __rb_verify() const;
    };
    // ralational operator
    template <class _Key, class _Value, class _KeyofValue,
              class _Compare, class _Alloc>
    inline bool
    operator==(const rbrtree<_Key, _Value, _KeyofValue, _Compare, _Alloc> &__x,
               const rbrtree<_Key, _Value, _KeyofValue, _Compare, _Alloc> &__y)
    {
        return __x.size() == __y.size() &&
               std::equal(__x.begin(), __x.end(), __y.begin());
    }

    template <class _Key, class _Value, class _KeyofValue,
              class _Compare, class _Alloc>
    inline bool
    operator<(const rbrtree<_Key, _Value, _KeyofValue, _Compare, _Alloc> &__x,
              const rbrtree<_Key, _Value, _KeyofValue, _Compare, _Alloc> &__y)
    {
        return std::lexicographical_compare(__x.begin(), __x.end(),
                                       __y.begin(), __y.end());
    }
    template <class _Key, class _Value, class _KeyofValue,
              class _Compare, class _Alloc>
    inline bool
    operator!=(const rbrtree<_Key, _Value, _KeyofValue, _Compare, _Alloc> &__x,
               const rbrtree<_Key, _Value, _KeyofValue, _Compare, _Alloc> &__y)
    {
        return !(__x == __y);
    }

    template <class _Key, class _Value, class _KeyofValue,
              class _Compare, class _Alloc>
    inline bool
    operator>(const rbrtree<_Key, _Value, _KeyofValue, _Compare, _Alloc> &__x,
              const rbrtree<_Key, _Value, _KeyofValue, _Compare, _Alloc> &__y)
    {
        return __y < __x;
    }

    template <class _Key, class _Value, class _KeyofValue,
              class _Compare, class _Alloc>
    inline bool
    operator<=(const rbrtree<_Key, _Value, _KeyofValue, _Compare, _Alloc> &__x,
               const rbrtree<_Key, _Value, _KeyofValue, _Compare, _Alloc> &__y)
    {
        return !(__y < __x);
    }

    template <class _Key, class _Value, class _KeyofValue,
              class _Compare, class _Alloc>
    inline bool
    operator>=(const rbrtree<_Key, _Value, _KeyofValue, _Compare, _Alloc> &__x,
               const rbrtree<_Key, _Value, _KeyofValue, _Compare, _Alloc> &__y)
    {
        return !(__x < __y);
    }

    template <class _Key, class _Value, class _KeyofValue,
              class _Compare, class _Alloc>
    inline void
    swap(rbrtree<_Key, _Value, _KeyofValue, _Compare, _Alloc> &__x,
         rbrtree<_Key, _Value, _KeyofValue, _Compare, _Alloc> &__y)
    {
        __x.swap(__y);
    }
    template <class _Key, class _Value, class _KeyofValue,
              class _Compare, class _Alloc>
    rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc> &
    rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc>::
        operator=(const rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc> &__x)
    {
        if(this!=&__x){
            clear();
            _M_key_compare=__x._M_key_compare;
            if(__x._M_root()==0){
                _M_root()=0;
                _M_leftmost()=_M_header;
                _M_rightmost()=_M_header;
            }else{
                _M_root() = _M_copy(__x._M_root(), _M_header);
                _M_leftmost() = _S_minimum(_M_root());
                _M_rightmost() = _S_maximum(_M_root());
                _M_node_count = __x._M_node_count;
            }
        }
        return *this;
    }
    template <class _Key, class _Value, class _KeyofValue,
              class _Compare, class _Alloc>
    typename rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc>::iterator
    rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc>
        ::_M_insert(link_type __x, link_type __y, const value_type &__v){
        link_type __z;
        if (__y == _M_header || __x != 0 ||
            _M_key_compare(_KeyofValue()(__v), _S_key(__y)))
        {
            __z = _M_create_node(__v);
            _S_left(__y) = __z; // also makes _M_leftmost() = __z
                                //    when __y == _M_header
            if (__y == _M_header)
            {
                _M_root() = __z;
                _M_rightmost() = __z;
            }
            else if (__y == _M_leftmost())
                _M_leftmost() = __z; // maintain _M_leftmost() pointing to min node
        }
        else
        {
            __z = _M_create_node(__v);
            _S_right(__y) = __z;
            if (__y == _M_rightmost())
                _M_rightmost() = __z; // maintain _M_rightmost() pointing to max node
        }
        _S_parent(__z) = __y;
        _S_left(__z) = 0;
        _S_right(__z) = 0;
        rbtree_rebalance(__z, _M_header->_M_parent);
        ++_M_node_count;
        return iterator(__z);
    }
    template <class _Key, class _Value, class _KeyofValue,
              class _Compare, class _Alloc>
    typename rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc>::link_type 
    rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc>
        ::_M_copy(link_type __x, link_type __p){
        // 循环处理当前节点、左节点
        // 递归处理右节点
        link_type __top = _M_clone_node(__x);
        __top->_M_parent = __p;
        try
        {
            if (__x->_M_right)
                __top->_M_right = _M_copy(_S_right(__x), __top);
            __p = __top;
            __x = _S_left(__x);

            while (__x != 0)
            {
                link_type __y = _M_clone_node(__x);
                __p->_M_left = __y;
                __y->_M_parent = __p;
                if (__x->_M_right)
                    __y->_M_right = _M_copy(_S_right(__x), __y);
                __p = __y;
                __x = _S_left(__x);
            }
        }
        catch(...){
            _M_erase(__top);
        }
        return __top;
    }
    template <class _Key, class _Value, class _KeyofValue,class _Compare, class _Alloc>
    void rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc>
        ::_M_erase(link_type __x){
        while (__x != 0)
        {
            _M_erase(_S_right(__x));
            link_type __y = _S_left(__x);
            destroy_node(__x);
            __x = __y;
        }
    }
    template <class _Key, class _Value, class _KeyofValue, class _Compare, class _Alloc>
    pair<typename rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc>::iterator, bool> 
    rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc>
        ::insert_unique(const value_type& __val){
        link_type __y = _M_header;
        link_type __x = _M_root();
        bool __comp = true;
        while (__x != 0)
        {
            __y = __x;
            __comp = _M_key_compare(_KeyofValue()(__val), _S_key(__x));
            __x = __comp ? _S_left(__x) : _S_right(__x);
        }
        //__y此时为插入位置的父节点
        iterator __j = iterator(__y);
        if (__comp)//__x要作为左节点插入
            if (__j == begin())
                return pair<iterator, bool>(_M_insert(__x, __y, __val), true);
            else
                --__j;
        //判断j节点是否小于val
        if (_M_key_compare(_S_key(__j._M_node), _KeyOfValue()(__val)))
            return pair<iterator, bool>(_M_insert(__x, __y, __val), true);
        //插入失败，发生重复
        return pair<iterator, bool>(__j, false);
    }
    template <class _Key, class _Value, class _KeyofValue, class _Compare, class _Alloc>
    typename rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc>::iterator
    rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc>
        ::insert_unique(iterator __position, const value_type& __val){
        if (__position._M_node == _M_header->_M_left)
        {
            if (size() > 0 &&
                _M_key_compare(_KeyofValue()(__val), _S_key(__position._M_node)))
                return _M_insert(__position._M_node, __position._M_node, __val);
                // first argument just needs to be non-null
            else
                return insert_unique(__val).first;
        }
        else if (__position._M_node == _M_header)
        {
            if (_M_key_compare(_S_key(_M_rightmost()), _KeyofValue()(__val)))
                return _M_insert(0, _M_rightmost(), __val);
            else
                return insert_unique(__val).first;
        }
        else
        {
            iterator __before = __position;
            --__before;
            if (_M_key_compare(_S_key(__before._M_node), _KeyofValue()(__val)) 
                && _M_key_compare(_KeyofValue()(__val), _S_key(__position._M_node)))
            {
                if (_S_right(__before._M_node) == 0)
                    return _M_insert(0, __before._M_node, __v);
                else
                    return _M_insert(__position._M_node, __position._M_node, __v);
                // first argument just needs to be non-null
            }
            else
                return insert_unique(__v).first;
        }
    }
    template <class _Key, class _Value, class _KeyofValue, class _Compare, class _Alloc>
    typename rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc>::iterator
    rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc>
        ::insert_equal(const value_type &__val){
        link_type __y = _M_header;
        link_type __x = _M_root();
        while (__x != 0)
        {
            __y = __x;
            __x = _M_key_compare(_KeyofValue()(__val), _S_key(__x)) ?
                 _S_left(__x) : _S_right(__x);
        }
        return _M_insert(__x,__y,__val)
    }

    template <class _Key, class _Value, class _KeyofValue, class _Compare, class _Alloc>
    typename rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc>::iterator
    rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc>
        ::insert_equal(iterator __position, const value_type &__val){
        if (__position._M_node == _M_header->_M_left)
        {
            if (size() > 0 &&
                !_M_key_compare(_S_key(__position._M_node),_KeyofValue()(__val) ))
                return _M_insert(__position._M_node, __position._M_node, __val);
            // first argument just needs to be non-null
            else
                return insert_equal(__val);
        }
        else if (__position._M_node == _M_header)
        {
            if (!_M_key_compare(_KeyofValue()(__val),_S_key(_M_rightmost()) ))
                return _M_insert(0, _M_rightmost(), __val);
            else
                return insert_equal(__val);
        }
        else
        {
            iterator __before = __position;
            --__before;
            if (!_M_key_compare(_KeyofValue()(__val,_S_key(__before._M_node) )) 
                && !_M_key_compare(_S_key(__position._M_node),_KeyofValue()(__val) ))
            {
                if (_S_right(__before._M_node) == 0)
                    return _M_insert(0, __before._M_node, __v);
                else
                    return _M_insert(__position._M_node, __position._M_node, __v);
                // first argument just needs to be non-null
            }
            else
                return insert_equal(__val);
        }
    }
    template <class _Key, class _Value, class _KeyofValue, class _Compare, class _Alloc>
    template <class _InputIterator>
    void rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc>
        ::insert_unique(_InputIterator __first, _InputIterator __last){
        for (; __first != __last; __first++)
        {
            insert_unique(*__first);
        }
    }
    template <class _Key, class _Value, class _KeyofValue, class _Compare, class _Alloc>
    template <class _InputIterator>
    void rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc>
        ::insert_equal(_InputIterator __first, _InputIterator __last){
        for (; __first != __last; __first++)
        {
            insert_equal(*__first);
        }
    }
    template <class _Key, class _Value, class _KeyofValue, class _Compare, class _Alloc>
    void rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc>
        ::erase(iterator __position){
            link_type __y = rbtree_rebalance_for_erase(__position._M_node,_M_root(),
                                                    _M_leftmost(),_M_rightmost());
            davis::destroy(__y);
            --_M_node_count;
    }
    template <class _Key, class _Value, class _KeyofValue, class _Compare, class _Alloc>
    typename rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc>::size_type 
    rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc>
        ::erase(const key_type &__k){
        pair<iterator, iterator> __p = equal_range(__k);
        size_type __n =distance(__p.first, __p.second,);
        erase(__p.first, __p.second);
        return __n;
    }
    template <class _Key, class _Value, class _KeyofValue, class _Compare, class _Alloc>
    void rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc>
        ::erase(iterator __first, iterator __last)
    {
        if (__first == begin() && __last == end())
            clear();
        else
            while (__first != __last)
                erase(__first++);
    }
    template <class _Key, class _Value, class _KeyofValue, class _Compare, class _Alloc>
    void rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc>
        ::erase(const key_type *__first, const key_type *__last){
        while(__first!=__last){
            erase(*__first++);
        }
    }
    template <class _Key, class _Value, class _KeyofValue, class _Compare, class _Alloc>
    typename rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc>::iterator
    rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc>
        ::find(const key_type &__k){
        link_type __y = _M_header; 
        link_type __x = _M_root(); 

        while (__x != 0)
            if (!_M_key_compare(_S_key(__x), __k))
                __y = __x, __x = _S_left(__x);
            else
                __x = _S_right(__x);
        // __y 大于等于k的节点
        iterator __j = iterator(__y);
        return (__j == end() || _M_key_compare(__k, _S_key(__j._M_node))) ? end() : __j;
    }
    template <class _Key, class _Value, class _KeyofValue, class _Compare, class _Alloc>
    typename rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc>::const_iterator
    rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc>
        ::find(const key_type &__k) const{
        link_type __y = _M_header;
        link_type __x = _M_root();

        while (__x != 0)
            if (!_M_key_compare(_S_key(__x), __k))
                __y = __x, __x = _S_left(__x);
            else
                __x = _S_right(__x);
        
        const_iterator __j = const_iterator(__y);
        return (__j == end() || _M_key_compare(__k, _S_key(__j._M_node))) ? end() : __j;
    }
    template <class _Key, class _Value, class _KeyofValue, class _Compare, class _Alloc>
    typename rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc>::size_type
    rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc>
        ::count(const key_type &__k) const
    {
        pair<const_iterator, const_iterator> __p = equal_range(__k);
        size_type __n =davis::distance(__p.first, __p.second);
        return __n;
    }
    template <class _Key, class _Value, class _KeyofValue, class _Compare, class _Alloc>
    typename rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc>::iterator
    rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc>
        ::lower_bound(const key_type &__k)
    {
        link_type __y=_M_header;
        link_type __x=_M_root();
        while (__x != 0)
        {
            if (!_M_key_compare(_S_key(__x), __k))
                __y = __x, __x = _S_left(__x);
            else
                __x = _S_right(__x);
        }
        return iterator(__y);
    }
    template <class _Key, class _Value, class _KeyofValue, class _Compare, class _Alloc>
    typename rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc>::const_iterator 
    rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc>
        ::lower_bound(const key_type &__k) const
    {
        link_type __y = _M_header;
        link_type __x = _M_root();
        while (__x != 0)
        {
            if (!_M_key_compare(_S_key(__x), __k))
                __y = __x, __x = _S_left(__x);
            else
                __x = _S_right(__x);
        }
        return const_iterator(__y);
    }
    template <class _Key, class _Value, class _KeyofValue, class _Compare, class _Alloc>
    typename rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc>::iterator
    rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc>::upper_bound(const key_type &__k)
    {
        link_type __y = _M_header;
        link_type __x = _M_root();
        while (__x != 0)
        {
            if (_M_key_compare(__k, _S_key(__x)))
                __y = __x, __x = _S_left(__x);
            else
                __x = _S_right(__x);
        }
        return iterator(__y);
    }
    template <class _Key, class _Value, class _KeyofValue, class _Compare, class _Alloc>
    typename rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc>::const_iterator
    rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc>::upper_bound(const key_type &__k) const
    {
        link_type __y = _M_header;
        link_type __x = _M_root();
        while (__x != 0)
        {
            if (_M_key_compare(__k, _S_key(__x)))
                __y = __x, __x = _S_left(__x);
            else
                __x = _S_right(__x);
        }
        return const_iterator(__y);
    }

    template <class _Key, class _Value, class _KeyofValue, class _Compare, class _Alloc>
    inline pair<typename rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc>::iterator,
                typename rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc>::iterator>
    rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc>::equal_range(const key_type &__k)
    {
        return pair<iterator, iterator>(lower_bound(__k), upper_bound(__k));
    }
    template <class _Key, class _Value, class _KeyofValue, class _Compare, class _Alloc>
    inline pair<typename rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc>::const_iterator,
                typename rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc>::const_iterator>
    rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc>::equal_range(const key_type &__k) const
    {
        return pair<const_iterator, const_iterator>(lower_bound(__k), upper_bound(__k));
    }
    template<class _Tp>
    inline int __black_count(__rbtree_node<_Tp> *__node, __rbtree_node<_Tp> *__root)
    {
        if (__node == 0)
            return 0;
        else
        {
            int __bc = __node->_M_color == __black_count ? 1 : 0;
            if (__node == __root)
                return __bc;
            else
                return __bc + __black_count(__node->_M_parent, __root);
        }
    }
    template <class _Key, class _Value, class _KeyofValue, class _Compare, class _Alloc>
    bool rbtree<_Key, _Value, _KeyofValue, _Compare, _Alloc>::__rb_verify() const
    {
        // 空树
        if (_M_node_count == 0 || begin() == end())
            return _M_node_count == 0 && begin() == end() &&
                   _M_header->_M_left == _M_header && _M_header->_M_right == _M_header;

        // __len 黑节点层数，即从叶子到根的黑节点数量
        int __len = __black_count(_M_leftmost(), _M_root());
        for (const_iterator __it = begin(); __it != end(); ++__it)
        {
            _Link_type __x = (_Link_type)__it._M_node;
            _Link_type __L = _S_left(__x);
            _Link_type __R = _S_right(__x);

            // 无两个连续的红色节点
            if (__x->_M_color == _S_rb_tree_red)
                if ((__L && __L->_M_color == _S_rb_tree_red) ||
                    (__R && __R->_M_color == _S_rb_tree_red))
                    return false;
            // 判断节点大小正确性
            if (__L && _M_key_compare(_S_key(__x), _S_key(__L)))
                return false;
            if (__R && _M_key_compare(_S_key(__R), _S_key(__x)))
                return false;
            // 若是叶子结点 判断层数是否正确
            if (!__L && !__R && __black_count(__x, _M_root()) != __len)
                return false;
        }
        // 验证header连接的头尾节点是否正确
        if (_M_leftmost() != _Rb_tree_node_base::_S_minimum(_M_root()))
            return false;
        if (_M_rightmost() != _Rb_tree_node_base::_S_maximum(_M_root()))
            return false;

        return true;
    }
}
#endif
