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
  float width;
  float height;
};

struct MusicSettings {
  const char* main_menu_bg;
  const char* game_bg;
  const char* game_over_bg;
};

struct SFXSettings {
  const char* game_over;
  const char* ball_hit_paddle;
  const char* ball_hit_brick;
  const char* ball_hit_wall;
  const char* ui_button_hover;
  const char* ui_button_click;
};

struct Settings {
  ScreenSettings screen;
  WorldSettings world;
  PaddleSettings paddle;
  BallSettings ball;
  MusicSettings music;
  SFXSettings sfx;

  Settings() {
    // Default values
    screen.width        = 1200;
    screen.height       = 800;
    world.width         = 20;
    world.height        = 20;
    paddle.width        = 2.0f;
    paddle.height       = 0.25f;
    paddle.max_speed    = 15.0f;
    paddle.acceleration = 80.0f;
    paddle.damping      = 0.005f;
    ball.launch_speed   = 8.0f;
    ball.max_speed      = 17.0f;
    ball.radius         = 0.2f;
    music.main_menu_bg  = "assets/audio/music/main_menu_bg.mp3";
    music.game_bg       = "assets/audio/music/game_bg.mp3";
    music.game_over_bg  = "assets/audio/music/game_over_bg.mp3";
    sfx.game_over       = "assets/audio/sfx/game_over.mp3";
    sfx.ball_hit_paddle = "assets/audio/sfx/ball_hit_paddle.mp3";
    sfx.ball_hit_brick  = "assets/audio/sfx/ball_hit_brick.mp3";
    sfx.ball_hit_wall   = "assets/audio/sfx/ball_hit_wall.mp3";
    sfx.ui_button_hover = "assets/audio/sfx/ui_button_hover.mp3";
    sfx.ui_button_click = "assets/audio/sfx/ui_button_click.mp3";
  }
};

const Settings& GetSettings();
void ReloadSettings();
}  // namespace Raykout
