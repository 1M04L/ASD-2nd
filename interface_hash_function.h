
#pragma once
#include <cstddef>

class InterfaceHashFunction {
public:
    virtual ~InterfaceHashFunction() = default;
    virtual size_t hashFunction(int key, size_t tableSize, int attempt = 0) = 0;
    virtual InterfaceHashFunction* clone() const = 0;
};
