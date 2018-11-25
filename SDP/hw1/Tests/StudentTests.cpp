//
// Created by yasen on 11/7/18.
//

#include "Student.h"
#include <gmock/gmock.h>

using testing::Eq;

class StudentTests : public ::testing::Test {
public:
    StudentTests() {
        testStudent = new Student("yasen", "fmi");
        emptyStudent = new Student();
    }
    ~StudentTests() {
        delete testStudent;
        delete emptyStudent;
    }
    Student* testStudent;
    Student* emptyStudent;
};

TEST_F(StudentTests, createStudentTest) {
    ASSERT_EQ(emptyStudent->name, nullptr);
    ASSERT_EQ(emptyStudent->uni, nullptr);
}

TEST_F(StudentTests, createStudentWithNameAndUniTest) {
    ASSERT_EQ(strcmp(testStudent->name, "yasen"), 0);
    ASSERT_EQ(strcmp(testStudent->uni, "fmi"), 0);
}

TEST_F(StudentTests, clearDataTest) {
    testStudent->clear();
    ASSERT_EQ(testStudent->name, nullptr);
    ASSERT_EQ(testStudent->uni, nullptr);
}

TEST_F(StudentTests, copyDataTest) {
    emptyStudent->copy(reinterpret_cast<const Student &>(testStudent));
    ASSERT_EQ(strcmp(emptyStudent->name, "yasen"), 0);
    ASSERT_EQ(strcmp(emptyStudent->uni, "fmi"), 0);

}
