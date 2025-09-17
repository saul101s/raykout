#include "button.h"

#include "renderer.h"
#include "raylib.h"

namespace Raykout {

void Button::draw() {
  RColor color;
  switch (state_) {
    case kButtonState_None: {
      color = style.idle_color;
    } break;
    case kButtonState_Hover: {
      color = style.hover_color;
    } break;
    case kButtonState_Down: {
      color = style.down_color;
    } break;
  }

  Renderer::DrawRectangle({position.x, position.y, size.x, size.y}, color);
  Renderer::DrawText({text.c_str(), position.x, position.y, 1.0f}, RColor::White());
}

void Button::update() {
  prev_state_ = state_;
  state_ &= 0;

  Vector2 mouse_position = Vector2{GetMousePosition().x, GetMousePosition().y};
  mouse_position         = Renderer::ScreenToWorld(mouse_position);

  bool inBounds = isInButtonBounds(mouse_position);

  if (inBounds) {
    state_ = kButtonState_Hover;
  }
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && inBounds) {
    state_ = kButtonState_Press;
  }
  if ((kButtonState_Press == prev_state_ || kButtonState_Down == prev_state_) &&
      inBounds && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
    state_ = kButtonState_Down;
  }

  if (kButtonState_Down == prev_state_ && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
    state_ = kButtonState_Click;
    if (click_audio_handle >= 0) {
      AudioManager::Instance().play(click_audio_handle);
    }
  } else if (kButtonState_Hover == state_ &&
             kButtonState_Hover != prev_state_ &&
             hover_audio_handle >= 0) {
    AudioManager::Instance().play(hover_audio_handle);
  }
}

bool Button::isInButtonBounds(Vector2 point) {
  Vector2 mouse_position = Vector2{GetMousePosition().x, GetMousePosition().y};
  mouse_position         = Renderer::ScreenToWorld(mouse_position);
  float half_width       = size.x / 2.0f;
  float half_height      = size.y / 2.0f;
  return (mouse_position.x > position.x - half_width &&
          mouse_position.x < position.x + half_width &&
          mouse_position.y > position.y - half_height &&
          mouse_position.y < position.y + half_height);
}
}  // namespace Raykout
