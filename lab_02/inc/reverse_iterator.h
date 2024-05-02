#ifndef REVERSE_ITERATOR_H
#define REVERSE_ITERATOR_H

#include <memory>

#include "base_iterator.h"
#include "concepts.h"

template <ArithmeticalComparable T>
class Vector;

template <typename T>
class ReverseIterator : public BaseIterator<T> {
public:
    explicit ReverseIterator(const ReverseIterator<T> &) noexcept = default;
    explicit ReverseIterator(const Vector<T> &) noexcept;
    ReverseIterator(ReverseIterator<T> &&) noexcept = default;

    ReverseIterator<T> &operator=(const ReverseIterator<T> &iterator);

    BaseIterator<T>::difference_type operator-(const ReverseIterator<T> &other) const noexcept;

    const T &operator*() const;
    T &operator*();

    const BaseIterator<T>::pointer operator->() const;
    BaseIterator<T>::pointer operator->();

    const T &operator[](int index) const;
    T &operator[](int index);

    ReverseIterator<T> &operator+=(int number);
    ReverseIterator<T> &operator++();    // префиксный инкремент
    ReverseIterator<T> operator++(int);  // постфиксный инкремент
    ReverseIterator<T> operator+(int number) const;

    ReverseIterator<T> &operator-=(int number);
    ReverseIterator<T> &operator--();    // префиксный декремент
    ReverseIterator<T> operator--(int);  // постфиксный декремент
    ReverseIterator<T> operator-(int number) const;

    bool operator<=(const ReverseIterator &iterator) const;
    bool operator<(const ReverseIterator &iterator) const;
    bool operator>=(const ReverseIterator &iterator) const;
    bool operator>(const ReverseIterator &iterator) const;
    bool operator==(const ReverseIterator &iterator) const;
    bool operator!=(const ReverseIterator &iterator) const;
};

#endif
