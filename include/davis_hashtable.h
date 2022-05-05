#ifndef DAVIS_HASHTABLE_H
#define DAVIS_HASHTABLE_H
#include "davis_allocate.h"
#include "davis_iterator.h"
#include "davis_vector.h"
#include "davis_construct.h"
namespace davis{
    enum    {   num_primes = 28    };
    static const unsigned long prime_list[num_primes] =
        {
            53ul, 97ul, 193ul, 389ul, 769ul,
            1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
            49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
            1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,
            50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
            1610612741ul, 3221225473ul, 4294967291ul};
    inline unsigned long next_prime(unsigned long __n)
    {
        const unsigned long *__first = prime_list;
        const unsigned long *__last = prime_list + (int)num_primes;
        const unsigned long *pos = std::lower_bound(__first, __last, __n);
        return pos == __last ? *(__last - 1) : *pos;
    }
    template <class _Tp>
    struct hashtable_node
    {
        hashtable_node* _M_next;
        _Tp _M_val;
    };
    template <class _Val, class _Key, class _HashFcn,
              class _ExtractKey, class _EqualKey, class _Alloc = davis::allocator<hashtable_node<_Val>>>
    class hashtable;

    template <class _Val, class _Key, class _HashFcn,
              class _ExtractKey, class _EqualKey, class _Alloc>
    struct hashtable_iterator;
    template <class _Val, class _Key, class _HashFcn,
              class _ExtractKey, class _EqualKey, class _Alloc>
    struct hashtable_const_iterator;

    template <class _Val, class _Key, class _HashFcn,
              class _ExtractKey, class _EqualKey, class _Alloc>
    struct hashtable_iterator
    {
        typedef hashtable<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>
            ht;
        typedef hashtable_iterator<_Val, _Key, _HashFcn,
                                   _ExtractKey, _EqualKey, _Alloc>
            iterator;
        typedef hashtable_node<_Val>                    _Node;
        typedef davis::forward_iterator_tag             iterator_category; 
        typedef _Val                                    value_type;
        typedef ptrdiff_t                               difference_type;
        typedef size_t                                  size_type;
        typedef _Val&                                   reference;
        typedef _Val*                                   pointer;

        _Node*          _M_cur;
        ht *_M_ht;
        hashtable_iterator(){}
        hashtable_iterator( _Node *__p, ht *__ht) : _M_cur(__p), _M_ht(__ht) {}
        reference operator*()const { return _M_cur->_M_val; }
        pointer operator->() const {return &(operator*());  }
        iterator& operator++();
        iterator operator++(int);
        bool operator==(const iterator &it) const { return _M_cur == it._M_cur; }
        bool operator!=(const iterator &it) const { return _M_cur != it._M_cur; }
    };
    template <class _Val, class _Key, class _HashFcn,
              class _ExtractKey, class _EqualKey, class _Alloc>
    struct hashtable_const_iterator
    {
        typedef hashtable<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>
            ht;
        typedef hashtable_iterator<_Val, _Key, _HashFcn,
                                   _ExtractKey, _EqualKey, _Alloc>
            iterator;
        typedef hashtable_const_iterator<_Val, _Key, _HashFcn,
                                   _ExtractKey, _EqualKey, _Alloc>
            const_iterator;
        typedef hashtable_node<_Val> _Node;
        typedef davis::forward_iterator_tag iterator_category;
        typedef _Val value_type;
        typedef ptrdiff_t difference_type;
        typedef size_t size_type;
        typedef const _Val &reference;
        typedef const _Val *pointer;

        _Node *_M_cur;
        ht *_M_ht;
        hashtable_const_iterator() {}
        hashtable_const_iterator(const _Node *__p, const ht *__ht) : _M_cur(__p), _M_ht(__ht) {}
        hashtable_const_iterator(const iterator &__it)
            : _M_cur(__it._M_cur), _M_ht(__it._M_ht) {}
        reference operator*() const { return _M_cur->_M_val; }
        pointer operator->() const { return &(operator*()); }
        const_iterator &operator++();
        const_iterator operator++(int);
        bool operator==(const const_iterator &it) const { return _M_cur == it._M_cur; }
        bool operator!=(const const_iterator &it) const { return _M_cur != it._M_cur; }
    };
    template <class _Val, class _Key, class _HashFcn, class _ExtractKey,
              class _EqualKey, class _Alloc>
    class hashtable
    {
    public:
        typedef _Key                                            key_type;
        typedef _Val                                            value_type;
        typedef _HashFcn                                        hasher;
        typedef _EqualKey                                       key_equal;
        typedef size_t                                          size_type;
        typedef ptrdiff_t                                       difference_type;
        typedef value_type *                                    pointer;
        typedef const value_type *                              const_pointer;
        typedef value_type &                                    reference;
        typedef const value_type &                              const_reference;
        typedef _Alloc                                          allocator_type;
        

    private:
        typedef hashtable_node<_Val>                            _Node;

    private:
        hasher                  _M_hasher;
        key_equal               _M_equals;
        _ExtractKey             _M_get_key;
        davis::vector<_Node*>    _M_buckets;
        size_type               _M_num_elements;

    private:
        allocator_type _M_node_allocator;
        _Node *_M_get_node() { return _M_node_allocator.allocate(1); }
        void _M_put_node(_Node* __p) { _M_node_allocator.deallocate(__p, 1); }

    public:
        allocator_type get_allocator() const { return _M_node_allocator; }
        hasher hash_function() const { return _M_hasher; }
        key_equal key_eq() const { return _M_equals; }

    public:
        typedef hashtable_iterator<_Val, _Key, _HashFcn,
                                   _ExtractKey, _EqualKey, _Alloc>
            iterator;
        typedef hashtable_const_iterator<_Val, _Key, _HashFcn,
                                         _ExtractKey, _EqualKey, _Alloc>
            const_iterator;
        friend struct
            hashtable_iterator<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>;
        friend struct
            hashtable_const_iterator<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>;

    public:
        hashtable(size_type __n,
                  const _HashFcn &__hf,
                  const _EqualKey &__eql,
                  const _ExtractKey &__ext,
                  const allocator_type &__a = allocator_type())
            : _M_node_allocator(__a),
              _M_hasher(__hf),
              _M_equals(__eql),
              _M_get_key(__ext),
              _M_num_elements(0)
        {
            _M_initialize_buckets(__n);
        }
        hashtable(size_type __n,
                  const _HashFcn &__hf,
                  const _EqualKey &__eql,
                  const allocator_type &__a = allocator_type())
            : _M_node_allocator(__a),
              _M_hasher(__hf),
              _M_equals(__eql),
              _M_get_key(_ExtractKey()),
              _M_num_elements(0)
        {
            _M_initialize_buckets(__n);
        }
        hashtable(const hashtable &__ht)
            : _M_node_allocator(__ht.get_allocator()),
              _M_hasher(__ht._M_hasher),
              _M_equals(__ht._M_equals),
              _M_get_key(__ht._M_get_key),
              _M_num_elements(__ht._M_num_elements)
        {
            _M_copy_from(__ht);
        }
        hashtable &operator=(const hashtable &__ht)
        {
            if (&__ht != this)
            {
                clear();
                _M_hasher = __ht._M_hasher;
                _M_equals = __ht._M_equals;
                _M_get_key = __ht._M_get_key;
                _M_copy_from(__ht);
            }
            return *this;
        }
        ~hashtable() { clear(); }

        size_type size() const { return _M_num_elements; }
        size_type max_size() const { return size_type(-1); }
        bool empty() const { return size() == 0; }

        void swap(hashtable &__ht)
        {
            std::swap(_M_hasher, __ht._M_hasher);
            std::swap(_M_equals, __ht._M_equals);
            std::swap(_M_get_key, __ht._M_get_key);
            _M_buckets.swap(__ht._M_buckets);
            std::swap(_M_num_elements, __ht._M_num_elements);
        }
        iterator begin(){
            for(size_type __i = 0 ; __i < _M_buckets.size() ; __i++){
                if(_M_buckets[__i]){
                    return iterator(_M_buckets[__i], this);
                }
            }
            return end();
        }
        const_iterator begin() const
        {
            for (size_type __i = 0; __i < _M_buckets.size(); __i++)
            {
                if (_M_buckets[__i])
                {
                    return const_iterator(_M_buckets[__i], this);
                }
            }
            return end();
        }
        iterator end() { return iterator(0, this); }
        const_iterator end() const { return const_iterator(0, this); }

        template <class _Vl, class _Ky, class _HF, class _Ex, class _Eq, class _Al>
        friend bool operator==(const hashtable<_Vl, _Ky, _HF, _Ex, _Eq, _Al> &,
                               const hashtable<_Vl, _Ky, _HF, _Ex, _Eq, _Al> &);

        size_type bucket_count() { return _M_buckets.size(); }
        size_type max_bucket_count() { return prime_list[(int)num_primes-1]; }
        size_type elems_in_bucket(size_type __bucket) const {
            size_type __result=0;
            for(_Node* __cur=_M_buckets[__bucket];__cur;__cur=__cur->_M_next,__result++){}
            return __result;
        }

        std::pair<iterator, bool> insert_unique_noresize(const value_type &__obj);
        // std::pair<const_iterator, bool> insert_unique_noresize(const value_type &__obj) const;
        iterator insert_equal_noresize(const value_type &__obj);

        std::pair<iterator, bool> insert_unique(const value_type &__obj)
        {
            resize(_M_num_elements + 1);
            return insert_unique_noresize(__obj);
        }
        // std::pair<const_iterator, bool> insert_unique(const value_type &__obj) const
        // {
        //     resize(_M_num_elements + 1);
        //     return insert_unique_noresize(__obj);
        // }
        iterator insert_equal(const value_type &__obj)
        {
            resize(_M_num_elements + 1);
            return insert_equal_noresize(__obj);
        }

        template <class _InputIterator>
        void insert_unique(_InputIterator __f, _InputIterator __l)
        {
            insert_unique(__f, __l, davis::iterator_category(__f));
        }

        template <class _InputIterator>
        void insert_equal(_InputIterator __f, _InputIterator __l)
        {
            insert_equal(__f, __l, davis::iterator_category(__f));
        }

        template <class _InputIterator>
        void insert_unique(_InputIterator __f, _InputIterator __l,
                           davis::input_iterator_tag)
        {
            for (; __f != __l; ++__f)
                insert_unique(*__f);
        }

        template <class _InputIterator>
        void insert_equal(_InputIterator __f, _InputIterator __l,
                          davis::input_iterator_tag)
        {
            for (; __f != __l; ++__f)
                insert_equal(*__f);
        }

        template <class _ForwardIterator>
        void insert_unique(_ForwardIterator __f, _ForwardIterator __l,
                           davis::forward_iterator_tag)
        {
            size_type __n = davis::distance(__f, __l);
            resize(_M_num_elements + __n);
            for (; __n > 0; --__n, ++__f)
                insert_unique_noresize(*__f);
        }

        template <class _ForwardIterator>
        void insert_equal(_ForwardIterator __f, _ForwardIterator __l,
                          davis::forward_iterator_tag)
        {
            size_type __n = davis::distance(__f, __l);
            resize(_M_num_elements + __n);
            for (; __n > 0; --__n, ++__f)
                insert_equal_noresize(*__f);
        }
        
        iterator find(const key_type &__key);

        const_iterator find(const key_type &__key) const;

        size_type count(const key_type &__key) const;
        
        reference find_or_insert(const value_type &__obj);

        std::pair<iterator, iterator> equal_range(const key_type &__key);

        std::pair<const_iterator, const_iterator> equal_range(const key_type &__key) const;

        size_type erase(const key_type &__key);
        void erase(const iterator &__it);
        void erase(iterator __first, iterator __last);

        void erase(const const_iterator &__it);
        void erase(const_iterator __first, const_iterator __last);

        void resize(size_type __num_elements_hint);
        void clear();
    private:
        size_type _M_next_size(size_type __n) const {  return next_prime(__n);  }
        void _M_initialize_buckets(size_type __n)
        {
            const size_type __n_buckets = _M_next_size(__n);
            _M_buckets.reserve(__n_buckets);
            _M_buckets.insert(_M_buckets.end(), __n_buckets, (_Node *)0);
            _M_num_elements = 0;
        }

        size_type _M_bkt_num_key(const key_type &__key) const
        {
            return _M_bkt_num_key(__key, _M_buckets.size());
        }
        size_type _M_bkt_num_key(const key_type &__key, size_t __n) const
        {
            return _M_hasher(__key) % __n;
        }
        size_type _M_bkt_num(const value_type &__obj) const
        {
            return _M_bkt_num_key(_M_get_key(__obj));
        }
        size_type _M_bkt_num(const value_type &__obj, size_t __n) const
        {
            return _M_bkt_num_key(_M_get_key(__obj), __n);
        }

        _Node *_M_new_node(const value_type &__obj)
        {
            _Node *__n = _M_get_node();
            __n->_M_next = 0;
            try
            {
                davis::construct(&__n->_M_val, __obj);
                return __n;
            }
            catch(...){
                _M_put_node(__n);
            }
            return __n;
        }

        void _M_delete_node(_Node *__n)
        {
            davis::destroy(&__n->_M_val);
            _M_put_node(__n);
        }
        void _M_erase_bucket(const size_type __n, _Node *__first, _Node *__last);
        void _M_erase_bucket(const size_type __n, _Node *__last);
        void _M_copy_from(const hashtable &__ht);
    };
    template <class _Val, class _Key, class _HashFcn,
              class _ExtractKey, class _EqualKey, class _Alloc>
    std::pair<typename hashtable<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>::iterator, bool>
    hashtable<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>::insert_unique_noresize(const value_type &__obj)
    {
        size_type __bucket = _M_bkt_num(__obj);
        _Node *__first = _M_buckets[__bucket];
        for(_Node* __cur = __first; __cur ; __cur=__cur->_M_next){
            if (_M_equals(_M_get_key(__cur->_M_val), _M_get_key(__obj)))
                return std::pair<iterator,bool>(iterator(__cur,this),false);
        }
        _Node *__tmp = _M_new_node(__obj);
        __tmp->_M_next=__first;
        _M_buckets[__bucket]=__tmp;
        ++_M_num_elements;
        return std::pair<iterator, bool>(iterator(__tmp, this), true);
    }
    template <class _Val, class _Key, class _HashFcn,
              class _ExtractKey, class _EqualKey, class _Alloc>
    typename hashtable<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>::iterator
    hashtable<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>::insert_equal_noresize(const value_type &__obj)
    {
        size_type __bucket = _M_bkt_num(__obj);
        _Node *__first = _M_buckets[__bucket];
        for (_Node *__cur = __first; __cur; __cur = __cur->_M_next)
        {
            if (_M_equals(_M_get_key(__cur->_M_val), _M_get_key(__obj))){
                _Node *__tmp = _M_new_node(__obj);
                __tmp->_M_next = __cur->_M_next;
                __cur->_M_next = __tmp;
                ++_M_num_elements;
                return iterator(__tmp, this);
            }
        }
        _Node *__tmp = _M_new_node(__obj);
        __tmp->_M_next = __first;
        _M_buckets[__bucket] = __tmp;
        ++_M_num_elements;
        return iterator(__tmp, this);
    }
    template <class _Val, class _Key, class _HashFcn,
              class _ExtractKey, class _EqualKey, class _Alloc>
    typename hashtable<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>::iterator
    hashtable<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>::find(const key_type &__key){
        size_type __bucket = _M_bkt_num_key(__key);
        _Node* __first = _M_buckets[__bucket];
        for (; __first && !_M_equals(_M_get_key(__first->_M_val), __key);
             __first = __first->_M_next){}
        return iterator(__first,this);
    }
    template <class _Val, class _Key, class _HashFcn,
              class _ExtractKey, class _EqualKey, class _Alloc>
    typename hashtable<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>::const_iterator
    hashtable<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>::find(const key_type &__key) const
    {
        size_type __bucket = _M_bkt_num_key(__key);
        _Node *__first = _M_buckets[__bucket];
        for (; __first && !_M_equals(_M_get_key(__first->_M_val), __key);
             __first = __first->_M_next)
        {
        }
        return const_iterator(__first, this);
    }
    template <class _Val, class _Key, class _HashFcn,
              class _ExtractKey, class _EqualKey, class _Alloc>
    typename hashtable<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>::size_type
    hashtable<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>::count(const key_type &__key) const
    {
        size_type __bucket = _M_bkt_num_key(__key);
        size_type __result=0;
        for (_Node *__cur = _M_buckets[__bucket];
             __cur;
             __cur = __cur->_M_next)
        {
            if (_M_equals(_M_get_key(__cur->_M_val), __key)){
                __result++;
            }
        }
        return __result;
    }
    template <class _Val, class _Key, class _HashFcn,
              class _ExtractKey, class _EqualKey, class _Alloc>
    typename hashtable<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>::reference
    hashtable<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>::find_or_insert(const value_type &__obj)
    {
        resize(_M_num_elements+1);
        size_type __bucket = _M_bkt_num(__obj);
        _Node* __first = _M_buckets[__bucket];
        for (const _Node *__cur = __first ; __cur ; ++__cur){
            if (_M_equals(_M_get_key(__obj), _M_get_key(__cur->_M_val)))
                return const_cast<reference>(__cur->_M_val);
        }
        _Node *__tmp = _M_new_node(__obj);
        __tmp->_M_next = _M_buckets[__bucket];
        _M_buckets[__bucket] = __tmp;
        ++_M_num_elements;
        return __tmp->_M_val;
    }
    template <class _Val, class _Key, class _HashFcn,
              class _ExtractKey, class _EqualKey, class _Alloc>
    std::pair<typename hashtable<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>::iterator,
              typename hashtable<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>::iterator>
    hashtable<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>::equal_range(const key_type &__key)
    {
        typedef std::pair<iterator, iterator> _Pii;
        size_type __bucket = _M_bkt_num_key(__key);
        for(const _Node* __first = _M_buckets[__bucket] ;__first;++__first){
            if(_M_equals(__key,_M_get_key(__first->_M_val))){
                for(const _Node* __cur = __first->_M_next ;__cur;++__cur){
                    if (!_M_equals(__key, _M_get_key(__cur->_M_val)))
                    {
                        return _Pii(iterator(__first,this),iterator(__cur,this));
                    }
                }
                for(size_type __nxt=__bucket+1;__nxt<_M_buckets.size();++__nxt){
                    if(_M_buckets[__nxt]){
                        return _Pii(iterator(__first, this), iterator(_M_buckets[__nxt], this));
                    }
                }
                return _Pii(iterator(__first, this), iterator(end(), this));
            }
        }
        return _Pii(iterator(end(), this), iterator(end(), this));
    }
    template <class _Val, class _Key, class _HashFcn,
              class _ExtractKey, class _EqualKey, class _Alloc>
    std::pair<typename hashtable<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>::const_iterator,
              typename hashtable<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>::const_iterator>
    hashtable<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>::equal_range(const key_type &__key) const
    {
        typedef std::pair<const_iterator, const_iterator> _Pii;
        size_type __bucket = _M_bkt_num_key(__key);
        for (const _Node *__first = _M_buckets[__bucket]; __first; ++__first)
        {
            if (_M_equals(__key, _M_get_key(__first->_M_val)))
            {
                for (const _Node *__cur = __first->_M_next; __cur; ++__cur)
                {
                    if (!_M_equals(__key, _M_get_key(__cur->_M_val)))
                    {
                        return _Pii(const_iterator(__first, this), const_iterator(__cur, this));
                    }
                }
                for (size_type __nxt = __bucket + 1; __nxt < _M_buckets.size(); ++__nxt)
                {
                    if (_M_buckets[__nxt])
                    {
                        return _Pii(const_iterator(__first, this), const_iterator(_M_buckets[__nxt], this));
                    }
                }
                return _Pii(const_iterator(__first, this), const_iterator(end(), this));
            }
        }
        return _Pii(const_iterator(end(), this), const_iterator(end(), this));
    }
    template <class _Val, class _Key, class _HashFcn,
              class _ExtractKey, class _EqualKey, class _Alloc>
    typename hashtable<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>::size_type
    hashtable<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>::erase(const key_type &__key)
    {
        const size_type __n = _M_bkt_num_key(__key);
        size_type __erased = 0;
        _Node* __first = _M_buckets[__n];
        if(__first){
            _Node* __cur = __first;
            _Node* __nxt = __cur->_M_next;
            while(__nxt){
                if(_M_equals(_M_get_key(__nxt->_M_val),__key)){
                    __cur->_M_next = __nxt->_M_next;
                    _M_delete_node(__nxt);
                    __nxt = __cur->_M_next;
                    ++__erased;
                    --_M_num_elements;
                }else{
                    __cur=__nxt;
                    __nxt=__nxt->_M_next;
                }
            }
            if (_M_equals(_M_get_key(__first->_M_val), __key))
            {
                _M_buckets[__n] = __first->_M_next;
                _M_delete_node(__first);
                ++__erased;
                --_M_num_elements;
            }
        }
        return __erased;
    }
    template <class _Val, class _Key, class _HashFcn,
              class _ExtractKey, class _EqualKey, class _Alloc>
    void hashtable<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>::erase(const iterator &__it)
    {
        _Node* __p = __it._M_cur;
        if(__p){
            const size_type __n = _M_bkt_num(__p->_M_val);
            _Node *__cur = _M_buckets[__n];
            if(__cur==__p){
                _M_buckets[__n]=__cur->_M_next;
                _M_delete_node(__cur);
                --_M_num_elements;
            }else{
                _Node *__next = __cur->_M_next;
                while (__next)
                {
                    if (__next == __p)
                    {
                        __cur->_M_next = __next->_M_next;
                        _M_delete_node(__next);
                        --_M_num_elements;
                        break;
                    }
                    else
                    {
                        __cur = __next;
                        __next = __cur->_M_next;
                    }
                }
            }
        }
    }
    template <class _Val, class _Key, class _HashFcn,
              class _ExtractKey, class _EqualKey, class _Alloc>
    void hashtable<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>::erase(iterator __first, iterator __last)
    {
        size_type __f_bucket = __first._M_cur ? _M_bkt_num(__first._M_cur->_M_val) : _M_buckets.size();
        size_type __l_bucket = __last._M_cur ? _M_bkt_num(__last._M_cur->_M_val) : _M_buckets.size();

        if (__first._M_cur == __last._M_cur)
            return;
        else if (__f_bucket == __l_bucket)
            _M_erase_bucket(__f_bucket, __first._M_cur, __last._M_cur);
        else
        {
            _M_erase_bucket(__f_bucket, __first._M_cur, 0);
            for (size_type __n = __f_bucket + 1; __n < __l_bucket; ++__n)
                _M_erase_bucket(__n, 0);
            if (__l_bucket != _M_buckets.size())
                _M_erase_bucket(__l_bucket, __last._M_cur);
        }
    }
    template <class _Val, class _Key, class _HashFcn,
              class _ExtractKey, class _EqualKey, class _Alloc>
    void hashtable<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>::erase(const const_iterator &__it)
    {
        erase(iterator(const_cast<_Node *>(__it._M_cur),
                       const_cast<hashtable *>(__it._M_ht)));
    }
    template <class _Val, class _Key, class _HashFcn,
              class _ExtractKey, class _EqualKey, class _Alloc>
    void hashtable<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>::erase(const_iterator __first, const_iterator __last)
    {
        erase(iterator(const_cast<_Node *>(__first._M_cur),
                       const_cast<hashtable *>(__first._M_ht)),
              iterator(const_cast<_Node *>(__last._M_cur),
                       const_cast<hashtable *>(__last._M_ht)));
    }
    template <class _Val, class _Key, class _HashFcn,
              class _ExtractKey, class _EqualKey, class _Alloc>
    void hashtable<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>::resize(size_type __num_elements_hint)
    {
        size_type __old_size = _M_buckets.size();
        if(__num_elements_hint > __old_size){
            size_type __n = _M_next_size(__num_elements_hint);
            if(__n > __old_size){
                davis::vector<_Node*> __tmp(__n,(_Node*)(0));
                try
                {
                    for(size_type __bucket = 0 ; __bucket < __old_size ; ++__bucket){
                        _Node* __fisrt = _M_buckets[__bucket];
                        while(__fisrt){
                            size_type __new_bucket = _M_bkt_num(__fisrt->_M_val,__n);
                            _M_buckets[__bucket] = __fisrt->_M_next;
                            __fisrt->_M_next = __tmp[__new_bucket];
                            __tmp[__new_bucket] = __fisrt;
                            __fisrt = _M_buckets[__bucket];
                        }
                    }
                    _M_buckets.swap(__tmp);
                }
                catch(...)
                {
                    for (size_type __bucket = 0; __bucket < __tmp.size(); ++__bucket)
                    {
                        while (__tmp[__bucket])
                        {
                            _Node *__next = __tmp[__bucket]->_M_next;
                            _M_delete_node(__tmp[__bucket]);
                            __tmp[__bucket] = __next;
                        }
                    }
                    throw;
                }
                
            }
        }
    }
    template <class _Val, class _Key, class _HashFcn,
              class _ExtractKey, class _EqualKey, class _Alloc>
    void hashtable<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>::clear()
    {
        for(size_type __n=0;__n<_M_buckets.size();++__n){
            _Node* __cur = _M_buckets[__n];
            while (__cur)
            {
                _Node* __nxt = __cur->_M_next;
                _M_delete_node(__cur);
                __cur=__nxt;
            }
            _M_buckets[__n] = 0;
        }
        _M_num_elements = 0;
    }
    template <class _Val, class _Key, class _HashFcn,
              class _ExtractKey, class _EqualKey, class _Alloc>
    void hashtable<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>::_M_erase_bucket(const size_type __n, _Node *__first, _Node *__last)
    {
        _Node *__cur = _M_buckets[__n];
        if (__cur == __first)
            _M_erase_bucket(__n, __last);
        else
        {
            _Node *__next;
            for (__next = __cur->_M_next;
                 __next != __first;
                 __cur = __next, __next = __cur->_M_next)
                ;
            while (__next != __last)
            {
                __cur->_M_next = __next->_M_next;
                _M_delete_node(__next);
                __next = __cur->_M_next;
                --_M_num_elements;
            }
        }
    }
    template <class _Val, class _Key, class _HashFcn,
              class _ExtractKey, class _EqualKey, class _Alloc>
    void hashtable<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>::_M_erase_bucket(const size_type __n, _Node *__last)
    {
        _Node *__cur = _M_buckets[__n];
        while (__cur != __last)
        {
            _Node *__next = __cur->_M_next;
            _M_delete_node(__cur);
            __cur = __next;
            _M_buckets[__n] = __cur;
            --_M_num_elements;
        }
    }
    template <class _Val, class _Key, class _HashFcn,
              class _ExtractKey, class _EqualKey, class _Alloc>
    void hashtable<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>::_M_copy_from(const hashtable &__ht)
    {
        _M_buckets.clear();
        _M_buckets.reserve(__ht._M_buckets.size());
        _M_buckets.insert(_M_buckets.end(), __ht._M_buckets.size(), (_Node *)0);
        try
        {
            for (size_type __i = 0; __i < __ht._M_buckets.size(); ++__i)
            {
                const _Node *__cur = __ht._M_buckets[__i];
                if (__cur)
                {
                    _Node *__copy = _M_new_node(__cur->_M_val);
                    _M_buckets[__i] = __copy;

                    for (_Node *__next = __cur->_M_next;
                         __next;
                         __cur = __next, __next = __cur->_M_next)
                    {
                        __copy->_M_next = _M_new_node(__next->_M_val);
                        __copy = __copy->_M_next;
                    }
                }
            }
            _M_num_elements = __ht._M_num_elements;
        }
        catch(...){
            clear();
        }
    }

    template <class _Val, class _Key, class _HashFcn,
              class _ExtractKey, class _EqualKey, class _Alloc>
    typename hashtable_iterator<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>::iterator&
    hashtable_iterator<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>::operator++()
    {
        const _Node* old_node = _M_cur;
        _M_cur = _M_cur->next;
        if (!_M_cur){
            size_type __bucket = _M_ht->_M_bkt_num(old_node->_M_val);
            while (!_M_cur && ++__bucket < _M_ht->_M_buckets.size())
                _M_cur = _M_ht->_M_buckets[__bucket];
        }
        return *this;
    }
    template <class _Val, class _Key, class _HashFcn,
              class _ExtractKey, class _EqualKey, class _Alloc>
    typename hashtable_iterator<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>::iterator 
    hashtable_iterator<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>::operator++(int)
    {
        iterator __tmp = *this;
        ++this;
        return __tmp;
    }
    template <class _Val, class _Key, class _HashFcn,
              class _ExtractKey, class _EqualKey, class _Alloc>
    typename hashtable_const_iterator<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>::const_iterator &
    hashtable_const_iterator<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>::operator++()
    {
        const _Node *old_node = _M_cur;
        _M_cur = _M_cur->_M_next;
        if (!_M_cur)
        {
            size_type __bucket = _M_ht->_M_bkt_num(old_node->_M_val);
            while (!_M_cur && ++__bucket < _M_ht->_M_buckets.size())
                _M_cur = _M_ht->_M_buckets[__bucket];
        }
        return *this;
    }
    template <class _Val, class _Key, class _HashFcn,
              class _ExtractKey, class _EqualKey, class _Alloc>
    typename hashtable_const_iterator<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>::const_iterator
    hashtable_const_iterator<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>::operator++(int)
    {
        const_iterator __tmp = *this;
        ++this;
        return __tmp;
    }
    template <class _Vl, class _Ky, class _HF, class _Ex, class _Eq, class _Al>
    bool operator==(const hashtable<_Vl, _Ky, _HF, _Ex, _Eq, _Al> & __x,
                    const hashtable<_Vl, _Ky, _HF, _Ex, _Eq, _Al> & __y)
    {
        typedef typename hashtable<_Vl, _Ky, _HF, _Ex, _Eq, _Al>::_Node _Node;
        if (__x.size() != __y.size())
            return false;
        if (__x._M_buckets.size() != __y._M_buckets.size())
            return false;
        for (int __bucket = 0; __bucket < __x._M_buckets.size(); ++__bucket)
        {
            _Node *__cur1 = __x._M_buckets[__bucket];
            _Node *__cur2 = __y._M_buckets[__bucket];
            for (; __cur1 && __cur2 && __cur1->_M_val == __cur2->_M_val;
                 __cur1 = __cur1->_M_next, __cur2 = __cur2->_M_next){}
            if(__cur1||__cur2){
                return false;
            }
        }
        return true;
    }
}


#endif