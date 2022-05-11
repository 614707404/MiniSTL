#ifndef DAVIS_FUNCTION_H
#define DAVIS_FUNCTION_H
namespace davis{
    template <class _Arg, class _Result>
    struct unary_function
    {
        typedef _Arg argument_type;
        typedef _Result result_type;
    };
    template <class _Arg1, class _Arg2, class _Result>
    struct binary_function
    {
        typedef _Arg1 first_argument_type;
        typedef _Arg2 second_argument_type;
        typedef _Result result_type;
    };
    template <class _Tp>
    struct plus : public binary_function<_Tp, _Tp, _Tp>
    {
        _Tp operator()(const _Tp &__x, const _Tp &__y) const { return __x + __y; }
    };
    template <class _Tp>
    struct minus : public binary_function<_Tp, _Tp, _Tp>
    {
        _Tp operator()(const _Tp &__x, const _Tp &__y) const { return __x - __y; }
    };
    template <class _Tp>
    struct multiplies : public binary_function<_Tp, _Tp, _Tp>
    {
        _Tp operator()(const _Tp &__x, const _Tp &__y) const { return __x * __y; }
    };
    template <class _Tp>
    struct divides : public binary_function<_Tp, _Tp, _Tp>
    {
        _Tp operator()(const _Tp &__x, const _Tp &__y) const { return __x / __y; }
    };
    template <class _Tp>
    struct modulus : public binary_function<_Tp, _Tp, _Tp>
    {
        _Tp operator()(const _Tp &__x, const _Tp &__y) const { return __x % __y; }
    };
    template <class _Tp>
    struct negates : public unary_function<_Tp, _Tp>
    {
        _Tp operator()(const _Tp &__x) const { return -__x; }
    };
    template <class _Tp>
    struct equal_to : public binary_function<_Tp, _Tp, bool>
    {
        bool operator()(const _Tp &__x, const _Tp &__y) const { return __x == __y; }
    };
    template <class _Tp>
    struct not_equal_to : public binary_function<_Tp, _Tp, bool>
    {
        bool operator()(const _Tp &__x, const _Tp &__y) const { return __x != __y; }
    };
    template <class _Tp>
    struct greater : public binary_function<_Tp, _Tp, bool>
    {
        bool operator()(const _Tp &__x, const _Tp &__y) const { return __x > __y; }
    };
    template <class _Tp>
    struct less : public binary_function<_Tp, _Tp, bool>
    {
        bool operator()(const _Tp &__x, const _Tp &__y) const { return __x < __y; }
    };
    template <class _Tp>
    struct greater_equal : public binary_function<_Tp, _Tp, bool>
    {
        bool operator()(const _Tp &__x, const _Tp &__y) const { return __x >= __y; }
    };
    template <class _Tp>
    struct less_equal : public binary_function<_Tp, _Tp, bool>
    {
        bool operator()(const _Tp &__x, const _Tp &__y) const { return __x <= __y; }
    };
    template <class _Tp>
    struct logical_and : public binary_function<_Tp, _Tp, bool>
    {
        bool operator()(const _Tp &__x, const _Tp &__y) const { return __x && __y; }
    };
    template <class _Tp>
    struct logical_or : public binary_function<_Tp, _Tp, bool>
    {
        bool operator()(const _Tp &__x, const _Tp &__y) const { return __x && __y; }
    };
    template <class _Tp>
    struct logical_not : public unary_function<_Tp, bool>
    {
        bool operator()(const _Tp &__x) const { return !__x; }
    };
    template <class _Predicate>
    class unary_negate  : public unary_function<typename _Predicate::argument_type, bool>
    {
        protected:
            _Predicate _M_pred;
        public:
            explicit unary_function(const _Predicate& __pred):_M_pred(__pred){}
            bool operator()(const typename _Predicate::argument_type & __x) const
            {
                return !_M_pred(__x);
            }
    };
    template <class _Predicate>
    class binary_negate : public binary_function<typename _Predicate::first_argument_type,
                                                 typename _Predicate::second_argument_type,
                                                 bool>
    {
    protected:
        _Predicate _M_pred;

    public:
        explicit binary_negate(const _Predicate &__pred) : _M_pred(__pred) {}
        bool operator()(const typename _Predicate::first_argument_type &__x,
                        const typename _Predicate::second_argument_type &__y) const
        {
            return !_M_pred(__x,__y);
        }
    };

    template <class _Predicate>
    inline unary_negate<_Predicate> not1(const _Predicate& __pred)
    {
        return unary_negate<_Predicate>(__pred);
    }
    template <class _Predicate>
    inline binary_negate<_Predicate> not1(const _Predicate &__pred)
    {
        return binary_negate<_Predicate>(__pred);
    }
    template <class _Operator>
    class binder1st : public unary_function<typename _Operator::second_argument_type,
                                            typename _Operator::result_type>
    {
        protected:
            _Operator _M_op;
            typename _Operator::first_argument_type _M_argu;
        public:
            binder1st(const _Operator &__op,
                      const typename _Operator::first_argument_type& __f)
                : _M_op(__op), _M_argu(__f) {}
            typename _Operator::result_type
            operator()(const typename _Operator::second_argument_type& __x) const
            {
                return _M_op(_M_argu,__x);
            }
    };
    template <class _Operator>
    class binder2nd : public unary_function<typename _Operator::first_argument_type,
                                            typename _Operator::result_type>
    {
    protected:
        _Operator _M_op;
        typename _Operator::second_argument_type _M_argu;

    public:
        binder2nd(const _Operator &__op,
                  const typename _Operator::second_argument_type &__f)
            : _M_op(__op), _M_argu(__f) {}
        typename _Operator::result_type
        operator()(const typename _Operator::first_argument_type &__x) const
        {
            return _M_op(__x,_M_argu);
        }
    };
    template <class _Operation, class _Tp>
    inline binder1st<_Operation>
    bind1st(const _Operator &__op, const _Tp &__x) const
    {
        typedef typename _Operation::first_argument_type _Argu;
        return binder1st<_Operation>(__op, _Argu(__x));
    }
    template <class _Operation, class _Tp>
    inline binder2nd<_Operation>
    bind2nd(const _Operator &__op, const _Tp &__x) const
    {
        typedef typename _Operation::second_argument_type _Argu;
        return binder2nd<_Operation>(__op, _Argu(__x));
    }
    template <class _Arg, calss _Result>
    class pointer_to_unary_function : public unary_function<_Arg, _Result>
    {
        protected:
            _Result (*_M_ptr)(_Arg);
        public:
            explicit pointer_to_unary_function(_Result (*__f)(_Arg)) : _M_ptr(__f) {}
            _Result operator()(_Arg __a) const {
                return _M_ptr(__a);
            }
    };
    template <class _Arg1, class _Arg2, calss _Result>
    class pointer_to_binary_function : public binary_function<_Arg1, _Arg2, _Result>
    {
    protected:
        _Result (*_M_ptr)(_Arg1, _Arg2);

    public:
        explicit pointer_to_binary_function(_Result (*__f)(_Arg1,_Arg2)) : _M_ptr(__f) {}
        _Result operator()(_Arg1 __a,_Arg2 __b) const
        {
            return _M_ptr(__a,__b);
        }
    };
    template <class _Arg, calss _Result>
    inline pointer_to_unary_function<_Arg,_Result> ptr_fun (_Redult (*__ptr)(_Arg)){
        return pointer_to_unary_function<_Arg, _Result>(__ptr);
    }
    template <class _Arg1, class _Arg2, calss _Result>
    inline pointer_to_binary_function<_Arg1, _Arg2, _Result> ptr_fun(_Redult (*__ptr)(_Arg1, _Arg2))
    {
        return pointer_to_binary_function<_Arg1, _Arg2, _Result>(__ptr);
    }

    ////////////////////////////////////////////////////////
    template <class _Ret, class _Tp>
    class mem_fun_t : public unary_function<_Tp *, _Ret>
    {
    public:
        explicit mem_fun_t(_Ret (_Tp::*__pf)()) : _M_f(__pf) {}
        _Ret operator()(_Tp *__p) const { return (__p->*_M_f)(); }

    private:
        _Ret (_Tp::*_M_f)();
    };

    template <class _Ret, class _Tp>
    class const_mem_fun_t : public unary_function<const _Tp *, _Ret>
    {
    public:
        explicit const_mem_fun_t(_Ret (_Tp::*__pf)() const) : _M_f(__pf) {}
        _Ret operator()(const _Tp *__p) const { return (__p->*_M_f)(); }

    private:
        _Ret (_Tp::*_M_f)() const;
    };

    template <class _Ret, class _Tp>
    class mem_fun_ref_t : public unary_function<_Tp, _Ret>
    {
    public:
        explicit mem_fun_ref_t(_Ret (_Tp::*__pf)()) : _M_f(__pf) {}
        _Ret operator()(_Tp &__r) const { return (__r.*_M_f)(); }

    private:
        _Ret (_Tp::*_M_f)();
    };

    template <class _Ret, class _Tp>
    class const_mem_fun_ref_t : public unary_function<_Tp, _Ret>
    {
    public:
        explicit const_mem_fun_ref_t(_Ret (_Tp::*__pf)() const) : _M_f(__pf) {}
        _Ret operator()(const _Tp &__r) const { return (__r.*_M_f)(); }

    private:
        _Ret (_Tp::*_M_f)() const;
    };

    template <class _Ret, class _Tp, class _Arg>
    class mem_fun1_t : public binary_function<_Tp *, _Arg, _Ret>
    {
    public:
        explicit mem_fun1_t(_Ret (_Tp::*__pf)(_Arg)) : _M_f(__pf) {}
        _Ret operator()(_Tp *__p, _Arg __x) const { return (__p->*_M_f)(__x); }

    private:
        _Ret (_Tp::*_M_f)(_Arg);
    };

    template <class _Ret, class _Tp, class _Arg>
    class const_mem_fun1_t : public binary_function<const _Tp *, _Arg, _Ret>
    {
    public:
        explicit const_mem_fun1_t(_Ret (_Tp::*__pf)(_Arg) const) : _M_f(__pf) {}
        _Ret operator()(const _Tp *__p, _Arg __x) const
        {
            return (__p->*_M_f)(__x);
        }

    private:
        _Ret (_Tp::*_M_f)(_Arg) const;
    };

    template <class _Ret, class _Tp, class _Arg>
    class mem_fun1_ref_t : public binary_function<_Tp, _Arg, _Ret>
    {
    public:
        explicit mem_fun1_ref_t(_Ret (_Tp::*__pf)(_Arg)) : _M_f(__pf) {}
        _Ret operator()(_Tp &__r, _Arg __x) const { return (__r.*_M_f)(__x); }

    private:
        _Ret (_Tp::*_M_f)(_Arg);
    };

    template <class _Ret, class _Tp, class _Arg>
    class const_mem_fun1_ref_t : public binary_function<_Tp, _Arg, _Ret>
    {
    public:
        explicit const_mem_fun1_ref_t(_Ret (_Tp::*__pf)(_Arg) const) : _M_f(__pf) {}
        _Ret operator()(const _Tp &__r, _Arg __x) const { return (__r.*_M_f)(__x); }

    private:
        _Ret (_Tp::*_M_f)(_Arg) const;
    };
    template <class _Tp>
    class mem_fun_t<void, _Tp> : public unary_function<_Tp *, void>
    {
    public:
        explicit mem_fun_t(void (_Tp::*__pf)()) : _M_f(__pf) {}
        void operator()(_Tp *__p) const { (__p->*_M_f)(); }

    private:
        void (_Tp::*_M_f)();
    };

    template <class _Tp>
    class const_mem_fun_t<void, _Tp> : public unary_function<const _Tp *, void>
    {
    public:
        explicit const_mem_fun_t(void (_Tp::*__pf)() const) : _M_f(__pf) {}
        void operator()(const _Tp *__p) const { (__p->*_M_f)(); }

    private:
        void (_Tp::*_M_f)() const;
    };

    template <class _Tp>
    class mem_fun_ref_t<void, _Tp> : public unary_function<_Tp, void>
    {
    public:
        explicit mem_fun_ref_t(void (_Tp::*__pf)()) : _M_f(__pf) {}
        void operator()(_Tp &__r) const { (__r.*_M_f)(); }

    private:
        void (_Tp::*_M_f)();
    };

    template <class _Tp>
    class const_mem_fun_ref_t<void, _Tp> : public unary_function<_Tp, void>
    {
    public:
        explicit const_mem_fun_ref_t(void (_Tp::*__pf)() const) : _M_f(__pf) {}
        void operator()(const _Tp &__r) const { (__r.*_M_f)(); }

    private:
        void (_Tp::*_M_f)() const;
    };

    template <class _Tp, class _Arg>
    class mem_fun1_t<void, _Tp, _Arg> : public binary_function<_Tp *, _Arg, void>
    {
    public:
        explicit mem_fun1_t(void (_Tp::*__pf)(_Arg)) : _M_f(__pf) {}
        void operator()(_Tp *__p, _Arg __x) const { (__p->*_M_f)(__x); }

    private:
        void (_Tp::*_M_f)(_Arg);
    };

    template <class _Tp, class _Arg>
    class const_mem_fun1_t<void, _Tp, _Arg>
        : public binary_function<const _Tp *, _Arg, void>
    {
    public:
        explicit const_mem_fun1_t(void (_Tp::*__pf)(_Arg) const) : _M_f(__pf) {}
        void operator()(const _Tp *__p, _Arg __x) const { (__p->*_M_f)(__x); }

    private:
        void (_Tp::*_M_f)(_Arg) const;
    };

    template <class _Tp, class _Arg>
    class mem_fun1_ref_t<void, _Tp, _Arg>
        : public binary_function<_Tp, _Arg, void>
    {
    public:
        explicit mem_fun1_ref_t(void (_Tp::*__pf)(_Arg)) : _M_f(__pf) {}
        void operator()(_Tp &__r, _Arg __x) const { (__r.*_M_f)(__x); }

    private:
        void (_Tp::*_M_f)(_Arg);
    };

    template <class _Tp, class _Arg>
    class const_mem_fun1_ref_t<void, _Tp, _Arg>
        : public binary_function<_Tp, _Arg, void>
    {
    public:
        explicit const_mem_fun1_ref_t(void (_Tp::*__pf)(_Arg) const) : _M_f(__pf) {}
        void operator()(const _Tp &__r, _Arg __x) const { (__r.*_M_f)(__x); }

    private:
        void (_Tp::*_M_f)(_Arg) const;
    };

    template <class _Ret, class _Tp>
    inline mem_fun_t<_Ret, _Tp> mem_fun(_Ret (_Tp::*__f)())
    {
        return mem_fun_t<_Ret, _Tp>(__f);
    }

    template <class _Ret, class _Tp>
    inline const_mem_fun_t<_Ret, _Tp> mem_fun(_Ret (_Tp::*__f)() const)
    {
        return const_mem_fun_t<_Ret, _Tp>(__f);
    }

    template <class _Ret, class _Tp>
    inline mem_fun_ref_t<_Ret, _Tp> mem_fun_ref(_Ret (_Tp::*__f)())
    {
        return mem_fun_ref_t<_Ret, _Tp>(__f);
    }

    template <class _Ret, class _Tp>
    inline const_mem_fun_ref_t<_Ret, _Tp> mem_fun_ref(_Ret (_Tp::*__f)() const)
    {
        return const_mem_fun_ref_t<_Ret, _Tp>(__f);
    }

    template <class _Ret, class _Tp, class _Arg>
    inline mem_fun1_t<_Ret, _Tp, _Arg> mem_fun(_Ret (_Tp::*__f)(_Arg))
    {
        return mem_fun1_t<_Ret, _Tp, _Arg>(__f);
    }

    template <class _Ret, class _Tp, class _Arg>
    inline const_mem_fun1_t<_Ret, _Tp, _Arg> mem_fun(_Ret (_Tp::*__f)(_Arg) const)
    {
        return const_mem_fun1_t<_Ret, _Tp, _Arg>(__f);
    }

    template <class _Ret, class _Tp, class _Arg>
    inline mem_fun1_ref_t<_Ret, _Tp, _Arg> mem_fun_ref(_Ret (_Tp::*__f)(_Arg))
    {
        return mem_fun1_ref_t<_Ret, _Tp, _Arg>(__f);
    }

    template <class _Ret, class _Tp, class _Arg>
    inline const_mem_fun1_ref_t<_Ret, _Tp, _Arg>
    mem_fun_ref(_Ret (_Tp::*__f)(_Arg) const)
    {
        return const_mem_fun1_ref_t<_Ret, _Tp, _Arg>(__f);
    }

    template <class _Ret, class _Tp, class _Arg>
    inline mem_fun1_t<_Ret, _Tp, _Arg> mem_fun1(_Ret (_Tp::*__f)(_Arg))
    {
        return mem_fun1_t<_Ret, _Tp, _Arg>(__f);
    }

    template <class _Ret, class _Tp, class _Arg>
    inline const_mem_fun1_t<_Ret, _Tp, _Arg> mem_fun1(_Ret (_Tp::*__f)(_Arg) const)
    {
        return const_mem_fun1_t<_Ret, _Tp, _Arg>(__f);
    }

    template <class _Ret, class _Tp, class _Arg>
    inline mem_fun1_ref_t<_Ret, _Tp, _Arg> mem_fun1_ref(_Ret (_Tp::*__f)(_Arg))
    {
        return mem_fun1_ref_t<_Ret, _Tp, _Arg>(__f);
    }

    template <class _Ret, class _Tp, class _Arg>
    inline const_mem_fun1_ref_t<_Ret, _Tp, _Arg>
    mem_fun1_ref(_Ret (_Tp::*__f)(_Arg) const)
    {
        return const_mem_fun1_ref_t<_Ret, _Tp, _Arg>(__f);
    }
}
#endif