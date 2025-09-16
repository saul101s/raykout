#include "application.h"

#include "raylib.h"
#include "renderer.h"
#include "settings.h"
#include "fsm.h"
#include "states.h"

const char* ICON_PATH = "assets/icon.png";

namespace Raykout {

void Application::run() {
  initialize();
  loop();
}

void Application::initialize() {
  unsigned int mm = fsm_.addState(std::make_shared<FSMStateMainMenu>("Main Menu"));
  unsigned int g  = fsm_.addState(std::make_shared<FSMStateGame>("Game"));
  unsigned int go = fsm_.addState(std::make_shared<FSMStateGameOver>("Game Over"));
  quit_state_id_  = fsm_.addState(std::make_shared<FSMStateQuit>("Quit"));
  fsm_.addTransition(mm, g, FSMStateMainMenu::kStateMainMenuEvent_Play);
  fsm_.addTransition(mm, quit_state_id_, FSMStateMainMenu::kStateMainMenuEvent_Quit);
  fsm_.addTransition(g, go, FSMStateGame::kStateGameEvent_GameOver);
  fsm_.addTransition(go, g, FSMStateGameOver::kStateGameOverEvent_Retry);
  fsm_.addTransition(go, mm, FSMStateGameOver::kStateGameOverEvent_Menu);

  const Raykout::Settings& settings = Raykout::GetSettings();

  float world_width  = settings.world.width;
  float world_height = settings.world.height;
  aspect_            = world_width / world_height;
  Raykout::Renderer::SetWorldSize(world_width, world_height);

  // Set vsync and work with high DPI displays.
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_RESIZABLE);

  // Create the window and the OpenGL context.
  InitWindow(settings.screen.width, settings.screen.height, "Raykout");

  Image icon = LoadImage(ICON_PATH);
  if (icon.data)
    SetWindowIcon(icon);

  updateViewport();
}

void Application::loop() {
  while (!WindowShouldClose() && fsm_.currentState() != quit_state_id_) {
    update(GetFrameTime());
    draw();
  }
}

void Application::update(float dt) {
  if (IsWindowResized()) {
    updateViewport();
  }

  fsm_.update(GetFrameTime());
}

void Application::updateViewport() {
  unsigned int screen_width  = (unsigned int)((float)GetRenderWidth() / GetWindowScaleDPI().x);
  unsigned int screen_height = (unsigned int)((float)GetRenderHeight() / GetWindowScaleDPI().y);
  float current_aspect       = (float)screen_width / (float)screen_height;

  if (current_aspect >= aspect_) {  // Wider than original
    viewport_.height = screen_height;
    viewport_.width  = (int)((float)viewport_.height * aspect_);
  } else {  // Higher than original
    viewport_.width  = screen_width;
    viewport_.height = (int)((float)screen_width / aspect_);
  }

  viewport_.x = screen_width / 2;
  viewport_.y = screen_height / 2;
  Raykout::Renderer::SetViewport({viewport_.x, viewport_.y, viewport_.width, viewport_.height});
}

void Application::draw() {
  const Raykout::Settings& settings = Raykout::GetSettings();

  // Setup frame buffer
  BeginDrawing();

  ClearBackground({0, 0, 0, 255});

  // Viewport
  DrawRectangle(viewport_.x - viewport_.width / 2, viewport_.y - viewport_.height / 2, viewport_.width, viewport_.height, {20, 20, 20, 255});
  DrawFPS(viewport_.x + viewport_.width / 2 - 100, viewport_.y - viewport_.height / 2 + 10);

  fsm_.draw();

  // Swap buffers
  EndDrawing();
}
}  // namespace Raykout
