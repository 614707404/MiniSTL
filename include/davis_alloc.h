// //具有次配置能力（sub-allocation）的SGI空间配置器
// //暂不实现
// #ifndef _DAVIS_ALLOC_H
// #define _DAVIS_ALLOC_H

// #if 0
// #include <new>
// #define __THROW_BAD_ALLOC throw bad_alloc
// #elif !defined(__THROW_BAD_ALLOC)
// #include <iostream>
// #define __THROW_BAD_ALLOC                      \
//     std::cerr << "out of memory" << std::endl; \
//     exit(1);
// #endif
// namespace DAVIS
// {
//     template <int inst>
//     class __mallo_alloc_template
//     {
//     private:
//         static void *oom_malloc(size_t);
//         static void *oom_realloc(void *, size_t);
//         static void (*__malloc_alloc_oom_handler)();

//     public:
//         static void *allocate(size_t n)
//         {
//             void *result = malloc(n);
//             if (result == 0)
//             {
//                 result = oom_malloc(n);
//             }
//             return result;
//         }
//         static void deallocate(void *p, size_t)
//         {
//             free(p);
//         }
//         static void *reallocate(void *p, size_t, size_t new_sz)
//         {
//             void *result = realloc(p, new_sz);
//             if (result == 0)
//             {
//                 result = oom_realloc(p, new_sz);
//             }
//             return result;
//         }
//         static void (*set_malloc_handler(void (*f)()))()
//         {
//             void (*old)() = __malloc_alloc_oom_handler;
//             __malloc_alloc_oom_handler = f;
//             return (old);
//         }
//     };
//     template <int inst>
//     void (*__malloc_alloc_template<inst>::__malloc_alloc_oom_handler)() = 0;

//     template <int inst>
//     void *__malloc_alloc_template<inst>
// }
// #endif