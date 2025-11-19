// ===============================
// PSEUDOCODE OVERVIEW (C++-like)
// Files to create later:
//   include/state.h                 (already created)
//   include/dispenser.h             (API + state management)
//   include/idle_state.h            (states' headers)
//   include/selecting_state.h
//   include/dispensing_state.h
//   include/maintenance_state.h
//   include/error_state.h
//   src/idle_state.cpp              (implementations later)
//   src/selecting_state.cpp
//   src/dispensing_state.cpp
//   src/maintenance_state.cpp
//   src/error_state.cpp
// ===============================
/*
#pragma region include_headers
// NOTE: Pseudocode — shows intent only; not yet compilable
#include <Arduino.h>        // millis(), types
#include <stdint.h>         // fixed-width ints
#include "ui.h"              // UserInterface
#include "state.h"           // base State interface (already exists)
#pragma endregion

// Forward decls
class State;               // from state.h
class UserInterface;       // from ui.h

// ===============================
// dispenser.h (PSEUDOCODE)
// ===============================
class Dispenser {
public:
  // CTOR gets reference to UI (injection) and initial state object
  Dispenser(UserInterface& ui);

  // lifecycle
  void begin();                 // init hardware drivers via UI, set initial state
  void tick(uint32_t now_ms);   // periodic pump: read inputs, forward events, run state's tick

  // state management
  void set_state(State& next, uint32_t now_ms);  // perform transition with on_exit/on_enter
  State& current_state() const;                   // for logging / tests

  // domain actions (invoked by states)
  void start_pump(uint16_t ms);    // command actuator (through UI/driver)
  void stop_pump();
  void open_valve(uint8_t id);
  void close_valve(uint8_t id);

  // configuration / timeouts shared by states
  uint32_t selecting_timeout_ms() const;   // e.g., 20_000
  uint32_t dispense_safety_ms() const;     // e.g., 6_000

  // routing of input events from UI to current state
  void on_button(const ButtonEvent& ev, uint32_t now_ms);
  void on_sensor(const SensorData& s, uint32_t now_ms);

  // high-level helpers
  void show(const char* line1, const char* line2 = nullptr);

private:
  UserInterface& ui_;
  State* state_;                // non-owning; lifetime managed externally or static singletons

  // book-keeping
  uint32_t last_tick_ms_;
};

// ===============================
// idle_state.h (PSEUDOCODE)
// ===============================
class IdleState : public State {
public:
  static IdleState& instance();            // singleton to avoid dynamic allocation

  StateId id() const override;             // StateId::Idle
  const char* name() const override;       // "Idle"

  void on_enter(Dispenser&, UserInterface&, uint32_t) override;  // clear screen, show welcome
  void handle_tick(Dispenser&, UserInterface&, uint32_t) override; // maybe blink, standby
  void handle_button(Dispenser&, UserInterface&, const ButtonEvent&) override; // any button -> Selecting
  void display(UserInterface&) const override; // draw idle UI
};

// ===============================
// selecting_state.h (PSEUDOCODE)
// ===============================
class SelectingState : public State {
public:
  static SelectingState& instance();

  StateId id() const override;           // StateId::Selecting
  const char* name() const override;     // "Selecting"

  void on_enter(Dispenser&, UserInterface&, uint32_t) override;   // reset selection, start timeout
  void handle_tick(Dispenser&, UserInterface&, uint32_t) override; // check inactivity -> Idle
  void handle_button(Dispenser&, UserInterface&, const ButtonEvent&) override; // navigate/confirm
  void handle_sensor_update(Dispenser&, UserInterface&, const SensorData&) override; // require cup
  void display(UserInterface&) const override; // draw menu and selection cursor

private:
  // internal selection index, deadline, etc. (kept inside state if not singleton, otherwise inside Dispenser)
};

// ===============================
// dispensing_state.h (PSEUDOCODE)
// ===============================
class DispensingState : public State {
public:
  static DispensingState& instance();

  StateId id() const override;           // StateId::Dispensing
  const char* name() const override;     // "Dispensing"

  void on_enter(Dispenser&, UserInterface&, uint32_t) override;     // start pump/valve, set end time
  void handle_tick(Dispenser&, UserInterface&, uint32_t) override;   // stop when time reached or sensor triggers
  void handle_button(Dispenser&, UserInterface&, const ButtonEvent&) override; // cancel -> Idle/Error
  void handle_sensor_update(Dispenser&, UserInterface&, const SensorData&) override; // cup removed? stop
  void display(UserInterface&) const override; // progress bar / countdown
};

// ===============================
// maintenance_state.h (PSEUDOCODE)
// ===============================
class MaintenanceState : public State {
public:
  static MaintenanceState& instance();

  StateId id() const override;           // StateId::Maintenance
  const char* name() const override;     // "Maintenance"

  void on_enter(Dispenser&, UserInterface&, uint32_t) override;    // enter menu: purge, prime, test
  void handle_tick(Dispenser&, UserInterface&, uint32_t) override; // maybe safety timeouts
  void handle_button(Dispenser&, UserInterface&, const ButtonEvent&) override; // choose action
  void display(UserInterface&) const override; // maintenance menu
};

// ===============================
// error_state.h (PSEUDOCODE)
// ===============================
class ErrorState : public State {
public:
  static ErrorState& instance();

  StateId id() const override;           // StateId::Error
  const char* name() const override;     // "Error"

  void on_enter(Dispenser&, UserInterface&, uint32_t) override;    // log error, buzzer, show code
  void handle_tick(Dispenser&, UserInterface&, uint32_t) override; // blink/beep pattern
  void handle_button(Dispenser&, UserInterface&, const ButtonEvent&) override; // acknowledge -> Idle
  void display(UserInterface&) const override; // show error text/code

  // Optional: set/get last error code via Dispenser or static storage
};

// ===============================
// src/dispenser.cpp (PSEUDOCODE SKETCH)
// ===============================
void Dispenser::begin() {
  // ui_.begin(); // init drivers
  // state_ = &IdleState::instance();
  // state_->on_enter(*this, ui_, millis());
}

void Dispenser::tick(uint32_t now_ms) {
  // poll inputs via UI
  //   ButtonEvent ev; while (ui_.poll_button(ev)) on_button(ev, now_ms);
  //   SensorData s;  if (ui_.read_sensors(s)) on_sensor(s, now_ms);
  // forward periodic tick to current state
  // state_->handle_tick(*this, ui_, now_ms);
  // state_->display(ui_); // centralize display call if desired
}

void Dispenser::set_state(State& next, uint32_t now_ms) {
  // if (state_) state_->on_exit(*this, ui_, now_ms);
  // state_ = &next;
  // state_->on_enter(*this, ui_, now_ms);
}

void Dispenser::on_button(const ButtonEvent& ev, uint32_t now_ms) {
  // if (state_) state_->handle_button(*this, ui_, ev);
}

void Dispenser::on_sensor(const SensorData& s, uint32_t now_ms) {
  // if (state_) state_->handle_sensor_update(*this, ui_, s);
}

// ===============================
// Transitions (illustrative logic; to be implemented inside states later):
//   IdleState::handle_button -> set_state(SelectingState::instance())
//   SelectingState::handle_button(confirm) -> set_state(DispensingState::instance())
//   SelectingState::handle_tick(timeout)   -> set_state(IdleState::instance())
//   DispensingState::handle_tick(done)     -> set_state(IdleState::instance())
//   DispensingState::handle_sensor_update(cup_removed) -> set_state(ErrorState::instance())
//   ErrorState::handle_button(ack) -> set_state(IdleState::instance())
//   MaintenanceState reachable via hidden combo (long-press) from Idle/Selecting
// ===============================

*/
