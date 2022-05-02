#ifndef DAVIS_SET_H
#define DAVIS_SET_H
#include "davis_rbtree.h"
namespace davis
{
    template <class _Key, class _Compare = std::less<_Key>,
              class _Alloc = davis::allocator<__rbtree_node<_Key>>>
    class multiset
    {
    public:
        typedef _Key key_type;
        typedef _Key value_type;
        typedef _Compare key_compare;
        typedef _Compare value_compare;

    private:
        typedef rbtree<key_type, value_type,
                       std::_Identity<value_type>, key_compare, _Alloc>
            _Rep_type;

        _Rep_type _M_t;

    public:
        typedef typename _Rep_type::const_pointer pointer;
        typedef typename _Rep_type::const_pointer const_pointer;
        typedef typename _Rep_type::const_reference reference;
        typedef typename _Rep_type::const_reference const_reference;
        typedef typename _Rep_type::const_iterator iterator;
        typedef typename _Rep_type::const_iterator const_iterator;
        // TODO reverse_iterator
        // typedef typename _Rep_type::const_reverse_iterator              reverse_iterator;
        // typedef typename _Rep_type::const_reverse_iterator              const_reverse_iterator;
        typedef typename _Rep_type::size_type size_type;
        typedef typename _Rep_type::difference_type difference_type;
        typedef typename _Rep_type::allocator_type allocator_type;
        multiset() : _M_t(_Compare()) {}
        explicit multiset(const _Compare &__comp) : _M_t(__comp) {}
        template <class _InputIterator>
        multiset(_InputIterator __first, _InputIterator __last) : _M_t(_Compare())
        {
            _M_t.insert_equal(__first, __last);
        }
        template <class _InputIterator>
        multiset(_InputIterator __first, _InputIterator __last, const _Compare &__comp)
            : _M_t(__comp)
        {
            _M_t.insert_equal(__first, __last);
        }
        multiset(const multiset<_Key, _Compare, _Alloc> &__x) : _M_t(__x._M_t) {}
        multiset<_Key, _Compare, _Alloc> &operator=(const multiset<_Key, _Compare, _Alloc> &__x)
        {
            _M_t = __x._M_t;
            return *this;
        }

        key_compare key_comp() const { return _M_t.key_comp(); }
        value_compare value_comp() const { return _M_t.key_comp(); }
        allocator_type get_allocator() const { return _M_t.get_allocator(); }
        iterator begin() const { return _M_t.begin(); }
        iterator end() const { return _M_t.end(); }
        // TODO reverse_iterator
        // reverse_iterator rbegin() const { return _M_t.rbegin(); }
        // reverse_iterator rend() const { return _M_t.rend(); }
        bool empty() const { return _M_t.empty(); }
        size_type size() const { return _M_t.size(); }
        size_type max_size() const { return _M_t.max_size(); }
        void swap(multiset<_Key, _Compare, _Alloc> &__x) { _M_t.swap(__x._M_t); }

        std::pair<iterator, bool> insert(const value_type &__x)
        {
            std::pair<typename _Rep_type::iterator, bool> __p = _M_t.insert_equal(__x);
            return std::pair<iterator, bool>(__p.first, __p.second);
        }
        iterator insert(iterator __position, const value_type &__x)
        {
            typedef typename _Rep_type::iterator _Rep_iterator;
            return _M_t.insert_equal((_Rep_iterator &)__position, __x);
        }
        template <class _InputIterator>
        void insert(_InputIterator __first, _InputIterator __last)
        {
            _M_t.insert_equal(__first, __last);
        }
        void erase(iterator __position)
        {
            typedef typename _Rep_type::iterator _Rep_iterator;
            _M_t.erase((_Rep_iterator &)__position);
        }
        size_type erase(const key_type &__x)
        {
            return _M_t.erase(__x);
        }
        void erase(iterator __first, iterator __last)
        {
            typedef typename _Rep_type::iterator _Rep_iterator;
            _M_t.erase((_Rep_iterator &)__first, (_Rep_iterator &)__last);
        }
        void clear() { _M_t.clear(); }

        iterator find(const key_type &__x) const { return _M_t.find(__x); }
        size_type count(const key_type &__x) const
        {
            return _M_t.find(__x) == _M_t.end() ? 0 : 1;
        }
        iterator lower_bound(const key_type &__x) const
        {
            return _M_t.lower_bound(__x);
        }
        iterator upper_bound(const key_type &__x) const
        {
            return _M_t.upper_bound(__x);
        }
        std::pair<iterator, iterator> equal_range(const key_type &__x) const
        {
            return _M_t.equal_range(__x);
        }
    };
    template <class _Key, class _Compare, class _Alloc>
    inline bool operator==(const multiset<_Key, _Compare, _Alloc> &__x,
                           const multiset<_Key, _Compare, _Alloc> &__y)
    {
        return __x._M_t == __y._M_t;
    }

    template <class _Key, class _Compare, class _Alloc>
    inline bool operator<(const multiset<_Key, _Compare, _Alloc> &__x,
                          const multiset<_Key, _Compare, _Alloc> &__y)
    {
        return __x._M_t < __y._M_t;
    }
    template <class _Key, class _Compare, class _Alloc>
    inline bool operator!=(const multiset<_Key, _Compare, _Alloc> &__x,
                           const multiset<_Key, _Compare, _Alloc> &__y)
    {
        return !(__x == __y);
    }

    template <class _Key, class _Compare, class _Alloc>
    inline bool operator>(const multiset<_Key, _Compare, _Alloc> &__x,
                          const multiset<_Key, _Compare, _Alloc> &__y)
    {
        return __y < __x;
    }

    template <class _Key, class _Compare, class _Alloc>
    inline bool operator<=(const multiset<_Key, _Compare, _Alloc> &__x,
                           const multiset<_Key, _Compare, _Alloc> &__y)
    {
        return !(__y < __x);
    }

    template <class _Key, class _Compare, class _Alloc>
    inline bool operator>=(const multiset<_Key, _Compare, _Alloc> &__x,
                           const multiset<_Key, _Compare, _Alloc> &__y)
    {
        return !(__x < __y);
    }

    template <class _Key, class _Compare, class _Alloc>
    inline void swap(multiset<_Key, _Compare, _Alloc> &__x,
                     multiset<_Key, _Compare, _Alloc> &__y)
    {
        __x.swap(__y);
    }
}
#endif