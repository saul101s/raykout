#pragma once

namespace Raykout {
struct RColor {
  unsigned char r, g, b, a;

  static RColor White() { return {255, 255, 255, 255}; }
  static RColor Gray() { return {50, 50, 50, 255}; }
  static RColor LightGray() { return {100, 100, 100, 255}; }
  static RColor DarkGray() { return {20, 20, 20, 255}; }
  static RColor Green() { return {0, 255, 0, 255}; }
  static RColor DarkGreen() { return {10, 200, 10, 255}; }
};
}  // namespace Raykout
