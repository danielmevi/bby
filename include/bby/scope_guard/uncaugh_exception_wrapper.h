//
//
//
//
//
//

#ifdef __UNCAUGHT_EXCEPTION_WRAPPER__
#define __UNCAUGHT_EXCEPTION_WRAPPER__

#include <exception>

namespace dmv {
class UncaughtExceptionCounter {
  int getUncaightExceptionCount() noexcept;
  int exceptionCount_;

public:
  UncaughtExceptionCounter() : exceptionCount_(std::uncaught_exceptions()) {}
  bool newUncaughtException() noexcept {
    return std::uncaught_exceptions() > exceptionCount_;
  }
}

#endif
