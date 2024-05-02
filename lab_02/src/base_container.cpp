#include "../inc/base_container.h"

size_t BaseContainer::getSize() const { return size; }

bool BaseContainer::isEmpty() const { return !bool(size); }

BaseContainer::~BaseContainer() = default;