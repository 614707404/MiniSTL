#ifndef DAVIS_HEAP_H
#define DAVIS_HEAP_H
#include "davis_iterator.h"
namespace davis
{
    template <class _RandomAccessIterator, class _Distance, class _Tp>
    inline void __push_heap(_RandomAccessIterator __first,
                            _Distance __holeIndex, _Distance __topIndex,
                            _Tp __val)
    {
        _Distance __parent = (__holeIndex - 1) / 2;
        while (__holeIndex > __topIndex && *(__first + __parent) < __val)
        {
            *(__first + __holeIndex) = *(__first + __parent);
            __holeIndex = __parent;
            __parent = (__holeIndex - 1) / 2;
        }
        *(__first + __holeIndex) = __val ;
    }
    template <class _RandomAccessIterator, class _Distance, class _Tp>
    inline void __push_heap_aux(_RandomAccessIterator __first,
                                _RandomAccessIterator __last,
                                _Distance *,
                                _Tp *)
    {
        __push_heap(__first,_Distance((__last-__first)-1),_Distance(0),_Tp(*(__last-1)));
    }
    template <class _RandomAccessIterator>
    inline void push_heap(_RandomAccessIterator __first, _RandomAccessIterator __last)
    {
        __push_heap_aux(__first,__last,davis::distance_type(__first),davis::value_type(__last));
    }
    template <class _RandomAccessIterator, class _Distance, class _Tp, class _Compare>
    inline void __push_heap(_RandomAccessIterator __first,
                            _Distance __holeIndex, _Distance __topIndex,
                            _Tp __val, _Compare __comp)
    {
        _Distance __parent = (__holeIndex - 1) / 2;
        while (__holeIndex > __topIndex && __comp(*(__first + __parent) , __val))
        {
            *(__first + __holeIndex) = *(__first + __parent);
            __holeIndex = __parent;
            __parent = (__holeIndex - 1) / 2;
        }
        *(__first + __holeIndex) = __val;
    }
    template <class _RandomAccessIterator, class _Distance, class _Tp,class _Compare>
    inline void __push_heap_aux(_RandomAccessIterator __first,
                                _RandomAccessIterator __last,
                                _Distance *,
                                _Tp *,_Compare __comp)
    {
        __push_heap(__first, _Distance((__last - __first) - 1), _Distance(0), _Tp(*(__last - 1)),__comp);
    }
    template <class _RandomAccessIterator, class _Compare>
    inline void push_heap(_RandomAccessIterator __first, _RandomAccessIterator __last, _Compare __comp)
    {
        __push_heap_aux(__first, __last, davis::distance_type(__first), davis::value_type(__last),__comp);
    }

    template <class _RandomAccessIterator, class _Tp, class _Distance>
    inline void __adjust_heap(_RandomAccessIterator __first,
                              _Distance __holeIndex,
                              _Distance __len,
                              _Tp __val)
    {
        _Distance __topIndex = __holeIndex;
        _Distance __secondChildIndex = __holeIndex * 2 + 2;
        while (__secondChildIndex < __len)
        {
            if (*(__first + __secondChildIndex) < *(__first + (__secondChildIndex - 1)))
                --__secondChildIndex;
            *(__first + __holeIndex) = *(__first + __secondChildIndex);
            __holeIndex = __secondChildIndex;
            __secondChildIndex = __holeIndex * 2 + 2;
        }
        if (__secondChildIndex == len)
        {
            *(__first + __holeIndex) = *(__first +(__secondChildIndex - 1));
            __holeIndex = __secondChildIndex - 1;
        }
        __push_heap(__first,__holeIndex,__topIndex,__val);
    }
    template <class _RandomAccessIterator, class _Tp, class _Distance>
    inline void __pop_heap(_RandomAccessIterator __first,
                               _RandomAccessIterator __last,
                               _RandomAccessIterator __result,
                               _Tp __val, _Distance *)
    {
        *__result = *__first;
        __adjust_heap(__first, _Distance(0), _Distance(__last - __first), __val);
    }
    template <class _RandomAccessIterator, class _Tp>
    inline void __pop_heap_aux(_RandomAccessIterator __first,
                               _RandomAccessIterator __last,
                               _Tp *)
    {
        __pop_heap(__first, __last - 1, __last - 1,
                   _Tp(*(__last - 1)), davis::distance_type(__first));
    }

    template <class _RandomAccessIterator>
    inline void pop_heap(_RandomAccessIterator __first, _RandomAccessIterator __last)
    {
        __pop_heap_aux(__first,__last,davis::value_type(__first));
    }
    template <class _RandomAccessIterator, class _Tp, class _Distance, class _Compare>
    inline void __adjust_heap(_RandomAccessIterator __first,
                              _Distance __holeIndex,
                              _Distance __len,
                              _Tp __val,_Compare __comp)
    {
        _Distance __topIndex = __holeIndex;
        _Distance __secondChildIndex = __holeIndex * 2 + 2;
        while (__secondChildIndex < __len)
        {
            if (__comp (* (__first + __secondChildIndex) , *(__first + (__secondChildIndex - 1))))
                --__secondChildIndex;
            *(__first + __holeIndex) = *(__first + __secondChildIndex);
            __holeIndex = __secondChildIndex;
            __secondChildIndex = __holeIndex * 2 + 2;
        }
        if (__secondChildIndex == len)
        {
            *(__first + __holeIndex) = *(__first + (__secondChildIndex - 1));
            __holeIndex = __secondChildIndex - 1;
        }
        __push_heap(__first, __holeIndex, __topIndex, __val,__comp);
    }
    template <class _RandomAccessIterator, class _Tp, class _Distance, class _Compare>
    inline void __pop_heap(_RandomAccessIterator __first,
                           _RandomAccessIterator __last,
                           _RandomAccessIterator __result,
                           _Tp __val, _Distance *,_Compare __comp)
    {
        *__result = *__first;
        __adjust_heap(__first, _Distance(0), _Distance(__last - __first), __val,__comp);
    }
    template <class _RandomAccessIterator, class _Tp, class _Compare>
    inline void __pop_heap_aux(_RandomAccessIterator __first,
                               _RandomAccessIterator __last,
                               _Tp *,_Compare __comp)
    {
        __pop_heap(__first, __last - 1, __last - 1,
                   _Tp(*(__last - 1)), davis::distance_type(__first),__comp);
    }

    template <class _RandomAccessIterator, class _Compare>
    inline void pop_heap(_RandomAccessIterator __first, _RandomAccessIterator __last,_Compare __comp)
    {
        __pop_heap_aux(__first, __last, davis::value_type(__first),__comp);
    }


    template <class _RandomAccessIterator, class _Tp, class _Distance>
    void
    __make_heap(_RandomAccessIterator __first,
                _RandomAccessIterator __last, _Tp *, _Distance *)
    {
        if (__last - __first < 2)
            return;                           
        _Distance __len = __last - __first;   
        _Distance __holeIndex = (__len - 2) / 2; 

        while (true)
        {
            __adjust_heap(__first, __holeIndex, __len, _Tp(*(__first + __holeIndex)));
            if (__holeIndex == 0)
                return;
            __holeIndex--;
        }
    }
    template <class _RandomAccessIterator>
    inline void
    make_heap(_RandomAccessIterator __first, _RandomAccessIterator __last)
    {
        __make_heap(__first, __last,
                    davis::value_type(__first), davis::distance_type(__first));
    }
    template <class _RandomAccessIterator, class _Tp, class _Distance, class _Compare>
    void
    __make_heap(_RandomAccessIterator __first,
                _RandomAccessIterator __last, _Tp *, _Distance *,_Compare __comp)
    {
        if (__last - __first < 2)
            return;
        _Distance __len = __last - __first;
        _Distance __holeIndex = (__len - 2) / 2;

        while (true)
        {
            __adjust_heap(__first, __holeIndex, __len, _Tp(*(__first + __holeIndex)),__comp);
            if (__holeIndex == 0)
                return;
            __holeIndex--;
        }
    }
    template <class _RandomAccessIterator,class _Compare>
    inline void
    make_heap(_RandomAccessIterator __first, _RandomAccessIterator __last,_Compare __comp)
    {
        __make_heap(__first, __last,
                    davis::value_type(__first), davis::distance_type(__first),__comp);
    }
    template <class _RandomAccessIterator>
    inline void sort_heap(_RandomAccessIterator __first, _RandomAccessIterator __last)
    {
        while (__last - __first > 1)
        {
            pop_heap(__first, __last--);
        }
    }
    template <class _RandomAccessIterator, class _Compare>
    inline void sort_heap(_RandomAccessIterator __first, _RandomAccessIterator __last, _Compare __comp)
    {
        while (__last - __first > 1)
        {
            pop_heap(__first, __last--, __comp);
        }
    }
} // namespace davis
#endif