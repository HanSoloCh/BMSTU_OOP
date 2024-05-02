#ifndef ITERATOR_H
#define ITERATOR_H

#include <cstdlib>
#include <memory>

#include "base_iterator.h"
#include "concepts.h"

template <ArithmeticalComparable T>
class Vector;

template <typename T>
class Iterator : public BaseIterator<T> {
public:
    explicit Iterator(const Iterator<T> &) noexcept = default;
    explicit Iterator(const Vector<T> &) noexcept;
    Iterator(Iterator<T> &&) noexcept = default;

    Iterator<T> &operator=(const Iterator<T> &iterator);

    BaseIterator<T>::difference_type operator-(const Iterator<T> &other) const noexcept;

    const T &operator*() const;
    T &operator*();

    const BaseIterator<T>::pointer operator->() const;
    BaseIterator<T>::pointer operator->();

    const T &operator[](int index) const;
    T &operator[](int index);

    Iterator<T> &operator+=(int number);
    Iterator<T> &operator++();    // префиксный инкремент
    Iterator<T> operator++(int);  // постфиксный инкремент
    Iterator<T> operator+(int number) const;

    Iterator<T> &operator-=(int number);
    Iterator<T> &operator--();    // префиксный декремент
    Iterator<T> operator--(int);  // постфиксный декремент
    Iterator<T> operator-(int number) const;

    bool operator<=(const Iterator &iterator) const;
    bool operator<(const Iterator &iterator) const;
    bool operator>=(const Iterator &iterator) const;
    bool operator>(const Iterator &iterator) const;
    bool operator==(const Iterator &iterator) const;
    bool operator!=(const Iterator &iterator) const;
};

#endif
