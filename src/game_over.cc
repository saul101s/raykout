#include "game_over.h"

#include "settings.h"
#include "audio_manager.h"
#include "renderer.h"

namespace Raykout {

GameOver::GameOver() {
  button_pressed_ = 0;

  int hover_audio_handle = AudioManager::Instance().load_with_cache(GetSettings().sfx.ui_button_hover);
  int click_audio_handle = AudioManager::Instance().load_with_cache(GetSettings().sfx.ui_button_click);

  retry_button_.position           = {0.0f, -4.0f};
  retry_button_.size               = Vector2{4.0f, 2.0f};
  retry_button_.text               = "Retry";
  retry_button_.hover_audio_handle = hover_audio_handle;
  retry_button_.click_audio_handle = click_audio_handle;

  menu_button_.position = {0.0f, -6.5f};
  menu_button_.size     = Vector2{4.0f, 2.0f};
  menu_button_.text     = "Menu";
  menu_button_.hover_audio_handle = hover_audio_handle;
  menu_button_.click_audio_handle = click_audio_handle;
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
