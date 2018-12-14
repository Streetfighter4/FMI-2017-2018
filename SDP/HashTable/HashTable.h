//
// Created by yasen on 12/10/18.
//

#ifndef HASHTABLE_HASHTABLE_H
#define HASHTABLE_HASHTABLE_H

#include <string>
#include <utility>
#include <vector>
#include <list>

class HashTable {
    struct table_elem {
        std::string name;
        std::string leftName;
        std::string rightName;
        bool isLeftGet;
        bool isRightGet;
        table_elem(std::string key = "", std::string leftKey = "", std::string rightKey = "") :
                name(key), leftName(leftKey), rightName(rightKey), isLeftGet(true), isRightGet(true) {}
    };
    using hash_table = std::vector<std::list<table_elem>>;
    using chain_iter = std::list<table_elem>::iterator;
private:
    hash_table table;

    static const size_t BASE_SIZE = 2;

    static const size_t MAX_CHAIN_SIZE = 3;

public:
    HashTable(size_t size = BASE_SIZE, const std::string& fName = "") : table(size), firstName(fName) {}
    std::string firstName;
private:
    static size_t hash_func(const std::string& key, size_t size);
    void rehash();
    chain_iter find(size_t index, const std::string& key);
    chain_iter get(const std::string& key);
    void erase(const chain_iter& it);


    bool isSideBySide(const chain_iter&, const chain_iter&);
    bool isElementFree(const chain_iter&, const chain_iter&, const chain_iter&);
    bool isTwoElementReleaseEachOther(const chain_iter& it1, const chain_iter& it2);
    void swapHelper(const chain_iter& it1, const chain_iter& it2, const chain_iter& it3, const chain_iter& it4);
public:
    void release(const std::string& key, const std::string& choice);
    void grab(const std::string& key, const std::string& choice);
    void info(const std::string& key);

    void addBetween(const std::string& key, const std::string& leftKey, const std::string& rightKey);
    bool remove(const std::string& key);
    void swap(const std::string& key1, const std::string& key2);

public:
    void insert(const std::string& key, const std::string& leftKey, const std::string& rightKey);

    void print();

};


#endif //HASHTABLE_HASHTABLE_H
