//
// Created by yasen on 11/1/18.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./DataManagement.hpp"

using testing::Eq;

class CongaQueuesTests : public ::testing::Test {
protected:
    void SetUp() override {
        setData(collection, "/home/yasen/Programming/FMI-2017-2018/SDP/hw1/commands.txt");
    }
    DynamicArray<LinkedList<Student*>*> collection;
};

TEST_F(CongaQueuesTests, append_test) {
    char* name = const_cast<char *>("sokrat");
    char* uni = const_cast<char *>("fmi");
    size_t indexQ = 0;
    size_t sizeQ = collection[indexQ]->getSize();

    append(indexQ, name, uni, collection);

    ASSERT_EQ(strcmp(collection[indexQ]->back()->name, name), 0);
    ASSERT_EQ(strcmp(collection[indexQ]->back()->uni, uni), 0);
    ASSERT_EQ(sizeQ+1, collection[indexQ]->getSize());
}

TEST_F(CongaQueuesTests, remove_last_test) {
    size_t indexQ = 0;
    size_t sizeQ = collection[indexQ]->getSize();

    removeLast(indexQ, collection); // remove mitko

    ASSERT_EQ(strcmp(collection[indexQ]->back()->name, "gabi"), 0);
    ASSERT_EQ(strcmp(collection[indexQ]->back()->uni, "fmi"), 0);
    ASSERT_EQ(sizeQ-1, collection[indexQ]->getSize());
}

TEST_F(CongaQueuesTests, remove_first_test) {
    size_t indexQ = 0;
    size_t sizeQ = collection[indexQ]->getSize();

    removeFirst(indexQ, collection); // remove yasen

    ASSERT_EQ(strcmp(collection[indexQ]->front()->name, "ali"), 0);
    ASSERT_EQ(strcmp(collection[indexQ]->front()->uni, "fmi"), 0);
    ASSERT_EQ(sizeQ - 1, collection[indexQ]->getSize());
}



