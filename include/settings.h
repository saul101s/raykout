#pragma once

#include "inicpp.h"

namespace Raykout {
static const char* SETTINGS_PATH = "assets/settings/settings.ini";

struct Settings {
  const char* paddle_sprite_path;
  float paddle_max_speed;
  float paddle_acceleration;
  float paddle_damping;
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
  s_ini_file.load(SETTINGS_PATH);
  s_settings.paddle_sprite_path  = GetSetting<const char*>("paddle_sprite", "path");
  s_settings.paddle_max_speed    = GetSetting<float>("paddle", "max_speed");
  s_settings.paddle_acceleration = GetSetting<float>("paddle", "acceleration");
  s_settings.paddle_damping      = GetSetting<float>("paddle", "damping");

  s_loaded = true;
}

const Settings& GetSettings() {
  if (!s_loaded) {
    LoadSettings();
  }

  return s_settings;
}
}  // namespace Raykout