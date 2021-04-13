// @name StdAppService.cpp
// @Author Daniel Medina - dmedinav
//

namespace {
// @brief Constants defined for Transferable Profile State Machine
std::string const error{"error"};
std::string const not_ready{"not_ready"};
std::string const standby{"standby"};
std::string const ready{"ready"};
std::string const setup{"setup"};
std::string const running{"running"};
std::string const end{"end"};

auto constexpr Ethernet{5};
auto constexpr Offboard{3};
auto constexpr MaxQueueSize{64};
auto constexpr MaxProfilesAvailable{10};
} // namespace

namespace flush {

// @brief Generic State Machine
class StateMachine {
  // TODO(thread): Make it thread safe by compile configuration
  // TODO(config): Make it configurable and put in a different file
public:
  std::string next(std::string const &next_state) {
    auto const current_node{SequenceNodes_.find(current_state_)};
    if (current_node == SequenceNodes_.end()) {
      // TODO(error): Make this check unit test (assert or similar)
      // TODO(alloc): Ensure no memory allocation
      return {"internal: " + current_state_ + "->" + next_state};
    }

    auto const &current_node_sequence{current_node->second};
    auto const found{current_node_sequence.find(next_state)};
    if (found == current_node_sequence.end()) {
      // TODO(alloc): Ensure no memory allocation
      return {"sequence: " + current_state_ + "->" + next_state};
    }
    current_state_ = next_state;
    return {""};
  }

private:
  std::string current_state_{not_ready};
  std::unordered_map<std::string, std::unordered_set<std::string>>
      SequenceNodes_{{error, {end}},     {not_ready, {standby}},
                     {standby, {ready}}, {ready, {setup}},
                     {setup, {running}}, {running, {end}}};
};
} // namespace flush
