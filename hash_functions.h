#pragma once
#include "interface_hash_function.h"
#include <cmath>

class HashFunction1 : public InterfaceHashFunction {
private:
    int c, d;
    
public:
    HashFunction1() : c(25 % 5), d(25 % 7) {}
    
    size_t hashFunction(int key, size_t tableSize, int attempt = 0) override {
        if (attempt == 0) {
            return static_cast<size_t>(key) % tableSize;
        }
        
        int prevHash = static_cast<int>(hashFunction(key, tableSize, attempt - 1));
        int result = (prevHash + c * attempt + d * attempt * attempt) % static_cast<int>(tableSize);
        return static_cast<size_t>(result >= 0 ? result : result + tableSize);
    }
    
    InterfaceHashFunction* clone() const override {
        return new HashFunction1(*this);
    }
};

class HashFunction2 : public InterfaceHashFunction {
private:
    double a;
    
public:
    HashFunction2() : a(-(1 - std::sqrt(5)) / 2) {}
    
    size_t hashFunction(int key, size_t tableSize, int attempt = 0) override {
        if (attempt == 0) {
            return static_cast<size_t>(key) % tableSize;
        }
        
        int prevHash = static_cast<int>(hashFunction(key, tableSize, attempt - 1));
        double temp = prevHash * a * tableSize;
        int result = static_cast<int>(std::floor(temp)) % static_cast<int>(tableSize);
        return static_cast<size_t>(result >= 0 ? result : result + tableSize);
    }
    
    InterfaceHashFunction* clone() const override {
        return new HashFunction2(*this);
    }
};

class HashFunction3 : public InterfaceHashFunction {
public:
    size_t hashFunction(int key, size_t tableSize, int attempt = 0) override {
        if (tableSize <= 2) return 0;
        
        if (attempt == 0) {
            return static_cast<size_t>(key) % tableSize;
        }
        
        int h0 = key % static_cast<int>(tableSize);
        int result = (h0 + attempt * (1 + key % (static_cast<int>(tableSize) - 2))) % static_cast<int>(tableSize);
        return static_cast<size_t>(result >= 0 ? result : result + tableSize);
    }
    
    InterfaceHashFunction* clone() const override {
        return new HashFunction3(*this);
    }
};
