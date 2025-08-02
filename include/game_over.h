#pragma once

#include "button.h"

namespace Raykout {
class GameOver {
 public:
  enum GameOverButton {
    kGameOverButton_Retry = 1 << 0,
    kGameOverButton_Menu = 1 << 1,
  };

  GameOver();
  ~GameOver() = default;

  void update(float dt);
  void draw();

  bool isButtonPressed(GameOverButton button) {
    return button_pressed_ & button;
  }

 private:
  int button_pressed_;
  Button retry_button_;
  Button menu_button_;
};
}  // namespace Raykout
