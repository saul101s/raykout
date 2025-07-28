#include "application.h"

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
  // Initialize the paddle
  Raykout::Paddle::Config paddle_config{settings.paddle.width, settings.paddle.height, settings.paddle.max_speed, settings.paddle.acceleration, settings.paddle.damping};
  paddle                     = std::make_unique<Paddle>(paddle_config, bounds);
  paddle->transform.position = Vector2{0.0f, -world_height / 2.0f + 1.0f};

  // Initialize the ball
  Raykout::Ball::Config ball_config{settings.ball.launch_speed, settings.ball.max_speed, settings.ball.radius};
  ball                     = std::make_shared<Ball>(ball_config, bounds);
  ball->transform.position = paddle->transform.position + Vector2{0.0f, settings.paddle.height / 2.0f + settings.ball.radius};
  paddle->attachBall(ball);

  // Initialize bricks
  bricks.reserve(100);
  Raykout::Brick::Config brick_config{1.5f, 0.5f};
  for (int y = -5; y < 5; y++)
    for (int x = -5; x < 5; x++) {
      bricks.push_back(std::make_shared<Brick>(brick_config));
      bricks.back()->transform.position = {(float)x * 2.0f, float(y)};
    }
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
  if (IsWindowResized()) {
    updateViewport();
  }

  solveCollisions(dt);
  ball->update(dt);
  paddle->update(dt);
}

void Application::solveCollisions(float dt) {
  solveCollisionBallPaddle(dt);
  solveCollisionsBallBricks(dt);
}

void Application::solveCollisionBallPaddle(float dt) {
  AABB a = paddle->aabb();
  AABB b = ball->aabb();
  float tfirst, tlast;
  Vector2 normal;

  bool test = Raykout::TestMovingAABBAABB(a, b, paddle->velocity(), ball->velocity(), tfirst, tlast, normal);
  if (test && tfirst < dt && normal.y * normal.y > 0.0f) {
    float t              = (ball->transform.position.x - a.min.x) / (a.max.x - a.min.x);
    Vector2 push_towards = Vector2{2.0f * t - 1.0f, 1.0f}.normalized();
    Vector2 inv_velocity = -ball->velocity().normalized();
    ball->onCollision(push_towards.halfWay(inv_velocity).normalized(), "paddle");
  }
}

void Application::solveCollisionsBallBricks(float dt) {
  float tfirst, tlast;
  Vector2 normal;

  for (auto brick : bricks) {
    if (!brick->enabled()) continue;
    bool test = Raykout::TestMovingAABBAABB(brick->aabb(), ball->aabb(), Vector2(), ball->velocity(), tfirst, tlast, normal);
    if (test && tfirst < dt) {
      ball->onCollision(normal, "brick");
      brick->damage(1);
      break;
    }
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

  ClearBackground(BLACK);

  // Viewport
  DrawRectangle(viewport_.x - viewport_.width / 2, viewport_.y - viewport_.height / 2, viewport_.width, viewport_.height, Color{20, 20, 20, 255});
  DrawFPS(viewport_.x + viewport_.width / 2 - 100, viewport_.y - viewport_.height / 2 + font_size_m / 2);

  int text_x = viewport_.x - MeasureText(welcome_text, font_size_m) / 2;
  int text_y = viewport_.y - viewport_.height / 2 + font_size_m / 2;
  DrawText(welcome_text, text_x, text_y, font_size_m, WHITE);

  Raykout::Renderer::DrawRectangle(paddle->primitive(), WHITE);
  Raykout::Renderer::DrawCircle(ball->primitive(), BEIGE);
  for (auto brick : bricks) {
    if (brick->enabled())
      Raykout::Renderer::DrawRectangle(brick->primitive(), DARKGREEN);
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
