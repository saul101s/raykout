#include "physics.h"

#include <stdio.h>
#include <algorithm>

namespace Raykout {
bool TestAABBAABB(AABB a, AABB b) {
  return a.max.x >= b.min.x && a.min.x <= b.max.x && a.max.y >= b.min.y && a.min.y <= b.max.y;
}

// Real-time Collision Detection (https://realtimecollisiondetection.net/)
bool TestMovingAABBAABB(AABB a, AABB b, Vector2 va, Vector2 vb, float& tfirst, float& tlast, Vector2& a_normal) {
  if (TestAABBAABB(a, b)) {  // a and b initially overlapping.
    tfirst = tlast = 0;
    // TODO(saul): What's the value of the normal vector?
    return true;
  }

  Vector2 v = vb - va;  // relative velocity from b to a.
  if (v.isZeroLength()) return false;

  tfirst = 0.0f;  // Time of first contact (start intersecting).
  tlast  = 1.0f;  // Time of last contact (stop intersecting).

  Vector2 normal;
  float max_tfirst = 0.0f;

  Vector2 axis[]{{1.0f, 0.0f},
                 {0.0f, 1.0f}};

  for (int i = 0; i < 2; i++) {
    if (v.d[i] < 0.0f) {
      if (b.max.d[i] < a.min.d[i])
        return 0;  // Moving apart.
      if (a.max.d[i] < b.min.d[i])
        // Dividing by v.d[i] < 0 inverts the substraction sign.
        tfirst = std::max((a.max.d[i] - b.min.d[i]) / v.d[i], tfirst);
      if (b.max.d[i] > a.min.d[i])
        tlast = std::min((a.min.d[i] - b.max.d[i]) / v.d[i], tlast);
    }

    if (v.d[i] > 0.0f) {
      if (b.min.d[i] > a.max.d[i])
        return 0;  // Moving apart.
      if (a.min.d[i] > b.max.d[i])
        tfirst = std::max((a.min.d[i] - b.max.d[i]) / v.d[i], tfirst);
      if (b.min.d[i] < a.max.d[i])
        tlast = std::min((a.max.d[i] - b.min.d[i]) / v.d[i], tlast);
    }

    if (v.d[i] == 0) {
      if (b.min.d[i] > a.max.d[i] || b.max.d[i] < a.min.d[i]) {
        return false;
      }
    }

    if (tfirst > max_tfirst) {
      max_tfirst  = tfirst;
      normal = axis[i] * (v.d[i] > 0.0f ? -1.0f : 1.0f);
    }

    if (tfirst > tlast) return false;
  }

  a_normal = normal;
  return true;
}
}  // namespace Raykout