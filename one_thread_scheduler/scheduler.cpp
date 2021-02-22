//
//
//


#include "Scheduler.h"

{
namespace scheduler
{

bool launch(PeriodicEventQueue& eventQueue, EventTimer const currentTime)
{
  Expects(!eventQueue.empty());

  std::uint32_t eventErrors{0};
  for (auto cnt{eventQueue.size()}; cnt != 0; --cnt)
  {
    auto event{eventQueue.top()};

    if (event.NextTimeout() > currentTime)
    {
      break;  // first event in sorted container still due, exit.
    }

    const auto success{event()};
    if (!success)
    {
      ++eventErrors;
    }

    eventQueue.pop();
    event.UpdateForNextTimeout();
    // Push new periodic event and sort
    eventQueue.push(std::move(event));
  }

  if (eventErrors != 0)
  {
    debug_console::print_ln("Periodic Event FAILED: ", eventErrors);
  }

  return eventErrors == 0;
}

}  // namespace scheduler
