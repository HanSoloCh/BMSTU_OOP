#ifndef BASE_ITERATOR_H
#define BASE_ITERATOR_H

#include <memory>

template <typename Type>
class BaseIterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = Type;
    using difference_type = ptrdiff_t;
    using pointer = Type*;
    using reference = Type&;

    operator bool() const;

protected:
    BaseIterator() = default;
    int index{};
    int size{};
    std::weak_ptr<Type[]> weakPtr;
    Type* getCurPtr() const;

    void expiredCheck(size_t) const;
    void indexCheck(size_t) const;
};

#endif
