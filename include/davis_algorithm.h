#ifndef DAVIS_ALGORI_TpHM_H
#define DAVIS_ALGORITHM_H
#include "davis_iterator.h"
#include "davis_type_traits.h"
namespace davis{
    // Non-modifying sequence operations
    // TODO
    template <class _InputIterator, class _UnaryPredicate>
    bool all_of(_InputIterator __first, _InputIterator __last, _UnaryPredicate __pred);
    // TODD
    template <class _InputIterator, class _UnaryPredicate>
    bool any_of(_InputIterator __first, _InputIterator __last, _UnaryPredicate __pred);
    // TODD
    template <class _InputIterator, class _UnaryPredicate>
    bool none_of(_InputIterator __first, _InputIterator __last, _UnaryPredicate __pred);

    template <class _InputIterator, class _Function>
    inline _Function for_each(_InputIterator __first, _InputIterator __last, _Function __fn)
    {
        for (; __first != __last; ++__first)
            __fn(*__first);
        return __fn;
    }

    template <class _InputIterator, class _Tp>
    inline _InputIterator find(_InputIterator __first, _InputIterator __last, const _Tp &__val)
    {
        while (__first != __last && !(*__first == __val))
            ++__first;
        return __first;
    }

    template <class _InputIterator, class _UnaryPredicate>
    inline _InputIterator find_if(_InputIterator __first, _InputIterator __last, _UnaryPredicate __pred)
    {
        while (__first != __last && !__pred(*__first))
            ++__first;
        return __first;
    }

    template <class _InputIterator, class _UnaryPredicate>
    inline _InputIterator find_if_not(_InputIterator __first, _InputIterator __last, _UnaryPredicate __pred)
    {
        while(__first!=__last&&__pred(__first))
            ++__first;
        return __first;
    }

    template <class _ForwardIterator1, class _ForwardIterator2>
    inline _ForwardIterator1 find_end(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
                              _ForwardIterator2 __first2, _ForwardIterator2 __last2)
    {
        if(__first2==__last2){
            return __last1;
        }
        _ForwardIterator1 __res = __last1;
        while(__first1!=__last1){
            _ForwardIterator1 __it1 = __first1;
            _ForwardIterator2 __it2 = __first2;
            while(*__it1 == *__it2){
                ++__it1;
                ++__it2;
                if(__it2 == __last2){
                    __res = __first1;
                    break;
                }
                if(__it1 == __last1){
                    return __res;
                }
            }
            ++__first1;
        }
        return __res;
    }

    template <class _ForwardIterator1, class _ForwardIterator2, class _BinaryPredicate>
    inline _ForwardIterator1 find_end(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
                              _ForwardIterator2 __first2, _ForwardIterator2 __last2,
                              _BinaryPredicate __pred)
    {
        if (__first2 == __last2)
        {
            return __last1;
        }
        _ForwardIterator1 __res = __last1;
        while (__first1 != __last1)
        {
            _ForwardIterator1 __it1 = __first1;
            _ForwardIterator2 __it2 = __first2;
            while (__pred(*__it1,*__it2))
            {
                ++__it1;
                ++__it2;
                if (__it2 == __last2)
                {
                    __res = __first1;
                    break;
                }
                if (__it1 == __last1)
                {
                    return __res;
                }
            }
            ++__first1;
        }
        return __res;
    }

    template <class _ForwardIterator1, class _ForwardIterator2>
    inline _ForwardIterator1 find_first_of(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
                                   _ForwardIterator2 __first2, _ForwardIterator2 __last2)
    {
        while (__first1 != __last1)
        {
            for (_ForwardIterator2 __it = __first2; __it != __last2; ++__it)
            {
                if(*__first1==*__it){
                    return __first1;
                }
            }
            ++__first1;
        }
        return __last1;
    }

    template <class _ForwardIterator1, class _ForwardIterator2, class _BinaryPredicate>
    _ForwardIterator1 find_first_of(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
                                   _ForwardIterator2 __first2, _ForwardIterator2 __last2,
                                   _BinaryPredicate __pred)
    {
        while (__first1 != __last1)
        {
            for (_ForwardIterator2 __it = __first2; __it != __last2; ++__it)
            {
                if (__pred(*__first1, *__it))
                {
                    return __first1;
                }
            }
            ++__first1;
        }
        return __last1;
    }

    template <class _ForwardIterator>
    inline _ForwardIterator adjacent_find(_ForwardIterator __first, _ForwardIterator __last)
    {
        if (__first != __last)
        {

            _ForwardIterator __next = __first;
            ++__next;
            while (__next != __last)
            {
                if (*__first == *__next)
                {
                    return __first;
                }
                ++__first;
                ++__next;
            }
        }
        return __last;
    }

    template <class _ForwardIterator, class _BinaryPredicate>
    inline _ForwardIterator adjacent_find(_ForwardIterator __first, _ForwardIterator __last,
                                  _BinaryPredicate __pred)
    {
        if (__first != __last)
        {

            _ForwardIterator __next = __first;
            ++__next;
            while (__next != __last)
            {
                if (__pred(*__first , *__next))
                {
                    return __first;
                }
                ++__first;
                ++__next;
            }
        }
        return __last;
    }

    template <class _InputIterator, class _Tp>
    inline typename iterator_traits<_InputIterator>::difference_type
    count(_InputIterator __first, _InputIterator __last, const _Tp& __val)
    {
        typename iterator_traits<_InputIterator>::difference_type __res = 0;
        while(__first!=__last){
            if(*__first==__val){
                ++__res;
            }
            ++__first;
        }
        return __res;
    }

    template <class _InputIterator, class _UnaryPredicate>
    inline typename iterator_traits<_InputIterator>::difference_type
    count_if(_InputIterator __first, _InputIterator __last, _UnaryPredicate __pred)
    {
        typename iterator_traits<_InputIterator>::difference_type __res = 0;
        while (__first != __last)
        {
            if (__pred(*__first) )
            {
                ++__res;
            }
            ++__first;
        }
        return __res;
    }

    template <class _InputIterator1, class _InputIterator2>
    inline std::pair<_InputIterator1, _InputIterator2>
    mismatch(_InputIterator1 __first1, _InputIterator1 __last1,
             _InputIterator2 __first2)
    {
        while (__first1 != __last1 && (*__first1 == *__first2))
        {
            ++__first1;
            ++__first2;
        }
        return std::make_pair(__first1, __first2);
    }

    template <class _InputIterator1, class _InputIterator2, class _BinaryPredicate>
    inline std::pair<_InputIterator1, _InputIterator2>
    mismatch(_InputIterator1 __first1, _InputIterator1 __last1,
             _InputIterator2 __first2, _BinaryPredicate __pred)
    {
        while (__first1 != __last1 && __pred(*__first1,*__first2))
        {
            ++__first1;
            ++__first2;
        }
        return std::make_pair(__first1, __first2);
    }

    template <class _InputIterator1, class _InputIterator2>
    inline bool equal(_InputIterator1 __first1, _InputIterator1 __last1,
               _InputIterator2 __first2)
    {
        while(__first1!=__last1){
            if (!(*__first1 == *__first2))
                return false;
            ++__first1;
            ++__first2;
        }
        return true;
    }

    template <class _InputIterator1, class _InputIterator2, class _BinaryPredicate>
    inline bool equal(_InputIterator1 __first1, _InputIterator1 __last1,
               _InputIterator2 __first2, _BinaryPredicate __pred)
    {
        while (__first1 != __last1)
        {
            if (!__pred(*__first1, *__first2))
                return false;
            ++__first1;
            ++__first2;
        }
        return true;
    }

    template <class _ForwardIterator1, class _ForwardIterator2>
    inline bool is_permutation(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
                        _ForwardIterator2 __first2)
    {
        // TODO
    }

    template <class _ForwardIterator1, class _ForwardIterator2, class _BinaryPredicate>
    bool is_permutation(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
                        _ForwardIterator2 __first2, _BinaryPredicate __pred)
    {
        // TODO
    }

    template <class _ForwardIterator1, class _ForwardIterator2>
    inline _ForwardIterator1 search(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
                            _ForwardIterator2 __first2, _ForwardIterator2 __last2)
    {
        while(__first1!=__last1){
            _ForwardIterator1 __it1 = __first1;
            _ForwardIterator2 __it2 = __first2;
            while(*__it1==*__it2){
                ++__it1;
                ++__it2;
                if(__it2==__last2)
                    return __first1;
                if(__it1==__last1)
                    return __last1;
            }
            ++__first1;
        }
        return __last1;
    }

    template <class _ForwardIterator1, class _ForwardIterator2, class _BinaryPredicate>
    inline _ForwardIterator1 search(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
                            _ForwardIterator2 __first2, _ForwardIterator2 __last2,
                            _BinaryPredicate __pred)
    {
        while (__first1 != __last1)
        {
            _ForwardIterator1 __it1 = __first1;
            _ForwardIterator2 __it2 = __first2;
            while (__pred(*__it1, *__it2))
            {
                ++__it1;
                ++__it2;
                if (__it2 == __last2)
                    return __first1;
                if (__it1 == __last1)
                    return __last1;
            }
            ++__first1;
        }
        return __last1;
    }

    template <class _ForwardIterator, class _Size, class _Tp>
    inline _ForwardIterator search_n(_ForwardIterator __first, _ForwardIterator __last,
                                     _Size __count, const _Tp& __val)
    {
        _ForwardIterator __limit=__first;
        davis::advance(__limit,davis::distance(__first,__last)-__count);
        while(__first!=__limit){
            _ForwardIterator __it=__first;
            _Size __cnt=0;
            while(*__it==__val){
                ++__cnt;
                ++__it;
                if(__cnt==__count){
                    return __first;
                }
            }
            ++__first;
        }
        return __last;
    }

    template <class _ForwardIterator, class _Size, class _Tp, class _BinaryPredicate>
    inline _ForwardIterator search_n(_ForwardIterator __first, _ForwardIterator __last,
                                     _Size __count, const _Tp &__val, _BinaryPredicate __pred)
    {
        _ForwardIterator __limit = __first;
        davis::advance(__limit, davis::distance(__first, __last) - __count);
        while (__first != __limit)
        {
            _ForwardIterator __it = __first;
            _Size __cnt = 0;
            while (__pred (* __it , __val))
            {
                ++__cnt;
                ++__it;
                if (__cnt == __count)
                {
                    return __first;
                }
            }
            ++__first;
        }
        return __last;
    }

    // Modifying sequence operations
    // copy 函数
    template <class _RandomAccessIterator, class _OutputIterator, class _Distance>
    inline _OutputIterator __copy_d(_RandomAccessIterator __first, _RandomAccessIterator __last,
                                    _OutputIterator __result, _Distance *)
    {
        for(_Distance n = __last-__first; n>0 ;--n,++__result,++__first){
            *__result = *__first;
        }
        return __result;
    }
    template <class _InputIterator, class _OutputIterator>
    inline _OutputIterator __copy(_InputIterator __first, _InputIterator __last,
                                  _OutputIterator __result, davis::input_iterator_tag)
    {
        for (; __first != __last; ++__first, ++__result)
        {
            *__result = *__first;
        }
        return __result;
    }
    template <class _RandomAccessIterator, class _OutputIterator>
    inline _OutputIterator __copy(_RandomAccessIterator __first, _RandomAccessIterator __last,
                                  _OutputIterator __result, davis::random_access_iterator_tag)
    {
        return __copy_d(__first,__last,__result,davis::distance_type(__first));
    }
    template <class _InputIterator, class _OutputIterator>
    struct __copy_dispatch
    {
        _OutputIterator operator()(_InputIterator __first, _InputIterator __last,
                                   _OutputIterator __result)
        {
            return __copy(__first,__last,__result,davis::iterator_category(__first));
        }
    };
    template <class _Tp>
    inline _Tp* __copy_t(const _Tp* __first, const _Tp* __last,_Tp* __result,davis::__true_type)
    {
        memmove(__result,__first,sizeof(_Tp)*(__last-__first));
        return __result+(__last-__first);
    }
    template <class _Tp>
    inline _Tp *__copy_t(const _Tp *__first, const _Tp *__last, _Tp *__result, davis::__false_type)
    {
        return __copy_d(__first, __last, __result, (ptrdiff_t *)0);
    }
    template <class _Tp>
    struct __copy_dispatch<_Tp *, _Tp*>
    {
        _Tp *operator()(_Tp *__first, _Tp *__last,
                        _Tp *__result)
        {
            typedef typename __type_traits<_Tp>::has_trivial_assignment_operator t;
            return __copy_t(__first, __last, __result,t());
        }
    };
    template <class _Tp>
    struct __copy_dispatch<const _Tp *,const _Tp *>
    {
        _Tp *operator()(const _Tp *__first,const _Tp *__last,
                        _Tp *__result)
        {
            typedef typename __type_traits<_Tp>::has_trivial_assignment_operator t;
            return __copy_t(__first, __last, __result, t());
        }
    };
    // copy 算法的入口函数
    // 完全泛化版本
    template <class _InputIterator, class _OutputIterator>
    inline _OutputIterator copy(_InputIterator __first, _InputIterator __last, _OutputIterator __result)
    {
        return __copy_dispatch<_InputIterator, _OutputIterator>()(__first,__last,__result);
    }
    // 特化
    inline char* copy(const char* __first,const char* __last,char* __result)
    {
        memmove(__result, __first, __last - __first);
        return __result + (__last - __first);
    }
    // 特化
    inline wchar_t* copy(const wchar_t* __first, const wchar_t* __last, wchar_t* __result)
    {
        memmove(__result, __first, sizeof(wchar_t)*(__last - __first));
        return __result + (__last - __first);
    }

    template <class _InputIterator, class Size, class OutputIterator>
    OutputIterator copy_n(_InputIterator __first, Size n, OutputIterator result)
    {
        // TODO
    }

    template <class _InputIterator, class OutputIterator, class UnaryPredicate>
    OutputIterator copy_if(_InputIterator __first, _InputIterator __last,
                           OutputIterator result, UnaryPredicate __pred)
    {
        // TODO
    }
    // copy_backward
    // 逆向复制
    template <class _BidirectionalIterator1, class _BidirectionalIterator2,class _Dis>
    inline _BidirectionalIterator2 __copy_backward(_BidirectionalIterator1 __first,
                                                   _BidirectionalIterator1 __last,
                                                   _BidirectionalIterator2 __result,
                                                   davis::bidirectional_iterator_tag,
                                                   _Dis*)
    {
        while(__last!=__first){
            *--__result=*--__last;
        }
        return __result;
    }
    template <class _BidirectionalIterator1, class _BidirectionalIterator2, class _Dis>
    inline _BidirectionalIterator2 __copy_backward(_BidirectionalIterator1 __first,
                                                   _BidirectionalIterator1 __last,
                                                   _BidirectionalIterator2 __result,
                                                   davis::random_access_iterator_tag,
                                                   _Dis *)
    {
        for (_Dis __n = __last - __first; __n > 0; --__n)
        {
            *--__result = *--__last;
        }
        return __result;
    }

    template <class _BidirectionalIterator1, class _BidirectionalIterator2>
    inline _BidirectionalIterator2 __copy_backward( _BidirectionalIterator1 __first,
                                                    _BidirectionalIterator1 __last,
                                                    _BidirectionalIterator2 __result,
                                                    davis::__false_type)
    {
        typedef typename davis::iterator_traits<_BidirectionalIterator1>::iterator_category _Cat;
        typedef typename davis::iterator_traits<_BidirectionalIterator1>::difference_type _Dis;
        return __copy_backward(__first, __last, __result, _Cat(), (_Dis *)0);
    }
    template <class _Tp>
    inline _Tp* __copy_backward(_Tp* __first,
                               _Tp* __last,
                               _Tp* __result,
                               davis::__true_type)
    {
        const ptrdiff_t _Num = __last - __first;
        memmove(__result - _Num, __first, sizeof(_Tp) * _Num);
        return __result - _Num;
    }
    template <class _Tp>
    inline _Tp* __copy_backward(const _Tp* __first,
                                _Tp* __last,
                                _Tp* __result,
                                davis::__true_type)
    {
        const ptrdiff_t _Num = __last - __first;
        memmove(__result - _Num, __first, sizeof(_Tp) * _Num);
        return __result - _Num;
    }
    template <class _BidirectionalIterator1, class _BidirectionalIterator2>
    struct __copy_backward_dispatch
    {
        _BidirectionalIterator2 operator()(_BidirectionalIterator1 __first, _BidirectionalIterator1 __last,
                                           _BidirectionalIterator2 __result)
        {
            typedef typename davis::__type_traits<typename davis::iterator_traits<_BidirectionalIterator1>::value_type>
                ::has_trivial_assignment_operator _Trivial;
            return __copy_backward(__first, __last, __result, _Trivial());
        }
    };
    template <class _BidirectionalIterator1, class _BidirectionalIterator2>
    _BidirectionalIterator2 copy_backward(_BidirectionalIterator1 __first,
                                          _BidirectionalIterator1 __last,
                                          _BidirectionalIterator2 __result)
    {
        return __copy_backward_dispatch<_BidirectionalIterator1, _BidirectionalIterator2>()(__first, __last, __result);
    }

    template <class _InputIterator, class OutputIterator>
    OutputIterator move(_InputIterator __first, _InputIterator __last, OutputIterator result);

    template <class BidirectionalIterator1, class BidirectionalIterator2>
    BidirectionalIterator2 move_backward(BidirectionalIterator1 __first,
                                         BidirectionalIterator1 __last,
                                         BidirectionalIterator2 result);

    template <class _Tp>
    void swap(_Tp & __a, _Tp & __b)
    {
        _Tp __tmp = __a;
        __a = __b;
        __b = __tmp;
    }

    template <class _ForwardIterator1, class _ForwardIterator2>
    _ForwardIterator2 swap_ranges(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
                                 _ForwardIterator2 __first2)
    {
        while(__first1!=__last1){
            swap(*__first1,*__first2);
            ++__first1;
            ++__first2;
        }
        return __first2;
    }

    template <class _ForwardIterator1, class _ForwardIterator2>
    void iter_swap(_ForwardIterator1 __a, _ForwardIterator2 __b)
    {
        swap(*__a,*__b);
    }

    template <class _InputIterator, class _OutputIterator, class _UnaryOperation>
    _OutputIterator transform(_InputIterator __first1, _InputIterator __last1,
                             _OutputIterator __result, _UnaryOperation __op)
    {
        while (__first1 != __last1)
        {
            *__result = __op(*__first1);
            ++__first1;
            ++__result;
        }
        return __result;
    }

    template <class _InputIterator1, class _InputIterator2,
              class _OutputIterator, class _BinaryOperation>
    _OutputIterator transform(_InputIterator1 __first1, _InputIterator1 __last1,
                             _InputIterator2 __first2, _OutputIterator __result,
                             _BinaryOperation __binary_op)
    {
        while (__first1 != __last1)
        {
            *__result = __binary_op(*__first1, *__first2);
            ++__first1;
            ++__first2;
            ++__result;
        }
        return __result;
    }

    template <class _ForwardIterator, class _Tp>
    void replace(_ForwardIterator __first, _ForwardIterator __last,
                 const _Tp& __old_value, const _Tp& __new_value)
    {
        while (__first != __last)
        {
            if (*__first == __old_value)
                *__first = __new_value;
            ++__first;
        }
    }

    template <class _ForwardIterator, class _UnaryPredicate, class _Tp>
    void replace_if(_ForwardIterator __first, _ForwardIterator __last,
                    _UnaryPredicate __pred, const _Tp& __new_value)
    {
        while (__first != __last)
        {
            if (__pred(*__first))
                *__first = __new_value;
            ++__first;
        }
    }

    template <class _InputIterator, class _OutputIterator, class _Tp>
    _OutputIterator replace_copy(_InputIterator __first, _InputIterator __last,
                                 _OutputIterator __result,
                                 const _Tp& __old_value, const _Tp& __new_value)
    {
        while (__first != __last)
        {
            if (*__first == __old_value)
                *__result = __new_value;
            else
                *__result = *__first;
            ++__first;
            ++__result;
        }
    }

    template <class _InputIterator, class _OutputIterator, class _UnaryPredicate, class _Tp>
    _OutputIterator replace_copy_if(_InputIterator __first, _InputIterator __last,
                                    _OutputIterator __result, _UnaryPredicate __pred,
                                    const _Tp& __new_value)
    {
        while (__first != __last)
        {
            if (__pred(*__first))
                *__result = __new_value;
            else
                *__result = *__first;
            ++__first;
            ++__result;
        }
    }
    template <class _ForwardIter, class _Tp>
    void fill(_ForwardIter __first, _ForwardIter __last, const _Tp &__value)
    {
        for (; __first != __last; ++__first)
            *__first = __value;
    }

    template <class _OutputIter, class _Size, class _Tp>
    _OutputIter fill_n(_OutputIter __first, _Size __n, const _Tp &__value)
    {
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

    template <class _ForwardIterator, class _Generator>
    void generate(_ForwardIterator __first, _ForwardIterator __last, _Generator __gen)
    {
        while(__first!=__last){
            *__first=__gen();
            ++__first;
        }
    }

    template <class _OutputIterator, class _Size, class _Generator>
    _OutputIterator generate_n(_OutputIterator __first, _Size __n, _Generator __gen)
    {
        for (; __n > 0; --__n, ++__first)
        {
            *__first = __gen();
        }
    }
    template <class _InputIterator, class _OutputIterator, class _Tp>
    _OutputIterator remove_copy(_InputIterator __first, _InputIterator __last,
                               _OutputIterator __result, const _Tp& __val)
    {
        while(__first!=__last)
        {
            if(!(*__first==__val)){
                *__result=*__first;
                ++__result;
            }
            ++__first;
        }
        return __result;
    }

    template <class _InputIterator, class _OutputIterator, class _UnaryPredicate>
    _OutputIterator remove_copy_if(_InputIterator __first, _InputIterator __last,
                                   _OutputIterator __result, _UnaryPredicate __pred)
    {
        while (__first != __last)
        {
            if (!__pred(*__first))
            {
                *__result = *__first;
                ++__result;
            }
            ++__first;
        }
        return __result;
    }

    template <class _ForwardIterator, class _Tp>
    _ForwardIterator remove(_ForwardIterator __first, _ForwardIterator __last, const _Tp& __val)
    {
        __first = davis::find(__first, __last, __val);
        _ForwardIterator __i = __first;
        return __first == __last ? __first
                                 : remove_copy(++__i, __last, __first, __val);
    }

    template <class _ForwardIterator, class _UnaryPredicate>
    _ForwardIterator remove_if(_ForwardIterator __first, _ForwardIterator __last,
                               _UnaryPredicate __pred)
    {
        __first = davis::find_if(__first, __last, __pred);
        _ForwardIterator __i = __first;
        return __first == __last ? __first
                                 : remove_copy_if(++__i, __last, __first, __pred);
    }

    
    template <class _ForwardIterator>
    _ForwardIterator unique(_ForwardIterator __first, _ForwardIterator __last)
    {
        if(__first == __last){
            return __first;
        }
        _ForwardIterator __result = __first;
        while(++__first!=__last)
        {
            if(!(*__result==*__first)){
                *(++__result)=*__first;
            }
        }
        ++__result;
    }

    template <class _ForwardIterator, class _BinaryPredicate>
    _ForwardIterator unique(_ForwardIterator __first, _ForwardIterator __last,
                           _BinaryPredicate __pred)
    {
        if (__first == __last)
        {
            return __first;
        }
        _ForwardIterator __result = __first;
        while (++__first != __last)
        {
            if (!__pred(*__result , *__first))
            {
                *(++__result) = *__first;
            }
        }
        ++__result;
    }

    template <class _InputIterator, class _OutputIterator>
    _OutputIterator unique_copy(_InputIterator __first, _InputIterator __last,
                               _OutputIterator __result)
    {
        *__result = *__first;
        while (++__first != __last)
        {
            if (!(*__result == *__first))
            {
                *(++__result) = *__first;
            }
        }
        ++__result;
    }

    template <class _InputIterator, class _OutputIterator, class _BinaryPredicate>
    _OutputIterator unique_copy(_InputIterator __first, _InputIterator __last,
                               _OutputIterator __result, _BinaryPredicate __pred)
    {
        *__result = *__first;
        while (++__first != __last)
        {
            if (!__pred(*__result, *__first))
            {
                *(++__result) = *__first;
            }
        }
        ++__result;
    }

    template <class _BidirectionalIterator>
    void reverse(_BidirectionalIterator __first, _BidirectionalIterator __last)
    {
        while ((__first != __last) && (__first != --__last))
        {
            std::iter_swap(__first, __last);
            ++__first;
        }
    }

    template <class _BidirectionalIterator, class _OutputIterator>
    _OutputIterator reverse_copy(_BidirectionalIterator __first,
                                 _BidirectionalIterator __last, _OutputIterator __result)
    {
        while(__first!=__last){
            --__last;
            *__result=*__last;
            ++__result;
        }
        return __result;
    }

    template <class _ForwardIterator>
    _ForwardIterator rotate(_ForwardIterator __first, _ForwardIterator __middle,
                           _ForwardIterator __last)
    {
        // TODO
        return __rotate(__first, __middle, __last,
                        davis::distance_type(__first), davis::iterator_category(__first));
    }

    template <class _ForwardIterator, class _OutputIterator>
    _OutputIterator rotate_copy(_ForwardIterator __first, _ForwardIterator __middle,
                                _ForwardIterator __last, _OutputIterator __result)
    {
        return copy(__first, __middle, copy(__middle,__last,__result));
    }
    template <class _Distance>
    inline _Distance __random_number(_Distance __n)
    {
        return rand() % __n;
    }
    template <class _RandomAccessIterator>
    void random_shuffle(_RandomAccessIterator __first, _RandomAccessIterator __last)
    {
        if (__first == __last)
            return;
        for (_RandomAccessIterator __i = __first + 1; __i != __last; ++__i)
            iter_swap(__i, __first + __random_number((__i - __first) + 1));
    }

    template <class _RandomAccessIterator, class _RandomNumberGenerator>
    void random_shuffle(_RandomAccessIterator __first, _RandomAccessIterator __last,
                        _RandomNumberGenerator &__gen)
    {
        if (__first == __last)
            return;
        for (_RandomAccessIterator __i = __first + 1; __i != __last; ++__i)
            iter_swap(__i, __first + __gen((__i - __first) + 1));
    }

    template <class RandomAccessIterator, class URNG>
    void shuffle(RandomAccessIterator __first, RandomAccessIterator __last, URNG &&g);

    // Partitions
    template <class _InputIterator, class UnaryPredicate>
    bool is_partitioned(_InputIterator __first, _InputIterator __last, UnaryPredicate __pred)
    {
        // TODO
    }

    template <class _ForwardIterator, class _UnaryPredicate>
    _ForwardIterator __partition(_ForwardIterator __first,
                                 _ForwardIterator __last,
                                 _UnaryPredicate __pred,
                                 davis::forward_iterator_tag)
    {
        if(__first == __last ) return __last;
        while(__pred(*__first)){
            if(++__first==__last) return __last;
        }
        _ForwardIterator __next = __first ;
        while(++__next != __last){
            if(__pred(*__next)){
                iter_swap(__next,__first);
                ++__first;
            }
        }
        return __first;
    }

    template <class _ForwardIterator, class _UnaryPredicate>
    _ForwardIterator __partition(_ForwardIterator __first,
                                 _ForwardIterator __last,
                                 _UnaryPredicate __pred,
                                 davis::bidirectional_iterator_tag)
    {
        while (__first != __last)
        {
            while (__first != __last && __pred(*__first))
                ++__first;
            do{
                --__last;
            } while (__first != __last && !__pred(*__last));
            iter_swap(__first, __last);
            ++__first;
        }
        return __first;
    }
    template <class _BidirectionalIterator, class _UnaryPredicate, class _Pointer, class _Distance>
    _BidirectionalIterator __stable_partition_adaptive(_BidirectionalIterator __first,
                                                       _BidirectionalIterator __last,
                                                       _UnaryPredicate __pred,
                                                       _Distance __len,
                                                       _Pointer __buffer,
                                                       _Distance __buffer_size)
    {
        if (__len <= __buffer_size)
        {
            _BidirectionalIterator __result1 = __first;
            _BidirectionalIterator __result2 = __buffer;
            while(__first!=__last){
                while (__first != __last && __pred(*__first))
                {
                    *__result1 = *__first;
                    ++__first;
                    ++__result1;
                }
                *__result2 = *__first;
                ++__result2;
            }
            copy(__buffer,__result2,__result1);
            return __result1;
        }
        else
        {
            _BidirectionalIterator __middle = __first;
            davis::advance(__middle, __len / 2);
            return davis::rotate(__stable_partition_adaptive(__first, __middle, __pred,
                                                             __len / 2, __buffer, __buffer_size),
                                                             __middle,
                                 __stable_partition_adaptive(__middle, __last, __pred,
                                                             __len - __len / 2, __buffer, __buffer_size));
        }
    }
    template <class _BidirectionalIterator, class _UnaryPredicate, class _Pointer, class _Distance>
    _BidirectionalIterator __inplace_stable_partition(_BidirectionalIterator __first,
                                                      _BidirectionalIterator __last,
                                                      _UnaryPredicate __pred,
                                                      _Distance __len)
    {
        if (__len == 1)
            return __pred(*__first) ? __last : __first;
        _BidirectionalIterator __middle = __first;
        davis::advance(__middle, __len / 2);
        return davis::rotate(__inplace_stable_partition(__first, __middle, __pred, __len / 2),
                             __middle,
                             __inplace_stable_partition(__middle, __last, __len - __len / 2));
    }
    template <class _BidirectionalIterator, class _UnaryPredicate, class _Tp, class _Distance>
    inline _BidirectionalIterator __stable_partition_aux(_BidirectionalIterator __first,
                                                  _BidirectionalIterator __last,
                                                  _UnaryPredicate __pred,
                                                  _Tp *,
                                                  _Distance *)
    {
        _Distance __n =davis::distance(__first,__last);
        std::pair<_Tp *, _Distance> __buf = std::get_temporary_buffer<_Tp>(__n);
        if(__buf.second>0){
            return __stable_partition_adaptive(__first, __last, __pred,
                                               __n, __buf.first, __buf.second);
        }else{
            return __inplace_stable_partition(__first, __last, __pred, __n);
        }
        std::return_temporary_buffer(__buf);
    }
    template <class _BidirectionalIterator, class _UnaryPredicate>
    inline _BidirectionalIterator stable_partition(_BidirectionalIterator __first,
                                            _BidirectionalIterator __last,
                                            _UnaryPredicate __pred)
    {
        return __stable_partition_aux(__first, __last, __pred,
                                      davis::value_type(__first),
                                      davis::distance_type(__first));
    }

    template <class _InputIterator, class _OutputIterator1,
              class _OutputIterator2, class _UnaryPredicate>
    std::pair<_OutputIterator1, _OutputIterator2>
    partition_copy(_InputIterator __first, _InputIterator __last,
                   _OutputIterator1 result_true, _OutputIterator2 result_false,
                   _UnaryPredicate __pred)
    {
        // TODO
    }

    template <class _ForwardIterator, class UnaryPredicate>
    _ForwardIterator partition_point(_ForwardIterator __first, _ForwardIterator __last,
                                     UnaryPredicate __pred); // TODO

    // Sorting
    template <class _Tp>
    inline const _Tp &__median(const _Tp &__a, const _Tp &__b, const _Tp &__c)
    {
        if (__a < __b)
            if (__b < __c) // a < b < c
                return __b;
            else if (__a < __c) // a<c<=b
                return __c;
            else
                return __a; // c<a<b
        else if (__a < __c) // a>=b, a<c
            return __a;
        else if (__b > __c) // a>=b,a>=c
            return __b;
        else
            return __c;
    }
    template <class _RandomAccessIterator, class _Tp>
    _RandomAccessIterator __unguarded_partition(_RandomAccessIterator __first,
                                                _RandomAccessIterator __last,
                                                _Tp pivot)
    {
        while (true)
        {
            while (*__first < pivot)
                ++__first;
            --__last;
            while (pivot < *__last)
                --__last;
            if (!(__first < __last))
                return __first;
            iter_swap(__first, __last);
            ++__first;
        }
    }
    const int __stl_threshold = 16;
    template <class _Size>
    inline _Size __lg(_Size __n)
    {
        _Size __k;
        for (__k = 0; __n > 1; __n >> 1)
            ++__k;
        return __k;
    }
    template <class _RandomAccessIterator, class _Tp, class _Size>
    void __introsort_loop(_RandomAccessIterator __first,
                          _RandomAccessIterator __last,
                          _Tp *, _Size __depth_limit)
    {
        while(__last-__first>__stl_threshold)
        {
            if(__depth_limit == 0){
                partial_sort(__first,__last,__last);
                return;
            }
            --__depth_limit;
            _RandomAccessIterator __cut =
                __unguarded_partition(__first, __last,
                                      __median(*__first, *__last,
                                               *(__first + (__last - __first) / 2)));
            __introsort_loop(__cut,__last,davis::value_type(__first),__depth_limit);
            __last = __cut;
        }
    }
    template <class __RandomAccessIterator, class _Tp>
    inline void __unguarded_linear_insert(__RandomAccessIterator __last, _Tp __val)
    {
        __RandomAccessIterator __next = __last;
        --__next;
        while (__val < *__next)
        {
            *__last = *__next;
            __last = __next;
            --__next;
        }
        *__last = __val;
    }

    template <class __RandomAccessIterator, class _Tp>
    inline void __lineat_insert(__RandomAccessIterator __first, __RandomAccessIterator __last)
    {
        _Tp __val = *__last;
        if (__val<*__first){
            copy_backward(__first,__last,__last+1);
            *__first = __val;
        }
        else
            __unguarded_linear_insert(__last, __val);
    }
    template <class _RandomAccessIter, class _Tp>
    void __unguarded_insertion_sort_aux(_RandomAccessIter __first,
                                        _RandomAccessIter __last, _Tp *)
    {
        for (_RandomAccessIter __i = __first; __i != __last; ++__i)
            __unguarded_linear_insert(__i, _Tp(*__i));
    }

    template <class _RandomAccessIter>
    inline void __unguarded_insertion_sort(_RandomAccessIter __first,
                                           _RandomAccessIter __last)
    {
        __unguarded_insertion_sort_aux(__first, __last, __VALUE_TYPE(__first));
    }
    template <class __RandomAccessIterator>
    void __insertion_sort(__RandomAccessIterator __first, __RandomAccessIterator __last)
    {
        if(__first!=__last)
            for (__RandomAccessIterator __i = __first+1;__i!=__last;++__i)
                __linear_insert(__first,__i,davis::value_type(__first));
    }
     template <class __RandomAccessIterator>
    void __final_insertion_sort(__RandomAccessIterator __first, __RandomAccessIterator __last)
    {
        if (__last - __first > __stl_threshold)
        {
            __insertion_sort(__first, __first + __stl_threshold);
            __unguarded_insertion_sort(__first + __stl_threshold, __last);
        }
        else
        {
            __insertion_sort(__first, __last);
        }
    }
    template <class _RandomAccessIterator>
    void sort(_RandomAccessIterator __first, _RandomAccessIterator __last)
    {
        __introsort_loop(__first, __last, davis::value_type(__first), __lg(__last - __first) * 2);
        __final_insertion_sort(__first, __last);
    }

    template <class _RandomAccessIterator, class _Tp,class _Compare>
    _RandomAccessIterator __unguarded_partition(_RandomAccessIterator __first,
                                                _RandomAccessIterator __last,
                                                _Tp pivot,_Compare __comp)
    {
        while (true)
        {
            while (__comp(*__first, pivot))
                ++__first;
            --__last;
            while (__comp(pivot, *__last))
                --__last;
            if (!(__comp(__first, __last)))
                return __first;
            iter_swap(__first, __last);
            ++__first;
        }
    }
    template <class _RandomAccessIterator, class _Tp, class _Size, class _Compare>
    void __introsort_loop(_RandomAccessIterator __first,
                          _RandomAccessIterator __last,
                          _Tp *, _Size __depth_limit, _Compare __comp)
    {
        while (__last - __first > __stl_threshold)
        {
            if (__depth_limit == 0)
            {
                partial_sort(__first, __last, __last);
                return;
            }
            --__depth_limit;
            _RandomAccessIterator __cut =
                __unguarded_partition(__first, __last,
                                      __median(*__first, *__last,
                                               *(__first + (__last - __first) / 2)));
            __introsort_loop(__cut, __last, davis::value_type(__first), __depth_limit);
            __last = __cut;
        }
    }
    template <class __RandomAccessIterator, class _Tp, class _Compare>
    inline void __unguarded_linear_insert(__RandomAccessIterator __last,
                                          _Tp __val, _Compare __comp)
    {
        __RandomAccessIterator __next = __last;
        --__next;
        while (__comp(__val, *__next))
        {
            *__last = *__next;
            __last = __next;
            --__next;
        }
        *__last = __val;
    }

    template <class __RandomAccessIterator, class _Tp,class _Compare>
    inline void __lineat_insert(__RandomAccessIterator __first,
                                __RandomAccessIterator __last,
                                _Compare __comp)
    {
        _Tp __val = *__last;
        if (__comp(__val, *__first))
        {
            copy_backward(__first, __last, __last + 1);
            *__first = __val;
        }
        else
            __unguarded_linear_insert(__last, __val);
    }
    template <class _RandomAccessIter, class _Tp, class _Compare>
    void __unguarded_insertion_sort_aux(_RandomAccessIter __first,
                                        _RandomAccessIter __last,
                                        _Tp *, _Compare __comp)
    {
        for (_RandomAccessIter __i = __first; __i != __last; ++__i)
            __unguarded_linear_insert(__i, _Tp(*__i), __comp);
    }

    template <class _RandomAccessIter,class _Compare>
    inline void __unguarded_insertion_sort(_RandomAccessIter __first,
                                           _RandomAccessIter __last,
                                           _Compare __comp)
    {
        __unguarded_insertion_sort_aux(__first, __last, __VALUE_TYPE(__first),__comp);
    }
    template <class __RandomAccessIterator, class _Compare>
    void __insertion_sort(__RandomAccessIterator __first,
                          __RandomAccessIterator __last,
                          _Compare __comp)
    {
        if (__first != __last)
            for (__RandomAccessIterator __i = __first + 1; __i != __last; ++__i)
                __linear_insert(__first, __i, davis::value_type(__first), __comp);
    }
    template <class __RandomAccessIterator, class _Compare>
    void __final_insertion_sort(__RandomAccessIterator __first,
                                __RandomAccessIterator __last,
                                _Compare __comp)
    {
        if (__last - __first > __stl_threshold)
        {
            __insertion_sort(__first, __first + __stl_threshold,__comp);
            __unguarded_insertion_sort(__first + __stl_threshold, __last,__comp);
        }
        else
        {
            __insertion_sort(__first, __last,__comp);
        }
    }
    template <class _RandomAccessIterator, class _Compare>
    void sort(_RandomAccessIterator __first, _RandomAccessIterator __last, _Compare __comp)
    {
        __introsort_loop(__first, __last, davis::value_type(__first), __lg(__last - __first) * 2, __comp);
        __final_insertion_sort(__first, __last, __comp);
    }

    // Stable_Sort
    template <class _BidirectionalIter, class _Distance>
    void __merge_without_buffer(_BidirectionalIter __first,
                                _BidirectionalIter __middle,
                                _BidirectionalIter __last,
                                _Distance __len1, _Distance __len2)
    {
        if (__len1 == 0 || __len2 == 0)
            return;
        if (__len1 + __len2 == 2)
        {
            if (*__middle < *__first)
                iter_swap(__first, __middle);
            return;
        }
        _BidirectionalIter __first_cut = __first;
        _BidirectionalIter __second_cut = __middle;
        _Distance __len11 = 0;
        _Distance __len22 = 0;
        if (__len1 > __len2)
        {
            __len11 = __len1 / 2;
            advance(__first_cut, __len11);
            __second_cut = lower_bound(__middle, __last, *__first_cut);
            distance(__middle, __second_cut, __len22);
        }
        else
        {
            __len22 = __len2 / 2;
            advance(__second_cut, __len22);
            __first_cut = upper_bound(__first, __middle, *__second_cut);
            distance(__first, __first_cut, __len11);
        }
        _BidirectionalIter __new_middle = rotate(__first_cut, __middle, __second_cut);
        __merge_without_buffer(__first, __first_cut, __new_middle,
                               __len11, __len22);
        __merge_without_buffer(__new_middle, __second_cut, __last, __len1 - __len11,
                               __len2 - __len22);
    }

    template <class _BidirectionalIter, class _Distance, class _Compare>
    void __merge_without_buffer(_BidirectionalIter __first,
                                _BidirectionalIter __middle,
                                _BidirectionalIter __last,
                                _Distance __len1, _Distance __len2,
                                _Compare __comp)
    {
        if (__len1 == 0 || __len2 == 0)
            return;
        if (__len1 + __len2 == 2)
        {
            if (__comp(*__middle, *__first))
                iter_swap(__first, __middle);
            return;
        }
        _BidirectionalIter __first_cut = __first;
        _BidirectionalIter __second_cut = __middle;
        _Distance __len11 = 0;
        _Distance __len22 = 0;
        if (__len1 > __len2)
        {
            __len11 = __len1 / 2;
            advance(__first_cut, __len11);
            __second_cut = lower_bound(__middle, __last, *__first_cut, __comp);
            distance(__middle, __second_cut, __len22);
        }
        else
        {
            __len22 = __len2 / 2;
            advance(__second_cut, __len22);
            __first_cut = upper_bound(__first, __middle, *__second_cut, __comp);
            distance(__first, __first_cut, __len11);
        }
        _BidirectionalIter __new_middle = rotate(__first_cut, __middle, __second_cut);
        __merge_without_buffer(__first, __first_cut, __new_middle, __len11, __len22,
                               __comp);
        __merge_without_buffer(__new_middle, __second_cut, __last, __len1 - __len11,
                               __len2 - __len22, __comp);
    }
    template <class _RandomAccessIter>
    void __inplace_stable_sort(_RandomAccessIter __first,
                               _RandomAccessIter __last)
    {
        if (__last - __first < 15)
        {
            __insertion_sort(__first, __last);
            return;
        }
        _RandomAccessIter __middle = __first + (__last - __first) / 2;
        __inplace_stable_sort(__first, __middle);
        __inplace_stable_sort(__middle, __last);
        __merge_without_buffer(__first, __middle, __last,
                               __middle - __first,
                               __last - __middle);
    }

    template <class _RandomAccessIter, class _Compare>
    void __inplace_stable_sort(_RandomAccessIter __first,
                               _RandomAccessIter __last, _Compare __comp)
    {
        if (__last - __first < 15)
        {
            __insertion_sort(__first, __last, __comp);
            return;
        }
        _RandomAccessIter __middle = __first + (__last - __first) / 2;
        __inplace_stable_sort(__first, __middle, __comp);
        __inplace_stable_sort(__middle, __last, __comp);
        __merge_without_buffer(__first, __middle, __last,
                               __middle - __first,
                               __last - __middle,
                               __comp);
    }
    template <class _RandomAccessIter1, class _RandomAccessIter2,
              class _Distance>
    void __merge_sort_loop(_RandomAccessIter1 __first,
                           _RandomAccessIter1 __last,
                           _RandomAccessIter2 __result, _Distance __step_size)
    {
        _Distance __two_step = 2 * __step_size;

        while (__last - __first >= __two_step)
        {
            __result = merge(__first, __first + __step_size,
                             __first + __step_size, __first + __two_step,
                             __result);
            __first += __two_step;
        }

        __step_size = min(_Distance(__last - __first), __step_size);
        merge(__first, __first + __step_size, __first + __step_size, __last,
              __result);
    }

    template <class _RandomAccessIter1, class _RandomAccessIter2,
              class _Distance, class _Compare>
    void __merge_sort_loop(_RandomAccessIter1 __first,
                           _RandomAccessIter1 __last,
                           _RandomAccessIter2 __result, _Distance __step_size,
                           _Compare __comp)
    {
        _Distance __two_step = 2 * __step_size;

        while (__last - __first >= __two_step)
        {
            __result = merge(__first, __first + __step_size,
                             __first + __step_size, __first + __two_step,
                             __result,
                             __comp);
            __first += __two_step;
        }
        __step_size = min(_Distance(__last - __first), __step_size);

        merge(__first, __first + __step_size,
              __first + __step_size, __last,
              __result,
              __comp);
    }

    const int __stl_chunk_size = 7;

    template <class _RandomAccessIter, class _Distance>
    void __chunk_insertion_sort(_RandomAccessIter __first,
                                _RandomAccessIter __last, _Distance __chunk_size)
    {
        while (__last - __first >= __chunk_size)
        {
            __insertion_sort(__first, __first + __chunk_size);
            __first += __chunk_size;
        }
        __insertion_sort(__first, __last);
    }

    template <class _RandomAccessIter, class _Distance, class _Compare>
    void __chunk_insertion_sort(_RandomAccessIter __first,
                                _RandomAccessIter __last,
                                _Distance __chunk_size, _Compare __comp)
    {
        while (__last - __first >= __chunk_size)
        {
            __insertion_sort(__first, __first + __chunk_size, __comp);
            __first += __chunk_size;
        }
        __insertion_sort(__first, __last, __comp);
    }

    template <class _RandomAccessIter, class _Pointer, class _Distance>
    void __merge_sort_with_buffer(_RandomAccessIter __first,
                                  _RandomAccessIter __last,
                                  _Pointer __buffer, _Distance *)
    {
        _Distance __len = __last - __first;
        _Pointer __buffer_last = __buffer + __len;

        _Distance __step_size = __stl_chunk_size;
        __chunk_insertion_sort(__first, __last, __step_size);

        while (__step_size < __len)
        {
            __merge_sort_loop(__first, __last, __buffer, __step_size);
            __step_size *= 2;
            __merge_sort_loop(__buffer, __buffer_last, __first, __step_size);
            __step_size *= 2;
        }
    }

    template <class _RandomAccessIter, class _Pointer, class _Distance,
              class _Compare>
    void __merge_sort_with_buffer(_RandomAccessIter __first,
                                  _RandomAccessIter __last, _Pointer __buffer,
                                  _Distance *, _Compare __comp)
    {
        _Distance __len = __last - __first;
        _Pointer __buffer_last = __buffer + __len;

        _Distance __step_size = __stl_chunk_size;
        __chunk_insertion_sort(__first, __last, __step_size, __comp);

        while (__step_size < __len)
        {
            __merge_sort_loop(__first, __last, __buffer, __step_size, __comp);
            __step_size *= 2;
            __merge_sort_loop(__buffer, __buffer_last, __first, __step_size, __comp);
            __step_size *= 2;
        }
    }
    template <class _RandomAccessIter, class _Pointer, class _Distance>
    void __stable_sort_adaptive(_RandomAccessIter __first,
                                _RandomAccessIter __last, _Pointer __buffer,
                                _Distance __buffer_size)
    {
        _Distance __len = (__last - __first + 1) / 2;
        _RandomAccessIter __middle = __first + __len;
        if (__len > __buffer_size)
        {
            __stable_sort_adaptive(__first, __middle, __buffer, __buffer_size);
            __stable_sort_adaptive(__middle, __last, __buffer, __buffer_size);
        }
        else
        {
            __merge_sort_with_buffer(__first, __middle, __buffer, (_Distance *)0);
            __merge_sort_with_buffer(__middle, __last, __buffer, (_Distance *)0);
        }
        __merge_adaptive(__first, __middle, __last, _Distance(__middle - __first),
                         _Distance(__last - __middle), __buffer, __buffer_size);
    }

    template <class _RandomAccessIter, class _Pointer, class _Distance,
              class _Compare>
    void __stable_sort_adaptive(_RandomAccessIter __first,
                                _RandomAccessIter __last, _Pointer __buffer,
                                _Distance __buffer_size, _Compare __comp)
    {
        _Distance __len = (__last - __first + 1) / 2;
        _RandomAccessIter __middle = __first + __len;
        if (__len > __buffer_size)
        {
            __stable_sort_adaptive(__first, __middle, __buffer, __buffer_size,
                                   __comp);
            __stable_sort_adaptive(__middle, __last, __buffer, __buffer_size,
                                   __comp);
        }
        else
        {
            __merge_sort_with_buffer(__first, __middle, __buffer, (_Distance *)0,
                                     __comp);
            __merge_sort_with_buffer(__middle, __last, __buffer, (_Distance *)0,
                                     __comp);
        }
        __merge_adaptive(__first, __middle, __last, _Distance(__middle - __first),
                         _Distance(__last - __middle), __buffer, __buffer_size,
                         __comp);
    }
    template <class _RandomAccessIter, class _Tp, class _Distance>
    inline void __stable_sort_aux(_RandomAccessIter __first,
                                  _RandomAccessIter __last, _Tp *, _Distance *)
    {
        _Distance __n = davis::distance(__first, __last);
        std::pair<_Tp *, _Distance> __buf = std::get_temporary_buffer<_Tp>(__n);
        if (__buf.first == nullptr)
            __inplace_stable_sort(__first, __last);
        else
            __stable_sort_adaptive(__first, __last, __buf.first,
                                   _Distance(__buf.second));
    }

    template <class _RandomAccessIter, class _Tp, class _Distance, class _Compare>
    inline void __stable_sort_aux(_RandomAccessIter __first,
                                  _RandomAccessIter __last, _Tp *, _Distance *,
                                  _Compare __comp)
    {
        _Distance __n = davis::distance(__first, __last);
        std::pair<_Tp *, _Distance> __buf = std::get_temporary_buffer<_Tp>(__n);
        if (__buf.first == nullptr)
            __inplace_stable_sort(__first, __last,__comp);
        else
            __stable_sort_adaptive(__first, __last, __buf.first,
                                   _Distance(__buf.second),__comp);
    }
    template <class _RandomAccessIterator>
    void stable_sort(_RandomAccessIterator __first, _RandomAccessIterator __last)
    {
        __stable_sort_aux(__first, __last, davis::value_type(__first), davis::distance_type(__first));
    }

    template <class _RandomAccessIterator, class _Compare>
    void stable_sort(_RandomAccessIterator __first, _RandomAccessIterator __last,
                     _Compare __comp)
    {
        __stable_sort_aux(__first, __last, davis::value_type(__first), davis::distance_type(__first),__comp);
    }

    template <class _RandomAccessIter, class _Tp>
    void __partial_sort(_RandomAccessIter __first, _RandomAccessIter __middle,
                        _RandomAccessIter __last, _Tp *)
    {
        make_heap(__first, __middle);
        for (_RandomAccessIter __i = __middle; __i < __last; ++__i)
            if (*__i < *__first)
                __pop_heap(__first, __middle, __i, _Tp(*__i),
                           davis::distance_type(__first));
        sort_heap(__first, __middle);
    }

    template <class _RandomAccessIterator>
    void partial_sort(_RandomAccessIterator __first, _RandomAccessIterator __middle,
                      _RandomAccessIterator __last)
    {
        __partial_sort(__first, __middle, __last, davis::value_type(__first));
    }

    template <class _RandomAccessIter, class _Tp, class _Compare>
    void __partial_sort(_RandomAccessIter __first, _RandomAccessIter __middle,
                        _RandomAccessIter __last, _Tp *, _Compare __comp)
    {
        make_heap(__first, __middle, __comp);
        for (_RandomAccessIter __i = __middle; __i < __last; ++__i)
            if (__comp(*__i, *__first))
                __pop_heap(__first, __middle, __i, _Tp(*__i), __comp,
                           davis::distance_type(__first));
        sort_heap(__first, __middle, __comp);
    }

    template <class _RandomAccessIterator, class _Compare>
    void partial_sort(_RandomAccessIterator __first, _RandomAccessIterator __middle,
                      _RandomAccessIterator __last, _Compare __comp)
    {
        __partial_sort(__first, __middle, __last, davis::value_type(__first),__comp);
    }

    template <class _InputIter, class _RandomAccessIter, class _Distance,
              class _Tp>
    _RandomAccessIter __partial_sort_copy(_InputIter __first,
                                          _InputIter __last,
                                          _RandomAccessIter __result_first,
                                          _RandomAccessIter __result_last,
                                          _Distance *, _Tp *)
    {
        if (__result_first == __result_last)
            return __result_last;
        _RandomAccessIter __result_real_last = __result_first;
        while (__first != __last && __result_real_last != __result_last)
        {
            *__result_real_last = *__first;
            ++__result_real_last;
            ++__first;
        }
        make_heap(__result_first, __result_real_last);
        while (__first != __last)
        {
            if (*__first < *__result_first)
                __adjust_heap(__result_first, _Distance(0),
                              _Distance(__result_real_last - __result_first),
                              _Tp(*__first));
            ++__first;
        }
        sort_heap(__result_first, __result_real_last);
        return __result_real_last;
    }
    template <class _InputIterator, class _RandomAccessIterator>
    _RandomAccessIterator
    partial_sort_copy(_InputIterator __first, _InputIterator __last,
                      _RandomAccessIterator __result_first,
                      _RandomAccessIterator __result_last)
    {
        return __partial_sort_copy(__first, __last, __result_first, __result_last,
                                   davis::distance_type(__result_first),
                                   davis::value_type(__first));
    }

    template <class _InputIter, class _RandomAccessIter, class _Compare,
              class _Distance, class _Tp>
    _RandomAccessIter __partial_sort_copy(_InputIter __first,
                                          _InputIter __last,
                                          _RandomAccessIter __result_first,
                                          _RandomAccessIter __result_last,
                                          _Compare __comp, _Distance *, _Tp *)
    {
        if (__result_first == __result_last)
            return __result_last;
        _RandomAccessIter __result_real_last = __result_first;
        while (__first != __last && __result_real_last != __result_last)
        {
            *__result_real_last = *__first;
            ++__result_real_last;
            ++__first;
        }
        make_heap(__result_first, __result_real_last, __comp);
        while (__first != __last)
        {
            if (__comp(*__first, *__result_first))
                __adjust_heap(__result_first, _Distance(0),
                              _Distance(__result_real_last - __result_first),
                              _Tp(*__first),
                              __comp);
            ++__first;
        }
        sort_heap(__result_first, __result_real_last, __comp);
        return __result_real_last;
    }

    template <class _InputIterator, class _RandomAccessIterator, class _Compare>
    _RandomAccessIterator
    partial_sort_copy(_InputIterator __first, _InputIterator __last,
                      _RandomAccessIterator __result_first,
                      _RandomAccessIterator __result_last, _Compare __comp)
    {
        return __partial_sort_copy(__first, __last, __result_first, __result_last,
                                   __comp,
                                   davis::distance_type(__result_first),
                                   davis::value_type(__first));
    }

    template <class _ForwardIterator>
    bool is_sorted(_ForwardIterator __first, _ForwardIterator __last);
    // TODO

    template <class _ForwardIterator, class _Compare>
    bool is_sorted(_ForwardIterator __first, _ForwardIterator __last, _Compare __comp);
    // TODO

    template <class _ForwardIterator>
    _ForwardIterator is_sorted_until(_ForwardIterator __first, _ForwardIterator __last);
    // TODO

    template <class _ForwardIterator, class Compare>
    _ForwardIterator is_sorted_until(_ForwardIterator __first, _ForwardIterator __last,
                                    Compare comp);
    // TODO
    template <class _RandomAccessIter, class _Tp>
    void __nth_element(_RandomAccessIter __first, _RandomAccessIter __nth,
                       _RandomAccessIter __last, _Tp *)
    {
        while (__last - __first > 3)
        {
            _RandomAccessIter __cut =
                __unguarded_partition(__first, __last,
                                      _Tp(__median(*__first,
                                                   *(__first + (__last - __first) / 2),
                                                   *(__last - 1))));
            if (__cut <= __nth)
                __first = __cut;
            else
                __last = __cut;
        }
        __insertion_sort(__first, __last);
    }
    template <class _RandomAccessIterator>
    void nth_element(_RandomAccessIterator __first, _RandomAccessIterator __nth,
                     _RandomAccessIterator __last)
    {
        __nth_element(__first, __nth, __last, davis::value_type(__first));
    }
    template <class _RandomAccessIter, class _Tp, class _Compare>
    void __nth_element(_RandomAccessIter __first, _RandomAccessIter __nth,
                       _RandomAccessIter __last, _Tp *, _Compare __comp)
    {
        while (__last - __first > 3)
        {
            _RandomAccessIter __cut =
                __unguarded_partition(__first, __last,
                                      _Tp(__median(*__first,
                                                   *(__first + (__last - __first) / 2),
                                                   *(__last - 1),
                                                   __comp)),
                                      __comp);
            if (__cut <= __nth)
                __first = __cut;
            else
                __last = __cut;
        }
        __insertion_sort(__first, __last, __comp);
    }
    template <class _RandomAccessIterator, class _Compare>
    void nth_element(_RandomAccessIterator __first, _RandomAccessIterator __nth,
                     _RandomAccessIterator __last, _Compare __comp)
    {
        __nth_element(__first, __nth, __last, davis::value_type(__first),__comp);
    }

    // Binary search
    template <class _ForwardIterator, class _Tp, class _Distance>
    _ForwardIterator __lower_bound(_ForwardIterator __first,
                                   _ForwardIterator __last,
                                   const _Tp &__val, _Distance *)
    {
        _Distance __len = davis::distance(__first, __last);
        _ForwardIterator __middle;
        while (__len > 0)
        {
            _Distance __half = __len >> 1;
            davis::advance(__middle, __half);
            if (*__middle < __val)
            {
                __first = __middle;
                ++__first;
                __len = __len - __half - 1;
            }
            else
                __len = __half;
        }
        return __first;
    }
    template <class _ForwardIterator, class _Tp>
    _ForwardIterator lower_bound(_ForwardIterator __first, _ForwardIterator __last,
                                 const _Tp &__val)
    {
        return __lower_bound(__first,__last,__val,davis::distance_type(__first));
    }
    template <class _ForwardIterator, class _Tp, class _Distance,class _Compare>
    _ForwardIterator __lower_bound(_ForwardIterator __first,
                                   _ForwardIterator __last,
                                   const _Tp &__val, _Distance *,_Compare __comp)
    {
        _Distance __len = davis::distance(__first, __last);
        _ForwardIterator __middle;
        while (__len > 0)
        {
            _Distance __half = __len >> 1;
            davis::advance(__middle, __half);
            if (__comp(*__middle, __val))
            {
                __first = __middle;
                ++__first;
                __len = __len - __half - 1;
            }
            else
                __len = __half;
        }
        return __first;
    }
    template <class _ForwardIterator, class _Tp, class _Compare>
    _ForwardIterator lower_bound(_ForwardIterator __first, _ForwardIterator __last,
                                const _Tp & __val, _Compare __comp)
    {
        return __lower_bound(__first, __last, __val, davis::distance_type(__first), __comp);
    }
    template <class _ForwardIterator, class _Tp, class _Distance>
    _ForwardIterator __upper_bound(_ForwardIterator __first, _ForwardIterator __last,
                                 const _Tp &__val, _Distance*)
    {
        _Distance __len = davis::distance(__first,__last);
        while (__len > 0)
        {
            _Distance __half = __len >> 1;
            _ForwardIterator __middle = __first;
            davis::advance(__middle, __half);
            if (__val < *__middle)
                __len = __half;
            else
            {
                __first=__middle;
                ++__first;
                __len = __len - __half - 1;
            }
        }
        return __first;
    }
    template <class _ForwardIterator, class _Tp>
    _ForwardIterator upper_bound(_ForwardIterator __first, _ForwardIterator __last,
                                const _Tp & __val)
    {
        return __upper_bound(__first, __last, __val, davis::distance_type(__first));
    }
    template <class _ForwardIterator, class _Tp, class _Distance, class _Compare>
    _ForwardIterator __upper_bound(_ForwardIterator __first, _ForwardIterator __last,
                                   const _Tp &__val, _Distance *, _Compare __comp)
    {
        _Distance __len = davis::distance(__first, __last);
        while (__len > 0)
        {
            _Distance __half = __len >> 1;
            _ForwardIterator __middle = __first;
            davis::advance(__middle, __half);
            if (__comp(__val, *__middle))
                __len = __half;
            else
            {
                __first = __middle;
                ++__first;
                __len = __len - __half - 1;
            }
        }
        return __first;
    }
    template <class _ForwardIterator, class _Tp, class _Compare>
    _ForwardIterator upper_bound(_ForwardIterator __first, _ForwardIterator __last,
                                const _Tp &__val, _Compare __comp)
    {
        return __upper_bound(__first, __last, __val, davis::distance_type(__first),__comp);
    }
    // template <class _ForwardIterator, class _Tp, class _Distance>
    // std::pair<_ForwardIterator, _ForwardIterator>
    // __equal_range(_ForwardIterator __first, _ForwardIterator __last,
    //               const _Tp &__val, _Distance *)
    // {
    //     _Distance __len = davis::distance(__first,__last);
    //     _ForwardIterator __middle, __left,__right;
    //     while (__len > 0)
    //     {
    //         _Distance __half = __len >> 1;
    //         __middle = __first;
    //         davis::advance(__middle, __half);
    //         if(__val<*__middle){
    //             __len = __half;
    //         }else if(*__middle<__val){
    //             __first = __middle;
    //             ++__first;
    //             __len = __len - __half -1;
    //         }else{
    //             __left = davis::lower_bound(__first,__middle,__val);
    //             davis::advance(__first, __len);
    //             __right = upper_bound(++__middle, __first, __val);
    //             return std::pair<_ForwardIterator, _ForwardIterator>(__left, __right);
    //         }
    //     }
    //     return std::pair<_ForwardIterator, _ForwardIterator>(__first,__first);
    // }
    // template <class _ForwardIterator, class _Tp>
    // inline std::pair<_ForwardIterator, _ForwardIterator>
    // equal_range(_ForwardIterator __first, _ForwardIterator __last, const _Tp &__val)
    // {
    //     return __equal_range(__first,__last,__val,davis::distance_type(__first));
    // }
    // template <class _ForwardIterator, class _Tp, class _Distance,class _Compare>
    // std::pair<_ForwardIterator, _ForwardIterator>
    // __equal_range(_ForwardIterator __first, _ForwardIterator __last,
    //               const _Tp &__val, _Distance *, _Compare __comp)
    // {
    //     _Distance __len = davis::distance(__first, __last);
    //     _ForwardIterator __middle, __left, __right;
    //     while (__len > 0)
    //     {
    //         _Distance __half = __len >> 1;
    //         __middle = __first;
    //         davis::advance(__middle, __half);
    //         if (__comp(__val, *__middle))
    //         {
    //             __len = __half;
    //         }
    //         else if (__comp(*__middle, __val))
    //         {
    //             __first = __middle;
    //             ++__first;
    //             __len = __len - __half - 1;
    //         }
    //         else
    //         {
    //             __left = davis::lower_bound(__first, __middle, __val);
    //             davis::advance(__first, __len);
    //             __right = upper_bound(++__middle, __first, __val);
    //             return std::pair<_ForwardIterator, _ForwardIterator>(__left, __right);
    //         }
    //     }
    //     return std::pair<_ForwardIterator, _ForwardIterator>(__first, __first);
    // }
    // template <class _ForwardIterator, class _Tp, class _Compare>
    // typename std::pair<_ForwardIterator, _ForwardIterator>
    // equal_range(_ForwardIterator __first, _ForwardIterator __last, const _Tp &__val,
    //             _Compare __comp)
    // {
    //     return __equal_range(__first, __last, __val, davis::distance_type(__first),__comp);
    // }

    template <class _ForwardIterator, class _Tp>
    bool binary_search(_ForwardIterator __first, _ForwardIterator __last,
                       const _Tp &__val)
    {
        _ForwardIterator __it = davis::lower_bound(__first, __last, __val);
        return !(__it == __last) && !(__val < *__it);
    }

    template <class _ForwardIterator, class _Tp, class _Compare>
    bool binary_search(_ForwardIterator __first, _ForwardIterator __last,
                       const _Tp &__val, _Compare __comp)
    {
        _ForwardIterator __it = davis::lower_bound(__first, __last, __val, __comp);
        return !(__it == __last) && !(__comp(__val , *__it));
    }

    // Merge
    template <class _InputIterator1, class _InputIterator2, class _OutputIterator>
    _OutputIterator merge(_InputIterator1 __first1, _InputIterator1 __last1,
                          _InputIterator2 __first2, _InputIterator2 __last2,
                          _OutputIterator __result)
    {
        while (__first1 != __last1 && __first2 != __last2)
        {
            if (*__first1 < *__first2)
            {
                *__result = *__first1;
                ++__first1;
                ++__result;
            }
            else
            {
                *__result = *__first2;
                ++__first2;
                ++__result;
            }
        }
        return davis::copy(__first1,__last1,davis::copy(__first2,__last2,__result));
    }
    template <class _BidirectionalIter1, class _BidirectionalIter2,
              class _BidirectionalIter3>
    _BidirectionalIter3 __merge_backward(_BidirectionalIter1 __first1,
                                         _BidirectionalIter1 __last1,
                                         _BidirectionalIter2 __first2,
                                         _BidirectionalIter2 __last2,
                                         _BidirectionalIter3 __result) 
    {
        if (__first1 == __last1)
            return davis::copy_backward(__first2, __last2, __result);
        if (__first2 == __last2)
            return davis::copy_backward(__first1, __last1, __result);
        --__last1;
        --__last2;
        while (true)
        {
            if(*__last1<*__last2){
                *--__result = *__last1;
                if(__last1==__first1)
                    return davis::copy_backward(__first2,__last2,__result);
                --__last1;
            }else{
                *--__result = *__last2;
                if (__last2 == __first2)
                    return davis::copy_backward(__first1, __last1, __result);
                --__last2;
            }
        }
    }
    template <class _BidirectionalIter, class _Distance, class _Pointer>
    void __merge_adaptive(_BidirectionalIter __first,
                          _BidirectionalIter __middle,
                          _BidirectionalIter __last,
                          _Distance __len1, _Distance __len2,
                          _Pointer __buffer, _Distance __buffer_size)
    {
        if (__len1 <= __len2 && __len1 <= __buffer_size)
        {
            _Pointer __buffer_end = copy(__first, __middle, __buffer);
            merge(__buffer, __buffer_end, __middle, __last, __first);
        }
        else if (__len2 <= __buffer_size)
        {
            _Pointer __buffer_end = copy(__middle, __last, __buffer);
            __merge_backward(__first, __middle, __buffer, __buffer_end, __last);
        }
        else
        {
            _BidirectionalIter __first_cut = __first;
            _BidirectionalIter __second_cut = __middle;
            _Distance __len11 = 0;
            _Distance __len22 = 0;
            if (__len1 > __len2)
            {
                __len11 = __len1 / 2;
                advance(__first_cut, __len11);
                __second_cut = lower_bound(__middle, __last, *__first_cut);
                distance(__middle, __second_cut, __len22);
            }
            else
            {
                __len22 = __len2 / 2;
                advance(__second_cut, __len22);
                __first_cut = upper_bound(__first, __middle, *__second_cut);
                distance(__first, __first_cut, __len11);
            }
            _BidirectionalIter __new_middle =
                __rotate_adaptive(__first_cut, __middle, __second_cut, __len1 - __len11,
                                  __len22, __buffer, __buffer_size);
            __merge_adaptive(__first, __first_cut, __new_middle, __len11,
                             __len22, __buffer, __buffer_size);
            __merge_adaptive(__new_middle, __second_cut, __last, __len1 - __len11,
                             __len2 - __len22, __buffer, __buffer_size);
        }
    }
    template <class _InputIterator1, class _InputIterator2,
              class _OutputIterator, class _Compare>
    _OutputIterator merge(_InputIterator1 __first1, _InputIterator1 __last1,
                         _InputIterator2 __first2, _InputIterator2 __last2,
                         _OutputIterator __result, _Compare __comp)
    {
        while (__first1 != __last1 && __first2 != __last2)
        {
            if (__comp(*__first1, *__first2))
            {
                *__result = *__first1;
                ++__first1;
                ++__result;
            }
            else
            {
                *__result = *__first2;
                ++__first2;
                ++__result;
            }
        }
        return davis::copy(__first1, __last1, davis::copy(__first2, __last2, __result));
    }
    
    template <class _BidirectionalIterator,class _Tp ,class _Distance>
    void __inplace_merge_aux(_BidirectionalIterator __first, _BidirectionalIterator __middle,
                             _BidirectionalIterator __last,_Tp*, _Distance *)
    {
       _Distance __len1 = davis::distance(__first,__middle);
       _Distance __len2 = davis::distance(__middle,__last);
       std::pair<_Tp*, _Distance> __buf = std::get_temporary_buffer<_Tp>(__len1 + __len2);
       if (__buf.first == nullptr)
           __merge_without_buffer(__first, __middle, __last, __len1, __len2);
       else
           __merge_adaptive(__first, __middle, __last, __len1, __len2,
                            __buf.first, __buf.second);
    }
    template <class _BidirectionalIterator>
    void inplace_merge(_BidirectionalIterator __first, _BidirectionalIterator __middle,
                       _BidirectionalIterator __last)
    {
        if (__first == __middle || __middle == __last)
            return;
        __inplace_merge_aux(__first, __middle, __last,
                            davis::value_type(__first),
                            davis::distance_type(__first));
    }
    template <class _BidirectionalIter1, class _BidirectionalIter2,
              class _BidirectionalIter3, class _Compare>
    _BidirectionalIter3 __merge_backward(_BidirectionalIter1 __first1,
                                         _BidirectionalIter1 __last1,
                                         _BidirectionalIter2 __first2,
                                         _BidirectionalIter2 __last2,
                                         _BidirectionalIter3 __result,
                                         _Compare __comp)
    {
        if (__first1 == __last1)
            return davis::copy_backward(__first2, __last2, __result);
        if (__first2 == __last2)
            return davis::copy_backward(__first1, __last1, __result);
        --__last1;
        --__last2;
        while (true)
        {
            if (__comp(*__last1, *__last2))
            {
                *--__result = *__last1;
                if (__last1 == __first1)
                    return davis::copy_backward(__first2, __last2, __result);
                --__last1;
            }
            else
            {
                *--__result = *__last2;
                if (__last2 == __first2)
                    return davis::copy_backward(__first1, __last1, __result);
                --__last2;
            }
        }
    }
    template <class _BidirectionalIter, class _Distance, class _Pointer,class _Compare>
    void __merge_adaptive(_BidirectionalIter __first,
                          _BidirectionalIter __middle,
                          _BidirectionalIter __last,
                          _Distance __len1, _Distance __len2,
                          _Pointer __buffer, _Distance __buffer_size, _Compare __comp)
    {
        if (__len1 <= __len2 && __len1 <= __buffer_size)
        {
            _Pointer __buffer_end = copy(__first, __middle, __buffer);
            merge(__buffer, __buffer_end, __middle, __last, __first,__comp);
        }
        else if (__len2 <= __buffer_size)
        {
            _Pointer __buffer_end = copy(__middle, __last, __buffer);
            __merge_backward(__first, __middle, __buffer, __buffer_end, __last,__comp);
        }
        else
        {
            _BidirectionalIter __first_cut = __first;
            _BidirectionalIter __second_cut = __middle;
            _Distance __len11 = 0;
            _Distance __len22 = 0;
            if (__len1 > __len2)
            {
                __len11 = __len1 / 2;
                advance(__first_cut, __len11);
                __second_cut = lower_bound(__middle, __last, *__first_cut,__comp);
                distance(__middle, __second_cut, __len22);
            }
            else
            {
                __len22 = __len2 / 2;
                advance(__second_cut, __len22);
                __first_cut = upper_bound(__first, __middle, *__second_cut, __comp);
                distance(__first, __first_cut, __len11);
            }
            _BidirectionalIter __new_middle =
                __rotate_adaptive(__first_cut, __middle, __second_cut, __len1 - __len11,
                                  __len22, __buffer, __buffer_size);
            __merge_adaptive(__first, __first_cut, __new_middle, __len11,
                             __len22, __buffer, __buffer_size, __comp);
            __merge_adaptive(__new_middle, __second_cut, __last, __len1 - __len11,
                             __len2 - __len22, __buffer, __buffer_size, __comp);
        }
    }
    template <class _BidirectionalIterator, class _Tp, class _Distance,class _Compare>
    void __inplace_merge_aux(_BidirectionalIterator __first, _BidirectionalIterator __middle,
                             _BidirectionalIterator __last, _Tp *,_Distance *,_Compare __comp)
    {
        _Distance __len1 = davis::distance(__first, __middle);
        _Distance __len2 = davis::distance(__middle, __last);
        std::pair<_Tp *, _Distance> __buf = std::get_temporary_buffer<_Tp>(__len1 + __len2);
        if (__buf.first == nullptr)
            __merge_without_buffer(__first, __middle, __last, __len1, __len2, __comp);
        else
            __merge_adaptive(__first, __middle, __last, __len1, __len2,
                             __buf.first, __buf.second,__comp);
    }
    template <class _BidirectionalIterator, class _Compare>
    void inplace_merge(_BidirectionalIterator __first, _BidirectionalIterator __middle,
                       _BidirectionalIterator __last, _Compare __comp)
    {
        if (__first == __middle || __middle == __last)
            return;
        __inplace_merge_aux(__first, __middle, __last,
                            davis::value_type(__first),
                            davis::distance_type(__first), __comp);
    }

    template <class _InputIterator1, class _InputIterator2>
    bool includes(_InputIterator1 __first1, _InputIterator1 __last1,
                  _InputIterator2 __first2, _InputIterator2 __last2)
    {
        while(__first1!=__last1&&__first2!=__last2){
            if(*__first2<*__first1){
                return false;
            }else if(*__first1<*__first2){
                ++__first1;
            }else{
                ++__first1;
                ++__first2;
            }
        }
        return __first2==__last2;
    }

    template <class _InputIterator1, class _InputIterator2, class _Compare>
    bool includes(_InputIterator1 __first1, _InputIterator1 __last1,
                  _InputIterator2 __first2, _InputIterator2 __last2, _Compare __comp)
    {
        while (__first1 != __last1 && __first2 != __last2)
        {
            if (__comp(*__first2 , *__first1))
                return false;
            else if (__comp(*__first1 , *__first2))
                ++__first1;
            else
            {
                ++__first1;
                ++__first2;
            }
        }
        return __first2 == __last2;
    }

    template <class _InputIterator1, class _InputIterator2, class _OutputIterator>
    _OutputIterator set_union(_InputIterator1 __first1, _InputIterator1 __last1,
                             _InputIterator2 __first2, _InputIterator2 __last2,
                             _OutputIterator __result)
    {
        while (__first1 != __last1 && __first2 != __last2)
        {
            if (*__first1 < *__first2)
            {
                *__result = __first1;
                ++__first1;
            }
            else if (*__first2 < *__first1)
            {
                *__result = __first2;
                ++__first2;
            }
            else
            {
                *__result = __first2;
                ++__first1;
                ++__first2;
            }
            ++__result;
        }
        return davis::copy(__first1, __last1, davis::copy(__first2, __last2, __result));
    }

    template <class _InputIterator1, class _InputIterator2,
              class _OutputIterator, class _Compare>
    _OutputIterator set_union(_InputIterator1 __first1, _InputIterator1 __last1,
                             _InputIterator2 __first2, _InputIterator2 __last2,
                             _OutputIterator __result, _Compare __comp)
    {
        while (__first1 != __last1 && __first2 != __last2)
        {
            if (__comp(*__first1, *__first2))
            {
                *__result = __first1;
                ++__first1;
            }
            else if (__comp(*__first2, *__first1))
            {
                *__result = __first2;
                ++__first2;
            }else{
                *__result = __first2;
                ++__first1;
                ++__first2;
            }
            ++__result;
        }
        return davis::copy(__first1, __last1, davis::copy(__first2, __last2, __result));
    }

    template <class _InputIterator1, class _InputIterator2, class _OutputIterator>
    _OutputIterator set_intersection(_InputIterator1 __first1, _InputIterator1 __last1,
                                    _InputIterator2 __first2, _InputIterator2 __last2,
                                    _OutputIterator __result)
    {
        while (__first1 != __last1 && __first2 != __last2)
        {
            if (*__first1 < *__first2)
                ++__first1;
            else if (*__first2 < *__first1)
                ++__first2;
            else
            {
                *__result = *__first1;
                ++__first1;
                ++__first2;
                ++__result;
            }
        }
        return __result;
    }

    template <class _InputIterator1, class _InputIterator2,
              class _OutputIterator, class _Compare>
    _OutputIterator set_intersection(_InputIterator1 __first1, _InputIterator1 __last1,
                                    _InputIterator2 __first2, _InputIterator2 __last2,
                                    _OutputIterator __result, _Compare __comp)
    {
        while (__first1 != __last1 && __first2 != __last2)
        {
            if (__comp(*__first1, *__first2))
                ++__first1;
            else if (__comp(*__first2, *__first1))
                ++__first2;
            else
            {
                *__result = *__first1;
                ++__first1;
                ++__first2;
                ++__result;
            }
        }
        return __result;
    }

    template <class _InputIterator1, class _InputIterator2, class _OutputIterator>
    _OutputIterator set_difference(_InputIterator1 __first1, _InputIterator1 __last1,
                                  _InputIterator2 __first2, _InputIterator2 __last2,
                                  _OutputIterator __result)
    {
        while(__first1!=__last1&&__first2!=__last2){
            if(*__first1<*__first2){
                *__result=*__first1;
                ++__result;
                ++__first1;
            }
            else if (*__first2 < *__first1)
                ++__first2;
            else
            {
                ++__first1;
                ++__first2;
            }
        }
        return davis::copy(__first1,__last1,__result);
    }

    template <class _InputIterator1, class _InputIterator2,
              class _OutputIterator, class _Compare>
    _OutputIterator set_difference(_InputIterator1 __first1, _InputIterator1 __last1,
                                  _InputIterator2 __first2, _InputIterator2 __last2,
                                  _OutputIterator __result, _Compare __comp)
    {
        while (__first1 != __last1 && __first2 != __last2)
        {
            if (__comp (* __first1 , *__first2))
            {
                *__result = *__first1;
                ++__result;
                ++__first1;
            }
            else if (__comp(*__first2 , *__first1))
                ++__first2;
            else
            {
                ++__first1;
                ++__first2;
            }
        }
        return davis::copy(__first1, __last1, __result);
    }

    template <class _InputIterator1, class _InputIterator2, class _OutputIterator>
    _OutputIterator set_symmetric_difference(_InputIterator1 __first1, _InputIterator1 __last1,
                                            _InputIterator2 __first2, _InputIterator2 __last2,
                                            _OutputIterator __result)
    {
        while (__first1 != __last1 && __first2 != __last2)
        {
            if (*__first1 < *__first2)
            {
                *__result = *__first1;
                ++__result;
                ++__first1;
            }
            else if (*__first2 < *__first1)
            {
                *__result = *__first2;
                ++__result;
                ++__first2;
            }
            else
            {
                ++__first1;
                ++__first2;
            }
        }
        return davis::copy(__first1, __last1, __result);
    }

    template <class _InputIterator1, class _InputIterator2,
              class _OutputIterator, class _Compare>
    _OutputIterator set_symmetric_difference(_InputIterator1 __first1, _InputIterator1 __last1,
                                            _InputIterator2 __first2, _InputIterator2 __last2,
                                            _OutputIterator __result, _Compare __comp)
    {
        while (__first1 != __last1 && __first2 != __last2)
        {
            if (__comp(*__first1, *__first2))
            {
                *__result = *__first1;
                ++__result;
                ++__first1;
            }
            else if (__comp(*__first2 , *__first1))
            {
                *__result = *__first2;
                ++__result;
                ++__first2;
            }
            else
            {
                ++__first1;
                ++__first2;
            }
        }
        return davis::copy(__first1, __last1, __result);
    }
    // Heap
    template <class RandomAccessIterator>
    void push_heap(RandomAccessIterator __first, RandomAccessIterator __last);

    template <class RandomAccessIterator, class _Compare>
    void push_heap(RandomAccessIterator __first, RandomAccessIterator __last,
                   _Compare __comp);

    template <class RandomAccessIterator>
    void pop_heap(RandomAccessIterator __first, RandomAccessIterator __last);
    template <class RandomAccessIterator, class _Compare>
    void pop_heap(RandomAccessIterator __first, RandomAccessIterator __last,
                  _Compare __comp);
    template <class RandomAccessIterator>
    void make_heap(RandomAccessIterator __first, RandomAccessIterator __last);
    template <class RandomAccessIterator, class _Compare>
    void make_heap(RandomAccessIterator __first, RandomAccessIterator __last,
                   _Compare __comp);

    template <class RandomAccessIterator>
    void sort_heap(RandomAccessIterator __first, RandomAccessIterator __last);

    template <class RandomAccessIterator, class _Compare>
    void sort_heap(RandomAccessIterator __first, RandomAccessIterator __last,
                   _Compare __comp);

    template <class RandomAccessIterator>
    bool is_heap(RandomAccessIterator __first, RandomAccessIterator __last);

    template <class RandomAccessIterator, class _Compare>
    bool is_heap(RandomAccessIterator __first, RandomAccessIterator __last,
                 _Compare __comp);

    template <class RandomAccessIterator>
    RandomAccessIterator is_heap_until(RandomAccessIterator __first,
                                       RandomAccessIterator __last);

    template <class RandomAccessIterator, class _Compare>
    RandomAccessIterator is_heap_until(RandomAccessIterator __first,
                                       RandomAccessIterator __last,
                                           _Compare __comp);
    //    Min/max
    template <class _Tp>
    const _Tp &min(const _Tp & __a, const _Tp & __b)
    {
        if(__a<__b)
            return __a;
        else
            return __b;
    }
    template <class _Tp, class _Compare>
    const _Tp &min(const _Tp & __a, const _Tp & __b, _Compare __comp)
    {
        if(__comp(__a,__b))
            return __a;
        else
            return __b;
    }
    // template <class _Tp>
    // _Tp min(initializer_list<_Tp> il);
    // template <class _Tp, class _Compare>
    // _Tp min(initializer_list<_Tp> il, _Compare __comp);
    template <class _Tp>
    const _Tp &max(const _Tp & __a, const _Tp & __b)
    {
        if (__a < __b)
            return __b;
        else
            return __a;
    }
    template <class _Tp, class _Compare>
    const _Tp &max(const _Tp & __a, const _Tp & __b, _Compare __comp)
    {
        if(__comp(__a,__b))
            return __b;
        else
            return __a;
    }
    // template <class _Tp>
    // _Tp max(initializer_list<_Tp> il);
    // template <class _Tp, class _Compare>
    // _Tp max(initializer_list<_Tp> il, _Compare __comp);
    template <class _Tp>
    std::pair<const _Tp &, const _Tp &> minmax(const _Tp &a, const _Tp &b);
    template <class _Tp, class _Compare>
    std::pair<const _Tp &, const _Tp &> minmax(const _Tp &a, const _Tp &b, _Compare __comp);

    // template <class _Tp>
    // std::pair<_Tp, _Tp> minmax(initializer_list<_Tp> il);

    // template <class _Tp, class _Compare>
    // std::pair<_Tp, _Tp> minmax(initializer_list<_Tp> il, _Compare __comp);

    template <class _ForwardIterator>
    _ForwardIterator min_element(_ForwardIterator __first, _ForwardIterator __last)
    {
        _ForwardIterator __result=__first;
        while(++__first!=__last)
        {
            if(*__first<*__result)
                *__result=*__first;
        }
        return __result;
    }

    template <class _ForwardIterator, class _Compare>
    _ForwardIterator min_element(_ForwardIterator __first, _ForwardIterator __last,
                                _Compare __comp)
    {
        _ForwardIterator __result = __first;
        while (++__first != __last)
        {
            if (__comp(*__first, *__result))
                *__result = *__first;
        }
        return __result;
    }
    template <class _ForwardIterator>
    _ForwardIterator max_element(_ForwardIterator __first, _ForwardIterator __last)
    {
        _ForwardIterator __result = __first;
        while (++__first != __last)
        {
            if (* __result< *__first)
                *__result = *__first;
        }
        return __result;
    }

    template <class _ForwardIterator, class _Compare>
    _ForwardIterator max_element(_ForwardIterator __first, _ForwardIterator __last,
                                _Compare __comp)
    {
        _ForwardIterator __result = __first;
        while (++__first != __last)
        {
            if (__comp(*__result, *__first))
                *__result = *__first;
        }
        return __result;
    }
    template <class _ForwardIterator>
    std::pair<_ForwardIterator, _ForwardIterator>
    minmax_element(_ForwardIterator __first, _ForwardIterator __last);

    template <class _ForwardIterator, class _Compare>
    std::pair<_ForwardIterator, _ForwardIterator>
    minmax_element(_ForwardIterator __first, _ForwardIterator __last, _Compare __comp);

    template <class _InputIterator1, class _InputIterator2>
    bool lexicographical___compare(_InputIterator1 __first1, _InputIterator1 __last1,
                                 _InputIterator2 __first2, _InputIterator2 __last2)
    {
        for (; __first1 != __last1 && __first2 != __last2; ++__first1, ++__first2)
        {
            if (*__first1 < *__first2)
                return true;
            if (*__first2 < *__first1)
                return false;
        }
        return __first1 == __last1 && __first2 != __last2;
    }

    template <class _InputIterator1, class _InputIterator2, class _Compare>
    bool lexicographical___compare(_InputIterator1 __first1, _InputIterator1 __last1,
                                 _InputIterator2 __first2, _InputIterator2 __last2,
                                 _Compare __comp)
    {
        for (; __first1 != __last1 && __first2 != __last2; ++__first1, ++__first2)
        {
            if (__comp(*__first1, *__first2))
                return true;
            if (__comp(*__first2, *__first1))
                return false;
        }
        return __first1 == __last1 && __first2 != __last2;
    }
    template <class _BidirectionalIterator>
    bool next_permutation(_BidirectionalIterator __first,
                          _BidirectionalIterator __last)
    {
        if (__first == __last)
            return false;
        _BidirectionalIterator __i = __first;
        ++__i;
        if (__i == __last)
            return false;
        __i = __last;
        --__i;

        for (;;)
        {
            _BidirectionalIterator __ii = __i;
            --__i;
            if (*__i < *__ii)
            {   
                _BidirectionalIterator __j = __last;
                while (!(*__i < *--__j))
                {
                }
                iter_swap(__i, __j);
                reverse(__ii, __last);
                return true;
            }
            if (__i == __first)
            {
                reverse(__first, __last);
                return false;
            }
        }
    }
    template <class _BidirectionalIterator, class _Compare>
    bool next_permutation(_BidirectionalIterator __first,
                          _BidirectionalIterator __last, _Compare __comp)
    {
        if(__first==__last) return false;
        _BidirectionalIterator __i = __first;
        ++__i;
        if(__i==__last) return false;
        __i=__last;
        --__i;
        while(true){
            _BidirectionalIterator __ii=__i;
            --__i;
            if(__comp(*__i,*__ii)){
                _BidirectionalIterator __j=__last;
                while(!(__comp(*__i,*--__j)));
                iter_swap(__i,__j);
                reverse(__ii,__last);
                return true;
            }
            if(__i==__first){
                reverse(__first,__last);
                return true;
            }
        }
    }
    template <class _BidirectionalIterator>
    bool prev_permutation(_BidirectionalIterator __first,
                          _BidirectionalIterator __last)
    {
        if (__first == __last)
            return false;
        _BidirectionalIterator __i = __first;
        ++__i;
        if (__i == __last)
            return false;
        __i = __last;
        --__i;
        while (true)
        {
            _BidirectionalIterator __ii = __i;
            --__i;
            if (*__ii < *__i)
            {
                _BidirectionalIterator __j = __last;
                while (!(*--__j< *__i))
                    ;
                iter_swap(__i, __j);
                reverse(__ii, __last);
                return true;
            }
            if (__i == __first)
            {
                reverse(__first, __last);
                return true;
            }
        }
    }
    template <class _BidirectionalIterator, class _Compare>
    bool prev_permutation(_BidirectionalIterator __first,
                          _BidirectionalIterator __last, _Compare __comp)
    {
        if (__first == __last)
            return false;
        _BidirectionalIterator __i = __first;
        ++__i;
        if (__i == __last)
            return false;
        __i = __last;
        --__i;
        while (true)
        {
            _BidirectionalIterator __ii = __i;
            --__i;
            if (__comp(*__ii, *__i))
            {
                _BidirectionalIterator __j = __last;
                while (!(__comp(*--__j, *__i)))
                    ;
                iter_swap(__i, __j);
                reverse(__ii, __last);
                return true;
            }
            if (__i == __first)
            {
                reverse(__first, __last);
                return true;
            }
        }
    }
}
#endif