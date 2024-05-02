#ifndef BASE_CONTAINER_H
#define BASE_CONTAINER_H

#include <cstddef>

class BaseContainer {
public:
    using size_type = size_t;

    BaseContainer() = default;
    explicit BaseContainer(size_t len) { size = len; };

    [[nodiscard]] size_t getSize() const;
    [[nodiscard]] bool isEmpty() const;
    virtual ~BaseContainer() = 0;

protected:
    size_t size = 0;
};

#endif
