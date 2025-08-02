#include "application.h"

#include "main_menu.h"
#include "raylib.h"
#include "physics.h"
#include "settings.h"

const char* ICON_PATH = "assets/icon.png";

namespace Raykout {

void Application::run() {
  initialize();
  loop();
}

void Application::initialize() {
  const Raykout::Settings& settings = Raykout::GetSettings();

  aspect_            = (float)settings.screen.width / (float)settings.screen.height;
  float world_height = settings.world.height;
  float world_width  = world_height * aspect_;
  Raykout::Renderer::SetWorldSize(world_width, world_height);

  // Set vsync and work with high DPI displays.
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_RESIZABLE);

  // Create the window and the OpenGL context.
  InitWindow(settings.screen.width, settings.screen.height, "Raykout");

  Image icon = LoadImage(ICON_PATH);
  if (icon.data)
    SetWindowIcon(icon);

  updateViewport();

  float half_world_width  = world_width / 2.0f;
  float half_world_height = world_height / 2.0f;
  AABB bounds{{-half_world_width, -half_world_height}, {half_world_width, half_world_height}};

  scene_.load(bounds);
  state_ = kState_MainMenu;
}

void Application::loop() {
  while (!WindowShouldClose() && kState_Quit != state_) {
    update(GetFrameTime());
    draw();

    if (IsKeyDown(KEY_ENTER)) {
      reload();
    }
  }
}

void Application::update(float dt) {
  if (IsWindowResized()) {
    updateViewport();
  }

  switch (state_) {
    case kState_MainMenu: {
      main_menu_.update(dt);
      if (main_menu_.isButtonPressed(MainMenu::kMainMenuButton_Play)) {
        state_ = kState_Game;
      }
      if (main_menu_.isButtonPressed(MainMenu::kMainMenuButton_Quit)) {
        state_ = kState_Quit;
      }
    } break;
    case kState_Game: {
      scene_.update(dt);
    } break;
    case kState_GameOver: {
    } break;
    case kState_Quit: {} break;
  }
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

  static char welcome_text[] = "Welcome to Raykout";
  static int font_size_m     = 20;

  // Setup frame buffer
  BeginDrawing();

  ClearBackground({0, 0, 0, 255});

  // Viewport
  DrawRectangle(viewport_.x - viewport_.width / 2, viewport_.y - viewport_.height / 2, viewport_.width, viewport_.height, {20, 20, 20, 255});
  DrawFPS(viewport_.x + viewport_.width / 2 - 100, viewport_.y - viewport_.height / 2 + font_size_m / 2);

  int text_x = viewport_.x - MeasureText(welcome_text, font_size_m) / 2;
  int text_y = viewport_.y - viewport_.height / 2 + font_size_m / 2;
  DrawText(welcome_text, text_x, text_y, font_size_m, {255, 255, 255, 255});

  switch (state_) {
    case kState_MainMenu: {
      main_menu_.draw();
    } break;
    case kState_Game: {
      scene_.draw();
    } break;
    case kState_GameOver: {
    } break;
  }

  // Swap buffers
  EndDrawing();
}

void Application::reload() {
  CloseWindow();
  Raykout::ReloadSettings();
  initialize();
}
}  // namespace Raykout
