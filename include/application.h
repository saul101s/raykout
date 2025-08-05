#pragma once

#include "fsm.h"
#include "renderer.h"

namespace Raykout {
class Application {
 public:
  enum State {
    kState_MainMenu = 0,
    kState_Game,
    kState_GameOver,
    kState_Quit
  };

  Application()  = default;
  ~Application() = default;

  void run();

 private:
  void initialize();
  void loop();
  void update(float dt);
  void updateViewport();
  void draw();
  void reload();

 private:
  FSM fsm_;
  unsigned int quit_state_id_;
  Renderer::Viewport viewport_;
  float aspect_;
};
}  // namespace Raykout
