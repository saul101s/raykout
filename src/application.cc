#include "application.h"

#include "raylib.h"

#include "paddle.h"
#include "settings.h"

constexpr int WINDOW_WIDTH  = 1200;
constexpr int WINDOW_HEIGHT = 800;

namespace Raykout {

void Application::run() {
  initialize();
  loop();
}

void Application::initialize() {
  // Set vsync and work with high DPI displays.
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

  // Create the window and the OpenGL context.
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Raykout");

  // Initialize the paddle
  const Raykout::Settings& settings = Raykout::GetSettings();
  Raykout::Paddle::Config paddle_config{settings.paddle_max_speed, settings.paddle_acceleration, settings.paddle_damping};
  paddle                     = std::make_unique<Paddle>(paddle_config);
  paddle->transform.position = Vector2{600.0f, 700.0f};
  paddle->transform.scale    = Vector2{2.0f, 0.5f};
}

void Application::loop() {
  while (!WindowShouldClose()) {
    update();
    draw();
  }
}

void Application::update() {
  paddle->update(GetFrameTime());
}

void Application::draw() {
  static char welcome_text[]        = "Welcome to Raykout";
  static int welcome_text_font_size = 20;

  // Setup frame buffer
  BeginDrawing();

  ClearBackground(BLACK);

  DrawFPS(WINDOW_WIDTH - 100, 20);

  int welcome_text_width = MeasureText(welcome_text, welcome_text_font_size);
  DrawText(welcome_text, WINDOW_WIDTH / 2 - welcome_text_width / 2, WINDOW_HEIGHT / 2, welcome_text_font_size, WHITE);

  paddle->draw();

  // Swap buffers
  EndDrawing();
}
}  // namespace Raykout