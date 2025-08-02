#pragma once

#include "scene.h"
#include "main_menu.h"
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
  Scene scene_;
  MainMenu main_menu_;
  State state_;

  Renderer::Viewport viewport_;
  float aspect_;
};
}  // namespace Raykout
