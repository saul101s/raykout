#pragma once

#include <memory>

#include "paddle.h"
#include "ball.h"

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
  void draw();
  void reload();

 private:
  std::unique_ptr<Paddle> paddle;
  std::unique_ptr<Ball> ball;
};
}  // namespace Raykout