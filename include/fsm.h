#pragma once

#include <memory>
#include <vector>
#include <cassert>

namespace Raykout {
class FSMState {
  friend class FSM;

 public:
  int event;

 public:
  FSMState(const char* name) : name_(name), event(-1) {}
  FSMState() : name_("State") {}
  virtual ~FSMState() = default;

  virtual void onEnter()        = 0;
  virtual void update(float dt) = 0;
  virtual void draw()           = 0;
  virtual void onExit()         = 0;

  unsigned int id() const { return id_; }
  const char* name() const { return name_; }

 private:
  unsigned int id_;
  const char* name_;
};

struct Transition {
  unsigned int initial_state_id;
  unsigned int final_state_id;
  int event;

  Transition(unsigned int initial_state_id, unsigned int final_state_id, int event)
      : initial_state_id(initial_state_id), final_state_id(final_state_id), event(event) {}

  bool operator==(const Transition& o) {
    return initial_state_id == o.initial_state_id && final_state_id == o.final_state_id && event == o.event;
  }

  bool operator!=(const Transition& o) { return !(*this == o); }

  static Transition Invalid() { return {0, 0, -1}; }
};

class FSM {
 public:
  FSM() : current_state_(0) {}
  ~FSM() = default;

  unsigned int currentState() { return current_state_; }

  unsigned int addState(std::shared_ptr<FSMState> state) {
    state->id_ = (unsigned int)states_.size();
    states_.push_back(state);
    return state->id_;
  };

  void addTransition(unsigned int id1, unsigned int id2, int event) {
    assert(id1 < (unsigned int)states_.size());
    assert(id2 < (unsigned int)states_.size());
    assert(transition(id1, event) == Transition::Invalid());

    transitions_.emplace_back(id1, id2, event);
  }

  void update(float dt) {
    assert(current_state_ < states_.size());

    handleTransitions();
    states_[current_state_]->update(dt);
  }

  void draw() {
    assert(current_state_ < states_.size());

    states_[current_state_]->draw();
  }

 private:
  void handleTransitions() {
    if (states_[current_state_]->event >= 0) {
      Transition t = transition(current_state_, states_[current_state_]->event);
      if (t != Transition::Invalid()) {
        transitionTo(t.final_state_id);
      }
    }
  }

  Transition transition(unsigned int id, int event) {
    for (const auto& transition : transitions_) {
      if (transition.initial_state_id == id && transition.event == event)
        return transition;
    }

    return Transition::Invalid();
  }

  void transitionTo(unsigned int state_id) {
    assert(state_id < states_.size());

    states_[current_state_]->onExit();
    states_[current_state_]->event = -1;
    current_state_                 = state_id;
    states_[current_state_]->onEnter();
  }

 private:
  unsigned int current_state_;
  std::vector<std::shared_ptr<FSMState>> states_;
  std::vector<Transition> transitions_;
};
}  // namespace Raykout
