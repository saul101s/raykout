#include "states.h"

#include "settings.h"

namespace Raykout {

FSMStateMainMenu::FSMStateMainMenu(const char* name) : FSMState(name) {
  bg_sample_ = AudioManager::Instance().load_with_cache(GetSettings().music.main_menu_bg);
}

void FSMStateMainMenu::onEnter() {
  bg_voice_ = AudioManager::Instance().play(bg_sample_);
}

void FSMStateMainMenu::update(float dt) {
  main_menu_.update(dt);
  if (main_menu_.isButtonPressed(MainMenu::kMainMenuButton_Play)) {
    event = kStateMainMenuEvent_Play;
  }
  if (main_menu_.isButtonPressed(MainMenu::kMainMenuButton_Quit)) {
    event = kStateMainMenuEvent_Quit;
  }
}

void FSMStateMainMenu::draw() {
  main_menu_.draw();
}

void FSMStateMainMenu::onExit() {
  AudioManager::Instance().stop(bg_voice_);
}

FSMStateGame::FSMStateGame(const char* name) : FSMState(name) {
  bg_sample_ = AudioManager::Instance().load_with_cache(GetSettings().music.game_bg);
}

void FSMStateGame::onEnter() {
  Vector2 world_size      = Raykout::Renderer::GetWorldSize();
  float half_world_width  = world_size.x / 2.0f;
  float half_world_height = world_size.y / 2.0f;
  AABB bounds             = {{-half_world_width, -half_world_height}, {half_world_width, half_world_height}};
  scene_.load(bounds);

  bg_voice_ = AudioManager::Instance().play(bg_sample_);
  AudioManager::Instance().setLoop(bg_voice_, true);
}

void FSMStateGame::update(float dt) {
  scene_.update(dt);
  if (scene_.ballsRemaining() == 0) {
    event = kStateGameEvent_GameOver;
  }
}

void FSMStateGame::draw() {
  scene_.draw();
}

void FSMStateGame::onExit() {
  scene_.unload();
  AudioManager::Instance().stop(bg_voice_);
}

FSMStateGameOver::FSMStateGameOver(const char* name) : FSMState(name) {
  sfx_sample_ = AudioManager::Instance().load_with_cache(GetSettings().sfx.game_over);
  bg_sample_  = AudioManager::Instance().load_with_cache(GetSettings().music.game_over_bg);
}

void FSMStateGameOver::onEnter() {
  AudioManager::Instance().play(sfx_sample_);
  bg_voice_ = AudioManager::Instance().play(bg_sample_);
}

void FSMStateGameOver::update(float dt) {
  game_over_.update(dt);
  if (game_over_.isButtonPressed(GameOver::kGameOverButton_Retry)) {
    event = kStateGameOverEvent_Retry;
  }
  if (game_over_.isButtonPressed(GameOver::kGameOverButton_Menu)) {
    event = kStateGameOverEvent_Menu;
  }
}

void FSMStateGameOver::draw() {
  game_over_.draw();
}

void FSMStateGameOver::onExit() {
  AudioManager::Instance().stop(bg_voice_);
}

void FSMStateQuit::onEnter() {}
void FSMStateQuit::update(float dt) {}
void FSMStateQuit::draw() {}
void FSMStateQuit::onExit() {}

}  // namespace Raykout
