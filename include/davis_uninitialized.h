#ifndef _DAVIS_UNINITIALIZED_H
#define _DAVIS_UNINITIALIZED_H
#include <cstring>
#include "davis_construct.h"
namespace davis
{
    template <class ForwardIterator, class Size, class T, class T1>
    inline ForwardIterator __uninitialized_fill_n(ForwardIterator first, Size n, const T &x, T1 *);

    template <class ForwardIterator, class Size, class T>
    inline ForwardIterator __uninitialized_fill_n_aux(ForwardIterator first, Size n, const T &x, davis::__true_type);

    template <class ForwardIterator, class Size, class T>
    inline ForwardIterator __uninitialized_fill_n_aux(ForwardIterator first, Size n, const T &x, davis::__false_type);

    template <class ForwardIterator, class Size, class T>
    inline ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n, const T &x);

    template <class InputIterator, class ForwardIterator>
    inline ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result);

    template <class InputIterator, class ForwardIterator, class T>
    inline ForwardIterator __uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result, T *);

    template <class InputIterator, class ForwardIterator>
    inline ForwardIterator __uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, davis::__true_type);

    template <class InputIterator, class ForwardIterator>
    inline ForwardIterator __uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, davis::__false_type);

    inline char *uninitialized_copy(const char *first, const char *last, char *result);

    inline wchar_t *uninitialized_copy(const wchar_t *first, const wchar_t *last, wchar_t *result);

    template <class ForwardIterator, class T>
    inline void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T &x);

    template <class ForwardIterator, class T, class T1>
    inline void __uninitialized_fill(ForwardIterator first, ForwardIterator last, const T &x, T1 *);

    template <class ForwardIterator, class T>
    inline void __uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T &x, davis::__true_type);
    template <class ForwardIterator, class T>
    inline void __uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T &x, davis::__false_type);

    template <class _ForwardIterator, class _Size, class _Tp, class _Tp1>
    inline _ForwardIterator __uninitialized_fill_n(_ForwardIterator __first, _Size __n, const _Tp& __x, _Tp1 *)
    {
        typedef typename davis::__type_traits<_Tp1>::is_POD_type is_POD;
        return __uninitialized_fill_n_aux(__first, __n, __x, is_POD());
    }

    template <class _ForwardIterator, class _Size, class _Tp>
    inline _ForwardIterator __uninitialized_fill_n_aux(_ForwardIterator __first, _Size __n, const _Tp& __x, davis::__true_type)
    {
        //TODO 使用了标准库的函数
        return std::fill_n(__first, __n, __x);
    }

    template <class _ForwardIterator, class _Size, class _Tp>
    inline _ForwardIterator __uninitialized_fill_n_aux(_ForwardIterator __first, _Size __n, const _Tp& __x, davis::__false_type)
    {
        _ForwardIterator __cur = __first;
        while (__n--)
        {
            davis::construct(&*__cur, __x);
            ++__cur;
        }
        return __cur;
    }

    template <class _ForwardIterator, class _Size, class _Tp>
    inline _ForwardIterator uninitialized_fill_n(_ForwardIterator __first, _Size __n, const _Tp& __x)
    {
        return __uninitialized_fill_n(__first, __n, __x, davis::value_type(__first));
    }

    template <class InputIterator, class ForwardIterator>
    inline ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result)
    {
        return __uninitialized_copy(first, last, result, value_type(first));
    }

    template <class InputIterator, class ForwardIterator, class T>
    inline ForwardIterator __uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result, T *)
    {
        typedef typename davis::__type_traits<T>::is_POD_type is_POD;
        return __uninitialized_copy_aux(first, last, result, is_POD());
    }

    template <class InputIterator, class ForwardIterator>
    inline ForwardIterator __uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, davis::__true_type)
    {
        //TODO 使用了标准库的函数
        return std::copy(first, last, result);
    }

    template <class InputIterator, class ForwardIterator>
    inline ForwardIterator __uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, davis::__false_type)
    {
        ForwardIterator cur = first;
        for (; first != last; cur++, first++)
        {
            davis::construct(&*cur, *first);
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

    template <class _ForwardIterator, class _Tp>
    inline void uninitialized_fill(_ForwardIterator __first, _ForwardIterator __last, const _Tp& __x)
    {
        __uninitialized_fill(__first,__last,__x,davis::value_type(__first));
    }

    template <class ForwardIterator, class T, class T1>
    inline void __uninitialized_fill(ForwardIterator first, ForwardIterator last, const T &x, T1 *)
    {
        typedef typename davis::__type_traits<T1>::is_POD_type is_POD;
        __uninitialized_fill_aux(first, last, x, is_POD());
    }

    template <class ForwardIterator, class T>
    inline void __uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T &x, davis::__true_type)
    {
        std::fill(first, last, x);
    }
    template <class ForwardIterator, class T>
    inline void __uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T &x, davis::__false_type)
    {
        ForwardIterator cur = first;
        for (; cur != last; cur++, cur++)
        {
            davis::construct(&*cur, x);
        }
    }
    template <class _InputIter, class _ForwardIter, class _Tp>
    inline void
    __uninitialized_copy_fill(_InputIter __first1, _InputIter __last1,
                              _ForwardIter __first2, _ForwardIter __last2,
                              const _Tp &__x)
    {
        _ForwardIter __mid2 = std::uninitialized_copy(__first1, __last1, __first2);
        try
        {
            uninitialized_fill(__mid2, __last2, __x);
        }
        catch(...){
            davis::destroy(__first2, __mid2);
        }
        
    }
    template <class _ForwardIter, class _Tp, class _InputIter>
    inline _ForwardIter
    __uninitialized_fill_copy(_ForwardIter __result, _ForwardIter __mid,
                              const _Tp &__x,
                              _InputIter __first, _InputIter __last)
    {
        uninitialized_fill(__result, __mid, __x);
        try
        {
            return uninitialized_copy(__first, __last, __mid);
        }
        catch (...)
        {
            davis::destroy(__result, __mid);
        }
        return __result;
    }
    template <class _InputIter1, class _InputIter2, class _ForwardIter>
    inline _ForwardIter
    __uninitialized_copy_copy(_InputIter1 __first1, _InputIter1 __last1,
                              _InputIter2 __first2, _InputIter2 __last2,
                              _ForwardIter __result)
    {
        _ForwardIter __mid = uninitialized_copy(__first1, __last1, __result);
        try
        {
            return uninitialized_copy(__first2, __last2, __mid);
        }
        catch(...){
            davis::destroy(__result, __mid);
        }
        return __result;
    }
}

#endif