//
// Created by yasen on 12/10/18.
//

#include <stdexcept>
#include <iostream>
#include "HashTable.h"

size_t HashTable::hash_func(const std::string& key, size_t size) {
    size_t result = key.size();
    for (const char c : key)
        result += c;

    return result & (size-1);
}

void HashTable::rehash() {
    HashTable new_table(table.size() * 2);

    for (std::list<table_elem>& list : table)
        if (!list.empty())
            for(table_elem& el : list)
                new_table.insert(el.name, el.leftName, el.rightName);

    table = new_table.table;
}

HashTable::chain_iter HashTable::find(size_t index, const std::string &key) {
    auto it = table[index].begin();
    while (it != table[index].end() && it->name != key)
        ++it;
    return it;
}

void HashTable::insert(const std::string& key, const std::string& leftKey, const std::string& rightKey) {
    size_t index = hash_func(key, table.size());
    auto it = find(index, key);

    if (it != table[index].end())
        throw std::logic_error("this key is already taken!\n");

    if (table[index].size() >= MAX_CHAIN_SIZE) {
        rehash();
        index = hash_func(key, table.size());
    }
    table[index].push_front({ key, leftKey, rightKey });
}

HashTable::chain_iter HashTable::get(const std::string& key) {
    size_t index = hash_func(key, table.size());

    auto it = find(index, key);

    if (it == table[index].end())
        throw std::logic_error("there isn't element with such key\n");

    return it;
}


void HashTable::erase(const chain_iter& it) {
    size_t index = hash_func(it->name, table.size());
    if(it->name == firstName) {
        firstName = it->rightName;
    }
    table[index].erase(it);
}

void HashTable::print() {
    chain_iter it;
    try {
        it = get(firstName);
    } catch (...) {
        std::cout << "No such name :( Sorry" << std::endl;
        return;
    }

    while(it->rightName != firstName) {
        std::cout << it->name << std::endl;
        it = get(it->rightName);
    }
    std::cout << it->name << std::endl;
}

void HashTable::release(const std::string &key, const std::string& choice) {
    chain_iter it;
    try {
        it = get(key);
    } catch (...) {
        std::cout << "No such name :( Sorry" << std::endl;
        return;
    }
    if(choice == "left") {

        it->isLeftGet = false;
        std::cout << "Release successful" << std::endl;

    } else if(choice == "right") {

        it->isRightGet = false;
        std::cout << "Release successful" << std::endl;

    } else if(choice == "both") {

        it->isLeftGet = it->isRightGet = false;
        std::cout << "Release successful" << std::endl;

    } else {
        std::cout << "Invalid command" << std::endl;
    }
}

void HashTable::grab(const std::string &key, const std::string& choice) {
    chain_iter it;
    try {
        it = get(key);
    } catch (...) {
        std::cout << "No such name :( Sorry" << std::endl;
        return;
    }

    if(choice == "left") {

        it->isLeftGet = true;
        std::cout << "Grab successful" << std::endl;

    } else if(choice == "right") {

        it->isRightGet = true;
        std::cout << "Grab successful" << std::endl;

    } else if(choice == "both") {

        it->isLeftGet = it->isRightGet = true;
        std::cout << "Grab successful" << std::endl;

    } else {
        std::cout << "Invalid command" << std::endl;
    }
}

void HashTable::info(const std::string &key) {
    chain_iter currentIt, previousIt, nextIt;
    try {
        currentIt = get(key);

        previousIt = get(currentIt->leftName);

        nextIt = get(currentIt->rightName);
    } catch (...) {
        std::cout << "No such name :( Sorry" << std::endl;
        return;
    }

    const char* handed1 = " ---> ";
    const char* handed2 = " <--- ";
    const char* handed3 = " <--> ";
    const char* handed4 = " ---- ";

    std::cout << previousIt->name;

    if(currentIt->isLeftGet && previousIt->isRightGet) {
        std::cout << handed3;
    } else if(currentIt->isLeftGet && !previousIt->isRightGet) {
        std::cout << handed2;
    } else if(!currentIt->isLeftGet && previousIt->isRightGet) {
        std::cout << handed1;
    } else {
        std::cout << handed4;
    }
    std::cout << currentIt->name;

    if(nextIt->isLeftGet && currentIt->isRightGet) {
        std::cout << handed3;
    } else if(nextIt->isLeftGet && !currentIt->isRightGet) {
        std::cout << handed2;
    } else if(!nextIt->isLeftGet && currentIt->isRightGet) {
        std::cout << handed1;
    } else {
        std::cout << handed4;
    }
    std::cout << nextIt->name << std::endl;
}

bool HashTable::isSideBySide(const chain_iter& it1, const chain_iter& it2) {
    return it1->rightName == it2->name || it1->leftName == it2->name;
}

void HashTable::addBetween(const std::string &key, const std::string &leftKey, const std::string &rightKey) {
    try {
        auto it1 = get(leftKey);
        auto it2 = get(rightKey);
        if (isSideBySide(it1, it2)) {

            it1->rightName = key;
            it1->isRightGet = true;

            it2->leftName = key;
            it2->isLeftGet = true;

            insert(key, leftKey, rightKey);
        } else {
            std::cout << "This two people it's not side by side" << std::endl;
        }
    } catch (...) {
        std::cout << "No such name :( Sorry" << std::endl;
        return;
    }
}

bool HashTable::isElementFree(const chain_iter& it1, const chain_iter& it2, const chain_iter& it3) {
    return !(it1->isRightGet || it1->isLeftGet || it2->isRightGet || it3->isLeftGet);
}

bool HashTable::remove(const std::string& key) {
    try {
        auto it1 = get(key);
        auto it2 = get(it1->leftName);
        auto it3 = get(it1->rightName);
        if (isElementFree(it1, it2, it3)) {

            it2->rightName = it3->name;
            it2->isRightGet = true;


            it3->leftName = it2->name;
            it3->isLeftGet = true;

            erase(it1);
            std::cout << "Free at last!" << std::endl;
            if(it2->rightName == it2->leftName) {
                std::cout << "...and the music stops!" << std::endl;
                return true;
            }
        } else {
            std::cout << "This won't be so easy!" << std::endl;
            return false;
        }
    } catch (...) {
        std::cout << "No such name :( Sorry" << std::endl;
        return false;
    }
}

void HashTable::swap(const std::string& key1, const std::string& key2) {
    try {

        auto it1 = get(key1);

        auto it4 = get(key2);
        if (isSideBySide(it1, it4)) {
            auto it2 = get(it1->leftName);
            auto it3 = get(it1->rightName);

            auto it5 = get(it4->rightName);
            auto it6 = get(it4->leftName);
            // it2 it1 it4 it5 before swap
            // it2 it4 it1 it5 after swap
            if (isTwoElementReleaseEachOther(it2, it1) && isTwoElementReleaseEachOther(it4, it5)) {
                swapHelper(it2, it1, it4, it5);

            }
                // it6 it4 it1 it3 before swap
                // it6 it1 it4 it3 after swap
            else if (isTwoElementReleaseEachOther(it6, it4) && isTwoElementReleaseEachOther(it1, it3)) {
                swapHelper(it6, it4, it1, it3);
            }
            else {
                std::cout << "This won't be so easy!" << std::endl;
            }

        } else {
            std::cout << "This two people it's not side by side" << std::endl;
        }
    } catch (...) {
        std::cout << "No such name :( Sorry" << std::endl;
    }
}

bool HashTable::isTwoElementReleaseEachOther(const chain_iter& it1, const chain_iter& it2) {
    return !(it1->isRightGet || it2->isLeftGet);
}

void HashTable::swapHelper(const HashTable::chain_iter &it1, const HashTable::chain_iter &it2,
                           const HashTable::chain_iter &it3, const HashTable::chain_iter &it4) {
    it1->rightName = it3->name;

    it3->leftName = it1->name;
    it3->rightName = it2->name;

    it2->leftName = it3->name;
    it2->rightName = it4->name;

    it4->leftName = it2->name;

    if(it2->isRightGet) {
        it2->isLeftGet = true;
    }
    if(it3->isLeftGet) {
        it3->isRightGet = true;
    }
    it2->isRightGet = false;
    it3->isLeftGet = false;
}

