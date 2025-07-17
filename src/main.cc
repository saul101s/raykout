#include "raylib.h"

constexpr int WINDOW_WIDTH  = 1200;
constexpr int WINDOW_HEIGHT = 800;

int main(int argc, char** argv) {
  // Set vsync and work with high DPI displays.
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

  // Create the window and the OpenGL context.
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Raykout");

  char welcome_text[]        = "Welcome to Raykout";
  int welcome_text_font_size = 20;

  while (!WindowShouldClose()) {
    // Setup frame buffer
    BeginDrawing();

    ClearBackground(BLACK);

    DrawFPS(WINDOW_WIDTH - 100, 20);

    int welcome_text_width = MeasureText(welcome_text, welcome_text_font_size);
    DrawText(welcome_text, WINDOW_WIDTH / 2 - welcome_text_width / 2, WINDOW_HEIGHT / 2, welcome_text_font_size, WHITE);

    // Swap buffers
    EndDrawing();
  }
}
