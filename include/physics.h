#pragma once

#include "vector2.h"

namespace Raykout {
struct AABB {
  Vector2 min;
  Vector2 max;
};

bool TestAABBAABB(AABB a, AABB b);
bool TestMovingAABBAABB(AABB a, AABB b, Vector2 va, Vector2 vb, float& tfirst, float& tlast, Vector2& normal);
}  // namespace Raykout
