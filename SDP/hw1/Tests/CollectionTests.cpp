//
// Created by yasen on 11/7/18.
//

#include <DataManagement.hpp>
#include <gmock/gmock.h>

using testing::Eq;

class CollectionTests : public ::testing::Test {
protected:
    void SetUp() override {
        setData(collection, "/home/yasen/Programming/FMI-2017-2018/SDP/hw1/commands.txt");
    }
    DynamicArray<LinkedList<Student*>*> collection;
};

