#pragma once
#ifndef GUARD_VEC_H
#define GUARD_VEC_H

#include <memory>
#include <algorithm>
#include <cstddef>

using namespace std;

template <class T>
class Vec
{
public:
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    Vec()
    {
        create();
    }

    explicit Vec(size_type n, const T& val = T())
    {
        create(n, val);
    }

    Vec(const Vec& v)
    {
        create(v.begin(), v.end());
    }

    ~Vec()
    {
        uncreate();
    }

    Vec& operator=(const Vec& rhs)
    {
        if (this != &rhs)
        {
            uncreate();
            create(rhs.begin(), rhs.end());
        }

        return *this;
    }

    size_type size() const
    {
        return avail - data;
    }

    bool empty() const
    {
        return data == avail;
    }

    iterator begin()
    {
        return data;
    }

    const_iterator begin() const
    {
        return data;
    }

    iterator end()
    {
        return avail;
    }

    const_iterator end() const
    {
        return avail;
    }

    T& operator[](size_type i)
    {
        return data[i];
    }

    const T& operator[](size_type i) const
    {
        return data[i];
    }

    // 2배 증가 push_back
    void push_back(const T& val)
    {
        if (avail == limit)
            grow();

        unchecked_append(val);
    }

    // 1칸 증가 push_back
    void push_back_grow_once(const T& val)
    {
        if (avail == limit)
            grow_once();

        unchecked_append(val);
    }

private:
    iterator data;
    iterator avail;
    iterator limit;

    allocator<T> alloc;

    void create();
    void create(size_type, const T&);
    void create(const_iterator, const_iterator);

    void uncreate();

    void grow();
    void grow_once();

    void unchecked_append(const T&);
};

// 빈 Vec
template <class T>
void Vec<T>::create()
{
    data = avail = limit = nullptr;
}

// n개 생성
template <class T>
void Vec<T>::create(size_type n, const T& val)
{
    data = alloc.allocate(n);

    limit = data + n;

    uninitialized_fill(data, limit, val);

    avail = limit;
}

// 범위 복사
template <class T>
void Vec<T>::create(const_iterator i, const_iterator j)
{
    data = alloc.allocate(j - i);

    limit = avail = uninitialized_copy(i, j, data);
}

// 메모리 해제
template <class T>
void Vec<T>::uncreate()
{
    if (data)
    {
        iterator it = avail;

        while (it != data)
            alloc.destroy(--it);

        alloc.deallocate(data, limit - data);
    }

    data = avail = limit = nullptr;
}

// 원소 추가
template <class T>
void Vec<T>::unchecked_append(const T& val)
{
    alloc.construct(avail++, val);
}

// capacity 2배 증가
template <class T>
void Vec<T>::grow()
{
    size_type new_size =
        max(2 * size(), size_type(1));

    iterator new_data = alloc.allocate(new_size);

    iterator new_avail =
        uninitialized_copy(data, avail, new_data);

    uncreate();

    data = new_data;
    avail = new_avail;
    limit = data + new_size;
}

// capacity 1 증가
template <class T>
void Vec<T>::grow_once()
{
    size_type new_size = size() + 1;

    iterator new_data = alloc.allocate(new_size);

    iterator new_avail =
        uninitialized_copy(data, avail, new_data);

    uncreate();

    data = new_data;
    avail = new_avail;
    limit = data + new_size;
}

#endif
