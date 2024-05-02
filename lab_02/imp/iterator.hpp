#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <memory>

#include "base_iterator.hpp"
#include "../inc/exceptions.h"
#include "../inc/iterator.h"

template <typename Type>
Iterator<Type>::Iterator(const Vector<Type>& vector) noexcept {
    this->index = 0;
    this->size = vector.getSize();
    this->weakPtr = vector.data;
}

template <typename Type>
Iterator<Type>& Iterator<Type>::operator=(const Iterator<Type>& it) {
    this->expiredCheck(__LINE__);
    this->weakPtr.reset(it.ptr);
    this->size = it.size;
    this->index = it.index;
}

template <typename T>
BaseIterator<T>::difference_type Iterator<T>::operator-(const Iterator<T>& other) const noexcept {
    return this->index - other.index;
}

// операторы разыменования
template <typename Type>
Type& Iterator<Type>::operator*() {
    this->expiredCheck(__LINE__);
    this->indexCheck(__LINE__);

    return *(this->getCurPtr());
}

template <typename Type>
BaseIterator<Type>::pointer Iterator<Type>::operator->() {
    this->expiredCheck(__LINE__);
    this->indexCheck(__LINE__);

    return *(this->getCurPtr());
}

template <typename Type>
Type& Iterator<Type>::operator[](int index) {
    return *(operator+(index));
}

template <typename Type>
const Type& Iterator<Type>::operator*() const {
    this->expiredCheck(__LINE__);
    this->indexCheck(__LINE__);

    return *(this->getCurPtr());
}

template <typename Type>
const BaseIterator<Type>::pointer Iterator<Type>::operator->() const {
    this->expiredCheck(__LINE__);
    this->indexCheck(__LINE__);

    return *(this->getCurPtr());
}

template <typename Type>
const Type& Iterator<Type>::operator[](int index) const {
    return *(operator+(index));
}

// операции сложения
template <typename Type>
Iterator<Type>& Iterator<Type>::operator+=(int number) {
    this->expiredCheck(__LINE__);
    if (this->index + number <= this->size) this->index += number;

    return *this;
}

template <typename Type>
Iterator<Type> Iterator<Type>::operator+(int number) const {
    this->expiredCheck(__LINE__);
    Iterator<Type> iterator(*this);
    if (this->index + number <= this->size) iterator += number;

    return iterator;
}

template <typename Type>
Iterator<Type> Iterator<Type>::operator++(int) {
    this->expiredCheck(__LINE__);
    if (this->index <= this->size) ++(*this);

    return *this;
}

template <typename Type>
Iterator<Type>& Iterator<Type>::operator++() {
    this->expiredCheck(__LINE__);
    if (this->index <= this->size) ++(this->index);

    return *this;
}

// операции вычитания
template <typename Type>
Iterator<Type>& Iterator<Type>::operator-=(int number) {
    this->expiredCheck(__LINE__);
    if (this->index >= number - 1) this->index -= number;

    return *this;
}

template <typename Type>
Iterator<Type> Iterator<Type>::operator-(int number) const {
    this->expiredCheck(__LINE__);

    Iterator<Type> iterator(*this);
    if (this->index >= number - 1) iterator -= number;

    return iterator;
}

template <typename Type>
Iterator<Type> Iterator<Type>::operator--(int) {
    this->expiredCheck(__LINE__);
    if (this->index >= 0) --(*this);

    return *this;
}

template <typename Type>
Iterator<Type>& Iterator<Type>::operator--() {
    this->expiredCheck(__LINE__);
    if (this->index >= 0) --(this->index);

    return *this;
}

// логические операции
template <typename Type>
bool Iterator<Type>::operator<=(const Iterator<Type>& iterator) const {
    this->expiredCheck(__LINE__);

    return this->index <= iterator.index;
}

template <typename Type>
bool Iterator<Type>::operator<(const Iterator<Type>& iterator) const {
    this->expiredCheck(__LINE__);
    return this->index < iterator.index;
}

template <class Type>
bool Iterator<Type>::operator>=(const Iterator<Type>& iterator) const {
    this->expiredCheck(__LINE__);

    return this->index >= iterator.index;
}

template <typename Type>
bool Iterator<Type>::operator>(const Iterator<Type>& iterator) const {
    this->expiredCheck(__LINE__);

    return this->index > iterator.index;
}

template <typename Type>
bool Iterator<Type>::operator==(const Iterator<Type>& iterator) const {
    this->expiredCheck(__LINE__);

    return this->index == iterator.index;
}

template <typename Type>
bool Iterator<Type>::operator!=(const Iterator<Type>& iterator) const {
    this->expiredCheck(__LINE__);

    return this->index != iterator.index;
}

#endif
