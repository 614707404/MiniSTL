#ifndef _DAVIS_ITERATOR_H
#define _DAVIS_ITERATOR_H
namespace davis
{

    //五种迭代器类型
    struct input_iterator_tag
    {
    };
    struct output_iterator_tag
    {
    };
    struct forward_iterator_tag : public input_iterator_tag
    {
    };
    struct bidirectional_iterator_tag : public forward_iterator_tag
    {
    };
    struct random_access_iterator_tag : public bidirectional_iterator_tag
    {
    };

    template <class _Category, class _Tp, class _Distance = ptrdiff_t,
              class _Pointer = _Tp *, class _Reference = _Tp &>
    struct iterator
    {
        typedef _Category               iterator_category;
        typedef _Tp                     value_type;
        typedef _Distance               difference_type;
        typedef _Pointer                pointer;
        typedef _Reference              reference;
    };

    template <class _Iterator>
    struct iterator_traits
    {
        typedef typename _Iterator::iterator_category           iterator_category;
        typedef typename _Iterator::value_type                  value_type;
        typedef typename _Iterator::difference_type             difference_type;
        typedef typename _Iterator::pointer                     pointer;
        typedef typename _Iterator::reference                   reference;
    };

    template <class _Tp>
    struct iterator_traits<_Tp *>
    {
        typedef random_access_iterator_tag                      iterator_category;
        typedef _Tp                                             value_type;
        typedef ptrdiff_t                                       difference_type;
        typedef _Tp*                                            pointer;
        typedef _Tp&                                            reference;
    };

    template <class _Tp>
    struct iterator_traits<const _Tp *>
    {
        typedef random_access_iterator_tag                      terator_category;
        typedef _Tp                                             value_type;
        typedef ptrdiff_t                                       difference_type;
        typedef const _Tp *                                     pointer;
        typedef const _Tp &                                     reference;
    };

    template <class _Iterator>
    inline typename iterator_traits<_Iterator>::iterator_category
    iterator_category(const _Iterator &)
    {
        typedef typename iterator_traits<_Iterator>::iterator_category category;
        return category();
    }

    template <class _Iterator>
    inline typename iterator_traits<_Iterator>::difference_type *
    distance_type(const _Iterator)
    {
        return static_cast<typename iterator_traits<_Iterator>::difference_type *>(0);
    }

    template <class _Iterator>
    inline typename iterator_traits<_Iterator>::value_type *
    value_type(const _Iterator)
    {
        return static_cast<typename iterator_traits<_Iterator>::value_type *>(0);
    }

    //  distance函数 辅助函数
    template <class _InputIterator>
    inline typename iterator_traits<_InputIterator>::difference_type
    __distance(_InputIterator __first, _InputIterator __last, input_iterator_tag)
    {
        typename iterator_traits<_InputIterator>::difference_type n = 0;
        while (__first != __last)
        {
            ++__first;
            ++n;
        }
        return n;
    }
    // distance函数 辅助函数
    template <class _RandonAccessIterator>
    inline typename iterator_traits<_RandonAccessIterator>::difference_type
    __distance(_RandonAccessIterator __first, _RandonAccessIterator __last, random_access_iterator_tag)
    {
        return __last - __first;
    }
    //distance函数
    template <class _InputIterator>
    inline typename iterator_traits<_InputIterator>::difference_type
    distance(_InputIterator __first, _InputIterator __last)
    {
        typename iterator_traits<_InputIterator>::iterator_category category;
        return __distance(__first, __last, category());
    }

    template <class _InputIterator, class _Distance>
    inline void __advance(_InputIterator & __i, _Distance __n, input_iterator_tag)
    {
        while (__n--)
        {
            ++__i;
        }
    }
    template <class _BidirectionalIterator, class _Distance>
    inline void __advance(_BidirectionalIterator & __i, _Distance __n, bidirectional_iterator_tag)
    {
        if (__n >= 0)
        {
            while (__n--)
            {
                __i++;
            }
        }
        else
        {
            while (__n++)
            {
                __i--;
            }
        }
    }

    template <class _RandomAccessIterator, class _Distance>
    inline void __advance(_RandomAccessIterator & __i, _Distance __n, random_access_iterator_tag)
    {
        __i += __n;
    }
    template <class __InputIterator, class __Distance>
    inline void advance(__InputIterator & __i, __Distance __n)
    {
        __advance(__i, __n, iterator_category(__i));
    }
    // TODO reverse_iterator
    
} // namespace davis
#endif