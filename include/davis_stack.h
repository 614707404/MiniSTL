#ifndef DAVIS_STACK_H
#define DAVIS_STACK_H
#include "davis_deque.h"
namespace davis{
    template <class _Tp, class _Container = davis::deque<_Tp>>
    class stack;

    template <class _Tp, class _Con>
    bool operator==(const stack<_Tp, _Con> &__x, const stack<_Tp, _Con> &__y);

    template <class _Tp, class _Con>
    bool operator<(const stack<_Tp, _Con> &__x, const stack<_Tp, _Con> &__y);

    template <class _Tp, class _Container>
    class stack{
        template <class _Tp1, class _Con>
        friend bool operator==(const stack<_Tp1, _Con> &, const stack<_Tp1, _Con> &);
        template <class _Tp1, class _Con>
        friend bool operator<(const stack<_Tp1, _Con> &, const stack<_Tp1, _Con> &);

    public:
        typedef _Container                      container_type;
        typedef _Container::value_type          value_type;
        typedef _Container::reference           reference;
        typedef _Container::const_reference     const_reference;
        typedef _Container::size_type           size_type;
    protected:
        container_type _M_container;
    public:
        stack() : _M_container() {}
        explicit stack(const container_type &__c) : _M_container(__c) {}
        bool empty() const { return _M_container.empty(); }
        size_type size() const { return _M_container.size(); }
        reference top() const { return _M_container.back(); }
        const_reference top() const { return _M_container.back(); }
        void push(const value_type& __val) { _M_container.push_back(__val); }
        void pop() { _M_container.pop_back(); }
    };
    template <class _Tp, class _Con>
    bool operator==(const stack<_Tp,_Con>& __x, const stack<_Tp,_Con>& __y){
        return __x._M_container == __y._M_container;
    }
    template <class _Tp, class _Con>
    bool operator<(const stack<_Tp, _Con> &__x, const stack<_Tp, _Con> &__y)
    {
        return __x._M_container < __y._M_container;
    }
    template <class _Tp, class _Con>
    bool operator!=(const stack<_Tp, _Con> &__x, const stack<_Tp, _Con> &__y)
    {
        return !(__x == __y);
    }
    template <class _Tp, class _Con>
    bool operator>(const stack<_Tp, _Con> &__x, const stack<_Tp, _Con> &__y)
    {
        return !(__x < __y);
    }
    template <class _Tp, class _Con>
    bool operator>=(const stack<_Tp, _Con> &__x, const stack<_Tp, _Con> &__y)
    {
        return !(__x < __y);
    }
    template <class _Tp, class _Con>
    bool operator<=(const stack<_Tp, _Con> &__x, const stack<_Tp, _Con> &__y)
    {
        return !(__x > __y);
    }
}
#endif