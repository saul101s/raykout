#include "scene.h"

#include "settings.h"

namespace Raykout {

void Scene::load(AABB bounds) {
  // TODO(saul): Load objects from file
  unload();

  const Raykout::Settings& settings = Raykout::GetSettings();

  // Initialize the paddle
  Raykout::Paddle::Config paddle_config{settings.paddle.width, settings.paddle.height, settings.paddle.max_speed, settings.paddle.acceleration, settings.paddle.damping};
  paddle_                     = std::make_shared<Paddle>(paddle_config, bounds);
  paddle_->transform.position = Vector2{0.0f, bounds.min.y + 1.0f};

  // Initialize the ball
  Raykout::Ball::Config ball_config{settings.ball.launch_speed, settings.ball.max_speed, settings.ball.radius};
  ball_                     = std::make_shared<Ball>(ball_config, bounds);
  ball_->transform.position = paddle_->transform.position + Vector2{0.0f, settings.paddle.height / 2.0f + settings.ball.radius};
  paddle_->attachBall(ball_);

  // Initialize bricks
  bricks_.reserve(100);
  Raykout::Brick::Config brick_config{2.0f, 0.75f};
  float xoffset = brick_config.width - 0.05f;
  float yoffset = brick_config.height - 0.05f;
  for (int y = 0; y <= 5; y++)
    for (int x = -5; x <= 5; x++) {
      bricks_.push_back(brick_config);
      bricks_.back().transform.position = {(float)x * xoffset, float(y) * yoffset};
    }
}

void Scene::unload() {
  paddle_.reset();
  ball_.reset();
  bricks_.clear();
}

void Scene::update(float dt) {
  solveCollisions(dt);
  ball_->update(dt);
  if (!ball_->enabled()) {
    ball_.reset();
  }
  paddle_->update(dt);
}

void Scene::solveCollisions(float dt) {
  solveCollisionBallPaddle(dt);
  solveCollisionsBallBricks(dt);
}

void Scene::solveCollisionBallPaddle(float dt) {
  AABB a = paddle_->aabb();
  AABB b = ball_->aabb();
  float tfirst, tlast;
  Vector2 normal;

  bool test = Raykout::TestMovingAABBAABB(a, b, paddle_->velocity(), ball_->velocity(), tfirst, tlast, normal);
  if (test && tfirst < dt && normal.y * normal.y > 0.0f) {
    float t              = (ball_->transform.position.x - a.min.x) / (a.max.x - a.min.x);
    Vector2 push_towards = Vector2{2.0f * t - 1.0f, 1.0f}.normalized();
    Vector2 inv_velocity = -ball_->velocity().normalized();
    ball_->onCollision(push_towards.halfWay(inv_velocity).normalized(), "paddle");
  }
}

void Scene::solveCollisionsBallBricks(float dt) {
  float tfirst, tlast;
  Vector2 normal;

  for (auto& brick : bricks_) {
    if (!brick.enabled()) continue;
    bool test = Raykout::TestMovingAABBAABB(brick.aabb(), ball_->aabb(), Vector2(), ball_->velocity(), tfirst, tlast, normal);
    if (test && tfirst < dt) {
      ball_->onCollision(normal, "brick");
      brick.damage(1);
      AABB aabb   = ball_->aabb();
      Vector2 vel = ball_->velocity();
      break;
    }
  }
}

void Scene::draw() {
  Raykout::Renderer::DrawRectangle(paddle_->primitive(), RColor::White());

  if (ballsRemaining() > 0)
    Raykout::Renderer::DrawCircle(ball_->primitive(), {150, 50, 50, 255});

  for (const auto& brick : bricks_) {
    if (brick.enabled())
      Raykout::Renderer::DrawRectangle(brick.primitive(), RColor::DarkGreen());
  }
}
}  // namespace Raykout
