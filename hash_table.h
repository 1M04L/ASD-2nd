#pragma once
#include "hash_functions.h"
#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <string>
#include <stdexcept>

template <typename T>
class HashTable {
public:
    HashTable();
    HashTable(size_t tableSize);
    HashTable(size_t tableSize, InterfaceHashFunction* function);
    HashTable(const HashTable<T>& other);
    ~HashTable();

    void insert(int key, const T& value);
    bool remove(int key);
    bool contains(int key) const;
    T& operator[](int key);
    const T& operator[](int key) const;
    
    void swap(HashTable<T>& other);
    void resize(size_t newSize);
    void setHashFunction(InterfaceHashFunction* newFunction);
    void clear();
    
    size_t getTableSize() const { return tableSize; }
    size_t getElementCount() const { return elementCount; }
    const std::vector<std::list<std::pair<int, T>>>& getHashTable() const { return table; }
    
    void print() const;
    
    HashTable<T>& operator=(const HashTable<T>& other);

private:
    InterfaceHashFunction* currentFunction;
    std::vector<std::list<std::pair<int, T>>> table;
    size_t tableSize;
    size_t elementCount;
    
    size_t calculateHash(int key) const;
    void rehashAll();
};



template <typename T>
HashTable<T>::HashTable() : tableSize(10), elementCount(0) {
    currentFunction = new HashFunction1();
    table.resize(tableSize);
}

template <typename T>
HashTable<T>::HashTable(size_t tableSize) : tableSize(tableSize > 0 ? tableSize : 10), elementCount(0) {
    currentFunction = new HashFunction1();
    table.resize(this->tableSize);
}

template <typename T>
HashTable<T>::HashTable(size_t tableSize, InterfaceHashFunction* function) 
    : tableSize(tableSize > 0 ? tableSize : 10), elementCount(0) {
    currentFunction = (function != nullptr) ? function->clone() : new HashFunction1();
    table.resize(this->tableSize);
}

template <typename T>
HashTable<T>::HashTable(const HashTable<T>& other) 
    : tableSize(other.tableSize), elementCount(other.elementCount) {
    currentFunction = other.currentFunction->clone();
    table = other.table;
}

template <typename T>
HashTable<T>::~HashTable() {
    delete currentFunction;
}

template <typename T>
size_t HashTable<T>::calculateHash(int key) const {
    return currentFunction->hashFunction(key, tableSize, 0);
}

template <typename T>
void HashTable<T>::insert(int key, const T& value) {
    size_t hash = calculateHash(key);
    

    for (auto& pair : table[hash]) {
        if (pair.first == key) {
            pair.second = value;
            return;
        }
    }
    
    table[hash].emplace_back(key, value);
    elementCount++;
}

template <typename T>
bool HashTable<T>::remove(int key) {
    if (!contains(key)) return false;
    
    size_t hash = calculateHash(key);
    auto& bucket = table[hash];
    
    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
        if (it->first == key) {
            bucket.erase(it);
            elementCount--;
            return true;
        }
    }
    return false;
}

template <typename T>
bool HashTable<T>::contains(int key) const {
    size_t hash = calculateHash(key);
    
    for (const auto& pair : table[hash]) {
        if (pair.first == key) {
            return true;
        }
    }
    return false;
}

template <typename T>
T& HashTable<T>::operator[](int key) {
    size_t hash = calculateHash(key);
    
    for (auto& pair : table[hash]) {
        if (pair.first == key) {
            return pair.second;
        }
    }
    
    table[hash].emplace_back(key, T());
    elementCount++;
    return table[hash].back().second;
}

template <typename T>
const T& HashTable<T>::operator[](int key) const {
    size_t hash = calculateHash(key);
    
    for (const auto& pair : table[hash]) {
        if (pair.first == key) {
            return pair.second;
        }
    }
    
    throw std::out_of_range("Key not found");
}

template <typename T>
void HashTable<T>::swap(HashTable<T>& other) {
    std::swap(table, other.table);
    std::swap(tableSize, other.tableSize);
    std::swap(elementCount, other.elementCount);
    std::swap(currentFunction, other.currentFunction);
}

template <typename T>
void HashTable<T>::resize(size_t newSize) {
    if (newSize == tableSize) return;
    if (newSize == 0) throw std::invalid_argument("Table size cannot be zero");
    
    std::vector<std::list<std::pair<int, T>>> newTable(newSize);
    
    // Перераспределяем все элементы
    for (const auto& bucket : table) {
        for (const auto& pair : bucket) {
            size_t newHash = currentFunction->hashFunction(pair.first, newSize, 0);
            newTable[newHash].push_back(pair);
        }
    }
    
    table = std::move(newTable);
    tableSize = newSize;
}

template <typename T>
void HashTable<T>::setHashFunction(InterfaceHashFunction* newFunction) {
    if (!newFunction) return;
    
    InterfaceHashFunction* oldFunction = currentFunction;
    currentFunction = newFunction->clone();
    
    // Перехешируем все элементы
    rehashAll();
    
    delete oldFunction;
}

template <typename T>
void HashTable<T>::clear() {
    for (auto& bucket : table) {
        bucket.clear();
    }
    elementCount = 0;
}

template <typename T>
void HashTable<T>::print() const {
    std::cout << "Hash Table (size: " << tableSize << ", elements: " << elementCount << "):" << std::endl;
    for (size_t i = 0; i < tableSize; ++i) {
        std::cout << "Hash " << i << ": ";
        if (table[i].empty()) {
            std::cout << "empty";
        } else {
            for (const auto& pair : table[i]) {
                std::cout << "[" << pair.first << ":\"" << pair.second << "\"] ";
            }
        }
        std::cout << std::endl;
    }
}

template <typename T>
void HashTable<T>::rehashAll() {
    std::vector<std::list<std::pair<int, T>>> newTable(tableSize);
    
    for (auto& bucket : table) {
        for (const auto& pair : bucket) {
            size_t newHash = calculateHash(pair.first);
            newTable[newHash].push_back(pair);
        }
    }
    
    table = std::move(newTable);
}

template <typename T>
HashTable<T>& HashTable<T>::operator=(const HashTable<T>& other) {
    if (this != &other) {
        HashTable temp(other);
        swap(temp);
    }
    return *this;
}
