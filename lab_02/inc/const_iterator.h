#ifndef CONST_ITERATOR_H
#define CONST_ITERATOR_H

#include <memory>

#include "base_iterator.h"
#include "concepts.h"
#include "iterator.h"

template <ArithmeticalComparable T>
class Vector;

template <typename T>
class ConstIterator : public BaseIterator<T> {
public:
    explicit ConstIterator(const Iterator<T> &) noexcept;
    explicit ConstIterator(const ConstIterator<T> &) noexcept = default;
    explicit ConstIterator(const Vector<T> &) noexcept;
    ConstIterator(ConstIterator<T> &&) noexcept = default;

    ConstIterator<T> &operator=(const ConstIterator<T> &iterator);

    BaseIterator<T>::difference_type operator-(const ConstIterator<T> &other) const noexcept;

    const T &operator*() const;

    const BaseIterator<T>::pointer operator->() const;

    const T &operator[](int index) const;

    ConstIterator<T> &operator+=(int number);
    ConstIterator<T> &operator++();    // префиксный инкремент
    ConstIterator<T> operator++(int);  // постфиксный инкремент
    ConstIterator<T> operator+(int number) const;

    ConstIterator<T> &operator-=(int number);
    ConstIterator<T> &operator--();    // префиксный декремент
    ConstIterator<T> operator--(int);  // постфиксный декремент
    ConstIterator<T> operator-(int number) const;

    bool operator<=(const ConstIterator &iterator) const;
    bool operator<(const ConstIterator &iterator) const;
    bool operator>=(const ConstIterator &iterator) const;
    bool operator>(const ConstIterator &iterator) const;
    bool operator==(const ConstIterator &iterator) const;
    bool operator!=(const ConstIterator &iterator) const;
};

#endif
