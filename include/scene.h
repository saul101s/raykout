#pragma once

#include <string>
#include <vector>
#include <memory>

#include "paddle.h"
#include "ball.h"
#include "brick.h"

namespace Raykout {
class Scene {
 public:
  Scene()  = default;
  ~Scene() = default;

  void load(AABB bounds);
  void update(float dt);
  void draw();

 private:
  void solveCollisions(float dt);
  void solveCollisionBallPaddle(float dt);
  void solveCollisionsBallBricks(float dt);

 private:
  std::string file_name_;
  std::shared_ptr<Paddle> paddle_;
  std::shared_ptr<Ball> ball_;
  std::vector<Brick> bricks_;
};
}  // namespace Raykout
