#ifndef _DAVIS_TYPE_TRAITS_H
#define _DAVIS_TYPE_TRAITS_H
namespace davis
{

    struct __true_type
    {
    };
    struct __false_type
    {
    };

    template <typename T>
    struct __type_traits
    {
        typedef __false_type has_trivial_default_constructor;
        typedef __false_type has_trivial_copy_constructor;
        typedef __false_type has_trivial_assignment_operator;
        typedef __false_type has_trivial_destructor;
        typedef __false_type is_POD_type;
    };
    template <>
    struct __type_traits<char>
    {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_destructor;
        typedef __true_type is_POD_type;
    };

    template <>
    struct __type_traits<unsigned char>
    {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_destructor;
        typedef __true_type is_POD_type;
    };
    template <>
    struct __type_traits<short>
    {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_destructor;
        typedef __true_type is_POD_type;
    };
    template <>
    struct __type_traits<unsigned short>
    {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_destructor;
        typedef __true_type is_POD_type;
    };
    template <>
    struct __type_traits<int>
    {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_destructor;
        typedef __true_type is_POD_type;
    };
    template <>
    struct __type_traits<unsigned int>
    {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_destructor;
        typedef __true_type is_POD_type;
    };
    template <>
    struct __type_traits<long>
    {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_destructor;
        typedef __true_type is_POD_type;
    };
    template <>
    struct __type_traits<float>
    {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_destructor;
        typedef __true_type is_POD_type;
    };
    template <>
    struct __type_traits<double>
    {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_destructor;
        typedef __true_type is_POD_type;
    };
    template <>
    struct __type_traits<long double>
    {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_destructor;
        typedef __true_type is_POD_type;
    };
    template <typename T>
    struct __type_traits<T *>
    {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_destructor;
        typedef __true_type is_POD_type;
    };


    //是否是基础类型  
    template <class _Tp>
    struct _Is_integer
    {
        typedef __false_type _Integral;
    };

    template <>
    struct _Is_integer<bool>
    {
        typedef __true_type _Integral;
    };

    template <>
    struct _Is_integer<char>
    {
        typedef __true_type _Integral;
    };

    template <>
    struct _Is_integer<signed char>
    {
        typedef __true_type _Integral;
    };

    template <>
    struct _Is_integer<unsigned char>
    {
        typedef __true_type _Integral;
    };

    template <>
    struct _Is_integer<wchar_t>
    {
        typedef __true_type _Integral;
    };

    template <>
    struct _Is_integer<short>
    {
        typedef __true_type _Integral;
    };

    template <>
    struct _Is_integer<unsigned short>
    {
        typedef __true_type _Integral;
    };

    template <>
    struct _Is_integer<int>
    {
        typedef __true_type _Integral;
    };

    template <>
    struct _Is_integer<unsigned int>
    {
        typedef __true_type _Integral;
    };

    template <>
    struct _Is_integer<long>
    {
        typedef __true_type _Integral;
    };

    template <>
    struct _Is_integer<unsigned long>
    {
        typedef __true_type _Integral;
    };

    template <>
    struct _Is_integer<long long>
    {
        typedef __true_type _Integral;
    };

    template <>
    struct _Is_integer<unsigned long long>
    {
        typedef __true_type _Integral;
    };
}

#endif