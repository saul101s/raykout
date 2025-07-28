#pragma once

#include <memory>
#include <vector>

#include "paddle.h"
#include "ball.h"
#include "brick.h"
#include "renderer.h"

namespace Raykout {
class Application {
 public:
  Application()                                = default;
  ~Application()                               = default;
  Application(const Application& o)            = default;
  Application& operator=(const Application& o) = default;

  void run();

 private:
  void initialize();
  void loop();
  void update(float dt);
  void solveCollisions(float dt);
  void solveCollisionBallPaddle(float dt);
  void solveCollisionsBallBricks(float dt);
  void updateViewport();
  void draw();
  void reload();

 private:
  std::unique_ptr<Paddle> paddle;
  std::shared_ptr<Ball> ball;
  std::vector<std::shared_ptr<Brick>> bricks;
  Renderer::Viewport viewport_;
  float aspect_;
};
}  // namespace Raykout
