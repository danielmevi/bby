// 
// Scope Guard source file
//
// Description:
//

#ifndef __SCOPE_GUARD__
#define __SCOPE_GUARD__

// Pre-processor trick
#define CONCATENATE_IMPL(s1, s2) s1##s2
#define CONCATENATE(s1, s2) CONCATENATE_IMPL(s1,s2)

#ifdef __COUNTER__
#define ANONYMOUS_VARIABLE(str) \
    CONCATENATE(str, __COUNTER)
#else
#define ANONYMOUS_VARIABLE(str) \
    CONCATENATE(str, __LINE)
#endif

#include <utility>

#include "uncaugh_exeption_wrapper.h"

namespace dmv {

class ScopeGuardOnExit {};
template <typename Callback>
ScopeGuard<Callback> operator+(ScopeGuardOnExit, Callback&& cb) {
    return ScopeGuard<Callback>(std::forward<Callback>(cb));

#define SCOPE_EXIT \
    auto ANONYMOUS_VARIABLE(SCOPE_EXIT_STATE) \
    = ScopeGuardOnExit() + [&] ()

}
#endif


