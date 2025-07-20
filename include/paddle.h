#pragma once

namespace Raykout {
class Paddle {
 public:
  struct Config {
    float max_speed;
    float acceleration;
    float damping;
  };

 public:
  Paddle(const Config& config);
  Paddle()                           = delete;
  ~Paddle()                          = default;
  Paddle(const Paddle& o)            = default;
  Paddle& operator=(const Paddle& o) = default;

  void setPosition(float x, float y);
  void update(float dt);
  void draw();

 private:
  void handleInput(float dt);
  void updatePosition(float dt);

 private:
  float speed_;
  float max_speed_;
  float acceleration_;
  float damping_;
  float x_, y_;
};
}  // namespace Raykout