#ifndef CONST_REVERSE_ITERATOR_H
#define CONST_REVERSE_ITERATOR_H

#include <memory>

#include "base_iterator.h"
#include "concepts.h"
#include "reverse_iterator.h"

template <ArithmeticalComparable T>
class Vector;

template <typename T>
class ConstReverseIterator : public BaseIterator<T> {
public:
    explicit ConstReverseIterator(const ReverseIterator<T> &) noexcept;
    explicit ConstReverseIterator(const ConstReverseIterator<T> &) noexcept = default;
    explicit ConstReverseIterator(const Vector<T> &) noexcept;
    ConstReverseIterator(ConstReverseIterator<T> &&) noexcept = default;

    ConstReverseIterator<T> &operator=(const ConstReverseIterator<T> &iterator);

    BaseIterator<T>::difference_type operator-(const ReverseIterator<T> &other) const noexcept;

    const T &operator*() const;

    const BaseIterator<T>::pointer operator->() const;

    const T &operator[](int index) const;

    ConstReverseIterator<T> &operator+=(int number);
    ConstReverseIterator<T> &operator++();    // префиксный инкремент
    ConstReverseIterator<T> operator++(int);  // постфиксный инкремент
    ConstReverseIterator<T> operator+(int number) const;

    ConstReverseIterator<T> &operator-=(int number);
    ConstReverseIterator<T> &operator--();    // префиксный декремент
    ConstReverseIterator<T> operator--(int);  // постфиксный декремент
    ConstReverseIterator<T> operator-(int number) const;

    bool operator<=(const ConstReverseIterator &iterator) const;
    bool operator<(const ConstReverseIterator &iterator) const;
    bool operator>=(const ConstReverseIterator &iterator) const;
    bool operator>(const ConstReverseIterator &iterator) const;
    bool operator==(const ConstReverseIterator &iterator) const;
    bool operator!=(const ConstReverseIterator &iterator) const;
};

#endif
