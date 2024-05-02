#ifndef CONCEPTS_H
#define CONCEPTS_H

#include <concepts>

template <typename T>
concept Summable = requires(T a, T b) {
    { a + b } -> std::same_as<T>;
};

template <typename T>
concept Subbable = requires(T a, T b) {
    { a - b } -> std::same_as<T>;
};

template <typename T>
concept Multable = requires(T a, T b) {
    { a* b } -> std::same_as<T>;
};

template <typename T>
concept Divable = requires(T a, T b) {
    { a / b } -> std::same_as<T>;
};

template <typename From, typename To>
concept Convertable = std::convertible_to<From, To>;

template <typename T>
concept Comparable = requires(T a, T b) {
    { a > b } -> std::same_as<bool>;
    { a >= b } -> std::same_as<bool>;
    { a < b } -> std::same_as<bool>;
    { a < b } -> std::same_as<bool>;
};

template <typename T, typename U>
concept EqComparable = requires(T t, U u) {
    { t == u } -> std::same_as<bool>;
    { t != u } -> std::same_as<bool>;
};

template <typename T>
concept Numeric = std::is_arithmetic_v<T> || requires(T a) {
    {sqrt(a)};
};

template <typename T>
concept ArithmeticalComparable = Numeric<T> && Summable<T> && Subbable<T> && Divable<T> && Multable<T> &&
    Comparable<T> && EqComparable<T, T>;

template <typename C>
concept ContainerClass = requires(C c) {
    typename C::value_type;
    typename C::size_type;
    typename C::iterator;
    typename C::const_iterator;

    { c.begin() }
    noexcept->std::same_as<typename C::iterator>;
    { c.end() }
    noexcept->std::same_as<typename C::iterator>;
    { c.cend() }
    noexcept->std::same_as<typename C::const_iterator>;
    { c.cbegin() }
    noexcept->std::same_as<typename C::const_iterator>;
    { c.size() }
    noexcept->std::same_as<typename C::size_type>;
};

template <typename C, typename T>
concept ConvertableContainerClass = ContainerClass<C> && Convertable<typename C::value_type, T>;

// Концепты для итератора
template <typename T>
concept IteratorCheck = requires() {
    typename T::value_type;
    typename T::pointer;
    typename T::reference;
    typename T::difference_type;
};

// Тип T порожден от типа U
template <typename T, typename U>
concept DerivedFrom = std::is_base_of<U, T>::value;

// Концепты для Input Iterator
template <typename T>
concept InputIterator = requires() {
    typename T::iterator_category;
}
&&EqComparable<T, T>&& IteratorCheck<T>&& DerivedFrom<typename T::iterator_category, std::input_iterator_tag>;

// Концепты для Forward Iterator
template <typename T>
concept Incrementable = requires(T it) {
    { it++ } -> std::same_as<T>;
    { ++it } -> std::same_as<T&>;
};

template <typename T>
concept ForwardIterator = InputIterator<T> && Incrementable<T> &&
    DerivedFrom<typename T::iterator_category, std::forward_iterator_tag>;

// Концепты для Bidirectional Iterator
template <typename I>
concept Decrementable = requires(I it) {
    { --it } -> std::same_as<I&>;
    { it-- } -> std::same_as<I>;
};

template <typename I>
concept BidirectionalIterator = ForwardIterator<I> && Decrementable<I> &&
    DerivedFrom<typename I::iterator_category, std::bidirectional_iterator_tag>;

// Концепты для Random Access Iterator
template <typename I>
concept RandomAccess = requires(I it, typename I::difference_type n) {
    { it + n } -> std::same_as<I>;
    { it - n } -> std::same_as<I>;
    { it += n } -> std::same_as<I&>;
    { it -= n } -> std::same_as<I&>;
    { it[n] } -> std::same_as<typename I::reference>;
};

template <typename I>
concept Distance = requires(I it1, I it2) {
    { it2 - it1 } -> std::convertible_to<typename I::difference_type>;
};

template <typename I>
concept RandomAccessIterator = BidirectionalIterator<I> && RandomAccess<I> && Distance<I> &&
    DerivedFrom<typename I::iterator_category, std::random_access_iterator_tag>;

// Прямой итератор, приводимый
template <typename Iter, typename T>
concept ConvertibleRandomAccessIterator =
    RandomAccessIterator<Iter> && Convertable<typename Iter::value_type, T>;

#endif
