#ifndef VECTOR_H_
#define VECTOR_H_

#include <initializer_list>
#include <memory>

#include "base_container.h"
#include "concepts.h"
#include "const_iterator.h"
#include "const_reverse_iterator.h"
#include "iterator.h"
#include "reverse_iterator.h"

template <ArithmeticalComparable T>
class Vector : public BaseContainer {
    friend Iterator<T>;
    friend ConstIterator<T>;
    friend ReverseIterator<T>;
    friend ConstReverseIterator<T>;

private:
    std::shared_ptr<T[]> data = nullptr;

public:
    using value_type = T;
    using iterator = Iterator<T>;
    using const_iterator = Iterator<T>;

    /// Конструкторы
    Vector() = default;
    // По длине
    explicit Vector(size_t len);
    // По длине со значением по умолчанию
    Vector(size_t len, const T &value);
    // Через массив в стиле C
    Vector(size_t len, const T *arr);
    // Через список инициализации
    Vector(std::initializer_list<T> elements);
    // Конструктор переноса
    Vector(Vector<T> &&vector) noexcept;
    // Конструктор копирования
    explicit Vector(const Vector<T> &source);
    // Конструктор через другой контейнер
    template <ConvertableContainerClass<T> C>
    explicit Vector(const C &container);

    // Конструктора через итератор
    template <ConvertibleRandomAccessIterator<T> Iter>
    Vector(Iter &begin, Iter &end);

    ~Vector() override = default;

    /// Операторы присвоения
    // Присвоение
    Vector<T> &operator=(const Vector<T> &other);
    // Присвоение переносом
    Vector<T> &operator=(Vector<T> &&other) noexcept;
    // Присвоение списком инициализации
    Vector<T> &operator=(std::initializer_list<T> elements);
    // Присвоение другого контейнера
    template <ConvertableContainerClass<T> C>
    Vector<T> &operator=(const C &container);

    // Итераторы
    Iterator<T> begin() noexcept;
    Iterator<T> end() noexcept;

    ConstIterator<T> begin() const noexcept;
    ConstIterator<T> end() const noexcept;
    ConstIterator<T> cbegin() const noexcept;
    ConstIterator<T> cend() const noexcept;

    ReverseIterator<T> rbegin() noexcept;
    ReverseIterator<T> rend() noexcept;

    ConstReverseIterator<T> rbegin() const noexcept;
    ConstReverseIterator<T> rend() const noexcept;
    ConstReverseIterator<T> crbegin() const noexcept;
    ConstReverseIterator<T> crend() const noexcept;

    // Операции равенства и неравенства
    template <typename U>
    bool operator==(const Vector<U> &other) const;
    template <typename U>
    bool isEqual(const Vector<U> &vector) const;

    template <typename U>
    bool operator!=(const Vector<U> &other) const;
    template <typename U>
    bool isNotEqual(const Vector<U> &vector) const;

    // Индексация
    T &operator[](size_t index);
    const T &operator[](size_t index) const;

    [[nodiscard]] decltype(auto) length() const;

    // Сумма
    template <Convertable<T> U>
    Vector<T> operator+(const Vector<U> &vector) const;
    template <Convertable<T> U>
    Vector<T> vecSum(const Vector<U> &vector) const;

    template <Convertable<T> U>
    Vector<T> operator+(const U &num) const;
    template <Convertable<T> U>
    Vector<T> byNumSum(const U &num) const;

    template <Convertable<T> U>
    Vector<T> &operator+=(const Vector<U> &vector);
    template <Convertable<T> U>
    Vector<T> &eqVecSum(const Vector<U> &vector);

    template <Convertable<T> U>
    Vector<T> &operator+=(const U &num);
    template <Convertable<T> U>
    Vector<T> &eqByNumSum(const U &num);

    // Вычитание
    template <Convertable<T> U>
    Vector<T> operator-(const Vector<U> &vector) const;
    template <Convertable<T> U>
    Vector<T> vecDiff(const Vector<U> &vector) const;

    template <Convertable<T> U>
    Vector<T> operator-(const U &num) const;
    template <Convertable<T> U>
    Vector<T> byNumDiff(const U &num) const;

    template <Convertable<T> U>
    Vector<T> &operator-=(const Vector<U> &vector);
    template <Convertable<T> U>
    Vector<T> &eqVecDiff(const Vector<U> &vector);

    template <Convertable<T> U>
    Vector<T> &operator-=(const U &num);
    template <Convertable<T> U>
    Vector<T> &eqByNumDiff(const U &num);

    // Умножение
    template <Convertable<T> U>
    Vector<T> operator*(const U &num) const;
    template <Convertable<T> U>
    Vector<T> byNumMul(const U &num) const;

    template <Convertable<T> U>
    Vector<T> &operator*=(const U &num);
    template <Convertable<T> U>
    Vector<T> &eqByNumMul(const U &num);

    // Деление
    template <Convertable<T> U>
    Vector<T> operator/(const U &num) const;
    template <Convertable<T> U>
    Vector<T> byNumDiv(const U &num) const;

    template <Convertable<T> U>
    Vector<T> &operator/=(const U &num);
    template <Convertable<T> U>
    Vector<T> &eqByNumDiv(const U &num);

    // Скалярное умножение
    template <Convertable<T> U>
    T scalarProd(const Vector<U> &vector) const;

    // Векторное умножение
    template <Convertable<T> U>
    Vector<T> vectorProd(const Vector<U> &vector) const;

    template <Convertable<T> U>
    Vector<T> hadamaraProd(const Vector<U> &vector) const;

    template <Convertable<T> U>
    Vector<T> hadamaraDiv(const Vector<U> &vector) const;

    template <Convertable<T> U>
    decltype(auto) angle(const Vector<U> &vector) const;

    template <Convertable<T> U>
    bool isCollinear(const Vector<U> &vector) const;

    template <Convertable<T> U>
    bool isOrthogonal(const Vector<U> &vector) const;

    Vector<T> normalize() const;

protected:
    void allocate(size_t size);

    void zeroVectorCheck(size_t line) const;

    void indexCheck(size_t index, size_t line) const;
    template <typename U>
    void sizesCheck(const Vector<U> &other, size_t line) const;
};

template <ArithmeticalComparable T, Convertable<T> U>
Vector<T> operator+(const U &num, const Vector<T> &vector) {
    return vector + num;
}

template <ArithmeticalComparable T, Convertable<T> U>
Vector<T> operator*(const U &num, const Vector<T> &vector) {
    return vector * num;
}

template <ArithmeticalComparable T>
Vector<T> operator-(const Vector<T> &vector);

template <typename T>
std::ostream &operator<<(std::ostream &os, const Vector<T> &vector);

#endif
