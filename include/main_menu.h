#pragma once

#include "button.h"

namespace Raykout {
class MainMenu {
 public:
  enum MainMenuButton {
    kMainMenuButton_Play = 1 << 0,
    kMainMenuButton_Quit = 1 << 1,
  };

  MainMenu();
  ~MainMenu() = default;

  void update(float dt);
  void draw();

  bool isButtonPressed(MainMenuButton button) {
    return button_pressed_ & button;
  }

 private:
  int button_pressed_;
  Button play_button_;
  Button quit_button_;
};
}  // namespace Raykout
