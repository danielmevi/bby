//
//
//
//


#pragma once

#include <gsl/gsl>

#include <chrono>
#include <queue>
#include <tuple>
#include <vector>

namespace scheduler
{

using Clock = std::chrono::steady_clock;
using EventTimer = std::chrono::time_point<Clock>;
using Callback = std::function<bool(void)>;

/// @brief Template type that represents the two updates events that can happen
///
/// @details PeriodicEvent represents the object that will hold the information
///          of the events required to be fired
///
// LCOV_EXCL_START
class PeriodicEvent
// LCOV_EXCL_STOP
{
public:
  /// @brief Helper type to name the two possible priorities the PeriodicEvent
  /// can have
  ///
  /// @details Enum Class with high and low priorities for the two priorities
  ///          PeriodicEvent can have
  enum class EPriority
  {
    high,
    low
  };

  PeriodicEvent(EPriority priority, EventTimer startClock,
                std::chrono::milliseconds timeout, Callback callback)
      : _priority{priority}
      , _timeout{timeout}
      , _nextTimeout{startClock + timeout}
      , _functor{std::move(callback)}
  {
  }

  /// @brief Functor execution of the callback for the specific event
  /// @return bool
  bool operator()()
  {
    auto const result{_functor()};
    return result;
  }

  /// @brief Each PeriodicEvent event after being executed it is required to be
  ///        rescheduled again for the next periodic timeout. This function is
  ///        responsible to update the object it self with its default periodic
  ///        timeout
  /// @return void
  void UpdateForNextTimeout() noexcept { _nextTimeout += _timeout; }

  /// @brief GetPriority will be used to prioritze PeriodicEvent execution with
  ///        the same timeout. This function returns the PeriodicEvent priority
  /// @return Enum Class EPriority
  EPriority const& Priority() const { return _priority; }

  /// @brief GetNextTimeout will be used to prioritze PeriodicEvent execution.
  ///        This function returns the PeriodicEvent next timeout
  /// @return std::chrono::time_point<std::chrono::steady_clock>
  EventTimer const& NextTimeout() const { return _nextTimeout; }

private:
  /// @brief Value holding the priority to define priority against type of
  ///        events when the next timeout is equal
  EPriority _priority;

  /// @brief Value holding the periodic time the event needs to be periodically
  ///        executed
  std::chrono::milliseconds _timeout;

  /// @brief Value holding the representation of the future time the events
  ///        will be executed.
  ///
  /// @details Initialization value is represented by (now + timeout). Following
  //           updates will be represented by (previous timeout + timeout)
  EventTimer _nextTimeout;

  /// @brief Generic Callback defined by event type
  ///
  /// @details This object is the non-onwning reference holder of Configuration,
  ///          SignalGroups, Pdu containers and socket container.
  Callback _functor;
};

/// @brief Provide ordering for PeriodicEvent objects in PeriodicEventQueue
///
/// @note Satisfies Compare concept
struct PeriodicEventComparison
{
  auto operator()(PeriodicEvent const& leftEvent,
                  PeriodicEvent const& rightEvent) const
  {
    return std::tie(leftEvent.NextTimeout(), leftEvent.Priority()) >
           std::tie(rightEvent.NextTimeout(), rightEvent.Priority());
  }
};

using PeriodicEventQueue =
    std::priority_queue<PeriodicEvent, std::vector<PeriodicEvent>,
                        PeriodicEventComparison>;

/// @brief Launch event template function
///
/// @param eventQueue - Sorted queue of events
/// @param currentTime - Current timestamp
/// @return success - the success status of the execution
///
/// @details Periodically checks if event callback needs to be called and
/// schedules next occurrence
bool launch(PeriodicEventQueue& eventQueue, EventTimer currentTime);

}  // namespace scheduler
