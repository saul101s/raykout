#include "raylib.h"

#include <iostream>

#include "paddle.h"
#include "settings.h"

constexpr int WINDOW_WIDTH  = 1200;
constexpr int WINDOW_HEIGHT = 800;

int main(int argc, char** argv) {
  // Set vsync and work with high DPI displays.
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

  // Create the window and the OpenGL context.
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Raykout");

  char welcome_text[]        = "Welcome to Raykout";
  int welcome_text_font_size = 20;

  Raykout::LoadSettings();
  const Raykout::Settings& settings = Raykout::GetSettings();

  Raykout::Paddle::Config paddle_config{settings.paddle_max_speed, settings.paddle_acceleration, settings.paddle_damping};
  Raykout::Paddle paddle(paddle_config);
  paddle.setPosition(600, 700);

  while (!WindowShouldClose()) {
    paddle.update(GetFrameTime());

    // Setup frame buffer
    BeginDrawing();

    ClearBackground(BLACK);

    DrawFPS(WINDOW_WIDTH - 100, 20);

    int welcome_text_width = MeasureText(welcome_text, welcome_text_font_size);
    DrawText(welcome_text, WINDOW_WIDTH / 2 - welcome_text_width / 2, WINDOW_HEIGHT / 2, welcome_text_font_size, WHITE);

    paddle.draw();

    // Swap buffers
    EndDrawing();
  }
}
