#pragma once

#include <string>

#include "rcolor.h"
#include "vector2.h"

namespace Raykout {
class Button {
 public:
  enum ButtonState {
    kButtonState_None = 0,
    kButtonState_Hover,
    kButtonState_Press,
    kButtonState_Down,
    kButtonState_Click,
  };

  struct Style {
    RColor idle_color = RColor::Gray();
    RColor hover_color = RColor::LightGray();
    RColor down_color = RColor::DarkGreen();
  } style;

  Vector2 position;
  Vector2 size;
  std::string text;

 public:
  Button()  = default;
  ~Button() = default;

  int state() const { return state_; }
  void update();
  void draw();

 private:
  bool isInButtonBounds(Vector2 point);

 private:
  int state_;
};
}  // namespace Raykout
