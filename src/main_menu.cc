#include "main_menu.h"

#include "button.h"
#include "vector2.h"

namespace Raykout {
MainMenu::MainMenu() {
  state_.pressed        = 0;

  play_button_.position = Vector2::Zero();
  play_button_.size     = Vector2{4.0f, 2.0f};
  play_button_.text     = "Start";

  quit_button_.position = Vector2{0.0f, -3.0f};
  quit_button_.size     = Vector2{4.0f, 2.0f};
  quit_button_.text     = "Quit";
}

void MainMenu::update(float dt) {
  // Clean the state
  state_.pressed = 0;

  play_button_.update();
  quit_button_.update();

  if (play_button_.state() == Button::kButtonState_Click) {
    state_.pressed |= kMainMenuButton_Play;
  }

  if (quit_button_.state() == Button::kButtonState_Click) {
    state_.pressed |= kMainMenuButton_Quit;
  }
}

void MainMenu::draw() {
  play_button_.draw();
  quit_button_.draw();
}

}  // namespace Raykout
