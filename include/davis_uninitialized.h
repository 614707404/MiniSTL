#ifndef _DAVIS_UNINITIALIZED_H
#define _DAVIS_UNINITIALIZED_H
#include <string.h>
#include "davis_construct.h"
namespace DAVIS
{
    template <class ForwardIterator, class Size, class T>
    inline ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n, const T &x)
    {
        return __uninitialized_fill_n(first, n, x, value_type(first));
    }

    template <class ForwardIterator, class Size, class T, class T1>
    inline ForwardIterator __uninitialized_fill_n(ForwardIterator first, Size n, const T &x, T1 *)
    {
        typedef typename DAVIS::__type_traits<T1>::is_POD_type is_POD;
        return __uninitialized_fill_n_aux(first, n, x, is_POD());
    }

    template <class ForwardIterator, class Size, class T>
    inline ForwardIterator __uninitialized_fill_n_aux(ForwardIterator first, Size n, const T &x, DAVIS::__true_type)
    {
        return fill_n(first, n, x);
    }

    template <class ForwardIterator, class Size, class T>
    inline ForwardIterator __uninitialized_fill_n_aux(ForwardIterator first, Size n, const T &x, DAVIS::__false_type)
    {
        ForwardIterator cur = first;
        while (n--)
        {
            DAVIS::construct(&*cur, x);
            ++cur;
        }
        return cur;
    }

    template <class InputIterator, class ForwardIterator>
    inline ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result)
    {
        return __uninitialized_copy(first, last, result, value_type(first));
    }

    template <class InputIterator, class ForwardIterator, class T>
    inline ForwardIterator __uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result, T *)
    {
        typedef typename DAVIS::__type_traits<T>::is_POD_type is_POD;
        return __uninitialized_copy_aux(first, last, result, is_POD());
    }

    template <class InputIterator, class ForwardIterator>
    inline ForwardIterator __uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, DAVIS::__true_type)
    {
        return copy(first, last, result);
    }

    template <class InputIterator, class ForwardIterator>
    inline ForwardIterator __uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, DAVIS::__false_type)
    {
        ForwardIterator cur = first;
        for (; first != last; cur++, first++)
        {
            DAVIS::construct(&*cur, *first);
        }
        return cur;
    }

    inline char *uninitialized_copy(const char *first, const char *last, char *result)
    {
        memmove(result, first, last - first);
        return result + (last - first);
    }

    inline wchar_t *uninitialized_copy(const wchar_t *first, const wchar_t *last, wchar_t *result)
    {
        memmove(result, first, last - first);
        return result + (last - first);
    }

    template <class ForwardIterator, class T>
    inline void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T &x)
    {
        __uninitialized_fill(first, last, x, value_type(x));
    }

    template <class ForwardIterator, class T, class T1>
    inline void __uninitialized_fill(ForwardIterator first, ForwardIterator last, const T &x, T1 *)
    {
        typedef typename DAVIS::__type_traits<T1>::is_POD_type is_POD;
        __uninitialized_fill_aux(first, last, x, is_POD());
    }

    template <class ForwardIterator, class T>
    inline void __uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T &x, DAVIS::__true_type)
    {
        fill(first, last, x);
    }
    template <class ForwardIterator, class T>
    inline void __uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T &x, DAVIS::__false_type)
    {
        ForwardIterator cur = first;
        for (; cur != last; cur++, cur++)
        {
            DAVIS::construct(&*cur, x);
        }
    }
}

#endif