#ifndef CONST_REVERSE_ITERATOR_HPP
#define CONST_REVERSE_ITERATOR_HPP

#include "base_iterator.hpp"
#include "../inc/const_reverse_iterator.h"
#include "../inc/exceptions.h"
#include "../inc/reverse_iterator.h"

template <typename T>
ConstReverseIterator<T>::ConstReverseIterator(const ReverseIterator<T> &iterator) noexcept {
    this->weakPtr = iterator.weakPtr;
    this->index = iterator.index;
    this->size = iterator.size;
}

template <typename Type>
ConstReverseIterator<Type>::ConstReverseIterator(const Vector<Type> &vector) noexcept {
    this->index = vector.getSize() - 1;
    this->size = vector.getSize();
    this->weakPtr = vector.data;
}

template <typename Type>
ConstReverseIterator<Type> &ConstReverseIterator<Type>::operator=(const ConstReverseIterator<Type> &it) {
    this->expiredCheck(__LINE__);
    this->weakPtr.reset(it.ptr);
    this->size = it.size;
    this->index = it.index;
}

template <typename T>
BaseIterator<T>::difference_type ReverseIterator<T>::operator-(
    const ReverseIterator<T> &other) const noexcept {
    return other.index - this->index;
}

// операторы разыменования
template <typename Type>
const Type &ConstReverseIterator<Type>::operator*() const {
    this->expiredCheck(__LINE__);
    this->indexCheck(__LINE__);

    return *(this->getCurPtr());
}

template <typename Type>
const BaseIterator<Type>::pointer ConstReverseIterator<Type>::operator->() const {
    this->expiredCheck(__LINE__);
    this->indexCheck(__LINE__);

    return *(this->getCurPtr());
}

template <typename Type>
const Type &ConstReverseIterator<Type>::operator[](int index) const {
    return *(operator+(index));
}

template <typename T>
ConstReverseIterator<T> &ConstReverseIterator<T>::operator+=(int number) {
    this->expiredCheck(__LINE__);
    if (this->index - number >= 0) this->index -= number;

    return *this;
}

template <typename T>
ConstReverseIterator<T> ConstReverseIterator<T>::operator+(int number) const {
    this->expiredCheck(__LINE__);

    ConstReverseIterator<T> iterator(*this);
    if (this->index - number + 1 >= 0) iterator -= number;

    return iterator;
}

template <typename T>
ConstReverseIterator<T> &ConstReverseIterator<T>::operator++() {
    this->expiredCheck(__LINE__);
    if (this->index >= 0) --(this->index);

    return *this;
}

template <typename T>
ConstReverseIterator<T> ConstReverseIterator<T>::operator++(int) {
    this->expiredCheck(__LINE__);
    if (this->index >= 0) --(*this);

    return *this;
}

template <typename T>
ConstReverseIterator<T> &ConstReverseIterator<T>::operator-=(int number) {
    this->expiredCheck(__LINE__);
    if (this->index + number <= this->size) this->index += number;

    return *this;
}

template <typename T>
ConstReverseIterator<T> &ConstReverseIterator<T>::operator--() {
    this->expiredCheck(__LINE__);
    if (this->index <= this->size) ++(this->index);

    return *this;
}

template <typename T>
ConstReverseIterator<T> ConstReverseIterator<T>::operator--(int) {
    this->expiredCheck(__LINE__);
    if (this->index <= this->size) ++(*this);

    return *this;
}

template <typename T>
ConstReverseIterator<T> ConstReverseIterator<T>::operator-(int number) const {
    this->expiredCheck(__LINE__);
    ConstReverseIterator<T> iterator(*this);
    if (this->index + number <= this->size) iterator += number;

    return iterator;
}

// логические операции
template <typename Type>
bool ConstReverseIterator<Type>::operator<=(const ConstReverseIterator<Type> &iterator) const {
    this->expiredCheck(__LINE__);

    return this->index >= iterator.index;
}

template <typename Type>
bool ConstReverseIterator<Type>::operator<(const ConstReverseIterator<Type> &iterator) const {
    this->expiredCheck(__LINE__);
    return this->index > iterator.index;
}

template <class Type>
bool ConstReverseIterator<Type>::operator>=(const ConstReverseIterator<Type> &iterator) const {
    this->expiredCheck(__LINE__);

    return this->index <= iterator.index;
}

template <typename Type>
bool ConstReverseIterator<Type>::operator>(const ConstReverseIterator<Type> &iterator) const {
    this->expiredCheck(__LINE__);

    return this->index < iterator.index;
}

template <typename Type>
bool ConstReverseIterator<Type>::operator==(const ConstReverseIterator<Type> &iterator) const {
    this->expiredCheck(__LINE__);

    return this->index == iterator.index;
}

template <typename Type>
bool ConstReverseIterator<Type>::operator!=(const ConstReverseIterator<Type> &iterator) const {
    this->expiredCheck(__LINE__);

    return this->index != iterator.index;
}

#endif
