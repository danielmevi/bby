// Bby C++ Library - Main Test file
//
// TBD
//
//

#include "gtest/gtest.h"

#define _CrtSetReportFile(a, b)
#define _CrtSetReportMode(a, b)

int main(int argc, char** argv) {
    // Disable message boxes on assertion failures.
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
    try {
        testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    } catch (...) {
        // Catch all exceptions to make Coverity happy.
    }
    return EXIT_FAILURE;
}
