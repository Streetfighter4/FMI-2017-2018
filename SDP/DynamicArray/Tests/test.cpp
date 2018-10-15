//
// Created by yasen on 10/15/18.
//


#include<gtest/gtest.h>
#include<gmock/gmock.h>
#include"./DynamicArray.h"

using testing::Eq;

class DynamicArrayTests : public ::testing::Test {
protected:
    void SetUp() override {
        for (int i = 0; i < 10; ++i) {
            if(i%2) {
                obj.push_back(i*(-1));
            } else {
                obj.push_back(i);
            }
        }
    }
    DynamicArray<int> obj;
    DynamicArray<int> obj1;
};


TEST_F(DynamicArrayTests, sorting_test) {
    obj.sort();
    for (int j = 0; j < obj.getSize()-1; ++j) {
        ASSERT_LE(obj[j], obj[j+1]);
    }
}

TEST_F(DynamicArrayTests, size_test) {
    ASSERT_EQ(obj.getSize(), 10);
}

TEST_F(DynamicArrayTests, search_test) {
    ASSERT_EQ(obj.search(-5), 5);
    ASSERT_EQ(obj.search(-4), -1);
}

TEST_F(DynamicArrayTests, operator_brekets_test) {
    ASSERT_EQ(obj[5], -5);
    obj[5] = 37;
    ASSERT_EQ(obj[5], 37);
}

TEST_F(DynamicArrayTests, out_of_range_test){
    try {
        obj[15];
        FAIL() << "Expected std::out_of_range";
    }
    catch(std::out_of_range const & err) {
        EXPECT_EQ(err.what(),std::string("Out of range\n"));
    }
    catch(...) {
        FAIL() << "Expected std::out_of_range";
    }
}

TEST_F(DynamicArrayTests, removeAt_test) {
    obj.removeAt(5);
    ASSERT_EQ(obj.search(-5), -1);
    ASSERT_EQ(obj.getSize(), 9);

    obj.removeAt(15);
    ASSERT_EQ(obj.search(-7), 6);
    ASSERT_EQ(obj.getSize(), 9);
}

TEST_F(DynamicArrayTests, insertAt_test) {
    obj.insertAt(5, 0);
    ASSERT_EQ(obj[0], 5);
    ASSERT_EQ(obj.getSize(), 11);

    obj.insertAt(15, 5);
    ASSERT_EQ(obj[5], 15);
    ASSERT_EQ(obj.getSize(), 12);

    obj.insertAt(37, 12);
    ASSERT_EQ(obj[12], 37);
    ASSERT_EQ(obj.getSize(), 13);

    try {
        obj.insertAt(8, 20);
        FAIL() << "Expected std::out_of_range";
    }
    catch(std::out_of_range const & err) {
        EXPECT_EQ(err.what(),std::string("Out of range\n"));
    }
    catch(...) {
        FAIL() << "Expected std::out_of_range";
    }

    ASSERT_EQ(obj.getSize(), 13);
}

TEST_F(DynamicArrayTests, pop_back_test) {
    ASSERT_EQ(obj.pop_back(), -9);
    ASSERT_EQ(obj.getSize(), 9);
}

TEST_F(DynamicArrayTests, is_empty_test) {
    ASSERT_EQ(obj1.getSize(), 0);
    ASSERT_EQ(obj1.isEmpty(), true);
}

TEST_F(DynamicArrayTests, capacity_test) {
    ASSERT_EQ(obj.getCapacity(), 16);
}

TEST_F(DynamicArrayTests, operator_equal_test) {
    obj1 = obj;
    ASSERT_EQ(obj.getSize(), obj1.getSize());
    ASSERT_EQ(obj.getCapacity(), obj1.getCapacity());

    for (int i = 0; i < obj.getSize(); ++i) {
        ASSERT_EQ(obj[i], obj1[i]);
    }
}

TEST_F(DynamicArrayTests, copy_constuctor_test) {
    DynamicArray<int>obj2(obj);
    ASSERT_EQ(obj.getSize(), obj2.getSize());
    ASSERT_EQ(obj.getCapacity(), obj2.getCapacity());

    for (int i = 0; i < obj.getSize(); ++i) {
        ASSERT_EQ(obj[i], obj2[i]);
    }
}



