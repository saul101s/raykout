#include "game_over.h"

#include "renderer.h"

namespace Raykout {

GameOver::GameOver() {
  button_pressed_ = 0;

  retry_button_.position = {0.0f, -4.0f};
  retry_button_.size     = Vector2{4.0f, 2.0f};
  retry_button_.text     = "Retry";

  menu_button_.position = {0.0f, -6.5f};
  menu_button_.size     = Vector2{4.0f, 2.0f};
  menu_button_.text     = "Menu";
}

void GameOver::update(float ft) {
  button_pressed_ = 0;

  retry_button_.update();
  menu_button_.update();

  if (retry_button_.state() == Button::kButtonState_Click) {
    button_pressed_ |= kGameOverButton_Retry;
  }

  if (menu_button_.state() == Button::kButtonState_Click) {
    button_pressed_ |= kGameOverButton_Menu;
  }
}

void GameOver::draw() {
  Renderer::DrawText({"Game Over", 0, 5, 2}, RColor::DarkRed());
  retry_button_.draw();
  menu_button_.draw();
}

}  // namespace Raykout
