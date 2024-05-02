#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cmath>
#include <initializer_list>

#include "../inc/exceptions.h"
#include "../inc/vector.h"

template <ArithmeticalComparable T>
Vector<T>::Vector(size_t len) : BaseContainer(len) {
    allocate(size);
}

template <ArithmeticalComparable T>
Vector<T>::Vector(const Vector<T> &source) : BaseContainer(source.size) {
    allocate(size);

    for (size_t i = 0; i < size; ++i) (*this)[i] = source[i];
}

template <ArithmeticalComparable T>
Vector<T>::Vector(size_t len, const T &value) : BaseContainer(len) {
    allocate(size);

    for (size_t i = 0; i < size; ++i) (*this)[i] = value;
}

template <ArithmeticalComparable T>
Vector<T>::Vector(size_t len, const T *arr) : BaseContainer(len) {
    allocate(size);

    for (size_t i = 0; i < size; ++i) (*this)[i] = arr[i];
}

template <ArithmeticalComparable T>
Vector<T>::Vector(std::initializer_list<T> elements) : BaseContainer(elements.size()) {
    allocate(size);

    size_t i = 0;
    for (auto elem : elements) (*this)[i++] = elem;
}

template <ArithmeticalComparable T>
Vector<T>::Vector(Vector<T> &&vector) noexcept : BaseContainer(vector.size) {
    data = vector.data;
    vector.data.reset();
}

template <ArithmeticalComparable T>
template <ConvertibleRandomAccessIterator<T> Iter>
Vector<T>::Vector(Iter &begin, Iter &end) {
    size_t len = 0;
    for (ConvertibleRandomAccessIterator<T> auto iter = begin; iter < end; ++iter, ++len)
        ;

    size = len;
    allocate(size);

    size_t i = 0;
    for (ConvertibleRandomAccessIterator<T> auto iter = begin; iter < end; ++iter, ++i) data[i] = *iter;
}

template <ArithmeticalComparable T>
template <ConvertableContainerClass<T> C>
Vector<T>::Vector(const C &container) {
    size_t len = 0;
    for (auto element : container) ++len;

    size = len;
    allocate(size);

    size_t i = 0;
    for (auto element : container) data[i++] = element;
}

template <ArithmeticalComparable T>
Vector<T> &Vector<T>::operator=(const Vector<T> &other) {
    size = other.size;
    allocate(size);

    for (size_t i = 0; i < size; ++i) (*this)[i] = other[i];

    return *this;
}

template <ArithmeticalComparable T>
Vector<T> &Vector<T>::operator=(Vector<T> &&other) noexcept {
    size = other.size;
    data = other.data;

    other.data.reset();
    return *this;
}

template <ArithmeticalComparable T>
Vector<T> &Vector<T>::operator=(std::initializer_list<T> elements) {
    size = elements.size();
    allocate(size);

    size_t i = 0;
    for (auto elem : elements) (*this)[i++] = elem;
    return *this;
}

template <ArithmeticalComparable T>
template <ConvertableContainerClass<T> C>
Vector<T> &Vector<T>::operator=(const C &container) {
    size_t len = 0;
    for (auto element : container) ++len;

    size = len;
    allocate(size);

    size_t i = 0;
    for (auto element : container) data[i++] = element;
}

// Итераторы
template <ArithmeticalComparable T>
Iterator<T> Vector<T>::begin() noexcept {
    return Iterator<T>(*this);
}

template <ArithmeticalComparable T>
Iterator<T> Vector<T>::end() noexcept {
    return Iterator<T>(*this) + static_cast<int>(size);
}

template <ArithmeticalComparable T>
ConstIterator<T> Vector<T>::begin() const noexcept {
    return ConstIterator<T>(*this);
}

template <ArithmeticalComparable T>
ConstIterator<T> Vector<T>::end() const noexcept {
    return ConstIterator<T>(*this) + static_cast<int>(size);
}

template <ArithmeticalComparable T>
ConstIterator<T> Vector<T>::cbegin() const noexcept {
    return ConstIterator<T>(*this);
}

template <ArithmeticalComparable T>
ConstIterator<T> Vector<T>::cend() const noexcept {
    return ConstIterator<T>(*this) + static_cast<int>(size);
}

//
template <ArithmeticalComparable T>
ReverseIterator<T> Vector<T>::rbegin() noexcept {
    return ReverseIterator<T>(*this);
}

template <ArithmeticalComparable T>
ReverseIterator<T> Vector<T>::rend() noexcept {
    return ReverseIterator<T>(*this) + static_cast<int>(size);
}

template <ArithmeticalComparable T>
ConstReverseIterator<T> Vector<T>::rbegin() const noexcept {
    return ConstReverseIterator<T>(*this);
}

template <ArithmeticalComparable T>
ConstReverseIterator<T> Vector<T>::rend() const noexcept {
    return ConstReverseIterator<T>(*this) + static_cast<int>(size);
}

template <ArithmeticalComparable T>
ConstReverseIterator<T> Vector<T>::crbegin() const noexcept {
    return ConstReverseIterator<T>(*this);
}

template <ArithmeticalComparable T>
ConstReverseIterator<T> Vector<T>::crend() const noexcept {
    return ConstReverseIterator<T>(*this) + static_cast<int>(size);
}

// Операторы присвоения
template <ArithmeticalComparable T>
template <typename U>
bool Vector<T>::operator==(const Vector<U> &other) const {
    return isEqual(other);
}

template <ArithmeticalComparable T>
template <typename U>
bool Vector<T>::isEqual(const Vector<U> &other) const {
    if (size != other.size) return false;

    for (size_t i = 0; i < size; ++i) {
        if (abs((*this)[i] - other[i]) > __DBL_EPSILON__) return false;
    }
    return true;
}

template <ArithmeticalComparable T>
template <typename U>
bool Vector<T>::operator!=(const Vector<U> &other) const {
    return isNotEqual(other);
}

template <ArithmeticalComparable T>
template <typename U>
bool Vector<T>::isNotEqual(const Vector<U> &other) const {
    return !isEqual(other);
}

template <ArithmeticalComparable T>
T &Vector<T>::operator[](size_t index) {
    indexCheck(index, __LINE__);

    return data[index];
}

template <ArithmeticalComparable T>
const T &Vector<T>::operator[](size_t index) const {
    indexCheck(index, __LINE__);

    return data[index];
}

// Выделение памяти
template <ArithmeticalComparable T>
void Vector<T>::allocate(size_t size) {
    time_t curTime = time(nullptr);
    uint line;
    try {
        line = __LINE__;
        data.reset(new T[size]);
    } catch (std::bad_alloc &err) {
        throw MemoryException(ctime(&curTime), __FILE__, line, typeid(*this).name(), __FUNCTION__);
    }
}

// Сложение
template <ArithmeticalComparable T>
template <Convertable<T> U>
Vector<T> Vector<T>::vecSum(const Vector<U> &vector) const {
    sizesCheck(vector, __LINE__);

    Vector<T> res(*this);

    for (size_t i = 0; i < size; ++i) res[i] += vector[i];

    return res;
}

template <ArithmeticalComparable T>
template <Convertable<T> U>
Vector<T> Vector<T>::byNumSum(const U &num) const {
    Vector<T> res(*this);

    for (size_t i = 0; i < size; ++i) res[i] += num;

    return res;
}

template <ArithmeticalComparable T>
template <Convertable<T> U>
Vector<T> &Vector<T>::eqVecSum(const Vector<U> &vector) {
    sizesCheck(vector, __LINE__);

    for (size_t i = 0; i < size; ++i) (*this)[i] += vector[i];

    return *this;
}

template <ArithmeticalComparable T>
template <Convertable<T> U>
Vector<T> &Vector<T>::eqByNumSum(const U &num) {
    for (size_t i = 0; i < size; ++i) (*this)[i] += num;

    return *this;
}

template <ArithmeticalComparable T>
template <Convertable<T> U>
Vector<T> Vector<T>::operator+(const Vector<U> &vector) const {
    return vecSum(vector);
}

template <ArithmeticalComparable T>
template <Convertable<T> U>
Vector<T> Vector<T>::operator+(const U &num) const {
    return byNumSum(num);
}

template <ArithmeticalComparable T>
template <Convertable<T> U>
Vector<T> &Vector<T>::operator+=(const Vector<U> &vector) {
    return eqVecSum(vector);
}

template <ArithmeticalComparable T>
template <Convertable<T> U>
Vector<T> &Vector<T>::operator+=(const U &num) {
    return eqByNumSum(num);
}

// Вычитание
template <ArithmeticalComparable T>
template <Convertable<T> U>
Vector<T> Vector<T>::vecDiff(const Vector<U> &vector) const {
    sizesCheck(vector, __LINE__);

    Vector<T> res(*this);

    for (size_t i = 0; i < size; ++i) res[i] += vector[i];

    return res;
}

template <ArithmeticalComparable T>
template <Convertable<T> U>
Vector<T> Vector<T>::byNumDiff(const U &num) const {
    Vector<T> res(*this);

    for (size_t i = 0; i < size; ++i) res[i] += num;

    return res;
}

template <ArithmeticalComparable T>
template <Convertable<T> U>
Vector<T> &Vector<T>::eqVecDiff(const Vector<U> &vector) {
    sizesCheck(vector, __LINE__);

    for (size_t i = 0; i < size; ++i) (*this)[i] -= vector[i];

    return *this;
}

template <ArithmeticalComparable T>
template <Convertable<T> U>
Vector<T> &Vector<T>::eqByNumDiff(const U &num) {
    for (size_t i = 0; i < size; ++i) (*this)[i] -= num;

    return *this;
}

template <ArithmeticalComparable T>
template <Convertable<T> U>
Vector<T> Vector<T>::operator-(const Vector<U> &vector) const {
    return vecDiff(vector);
}

template <ArithmeticalComparable T>
template <Convertable<T> U>
Vector<T> Vector<T>::operator-(const U &num) const {
    return byNumDiff(num);
}

template <ArithmeticalComparable T>
Vector<T> operator-(const Vector<T> &vector) {
    Vector<T> result(vector.getSize());
    for (size_t i = 0; i < vector.getSize(); ++i) result[i] = -vector[i];
    return result;
}

template <ArithmeticalComparable T>
template <Convertable<T> U>
Vector<T> &Vector<T>::operator-=(const Vector<U> &vector) {
    return eqVecDiff(vector);
}

template <ArithmeticalComparable T>
template <Convertable<T> U>
Vector<T> &Vector<T>::operator-=(const U &num) {
    return eqByNumDiff(num);
}

// Умножение
template <ArithmeticalComparable T>
template <Convertable<T> U>
Vector<T> Vector<T>::byNumMul(const U &num) const {
    Vector<T> res(*this);

    for (size_t i = 0; i < size; ++i) res[i] *= num;

    return res;
}

template <ArithmeticalComparable T>
template <Convertable<T> U>
Vector<T> &Vector<T>::eqByNumMul(const U &num) {
    for (size_t i = 0; i < size; ++i) (*this)[i] *= num;
    return *this;
}

template <ArithmeticalComparable T>
template <Convertable<T> U>
Vector<T> Vector<T>::operator*(const U &num) const {
    return byNumMul(num);
}

template <ArithmeticalComparable T>
template <Convertable<T> U>
Vector<T> &Vector<T>::operator*=(const U &num) {
    return eqByNumMul(num);
}

// Деление
template <ArithmeticalComparable T>
template <Convertable<T> U>
Vector<T> Vector<T>::byNumDiv(const U &num) const {
    Vector<T> res(*this);

    for (size_t i = 0; i < size; ++i) res[i] /= num;

    return res;
}

template <ArithmeticalComparable T>
template <Convertable<T> U>
Vector<T> &Vector<T>::eqByNumDiv(const U &num) {
    for (size_t i = 0; i < size; ++i) (*this)[i] /= num;
    return *this;
}

template <ArithmeticalComparable T>
template <Convertable<T> U>
Vector<T> Vector<T>::operator/(const U &num) const {
    return byNumDiv(num);
}

template <ArithmeticalComparable T>
template <Convertable<T> U>
Vector<T> &Vector<T>::operator/=(const U &num) {
    return eqByNumDiv(num);
}

// Скалярное произведение
template <ArithmeticalComparable T>
template <Convertable<T> U>
T Vector<T>::scalarProd(const Vector<U> &vector) const {
    sizesCheck(vector, __LINE__);
    Vector<T> res(getSize());

    for (size_t i = 0; i < size; ++i) res += (*this)[i] * vector[i];
    return res;
}

// Векторное произведение
template <ArithmeticalComparable T>
template <Convertable<T> U>
Vector<T> Vector<T>::vectorProd(const Vector<U> &vector) const {
    sizesCheck(vector, __LINE__);

    Vector<T> res(size);

    for (size_t i = 0; i < size; ++i)
        res[i] = (*this)[(i + 1) % size] * vector[(i + 2) % size] -
                 (*this)[(i + 2) % size] * vector[(i + 1) % size];

    return res;
}

// Модуль вектора
template <ArithmeticalComparable T>
decltype(auto) Vector<T>::length() const {
    decltype(auto) sum = 0.;
    for (size_t i = 0; i < getSize(); ++i) sum = (*this)[i] * (*this)[i];
    sum = sqrt(sum);
    return sum;
}

template <ArithmeticalComparable T>
template <Convertable<T> U>
Vector<T> Vector<T>::hadamaraProd(const Vector<U> &vector) const {
    sizesCheck(vector, __LINE__);
    Vector<T> result(getSize());
    for (size_t i = 0; i < getSize(); ++i) result[i] = (*this)[i] * vector[i];
    return result;
}

template <ArithmeticalComparable T>
template <Convertable<T> U>
Vector<T> Vector<T>::hadamaraDiv(const Vector<U> &vector) const {
    sizesCheck(vector, __LINE__);
    Vector<T> result(getSize());
    for (size_t i = 0; i < getSize(); ++i) result[i] = (*this)[i] / vector[i];
    return result;
}

template <ArithmeticalComparable T>
template <Convertable<T> U>
decltype(auto) Vector<T>::angle(const Vector<U> &vector) const {
    zeroVectorCheck(__LINE__);
    vector.zeroVectorCheck(__LINE__);
    double angle = (*this * vector) / (this->GetLength() * vector.GetLength());
    if (angle > 1) angle = 1.0;
    return acos(angle) * 180 / M_PI;
}

// Проверка на коллинеарность
template <ArithmeticalComparable T>
template <Convertable<T> U>
bool Vector<T>::isCollinear(const Vector<U> &vector) const {
    sizesCheck(vector, __LINE__);

    double ang = angle(vector);

    return std::abs(ang) < __DBL_EPSILON__ || std::abs(ang - M_PI) < __DBL_EPSILON__;
}

// Проверка на ортодоксальность
template <ArithmeticalComparable T>
template <Convertable<T> U>
bool Vector<T>::isOrthogonal(const Vector<U> &vector) const {
    sizesCheck(vector, __LINE__);

    return abs(angle(vector) - M_PI / 2) < __DBL_EPSILON__;
}

template <ArithmeticalComparable T>
Vector<T> Vector<T>::normalize() const {
    zeroVectorCheck(__LINE__);
    Vector<T> result(getSize());
    double len = length();
    for (size_t i = 0; i < getSize(); ++i) (*this)[i] /= len;
    return result;
}

// Чекеры
template <ArithmeticalComparable T>
void Vector<T>::zeroVectorCheck(size_t line) const {
    if (length() < __DBL_EPSILON__) {
        time_t cur_time = time(nullptr);
        throw ZeroVectorException(ctime(&cur_time), __FILE__, line, typeid(*this).name(), __FUNCTION__);
    }
}

template <ArithmeticalComparable T>
void Vector<T>::indexCheck(size_t index, size_t line) const {
    if (index >= getSize()) {
        time_t cur_time = time(nullptr);
        throw OutOfRangeException(ctime(&cur_time), __FILE__, line, typeid(*this).name(), __FUNCTION__);
    }
}

template <ArithmeticalComparable T>
template <typename U>
void Vector<T>::sizesCheck(const Vector<U> &other, size_t line) const {
    if (getSize() != other.getSize()) {
        time_t cur_time = time(nullptr);
        throw NotEqualSizesException(ctime(&cur_time), __FILE__, line, typeid(*this).name(), __FUNCTION__);
    }
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Vector<T> &vector) {
    os << "[";
    for (size_t i = 0; i < vector.getSize(); ++i) os << " " << vector[i];
    os << " ]\n";
    return os;
}

#endif
