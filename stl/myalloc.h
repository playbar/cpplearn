//
// Created by mac on 2019-05-18.
//

#ifndef STL_MYALLOC_H
#define STL_MYALLOC_H


#include <new>
#include <cstddef>
#include <cstdlib>
#include <climits>
#include <iostream>

namespace cpl
{
    template<class T>
    inline T* _allocate(ptrdiff_t size, T*)
    {
        T* tmp = (T*)(::operator new((size_t)(size * sizeof(T)))); // size：待分配的元素量，sizeof(T)每个元素的大小
        printf("alloc : %p, size = %d \n", tmp, size);
        if (tmp == 0)
        {
            printf("out of memory \n");
            exit(1);
        }
        return tmp;
    }

    template<class T>
    inline void _deallocate(T* buffer)
    {
        printf("dealloc : %p\n", buffer);
        ::operator delete(buffer);
    }

    template<class T1, class  T2>
    inline void _construct(T1* p, const T2& value)
    {
        new(p)T1(value); // 调用placement new，在指定的内存位置p处初始化T1对象，初始化T1对象时调用T1的复制构造函数
    }

    template<class T>
    inline void _destroy(T* ptr)
    {
        ptr->~T();
    }

    template<class T>
    class allocator
    {
    public:
        typedef T			value_type;
        typedef T*			pointer;
        typedef const T*	const_pointer;
        typedef T&			reference;
        typedef const T&	const_reference;
        typedef size_t		size_type;
        typedef ptrdiff_t	difference_type;

        template<class U>
        struct rebind
        {
            typedef allocator<U> other;
        };

        pointer allocate(size_type n, const void* hint = 0)
        {
            return _allocate((difference_type)n, (pointer)0);
        }

        void deallocate(pointer p, size_type n)
        {
            _deallocate(p);
        }

        void construct(pointer p, const T& value)
        {
            _construct(p, value);
        }

        void destroy(pointer p)
        {
            _destroy(p);
        }

        pointer address(reference x)
        {
            return (pointer)&x;
        }

        const_pointer const_address(const_reference x)
        {
            return (const_pointer)&x;
        }

        size_type max_size() const
        {
            return size_type(UINT_MAX / sizeof(T));
        }
    };
}


#endif //STL_MYALLOC_H
