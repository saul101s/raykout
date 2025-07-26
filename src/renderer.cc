#include "renderer.h"

#include <stdio.h>

namespace Raykout {
namespace Renderer {

static Viewport s_viewport;
static float s_world_width  = 16.0f;
static float s_world_height = 9.0f;

void SetViewport(const Viewport& viewport) {
  s_viewport = viewport;
}

void SetWorldSize(float width, float height) {
  s_world_width  = width;
  s_world_height = height;
}

static Vector2 WorldToScreen(const Vector2& v) {
  return {v.x * ((float)s_viewport.width / s_world_width),
          v.y * ((float)s_viewport.height / s_world_height)};
}

void DrawRectangle(const PriRectangle& rect, const Color& color) {
  Vector2 relative_pos = WorldToScreen(Vector2{rect.x, rect.y});
  Vector2 world_size   = WorldToScreen(Vector2{rect.width, rect.height});
  float x              = s_viewport.x + relative_pos.x - world_size.x / 2.0f;
  float y              = s_viewport.y - relative_pos.y - world_size.y / 2.0f;
  DrawRectangle((int)x, (int)y, (int)world_size.x, (int)world_size.y, color);
}

void DrawCircle(const PriCircle& circle, const Color& color) {
  Vector2 relative_pos = WorldToScreen(Vector2{circle.x, circle.y});
  Vector2 world_size   = WorldToScreen(Vector2{circle.radius, circle.radius});
  float x              = s_viewport.x + relative_pos.x;
  float y              = s_viewport.y - relative_pos.y;
  DrawCircle((int)x, (int)y, world_size.x, color);
}

}  // namespace Renderer
}  // namespace Raykout