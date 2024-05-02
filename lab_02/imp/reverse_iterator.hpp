#ifndef REVERSE_ITERATOR_HPP_
#define REVERSE_ITERATOR_HPP_

#include <memory>

#include "base_iterator.hpp"
#include "../inc/exceptions.h"
#include "../inc/reverse_iterator.h"

template <typename Type>
ReverseIterator<Type>::ReverseIterator(const Vector<Type>& vector) noexcept {
    this->index = vector.getSize() - 1;
    this->size = vector.getSize();
    this->weakPtr = vector.data;
}

template <typename Type>
ReverseIterator<Type>& ReverseIterator<Type>::operator=(const ReverseIterator<Type>& it) {
    this->expiredCheck(__LINE__);
    this->weakPtr.reset(it.ptr);
    this->size = it.size;
    this->index = it.index;
}

template <typename T>
BaseIterator<T>::difference_type ReverseIterator<T>::operator-(
    const ReverseIterator<T>& other) const noexcept {
    return other.index - this->index;
}

// операторы разыменования
template <typename Type>
Type& ReverseIterator<Type>::operator*() {
    this->expiredCheck(__LINE__);
    this->indexCheck(__LINE__);

    return *(this->getCurPtr());
}

template <typename Type>
BaseIterator<Type>::pointer ReverseIterator<Type>::operator->() {
    this->expiredCheck(__LINE__);
    this->indexCheck(__LINE__);

    return *(this->getCurPtr());
}

template <typename Type>
Type& ReverseIterator<Type>::operator[](int index) {
    return *(operator+(index));
}

template <typename Type>
const Type& ReverseIterator<Type>::operator*() const {
    this->expiredCheck(__LINE__);
    this->indexCheck(__LINE__);

    return *(this->getCurPtr());
}

template <typename Type>
const BaseIterator<Type>::pointer ReverseIterator<Type>::operator->() const {
    this->expiredCheck(__LINE__);
    this->indexCheck(__LINE__);

    return *(this->getCurPtr());
}

template <typename Type>
const Type& ReverseIterator<Type>::operator[](int index) const {
    return *(operator+(index));
}

template <typename T>
ReverseIterator<T>& ReverseIterator<T>::operator+=(int number) {
    this->expiredCheck(__LINE__);
    if (this->index - number >= 0) this->index -= number;

    return *this;
}

template <typename T>
ReverseIterator<T> ReverseIterator<T>::operator+(int number) const {
    this->expiredCheck(__LINE__);

    ReverseIterator<T> iterator(*this);
    if (this->index - number + 1 >= 0) iterator.index -= number;

    return iterator;
}

template <typename T>
ReverseIterator<T>& ReverseIterator<T>::operator++() {
    this->expiredCheck(__LINE__);
    if (this->index >= 0) --(this->index);

    return *this;
}

template <typename T>
ReverseIterator<T> ReverseIterator<T>::operator++(int) {
    this->expiredCheck(__LINE__);
    if (this->index >= 0) --(*this);

    return *this;
}

template <typename T>
ReverseIterator<T>& ReverseIterator<T>::operator-=(int number) {
    this->expiredCheck(__LINE__);
    if (this->index + number <= this->size) this->index += number;

    return *this;
}

template <typename T>
ReverseIterator<T>& ReverseIterator<T>::operator--() {
    this->expiredCheck(__LINE__);
    if (this->index <= this->size) ++(this->index);

    return *this;
}

template <typename T>
ReverseIterator<T> ReverseIterator<T>::operator--(int) {
    this->expiredCheck(__LINE__);
    if (this->index <= this->size) ++(*this);

    return *this;
}

template <typename T>
ReverseIterator<T> ReverseIterator<T>::operator-(int number) const {
    this->expiredCheck(__LINE__);
    ReverseIterator<T> iterator(*this);
    if (this->index + number <= this->size) iterator.index += number;

    return iterator;
}

template <typename Type>
bool ReverseIterator<Type>::operator<=(const ReverseIterator<Type>& iterator) const {
    this->expiredCheck(__LINE__);
    return this->index >= iterator.index;
}

template <typename Type>
bool ReverseIterator<Type>::operator<(const ReverseIterator<Type>& iterator) const {
    this->expiredCheck(__LINE__);
    return this->index > iterator.index;
}

template <class Type>
bool ReverseIterator<Type>::operator>=(const ReverseIterator<Type>& iterator) const {
    this->expiredCheck(__LINE__);

    return this->index <= iterator.index;
}

template <typename Type>
bool ReverseIterator<Type>::operator>(const ReverseIterator<Type>& iterator) const {
    this->expiredCheck(__LINE__);

    return this->index < iterator.index;
}

template <typename Type>
bool ReverseIterator<Type>::operator==(const ReverseIterator<Type>& iterator) const {
    this->expiredCheck(__LINE__);

    return this->index == iterator.index;
}

template <typename Type>
bool ReverseIterator<Type>::operator!=(const ReverseIterator<Type>& iterator) const {
    this->expiredCheck(__LINE__);

    return this->index != iterator.index;
}

#endif