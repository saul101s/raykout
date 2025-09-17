#include "main_menu.h"

#include "settings.h"
#include "renderer.h"
#include "button.h"
#include "vector2.h"

namespace Raykout {
MainMenu::MainMenu() {
  button_pressed_ = 0;

  int hover_audio_handle = AudioManager::Instance().load_with_cache(GetSettings().sfx.ui_button_hover);
  int click_audio_handle = AudioManager::Instance().load_with_cache(GetSettings().sfx.ui_button_click);

  play_button_.position           = {0.0f, -4.0f};
  play_button_.size               = Vector2{4.0f, 2.0f};
  play_button_.text               = "Start";
  play_button_.hover_audio_handle = hover_audio_handle;
  play_button_.click_audio_handle = click_audio_handle;

  quit_button_.position           = Vector2{0.0f, -6.5f};
  quit_button_.size               = Vector2{4.0f, 2.0f};
  quit_button_.text               = "Quit";
  quit_button_.hover_audio_handle = hover_audio_handle;
  quit_button_.click_audio_handle = click_audio_handle;
}

void MainMenu::update(float dt) {
  // Clean the state
  button_pressed_ = 0;

  play_button_.update();
  quit_button_.update();

  if (play_button_.state() == Button::kButtonState_Click) {
    button_pressed_ |= kMainMenuButton_Play;
  }

  if (quit_button_.state() == Button::kButtonState_Click) {
    button_pressed_ |= kMainMenuButton_Quit;
  }
}

void MainMenu::draw() {
  Renderer::DrawText({"Raykout", 0.0f, 5.0f, 2.0f}, RColor::White());

  play_button_.draw();
  quit_button_.draw();
}

}  // namespace Raykout
