#include "Scheduler.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

class CallbackMockContainer {
public:
  class CallbackMock {
  public:
    // TODO(dmedinav): Change mockcallback to bool return type to better use of
    // gtest and reduce workarounds
    MOCK_METHOD0(Callback1, bool());
    MOCK_METHOD0(Callback2, bool());
    MOCK_METHOD0(Callback3, bool());
  };

  /// @brief Declaration of static unique_ptr
  static std::unique_ptr<CallbackMock> g_callback_mock_obj;
};

std::unique_ptr<CallbackMockContainer::CallbackMock>
    CallbackMockContainer::g_callback_mock_obj;

class CheckPeriodicEventsTest : public testing::Test {
public:
  void SetUp() override {
    CallbackMockContainer::g_callback_mock_obj =
        std::make_unique<CallbackMockContainer::CallbackMock>();
  }

  void TearDown() override {
    // NOLINTNEXTLINE(clang-analyzer-optin.cplusplus.VirtualCall)
    CallbackMockContainer::g_callback_mock_obj = nullptr;
  }

  scheduler::PeriodicEventQueue eventQueue;
};

constexpr auto g_cb_1_id{1};
constexpr auto g_cb_2_id{2};
constexpr auto g_cb_3_id{3};

// Unit tests
// NOLINTNEXTLINE
TEST_F(CheckPeriodicEventsTest, TestPriorityQueueSequence) {
  std::chrono::milliseconds const delta{std::chrono::milliseconds(1)};

  scheduler::EventTimer const startTime(std::chrono::milliseconds(0));
  scheduler::EventTimer currentTime(startTime);

  const auto timeout1{delta};
  const auto timeout2{delta * 2};
  const auto timeout3{delta * 4};
  constexpr auto maxCount{500};

  auto cB1{[](int const id) {
    // NOLINTNEXTLINE
    EXPECT_EQ(id, g_cb_1_id);
    return CallbackMockContainer::g_callback_mock_obj->Callback1();
  }};

  auto cB2{[](int const id) {
    // NOLINTNEXTLINE
    EXPECT_EQ(id, g_cb_2_id);
    return CallbackMockContainer::g_callback_mock_obj->Callback2();
  }};

  auto cB3{[](int const id) {
    // NOLINTNEXTLINE
    EXPECT_EQ(id, g_cb_3_id);
    return CallbackMockContainer::g_callback_mock_obj->Callback3();
  }};

  auto eventCB1{[=]() { return cB1(g_cb_1_id); }};
  auto eventCB2{[=]() { return cB2(g_cb_2_id); }};
  auto eventCB3{[=]() { return cB3(g_cb_3_id); }};

  eventQueue.emplace(scheduler::PeriodicEvent::EPriority::high, startTime,
                     timeout1, eventCB1);
  eventQueue.emplace(scheduler::PeriodicEvent::EPriority::low, startTime,
                     timeout2, eventCB2);
  eventQueue.emplace(scheduler::PeriodicEvent::EPriority::high, startTime,
                     timeout3, eventCB3);

  // NOLINTNEXTLINE
  EXPECT_CALL(*CallbackMockContainer::g_callback_mock_obj, Callback1).Times(0);
  // NOLINTNEXTLINE
  EXPECT_CALL(*CallbackMockContainer::g_callback_mock_obj, Callback2).Times(0);
  // NOLINTNEXTLINE
  EXPECT_CALL(*CallbackMockContainer::g_callback_mock_obj, Callback3).Times(0);
  scheduler::launch(eventQueue, currentTime);

  for (auto cnt{maxCount}; cnt != 0; --cnt) {
    // NOLINTNEXTLINE
    EXPECT_CALL(*CallbackMockContainer::g_callback_mock_obj, Callback1())
        .WillOnce(testing::Return(true));
    // NOLINTNEXTLINE
    EXPECT_CALL(*CallbackMockContainer::g_callback_mock_obj, Callback2())
        .Times(0);
    // NOLINTNEXTLINE
    EXPECT_CALL(*CallbackMockContainer::g_callback_mock_obj, Callback3())
        .Times(0);
    currentTime += std::chrono::milliseconds(delta);
    scheduler::launch(eventQueue, currentTime);

    // NOLINTNEXTLINE
    EXPECT_CALL(*CallbackMockContainer::g_callback_mock_obj, Callback1())
        .WillOnce(testing::Return(true));
    // NOLINTNEXTLINE
    EXPECT_CALL(*CallbackMockContainer::g_callback_mock_obj, Callback2())
        .WillOnce(testing::Return(true));
    // NOLINTNEXTLINE
    EXPECT_CALL(*CallbackMockContainer::g_callback_mock_obj, Callback3())
        .Times(0);
    currentTime += std::chrono::milliseconds(delta);
    scheduler::launch(eventQueue, currentTime);

    // NOLINTNEXTLINE
    EXPECT_CALL(*CallbackMockContainer::g_callback_mock_obj, Callback1())
        .WillOnce(testing::Return(true));
    // NOLINTNEXTLINE
    EXPECT_CALL(*CallbackMockContainer::g_callback_mock_obj, Callback2())
        .Times(0);
    // NOLINTNEXTLINE
    EXPECT_CALL(*CallbackMockContainer::g_callback_mock_obj, Callback3())
        .Times(0);
    currentTime += std::chrono::milliseconds(delta);
    scheduler::launch(eventQueue, currentTime);

    // NOLINTNEXTLINE
    EXPECT_CALL(*CallbackMockContainer::g_callback_mock_obj, Callback1())
        .WillOnce(testing::Return(true));
    // NOLINTNEXTLINE
    EXPECT_CALL(*CallbackMockContainer::g_callback_mock_obj, Callback2())
        .WillOnce(testing::Return(true));
    // NOLINTNEXTLINE
    EXPECT_CALL(*CallbackMockContainer::g_callback_mock_obj, Callback3())
        .WillOnce(testing::Return(true));
    currentTime += std::chrono::milliseconds(delta);
    scheduler::launch(eventQueue, currentTime);
  }
}

// NOLINTNEXTLINE
TEST_F(CheckPeriodicEventsTest, EmptyEventContainer) {
  scheduler::EventTimer currentTime(std::chrono::milliseconds(0));
  scheduler::PeriodicEventQueue periodicEventContainer;

  // NOLINTNEXTLINE
  EXPECT_EXIT(scheduler::launch(periodicEventContainer, currentTime),
              ::testing::KilledBySignal(SIGABRT), "");
}

// NOLINTNEXTLINE
TEST_F(CheckPeriodicEventsTest, EventNotSucceded) {
  scheduler::EventTimer const startTime(std::chrono::milliseconds(0));
  std::chrono::milliseconds const timeout{std::chrono::milliseconds(1)};

  auto eventCB{[] { return false; }};

  scheduler::PeriodicEventQueue eventQueue;
  eventQueue.emplace(scheduler::PeriodicEvent::EPriority::high, startTime,
                     timeout, eventCB);

  scheduler::EventTimer const currentTime(startTime +
                                          std::chrono::milliseconds(1));
  // NOLINTNEXTLINE
  EXPECT_FALSE(scheduler::launch(eventQueue, currentTime));
}

// NOLINTNEXTLINE
TEST_F(CheckPeriodicEventsTest, EventNextTimeoutChecks) {
  using namespace std::chrono_literals;

  constexpr auto eventTimeout1{std::chrono::milliseconds{10}};
  constexpr auto eventTimeout2{std::chrono::milliseconds{20}};

  scheduler::EventTimer startTime(std::chrono::milliseconds(0));
  auto eventCB{[] { return true; }};

  eventQueue.emplace(scheduler::PeriodicEvent::EPriority::high, startTime,
                     eventTimeout1, eventCB);

  eventQueue.emplace(scheduler::PeriodicEvent::EPriority::low, startTime,
                     eventTimeout2, eventCB);

  {
    // Prioritized event 1
    auto event{eventQueue.top()};
    // NOLINTNEXTLINE
    EXPECT_EQ(event.Priority(), scheduler::PeriodicEvent::EPriority::high);
    auto const timeout(event.NextTimeout());
    event.UpdateForNextTimeout();
    // NOLINTNEXTLINE
    EXPECT_NE(event.NextTimeout(), timeout);
    eventQueue.pop();
  }

  {
    // Prioritized event 2
    auto event{eventQueue.top()};
    // NOLINTNEXTLINE
    EXPECT_EQ(event.Priority(), scheduler::PeriodicEvent::EPriority::low);
    auto const timeout(event.NextTimeout());
    event.UpdateForNextTimeout();
    // NOLINTNEXTLINE
    EXPECT_NE(event.NextTimeout(), timeout);
    eventQueue.pop();
  }

  // NOLINTNEXTLINE
  EXPECT_TRUE(eventQueue.empty());
}
