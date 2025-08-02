#pragma once

namespace Raykout {
struct PaddleSettings {
  float width;
  float height;
  float max_speed;
  float acceleration;
  float damping;
};

struct BallSettings {
  float launch_speed;
  float max_speed;
  float radius;
};

struct ScreenSettings {
  unsigned int width;
  unsigned int height;
};

struct WorldSettings {
  float height;
};

struct Settings {
  ScreenSettings screen;
  WorldSettings world;
  PaddleSettings paddle;
  BallSettings ball;

  Settings() {
    // Default values
    screen.width        = 1200;
    screen.height       = 800;
    world.height        = 22;
    paddle.width        = 2.0f;
    paddle.height       = 0.25f;
    paddle.max_speed    = 15.0f;
    paddle.acceleration = 80.0f;
    paddle.damping      = 0.005f;
    ball.launch_speed   = 8.0f;
    ball.max_speed      = 17.0f;
    ball.radius         = 0.2f;
  }
};

const Settings& GetSettings();
void ReloadSettings();
}  // namespace Raykout
