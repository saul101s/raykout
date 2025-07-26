#pragma once

#include "inicpp.h"

namespace Raykout {
static const char* SETTINGS_PATH = "assets/settings/settings.ini";

struct PaddleSettings {
  float max_speed;
  float acceleration;
  float damping;
};

struct BallSettings {
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
    paddle.max_speed    = 500.0f;
    paddle.acceleration = 3000.0f;
    paddle.damping      = 0.01f;
    ball.max_speed      = 700.0f;
    ball.radius         = 8.0f;
  }
};

static Settings s_settings;
static bool s_loaded;

static ini::IniFile s_ini_file;

template <typename T>
static T GetSetting(const char* section, const char* key) {
  // TODO(saul): handle when the key is not present.
  return s_ini_file[section][key].as<T>();
}

static void LoadSettings() {
  if (s_loaded) return;

  s_ini_file.load(SETTINGS_PATH);

  // Paddle settings
  s_settings.paddle.max_speed    = GetSetting<float>("paddle", "max_speed");
  s_settings.paddle.acceleration = GetSetting<float>("paddle", "acceleration");
  s_settings.paddle.damping      = GetSetting<float>("paddle", "damping");

  // Ball settings
  s_settings.ball.max_speed = GetSetting<float>("ball", "max_speed");
  s_settings.ball.radius    = GetSetting<float>("ball", "radius");

  // Screen settings
  s_settings.screen.width  = GetSetting<unsigned int>("screen", "width");
  s_settings.screen.height = GetSetting<unsigned int>("screen", "height");

  // World settings
  s_settings.world.height = GetSetting<float>("world", "height");

  s_loaded = true;
}

static void ReloadSettings() {
  s_loaded = false;
  LoadSettings();
}

const Settings& GetSettings() {
  if (!s_loaded) {
    LoadSettings();
  }

  return s_settings;
}
}  // namespace Raykout