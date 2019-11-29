//
// Google test source code implementation
//


#include "index_range.hpp"

#include <vector>
#include <iostream>

#include "gtest/gtest.h"

//TODO(): Add GSL to conan
//TODO(): Add testing
//


void foo1(std::vector<int>& a, std::vector<int>& b) {
    for(const auto index : dmv::range(a)){
        a[index] += b[index];
    }
}

void foo2(std::vector<int>& a, std::vector<int>& b) {
    const auto end{a.size()};
    for(auto index{0}; index != end; ++index){
        a[index] += b[index];
    }
}

TEST(Basic, basic){
    std::vector<int> a{0,1,2,3,4,5,6,7,8,9};
    std::vector<int> b{9,8,7,6,5,4,3,2,1,0};
    foo1(a, b);
    foo2(a, b);
}

