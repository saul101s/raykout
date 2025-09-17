#include "settings.h"

#include "inicpp.h"

namespace Raykout {
static const char* SETTINGS_PATH = "assets/settings/settings.ini";
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
  s_settings.paddle.width        = GetSetting<float>("paddle", "width");
  s_settings.paddle.height       = GetSetting<float>("paddle", "height");
  s_settings.paddle.max_speed    = GetSetting<float>("paddle", "max_speed");
  s_settings.paddle.acceleration = GetSetting<float>("paddle", "acceleration");
  s_settings.paddle.damping      = GetSetting<float>("paddle", "damping");

  // Ball settings
  s_settings.ball.launch_speed = GetSetting<float>("ball", "launch_speed");
  s_settings.ball.max_speed    = GetSetting<float>("ball", "max_speed");
  s_settings.ball.radius       = GetSetting<float>("ball", "radius");

  // Screen settings
  s_settings.screen.width  = GetSetting<unsigned int>("screen", "width");
  s_settings.screen.height = GetSetting<unsigned int>("screen", "height");

  // World settings
  s_settings.world.width  = GetSetting<float>("world", "width");
  s_settings.world.height = GetSetting<float>("world", "height");

  // Audio settings
  s_settings.music.main_menu_bg  = GetSetting<const char*>("music", "main_menu_bg");
  s_settings.music.game_bg       = GetSetting<const char*>("music", "game_bg");
  s_settings.music.game_over_bg  = GetSetting<const char*>("music", "game_over_bg");
  s_settings.sfx.game_over       = GetSetting<const char*>("sfx", "game_over");
  s_settings.sfx.ball_hit_paddle = GetSetting<const char*>("sfx", "ball_hit_paddle");
  s_settings.sfx.ball_hit_brick  = GetSetting<const char*>("sfx", "ball_hit_brick");
  s_settings.sfx.ball_hit_wall   = GetSetting<const char*>("sfx", "ball_hit_wall");
  s_settings.sfx.ui_button_hover = GetSetting<const char*>("sfx", "ui_button_hover");
  s_settings.sfx.ui_button_click = GetSetting<const char*>("sfx", "ui_button_click");

  s_loaded = true;
}

const Settings& GetSettings() {
  if (!s_loaded) {
    LoadSettings();
  }

  return s_settings;
}

void ReloadSettings() {
  s_loaded = false;
  LoadSettings();
}
}  // namespace Raykout
