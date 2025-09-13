#ifndef LINEARALLOC_CPP
#define LINEARALLOC_CPP
#include "linearalloc.hpp"

template<typename T>
LinearAlloc<T>::LinearAlloc(size_t size) : m_size{size} {
    buf = static_cast<T*>(operator new(sizeof(value_type) * size));
    if (!buf) throw std::runtime_error("Can't allocate buffer");
    cur = buf;
}

template<class T>
T* LinearAlloc<T>::allocate(size_t n) {
    if (m_size - static_cast<size_t>(cur - buf) >= n) {
        T* tmp = cur;
        cur += n;
        return tmp;
    }
    return nullptr;
}

template<class T>
template <typename... Args>
void LinearAlloc<T>::construct(pointer p, Args&&... args)
{
    ::new((T*)p) T(std::forward<Args>(args)...);
}

template<class T>
void LinearAlloc<T>::destroy(pointer p)
{
    return p->~T();
}


template<class T>
LinearAlloc<T>::~LinearAlloc() {
    operator delete(buf);
}

template<class T>
void LinearAlloc<T>::reset() {
    cur = buf;
}



#endif