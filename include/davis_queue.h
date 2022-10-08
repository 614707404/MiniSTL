#ifndef DAVIS_QUEUE_H
#define DAVIS_QUEUE_H
#include "davis_deque.h"
#include "davis_algorithm.h"
#include "davis_vector.h"
namespace davis
{
    template <class _Tp, class _Container = davis::deque<_Tp>>
    class queue;

    template <class _Tp, class _Con>
    bool operator==(const queue<_Tp, _Con> &__x, const queue<_Tp, _Con> &__y);

    template <class _Tp, class _Con>
    bool operator<(const queue<_Tp, _Con> &__x, const queue<_Tp, _Con> &__y);

    template <class _Tp, class _Container>
    class queue
    {
        template <class _Tp1, class _Con>
        friend bool operator==(const queue<_Tp1, _Con> &, const queue<_Tp1, _Con> &);
        template <class _Tp1, class _Con>
        friend bool operator<(const queue<_Tp1, _Con> &, const queue<_Tp1, _Con> &);

    public:
        typedef _Container container_type;
        typedef _Container::value_type value_type;
        typedef _Container::reference reference;
        typedef _Container::const_reference const_reference;
        typedef _Container::size_type size_type;

    protected:
        container_type _M_container;

    public:
        queue() : _M_container() {}
        explicit queue(const container_type &__c) : _M_container(__c) {}
        bool empty() const { return _M_container.empty(); }
        size_type size() const { return _M_container.size(); }
        reference front() const { return _M_container.front(); }
        const_reference front() const { return _M_container.front(); }
        reference back() const { return _M_container.back(); }
        const_reference back() const { return _M_container.back(); }
        void push(const value_type &__val) { _M_container.push_back(__val); }
        void pop() { _M_container.pop_front(); }
    };
    template <class _Tp, class _Con>
    bool operator==(const queue<_Tp, _Con> &__x, const queue<_Tp, _Con> &__y)
    {
        return __x._M_container == __y._M_container;
    }
    template <class _Tp, class _Con>
    bool operator<(const queue<_Tp, _Con> &__x, const queue<_Tp, _Con> &__y)
    {
        return __x._M_container < __y._M_container;
    }
    template <class _Tp, class _Con>
    bool operator!=(const queue<_Tp, _Con> &__x, const queue<_Tp, _Con> &__y)
    {
        return !(__x == __y);
    }
    template <class _Tp, class _Con>
    bool operator>(const queue<_Tp, _Con> &__x, const queue<_Tp, _Con> &__y)
    {
        return !(__x < __y);
    }
    template <class _Tp, class _Con>
    bool operator>=(const queue<_Tp, _Con> &__x, const queue<_Tp, _Con> &__y)
    {
        return !(__x < __y);
    }
    template <class _Tp, class _Con>
    bool operator<=(const queue<_Tp, _Con> &__x, const queue<_Tp, _Con> &__y)
    {
        return !(__x > __y);
    }


    // priority_queue
    template <class _Tp, class _Container = davis::vector<_Tp>, class _Compare = davis::less<typename _Container::value_type>>
    class priority_queue{
    public:
        typedef typename _Container::value_type         value_type;
        typedef typename _Container::size_type          size_type;
        typedef _Container                              container_type;
        typedef typename _Container::reference          reference;
        typedef typename _Container::const_reference    const_reference;
    protected:
        _Compare _M_compare;
        _Container _M_container;
    public:
        priority_queue() : _M_container() {}
        explicit priority_queue(const _Compare &__x) : _M_container(), _M_compare(__x) {}
        priority_queue(const _Compare &__x, const _Container &__s)
            : _M_container(__s), _M_compare(__x)
        {
            make_heap(_M_container.begin(), _M_container.end(), _M_compare);
        }
        template <class _InputIterator>
        priority_queue(_InputIterator __first, _InputIterator __last)
            : _M_container(__first, __last)
        {
            make_heap(_M_container.begin(), _M_container.end(), _M_compare);
        }

        template <class _InputIterator>
        priority_queue(_InputIterator __first,
                       _InputIterator __last, const _Compare &__x)
            : _M_container(__first, __last), _M_compare(__x)
        {
            make_heap(_M_container.begin(), _M_container.end(), _M_compare);
        }

        template <class _InputIterator>
        priority_queue(_InputIterator __first, _InputIterator __last,
                       const _Compare &__x, const _Container &__s)
            : _M_container(__s), _M_compare(__x)
        {
            _M_container.insert(_M_container.end(), __first, __last);
            make_heap(_M_container.begin(), _M_container.end(), _M_compare);
        }
        bool empty() const { return _M_container.empty(); }
        size_type size() const { return _M_container.size(); }
        const_reference top() const { return _M_container.front(); } 
        void push(const value_type &__x)
        {
            try
            {
                _M_container.push_back(__x);        
                push_heap(_M_container.begin(), _M_container.end(), __comp); 
            }
            catch(...){
                _M_container.clear();
            }
        }
        void pop()
        {
            try
            {
                pop_heap(_M_container.begin(), _M_container.end(), __comp);
                _M_container.pop_back();
            }
            catch (...)
            {
                _M_container.clear();
            }
        }
    };
}
#endif