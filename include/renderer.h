#pragma once

#include "raylib.h"

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

void SetViewport(const Viewport& viewport);
void SetWorldSize(float width, float height);
void DrawRectangle(const PriRectangle& rect, const Color& color);
void DrawCircle(const PriCircle& circle, const Color& color);
}  // namespace Renderer
}  // namespace Raykout