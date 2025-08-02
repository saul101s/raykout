#pragma once

#include "rcolor.h"
#include "vector2.h"

namespace Raykout {

namespace Renderer {

struct Viewport {
  unsigned int x, y, width, height;
};

struct PriRectangle {
  float x, y, width, height;
};

struct PriCircle {
  float x, y, radius;
};

struct PriText {
  const char* text;
  float x, y, font_size;
};

void SetViewport(const Viewport& viewport);
void SetWorldSize(float width, float height);
Vector2 GetWorldSize();


float WorldToScreen(float v);
Vector2 WorldToScreen(Raykout::Vector2 v);
float ScreenToWorld(float v);
Vector2 ScreenToWorld(Raykout::Vector2 v);

void DrawRectangle(const PriRectangle& rect, const RColor& color);
void DrawCircle(const PriCircle& circle, const RColor& color);
void DrawText(const PriText& text, const RColor& color);
}  // namespace Renderer
}  // namespace Raykout
