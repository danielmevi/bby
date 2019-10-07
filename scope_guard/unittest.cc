//
//
//
//
//


#include "scope_guard.h"

void foo() {
    auto buffer = new int[10];
    SCOPE_EXIT {delete buffer; };
}

int main() {
    foo();
}
