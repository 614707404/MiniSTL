#ifndef DAVIS_VECTOR_H
#define DAVIS_VECTOR_H

namespace davis
{
    template <class _Tp ,class _Alloc>
    class vector{

    // Member Type
    public:
        typedef _Tp                                 value_type;
        typedef _Alloc                              allocator_type;
        typedef value_type&                         reference;
        typedef const value_type&                   const_reference;
        typedef value_type *                        pointer;
        typedef const value_type *                  const_pointer;
        typedef value_type *                        iterator;
        typedef const value_type *                  const_iterator;
        typedef reverse_iterator<iterator>          reverse_iterator;
        typedef reverse_iterator<const_iterator>    const_reverse_iterator;
        typedef size_t                              size_type;
        typedef ptrdiff_t                           difference_type;

    // Member Functions
    public:
        // constructors
        // default constructor
        // fill constructor
        // range constructor
        // copy constructor (and copying with allocator)
        // move constructor (and moving with allocator)
        // initializer list constructor

        // destructor
        // operator=

        // Iterators
        // begin
        // end
        // rbegin
        // rend
        // cbegin
        // cend
        // crbegin
        // crend

        // Capacity
        // size
        // max_size
        // resize
        // capacity
        // empty
        // reserve
        // shrink_to_fit

        // Element access
        // operator[]
        // at
        // front
        // back
        // data

        // Modifiers
        // assign
        // push_back
        // pop_back
        // insert
        // erase
        // swap
        // clear
        // emplace
        // emplace_back

        // Allocator
        // get_allocator

        // Non-member function overloads
        // relational operators
        // swap

        // Template specializations
        // vector<bool>
    };
} // namespace davis

#endif