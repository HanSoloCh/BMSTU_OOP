#ifndef BASE_ITERATOR_HPP
#define BASE_ITERATOR_HPP

#include "../inc/base_iterator.h"

template <typename Type>
BaseIterator<Type>::operator bool() const {
    expiredCheck(__LINE__);
    bool res = true;
    if (index >= size || index < 0 || size == 0) res = false;

    return res;
}

template <typename T>
T *BaseIterator<T>::getCurPtr() const {
    std::shared_ptr<T[]> tmp = weakPtr.lock();
    return tmp.get() + index;
}

template <typename T>
void BaseIterator<T>::expiredCheck(size_t line) const {
    if (weakPtr.expired()) {
        time_t cur_time = time(nullptr);
        throw ExpiredException(ctime(&cur_time), __FILE__, line, typeid(*this).name(), __FUNCTION__);
    }
}

template <typename T>
void BaseIterator<T>::indexCheck(size_t line) const {
    if (index >= size) {
        time_t cur_time = time(nullptr);
        throw OutOfRangeException(ctime(&cur_time), __FILE__, line, typeid(*this).name(), __FUNCTION__);
    }
}

#endif
