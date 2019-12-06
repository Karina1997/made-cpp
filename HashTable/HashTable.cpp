

#include "HashTable.h"

HashTable::HashTable(size_t initial_size) : table(initial_size, nullptr) {}

HashTable::~HashTable() {
    for (HashTableNode *node: table) {
        delete node;
    }
}

size_t HashTable::Hash (const char *str, size_t a) const {
    size_t hash = 0;
    for (; *str != 0; ++str) {
        hash = (hash * a + *str) % m;
    }
    return hash;
}

bool HashTable::Has(const std::string &key) {
    assert(!key.empty());

    size_t hash = Hash(key.c_str(), a1);
    int i = 0;
    while (table[hash % table.size()] != nullptr) {
        if (table[hash % table.size()]->key == key) {
            return table[hash % table.size()]->ifPresent;
        }
        i++;
        hash = NextHash(key.c_str(), i);
    }

    return false;
}


bool HashTable::Add(const std::string &key) {
    assert(!key.empty());

    resize();

    size_t hash = Hash(key.c_str(), a1);
    auto newNode = new HashTableNode(key, hash);
    bool ifPutted = PutToTable(table, newNode);
    if (ifPutted) {
        size++;
    }
    return ifPutted;
}

void HashTable::resize() {
    if (4 * size >= 3 * table.size()) {
        std::vector<HashTableNode *> newTable = std::vector<HashTableNode *>(table.size() * 2);
        for (HashTableNode *elem: table) {
            if (elem != nullptr && elem->ifPresent) {
                PutToTable(newTable, elem);
            }
        }
        table = newTable;
    }
}

bool HashTable::Remove(const std::string &key) {
    assert(!key.empty());

    size_t hash = Hash(key.c_str(), a1);
    int i = 0;
    while (table[hash % table.size()] != nullptr) {
        if (table[hash % table.size()]->key == key) {
            if (table[hash % table.size()]->ifPresent) {
                table[hash % table.size()]->ifPresent = false;
                return true;
            } else {
                return false;
            }
        }
        i++;
        hash = NextHash(key.c_str(), i);
    }

    return false;
}

size_t HashTable::NextHash(const char *str, size_t i) {
    return Hash(str, a1) + (2 * Hash(str, a2) + 1) * i;
}


bool HashTable::PutToTable(std::vector<HashTableNode *> &vector, HashTable::HashTableNode *node) {
    size_t hash = Hash(node->key.c_str(), a1);
    int i = 0;
    while (vector[hash % vector.size()] != nullptr && vector[hash % vector.size()]->ifPresent) {
        if (vector[hash % vector.size()]->key == node->key) {
            delete(node);
            return false;
        }
        i++;
        hash = NextHash(node->key.c_str(), i);
    }

    vector[hash % vector.size()] = node;
    return true;
}

int hashTableMain() {
    HashTable table(8);
    char command = ' ';
    std::string value;
    while (std::cin >> command >> value) {
        switch (command) {
            case '?':
                std::cout << (table.Has(value) ? "OK" : "FAIL") << std::endl;
                break;
            case '+':
                std::cout << (table.Add(value) ? "OK" : "FAIL") << std::endl;
                break;
            case '-':
                std::cout << (table.Remove(value) ? "OK" : "FAIL") << std::endl;
                break;
        }
    }
    return 0;
}
