#include "fsm.h"

#include "audio_manager.h"
#include "main_menu.h"
#include "scene.h"
#include "game_over.h"

namespace Raykout {

class FSMStateMainMenu : public FSMState {
 public:
  enum StateMainMenuEvent {
    kStateMainMenuEvent_Play = 0,
    kStateMainMenuEvent_Quit
  };

  FSMStateMainMenu(const char* name);
  void onEnter() override;
  void update(float dt) override;
  void draw() override;
  void onExit() override;

 private:
  MainMenu main_menu_;
  SampleHandle bg_sample_;
  VoiceHandle bg_voice_;
};

class FSMStateGame : public FSMState {
 public:
  enum StateGameEvent {
    kStateGameEvent_GameOver = 0,
  };

  FSMStateGame(const char* name);

  void onEnter() override;
  void update(float dt) override;
  void draw() override;
  void onExit() override;

 private:
  Scene scene_;
  SampleHandle bg_sample_;
  VoiceHandle bg_voice_;
};

class FSMStateQuit : public FSMState {
 public:
  FSMStateQuit(const char* name) : FSMState(name) {}

  void onEnter() override;
  void update(float dt) override;
  void draw() override;
  void onExit() override;
};

class FSMStateGameOver : public FSMState {
 public:
  enum StateGameOverEvent {
    kStateGameOverEvent_Retry = 0,
    kStateGameOverEvent_Menu,
  };

  FSMStateGameOver(const char* name);

  void onEnter() override;
  void update(float dt) override;
  void draw() override;
  void onExit() override;

 private:
  GameOver game_over_;
  SampleHandle sfx_sample_;
  SampleHandle bg_sample_;
  VoiceHandle bg_voice_;
};
}  // namespace Raykout
