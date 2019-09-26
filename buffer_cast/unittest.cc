//
// Google test source code implementation
//

#include "buffer_cast.hpp"
#include <iostream>

#include "gtest/gtest.h"

// TODO: Test without size parameter
// TODO: Test for ranges of size
// TODO: Test on diferent pointer types and conversion types to pointers

namespace {

struct S {
    int x;
    int y;
};

constexpr auto cast_size = 2;
constexpr auto random_index = 1;
constexpr auto new_data = 10;
constexpr auto test_data = 9;
constexpr auto test_index = 8;

void BasicScopeTest(char* buffer) {
    // By creating the buffer_cast object with scope existence,
    // the mapping of the new data to the buffer, will be reflected at
    // destruction of the buffer_cast object
    auto cast_obj = dmv::buffer_cast<S,cast_size>(buffer);
    cast_obj[random_index].x = new_data;
}

TEST(ScopeTest, Basic) {
    char buffer[] = {1,2,3,4,5,6,7,8,test_data,10,11,12,13,14,15,16,17,18};

    EXPECT_EQ(test_data, buffer[test_index]);
    BasicScopeTest(buffer);
    EXPECT_EQ(new_data, buffer[test_index]);
}

TEST(InlineTest, Basic) {
    char buffer[] = {1,2,3,4,5,6,7,8,test_data,10,11,12,13,14,15,16,17,18};

    EXPECT_EQ(test_data, buffer[test_index]);
    dmv::buffer_cast<S,cast_size>(buffer)[random_index].x = new_data;
    EXPECT_EQ(new_data, buffer[test_index]);
}

}
