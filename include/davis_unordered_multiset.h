#ifndef DAVIS_UNORDERED_MULTISET_H
#define DAVIS_UNORDERED_MULTISET_H
#include "davis_hashtable.h"
#include "davis_allocate.h"
namespace davis
{
    template <class _Value,
              class _HashFcn = std::hash<_Value>,
              class _EqualKey = std::equal_to<_Value>,
              class _Alloc = davis::allocator<hashtable_node<_Value>>>
    class unordered_multiset;
    template <class _Value, class _HashFcn, class _EqualKey, class _Alloc>
    class unordered_multiset
    {
    private:
        typedef hashtable<_Value, _Value, _HashFcn, std::_Identity<_Value>, _EqualKey, _Alloc> _HT;
        _HT _M_ht;

    public:
        typedef typename _HT::key_type key_type;
        typedef typename _HT::value_type value_type;
        typedef typename _HT::hasher hasher;
        typedef typename _HT::key_equal key_equal;
        typedef typename _HT::size_type size_type;
        typedef typename _HT::difference_type difference_type;

        typedef typename _HT::const_pointer pointer;
        typedef typename _HT::const_pointer const_pointer;

        typedef typename _HT::const_reference reference;
        typedef typename _HT::const_reference const_reference;

        typedef typename _HT::const_iterator iterator;
        typedef typename _HT::const_iterator const_iterator;

        typedef typename _HT::allocator_type allocator_type;

        key_equal key_eq() const { return _M_ht.key_eq(); }
        hasher hash_function() const { return _M_ht.hash_function(); }
        allocator_type get_allocator() const { return _M_ht.get_allocator(); }

    public:
        unordered_multiset() : _M_ht(100, hasher(), key_equal()) {}
        explicit unordered_multiset(size_type __n)
            : _M_ht(__n, hasher(), key_equal()) {}
        unordered_multiset(size_type __n, const hasher &__hf)
            : _M_ht(__n, __hf, key_equal()) {}
        unordered_multiset(size_type __n, const hasher &__hf, const key_equal &__eql)
            : _M_ht(__n, __hf, __eql) {}

        // range constructor
        template <class _InputIterator>
        unordered_multiset(_InputIterator __first, _InputIterator __last)
            : _M_ht(100, hasher(), key_equal())
        {
            _M_ht.insert_equal(__first, __last);
        }
        template <class _InputIterator>
        unordered_multiset(_InputIterator __first, _InputIterator __last, size_type __n)
            : _M_ht(__n, hasher(), key_equal())
        {
            _M_ht.insert_equal(__first, __last);
        }
        template <class _InputIterator>
        unordered_multiset(_InputIterator __first, _InputIterator __last, size_type __n, const hasher &__hf)
            : _M_ht(__n, __hf, key_equal())
        {
            _M_ht.insert_equal(__first, __last);
        }
        template <class _InputIterator>
        unordered_multiset(_InputIterator __first, _InputIterator __last, size_type __n, const hasher &__hf, const key_equal &__eql)
            : _M_ht(__n, __hf, __eql)
        {
            _M_ht.insert_equal(__first, __last);
        }
        // copy
        unordered_multiset(const unordered_multiset &ust) : _M_ht(ust._M_ht) {}

        unordered_multiset &operator=(const unordered_multiset &ust)
        {
            _M_ht = ust._M_ht;
            return *this;
        }
        size_type size() const { return _M_ht.size(); }
        size_type max_size() const { return _M_ht.max_size(); }
        bool empty() const { return _M_ht.empty(); }
        void swap(unordered_multiset &ust) { _M_ht.swap(ust._M_ht); }
        iterator begin() { return _M_ht.begin(); }
        const_iterator begin() const { return _M_ht.begin(); }
        const_iterator cbegin() const { return _M_ht.begin(); }
        iterator end() { return _M_ht.end(); }
        const_iterator end() const { return _M_ht.end(); }
        const_iterator cend() const { return _M_ht.end(); }
        iterator find(const key_type &__k) { return _M_ht.find(__k); }
        const_iterator find(const key_type &__k) const { return _M_ht.find(__k); }

        size_type count(const key_type &__k) const { return _M_ht.count(__k); }

        std::pair<iterator, iterator> equal_range(const key_type &__k)
        {
            return _M_ht.equal_range(__k);
        }
        std::pair<const_iterator, const_iterator> equal_range(const key_type &__k) const
        {
            return _M_ht.equal_range(__k);
        }
        iterator insert(const value_type &__val)
        {
            typename _HT::iterator __p = _M_ht.insert_equal(__val);
            // iterator __tmp = iterator(__p.first._M_cur,__p.first._M_ht);
            return iterator(__p);
        }
        template <class InputIterator>
        void insert(InputIterator __first, InputIterator __last)
        {
            insert_equal(__first, __last);
        }
        size_type erase(const key_type &__key)
        {
            return _M_ht.erase(__key);
        }
        void erase(const iterator &__it)
        {
            _M_ht.erase(__it);
        }
        void erase(iterator __first, iterator __last)
        {
            _M_ht.erase(__first, __last);
        }
        void clear() { _M_ht.clear(); }
        size_type bucket_count() { return _M_ht.bucket_count(); }
        size_type max_bucket_count() { return _M_ht.max_bucket_count(); }
        size_type bucket_size(size_type __bucket) const { return _M_ht.elems_in_bucket(); }
        size_type bucket(const key_type &__k) const { return _M_ht._M_bkt_num_key(__k); }
        template <class Key, class Hash, class Pred, class Alloc>
        friend bool operator==(const unordered_multiset<Key, Hash, Pred, Alloc> &lhs,
                               const unordered_multiset<Key, Hash, Pred, Alloc> &rhs);
        template <class Key, class Hash, class Pred, class Alloc>
        friend bool operator!=(const unordered_multiset<Key, Hash, Pred, Alloc> &lhs,
                               const unordered_multiset<Key, Hash, Pred, Alloc> &rhs);
    };
    template <class Key, class Hash, class Pred, class Alloc>
    bool operator==(const unordered_multiset<Key, Hash, Pred, Alloc> &lhs,
                    const unordered_multiset<Key, Hash, Pred, Alloc> &rhs)
    {
        return lhs._M_ht == rhs._M_ht;
    }
    template <class Key, class Hash, class Pred, class Alloc>
    bool operator!=(const unordered_multiset<Key, Hash, Pred, Alloc> &lhs,
                    const unordered_multiset<Key, Hash, Pred, Alloc> &rhs)
    {
        return !lhs == rhs;
    }
    template <class Key, class Hash, class Pred, class Alloc>
    void swap(const unordered_multiset<Key, Hash, Pred, Alloc> &lhs,
              const unordered_multiset<Key, Hash, Pred, Alloc> &rhs)
    {
        lhs.swap(rhs);
    }
}

#endif