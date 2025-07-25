#include "application.h"

#include "raylib.h"
#include "physics.h"
#include "settings.h"

constexpr int WINDOW_WIDTH  = 1200;
constexpr int WINDOW_HEIGHT = 800;

namespace Raykout {

void Application::run() {
  initialize();
  loop();
}

void Application::initialize() {
  const Raykout::Settings& settings = Raykout::GetSettings();

  // Set vsync and work with high DPI displays.
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

  // Create the window and the OpenGL context.
  InitWindow(settings.screen.width, settings.screen.height, "Raykout");

  // Initialize the paddle
  Raykout::Paddle::Config paddle_config{settings.paddle.max_speed, settings.paddle.acceleration, settings.paddle.damping};
  paddle                     = std::make_unique<Paddle>(paddle_config);
  paddle->transform.position = Vector2{600.0f, 700.0f};

  // Initialize the ball
  Raykout::Ball::Config ball_config{settings.ball.max_speed, settings.ball.radius};
  ball                     = std::make_unique<Ball>(ball_config);
  ball->transform.position = Vector2{600.0f, 600.0f};
}

void Application::loop() {
  while (!WindowShouldClose()) {
    update(GetFrameTime());
    draw();

    if (IsKeyDown(KEY_ENTER)) {
      reload();
    }
  }
}

void Application::update(float dt) {
  solveCollisions(dt);

  ball->update(dt);
  paddle->update(dt);
}

void Application::solveCollisions(float dt) {
  AABB a = paddle->aabb();
  AABB b = ball->aabb();
  float tfirst, tlast;
  Vector2 normal;

  bool test = Raykout::TestMovingAABBAABB(a, b, paddle->velocity(), ball->velocity(), tfirst, tlast, normal);
  if (test && tfirst < dt && normal.y * normal.y > 0.0f) {
    ball->transform.position += ball->velocity() * tfirst * 2; // Move the ball passed the collision to pay for extra dt on update. 
    float t              = (ball->transform.position.x - a.min.x) / (a.max.x - a.min.x);
    Vector2 push_towards = Vector2{2.0f * t - 1.0f, -1.0f}.normalized();
    Vector2 inv_velocity = -ball->velocity().normalized();
    ball->onCollision(push_towards.halfWay(inv_velocity).normalized());
  }
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
  ball->draw();

  // Swap buffers
  EndDrawing();
}

void Application::reload() {
  CloseWindow();
  Raykout::ReloadSettings();
  initialize();
}
}  // namespace Raykout