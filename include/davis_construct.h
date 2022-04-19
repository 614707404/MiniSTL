#ifndef _DAVIS_CONSTRUCT_H
#define _DAVIS_CONSTRUCT_H
#include <new>
#include "davis_type_traits.h"
#include "davis_iterator.h"
namespace davis
{
    template <class T1, class T2>
    inline void construct(T1 *p, const T2 &value)
    {
        new (p) T1(value);
    }
    template <class T1>
    inline void construct(T1 *p)
    {
        new (p) T1();
    }

    template <class T>
    inline void destroy(T *pointer)
    {
        pointer->~T();
    }

    

    template <class ForwardIterator>
    inline void __destroy_aux(ForwardIterator first, ForwardIterator last, davis::__false_type)
    {
        for (; first != last; first++)
        {
            destroy(&*first);
        }
    }

    template <class ForwardIterator>
    inline void __destroy_aux(ForwardIterator first, ForwardIterator last, davis::__true_type) {}

    

    template <class ForwardIterator, class T>
    inline void __destroy(ForwardIterator first, ForwardIterator last, T *)
    {
        typedef typename davis::__type_traits<T>::has_trivial_destructor trivial_destructor;
        __destroy_aux(first, last, trivial_destructor());
    }

    template <class ForwardIterator>
    inline void destroy(ForwardIterator first, ForwardIterator last)
    {
        __destroy(first, last, davis::value_type(first));
    }

    inline void destroy(char *, char *) {}
    inline void destroy(wchar_t *, wchar_t *) {}
}
#endif