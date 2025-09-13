#ifndef LINEARALLOC_HPP
#define LINEARALLOC_HPP
#include <iostream>


template <typename T>
class LinearAlloc {
private:
    T* buf;
    T* cur;
    size_t m_size;
public: 
    using value_type = T;
    using pointer = T*;

    explicit LinearAlloc(size_t size);
    ~LinearAlloc();

    T* allocate(size_t n);
    template <typename... Args>
    void construct(pointer p, Args&&... args);
    void destroy(pointer p);
    void reset();
};

#include "linearalloc.cpp"

#endif