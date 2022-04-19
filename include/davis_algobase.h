#ifndef _DAVIS_ALGOBASE_H
#define _DAVIS_ALGOBASE_H

namespace davis
{
    template <class _ForwardIter, class _Tp>
    void fill(_ForwardIter __first, _ForwardIter __last ,const _Tp& __value)
    {
        //TODO  __STL_REQUIRES
        // __STL_REQUIRES(_ForwardIter, _Mutable_ForwardIterator);
        for(;__first!=__last;++__first)
        {
            *__first = __value;
        }
    }

    template <class _OutputIter, class _Size, class _Tp>
    _OutputIter fill_n(_OutputIter __first, _Size __n, const _Tp &__value)
    {
        __STL_REQUIRES(_OutputIter, _OutputIterator);
        for (; __n > 0; --__n, ++__first)
            *__first = __value;
        return __first;
    }

    inline void fill(unsigned char *__first, unsigned char *__last,
                     const unsigned char &__c)
    {
        unsigned char __tmp = __c;
        memset(__first, __tmp, __last - __first);
    }

    inline void fill(signed char *__first, signed char *__last,
                     const signed char &__c)
    {
        signed char __tmp = __c;
        memset(__first, static_cast<unsigned char>(__tmp), __last - __first);
    }

    inline void fill(char *__first, char *__last, const char &__c)
    {
        char __tmp = __c;
        memset(__first, static_cast<unsigned char>(__tmp), __last - __first);
    }

    template <class _Size>
    inline unsigned char *fill_n(unsigned char *__first, _Size __n,
                                 const unsigned char &__c)
    {
        fill(__first, __first + __n, __c);
        return __first + __n;
    }

    template <class _Size>
    inline signed char *fill_n(char *__first, _Size __n,
                               const signed char &__c)
    {
        fill(__first, __first + __n, __c);
        return __first + __n;
    }

    template <class _Size>
    inline char *fill_n(char *__first, _Size __n, const char &__c)
    {
        fill(__first, __first + __n, __c);
        return __first + __n;
    }
}

#endif