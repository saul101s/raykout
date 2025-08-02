#include "renderer.h"

#include "raylib.h"

namespace Raykout {
namespace Renderer {

static Viewport s_viewport;
static float s_world_width  = 16.0f;
static float s_world_height = 9.0f;

void SetViewport(const Viewport& viewport) {
  s_viewport = viewport;
}

Vector2 GetWorldSize() {
  return {s_world_width, s_world_height};
}

void SetWorldSize(float width, float height) {
  s_world_width  = width;
  s_world_height = height;
}

// Distance
float WorldToScreen(float v) {
  //  viewport.width / world_width = viewport.height / world_height;
  return v * ((float)s_viewport.width / s_world_width);
}

// Point
Vector2 WorldToScreen(Vector2 v) {
  return {s_viewport.x + WorldToScreen(v.x),
          s_viewport.y - WorldToScreen(v.y)};
}

// Distance
float ScreenToWorld(float v) {
  return v * (s_world_width / (float)s_viewport.width);
}

// Point
Vector2 ScreenToWorld(Vector2 v) {
  return {ScreenToWorld(v.x - s_viewport.x),
          ScreenToWorld(s_viewport.y - v.y)};  // Inverted axis
}

void DrawRectangle(const PriRectangle& rect, const RColor& color) {
  Vector2 relative_pos = WorldToScreen(Vector2{rect.x, rect.y});
  Vector2 world_size   = {WorldToScreen(rect.width), WorldToScreen(rect.height)};
  float x              = relative_pos.x - world_size.x / 2.0f;
  float y              = relative_pos.y - world_size.y / 2.0f;  // Inverted axis
  DrawRectangle((int)x, (int)y, (int)world_size.x, (int)world_size.y, (const Color&)color);
}

void DrawCircle(const PriCircle& circle, const RColor& color) {
  Vector2 relative_pos = WorldToScreen(Vector2{circle.x, circle.y});
  float world_radius   = WorldToScreen(circle.radius);
  float x              = relative_pos.x;
  float y              = relative_pos.y;  // Inverted axis
  DrawCircle((int)x, (int)y, world_radius, (const Color&)color);
}

void DrawText(const PriText& text, const RColor& color) {
  Vector2 relative_pos = WorldToScreen(Vector2{text.x, text.y});
  int font_size        = (int)WorldToScreen((float)text.font_size);
  int width            = MeasureText(text.text, font_size);
  float x              = relative_pos.x - (float)width / 2.0f;
  float y              = relative_pos.y - (float)font_size / 2.0f;  // Inverted axis
  DrawText(text.text, (int)x, (int)y, font_size, (const Color&)color);
}

}  // namespace Renderer
}  // namespace Raykout
