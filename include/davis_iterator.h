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
        return __distance(__first, __last, category);
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

    template <class _Container>
    class back_insert_iterator
    {
    protected:
        _Container *container;

    public:
        typedef _Container container_type;
        typedef output_iterator_tag iterator_category;
        typedef void value_type;
        typedef void difference_type;
        typedef void pointer;
        typedef void reference;

        explicit back_insert_iterator(_Container &__x) : container(&__x) {}
        back_insert_iterator<_Container> &
        operator=(const typename _Container::value_type &__value)
        {
            container->push_back(__value);
            return *this;
        }
        back_insert_iterator<_Container> &operator*() { return *this; }
        back_insert_iterator<_Container> &operator++() { return *this; }
        back_insert_iterator<_Container> &operator++(int) { return *this; }
    };

    template <class _Container>
    class front_insert_iterator
    {
    protected:
        _Container *container;

    public:
        typedef _Container container_type;
        typedef output_iterator_tag iterator_category;
        typedef void value_type;
        typedef void difference_type;
        typedef void pointer;
        typedef void reference;

        explicit front_insert_iterator(_Container &__x) : container(&__x) {}
        front_insert_iterator<_Container> &
        operator=(const typename _Container::value_type &__value)
        {
            container->push_front(__value);
            return *this;
        }
        front_insert_iterator<_Container> &operator*() { return *this; }
        front_insert_iterator<_Container> &operator++() { return *this; }
        front_insert_iterator<_Container> &operator++(int) { return *this; }
    };

    template <class _Container>
    class insert_iterator
    {
    protected:
        _Container *container;
        typename _Container::iterator iter;

    public:
        typedef _Container container_type;
        typedef output_iterator_tag iterator_category;
        typedef void value_type;
        typedef void difference_type;
        typedef void pointer;
        typedef void reference;

        insert_iterator(_Container &__x, typename _Container::iterator __i)
            : container(&__x), iter(__i) {}
        insert_iterator<_Container> &
        operator=(const typename _Container::value_type &__value)
        {
            iter = container->insert(iter, __value);
            ++iter;
            return *this;
        }
        insert_iterator<_Container> &operator*() { return *this; }
        insert_iterator<_Container> &operator++() { return *this; }
        insert_iterator<_Container> &operator++(int) { return *this; }
    };

    template <class _Iterator>
    class reverse_iterator
    {
    protected:
        _Iterator current;

    public:
        typedef typename iterator_traits<_Iterator>::iterator_category
            iterator_category;
        typedef typename iterator_traits<_Iterator>::value_type
            value_type;
        typedef typename iterator_traits<_Iterator>::difference_type
            difference_type;
        typedef typename iterator_traits<_Iterator>::pointer
            pointer;
        typedef typename iterator_traits<_Iterator>::reference
            reference;

        typedef _Iterator iterator_type;
        typedef reverse_iterator<_Iterator> _Self;

    public:
        reverse_iterator() {}
        explicit reverse_iterator(iterator_type __x) : current(__x) {}

        reverse_iterator(const _Self &__x) : current(__x.current) {}

        template <class _Iter>
        reverse_iterator(const reverse_iterator<_Iter> &__x)
            : current(__x.base())
        {
        }


        iterator_type base() const
        {
            return current;
        }
        reference operator*() const
        {
            _Iterator __tmp = current;
            return *--__tmp;
        }

        pointer operator->() const
        {
            return &(operator*());
        }


        _Self &operator++()
        {
            --current;
            return *this;
        }
        _Self operator++(int)
        {
            _Self __tmp = *this;
            --current;
            return __tmp;
        }
        _Self &operator--()
        {
            ++current;
            return *this;
        }
        _Self operator--(int)
        {
            _Self __tmp = *this;
            ++current;
            return __tmp;
        }

        _Self operator+(difference_type __n) const
        {
            return _Self(current - __n);
        }
        _Self &operator+=(difference_type __n)
        {
            current -= __n;
            return *this;
        }
        _Self operator-(difference_type __n) const
        {
            return _Self(current + __n);
        }
        _Self &operator-=(difference_type __n)
        {
            current += __n;
            return *this;
        }
        reference operator[](difference_type __n) const { return *(*this + __n); }
    };

    template <class _Iterator>
    inline bool operator==(const reverse_iterator<_Iterator> &__x,
                           const reverse_iterator<_Iterator> &__y)
    {
        return __x.base() == __y.base();
    }

    template <class _Iterator>
    inline bool operator<(const reverse_iterator<_Iterator> &__x,
                          const reverse_iterator<_Iterator> &__y)
    {
        return __y.base() < __x.base();
    }



    template <class _Iterator>
    inline bool operator!=(const reverse_iterator<_Iterator> &__x,
                           const reverse_iterator<_Iterator> &__y)
    {
        return !(__x == __y);
    }

    template <class _Iterator>
    inline bool operator>(const reverse_iterator<_Iterator> &__x,
                          const reverse_iterator<_Iterator> &__y)
    {
        return __y < __x;
    }

    template <class _Iterator>
    inline bool operator<=(const reverse_iterator<_Iterator> &__x,
                           const reverse_iterator<_Iterator> &__y)
    {
        return !(__y < __x);
    }

    template <class _Iterator>
    inline bool operator>=(const reverse_iterator<_Iterator> &__x,
                           const reverse_iterator<_Iterator> &__y)
    {
        return !(__x < __y);
    }

    template <class _Tp,
              class _CharT = char, class _Traits = char_traits<_CharT>,
              class _Dist = ptrdiff_t>
    class istream_iterator
    {
    public:
        typedef _CharT char_type;
        typedef _Traits traits_type;
        typedef std::basic_istream<_CharT, _Traits> istream_type;

        typedef input_iterator_tag iterator_category;
        typedef _Tp value_type;
        typedef _Dist difference_type;
        typedef const _Tp *pointer;
        typedef const _Tp &reference;

        istream_iterator() : _M_stream(0), _M_ok(false) {}
        istream_iterator(istream_type &__s) : _M_stream(&__s) { _M_read(); }

        reference operator*() const { return _M_value; }
        pointer operator->() const { return &(operator*()); }

        istream_iterator &operator++()
        {
            _M_read();
            return *this;
        }
        istream_iterator operator++(int)
        {
            istream_iterator __tmp = *this;
            _M_read();
            return __tmp;
        }

        bool _M_equal(const istream_iterator &__x) const
        {
            return (_M_ok == __x._M_ok) && (!_M_ok || _M_stream == __x._M_stream);
        }

    private:
        istream_type *_M_stream;
        _Tp _M_value;
        bool _M_ok;

        void _M_read()
        {
            _M_ok = (_M_stream && *_M_stream) ? true : false;
            if (_M_ok)
            {
                *_M_stream >> _M_value;
                _M_ok = *_M_stream ? true : false;
            }
        }
    };

    template <class _Tp, class _CharT, class _Traits, class _Dist>
    inline bool
    operator==(const istream_iterator<_Tp, _CharT, _Traits, _Dist> &__x,
               const istream_iterator<_Tp, _CharT, _Traits, _Dist> &__y)
    {
        return __x._M_equal(__y);
    }


    template <class _Tp, class _CharT, class _Traits, class _Dist>
    inline bool
    operator!=(const istream_iterator<_Tp, _CharT, _Traits, _Dist> &__x,
               const istream_iterator<_Tp, _CharT, _Traits, _Dist> &__y)
    {
        return !__x._M_equal(__y);
    }
    template <class _Tp>
    class ostream_iterator
    {
    protected:
        ostream *_M_stream;
        const char *_M_string;

    public:
        typedef output_iterator_tag iterator_category;
        typedef void value_type;
        typedef void difference_type;
        typedef void pointer;
        typedef void reference;

        ostream_iterator(ostream &__s) : _M_stream(&__s), _M_string(0) {}
        ostream_iterator(ostream &__s, const char *__c)
            : _M_stream(&__s), _M_string(__c) {}
        ostream_iterator<_Tp> &operator=(const _Tp &__value)
        {
            *_M_stream << __value;
            if (_M_string)
                *_M_stream << _M_string;
            return *this;
        }
        ostream_iterator<_Tp> &operator*() { return *this; }
        ostream_iterator<_Tp> &operator++() { return *this; }
        ostream_iterator<_Tp> &operator++(int) { return *this; }
    };
} // namespace davis
#endif