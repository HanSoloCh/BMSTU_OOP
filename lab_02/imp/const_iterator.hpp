#ifndef CONST_ITERATOR_HPP
#define CONST_ITERATOR_HPP

#include <memory>

#include "base_iterator.hpp"
#include "../inc/const_iterator.h"
#include "../inc/exceptions.h"
#include "../inc/iterator.h"

template <typename Type>
ConstIterator<Type>::ConstIterator(const Iterator<Type>& iterator) noexcept {
    this->weakPtr = iterator.weakPtr;
    this->index = iterator.index;
    this->size = iterator.size;
}

template <typename Type>
ConstIterator<Type>::ConstIterator(const Vector<Type>& vector) noexcept {
    this->index = 0;
    this->size = vector.getSize();
    this->weakPtr = vector.data;
}

template <typename Type>
ConstIterator<Type>& ConstIterator<Type>::operator=(const ConstIterator<Type>& it) {
    this->expiredCheck(__LINE__);
    this->weakPtr.reset(it.ptr);
    this->size = it.size;
    this->index = it.index;
}

template <typename T>
BaseIterator<T>::difference_type ConstIterator<T>::operator-(const ConstIterator<T>& other) const noexcept {
    return this->index - other.index;
}

// операторы разыменования
template <typename Type>
const Type& ConstIterator<Type>::operator*() const {
    this->expiredCheck(__LINE__);
    this->indexCheck(__LINE__);

    return *(this->getCurPtr());
}

template <typename Type>
const BaseIterator<Type>::pointer ConstIterator<Type>::operator->() const {
    this->expiredCheck(__LINE__);
    this->indexCheck(__LINE__);

    return *(this->getCurPtr());
}

template <typename Type>
const Type& ConstIterator<Type>::operator[](int index) const {
    return *(operator+(index));
}

// операции сложения
template <typename Type>
ConstIterator<Type>& ConstIterator<Type>::operator+=(int number) {
    this->expiredCheck(__LINE__);
    if (this->index + number <= this->size) this->index += number;

    return *this;
}

template <typename Type>
ConstIterator<Type> ConstIterator<Type>::operator+(int number) const {
    this->expiredCheck(__LINE__);
    ConstIterator<Type> iterator(*this);
    if (this->index + number <= this->size) iterator += number;

    return iterator;
}

template <typename Type>
ConstIterator<Type> ConstIterator<Type>::operator++(int) {
    this->expiredCheck(__LINE__);
    if (this->index <= this->size) ++(*this);

    return *this;
}

template <typename Type>
ConstIterator<Type>& ConstIterator<Type>::operator++() {
    this->expiredCheck(__LINE__);
    if (this->index <= this->size) ++this->index;

    return *this;
}

// операции вычитания
template <typename Type>
ConstIterator<Type>& ConstIterator<Type>::operator-=(int number) {
    this->expiredCheck(__LINE__);
    if (this->index >= number - 1) this->index -= number;

    return *this;
}

template <typename Type>
ConstIterator<Type> ConstIterator<Type>::operator-(int number) const {
    this->expiredCheck(__LINE__);

    ConstIterator<Type> iterator(*this);
    if (this->index >= number - 1) iterator -= number;

    return iterator;
}

template <typename Type>
ConstIterator<Type> ConstIterator<Type>::operator--(int) {
    this->expiredCheck(__LINE__);
    if (this->index >= 0) --(*this);

    return *this;
}

template <typename Type>
ConstIterator<Type>& ConstIterator<Type>::operator--() {
    this->expiredCheck(__LINE__);
    if (this->index >= 0) --this->index;

    return *this;
}

// логические операции
template <typename Type>
bool ConstIterator<Type>::operator<=(const ConstIterator<Type>& iterator) const {
    this->expiredCheck(__LINE__);

    return this->index <= iterator.index;
}

template <typename Type>
bool ConstIterator<Type>::operator<(const ConstIterator<Type>& iterator) const {
    this->expiredCheck(__LINE__);
    return this->index < iterator.index;
}

template <class Type>
bool ConstIterator<Type>::operator>=(const ConstIterator<Type>& iterator) const {
    this->expiredCheck(__LINE__);

    return this->index >= iterator.index;
}

template <typename Type>
bool ConstIterator<Type>::operator>(const ConstIterator<Type>& iterator) const {
    this->expiredCheck(__LINE__);

    return this->index > iterator.index;
}

template <typename Type>
bool ConstIterator<Type>::operator==(const ConstIterator<Type>& iterator) const {
    this->expiredCheck(__LINE__);

    return this->index == iterator.index;
}

template <typename Type>
bool ConstIterator<Type>::operator!=(const ConstIterator<Type>& iterator) const {
    this->expiredCheck(__LINE__);

    return this->index != iterator.index;
}

#endif
