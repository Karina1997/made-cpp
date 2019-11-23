//
// Created by Карина Зайнуллина on 22/11/2019.
//

#ifndef MADE_CPP_HASHTABLE_H
#define MADE_CPP_HASHTABLE_H

#include <cassert>
#include <iostream>
#include <string>
#include <utility>
#include <vector>


class HashTable {
    const size_t a1 = 22861;
    const size_t m = 33554432;

    const size_t a2 = 12113;
public:
    explicit HashTable(size_t initial_size);

    ~HashTable();

    HashTable(const HashTable &) = delete;

    HashTable(HashTable &&) = delete;

    HashTable &operator=(const HashTable &) = delete;

    HashTable &operator=(HashTable &&) = delete;

    bool Has(const std::string &key);

    bool Add(const std::string &key);

    bool Remove(const std::string &key);

private:
    size_t Hash(const char *str, size_t a);

    size_t NextHash(const char *str, size_t i);

    struct HashTableNode {
        std::string key;
        bool ifPresent = true;
        size_t hash;

        HashTableNode(std::string key, size_t hash) : key(std::move(key)), hash(hash) {}
    };

    std::vector<HashTableNode *> table;
    size_t size = 0;

    bool PutToTable(std::vector<HashTableNode *> & vector, HashTableNode *node);
};


#endif //MADE_CPP_HASHTABLE_H
