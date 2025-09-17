#include "physics.h"

#include <algorithm>

namespace Raykout {
bool TestAABBAABB(AABB a, AABB b) {
  return a.max.x >= b.min.x && a.min.x <= b.max.x && a.max.y >= b.min.y && a.min.y <= b.max.y;
}

// Real-time Collision Detection (https://realtimecollisiondetection.net/)
bool TestMovingAABBAABB(AABB a, AABB b, Vector2 va, Vector2 vb, float& tfirst, float& tlast, Vector2& a_normal) {
  Vector2 v = vb - va;  // relative velocity from b to a.
  Vector2 axis[]{{1.0f, 0.0f},
                 {0.0f, 1.0f}};

  Vector2 normal;

  if (TestAABBAABB(a, b)) {  // a and b initially overlapping.
    tfirst = tlast     = 0;
    float time_to_exit = -1.0;

    for (int i = 0; i < 2; i++) {
      float axis_time_to_exit = 0;

      if (v.d[i] < 0.0f)
        axis_time_to_exit = (a.min.d[i] - b.max.d[i]) / v.d[i];
      else if (v.d[i] > 0.0f)
        axis_time_to_exit = (a.max.d[i] - b.min.d[i]) / v.d[i];

      if (axis_time_to_exit > time_to_exit) {
        time_to_exit = axis_time_to_exit;
        normal       = axis[i] * (v.d[i] > 0.0f ? -1.0f : 1.0f);
      }
    }

    a_normal = normal;
    return true;
  }

  if (v.isZeroLength()) return false;

  tfirst = 0.0f;  // Time of first contact (start intersecting).
  tlast  = 1.0f;  // Time of last contact (stop intersecting).

  float max_tfirst = 0.0f;

  for (int i = 0; i < 2; i++) {
    if (v.d[i] < 0.0f) {
      if (b.max.d[i] < a.min.d[i])
        return false;  // Moving apart.
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
      max_tfirst = tfirst;
      normal     = axis[i] * (v.d[i] > 0.0f ? -1.0f : 1.0f);
    }

    if (tfirst > tlast) return false;
  }

  a_normal = normal;
  return true;
}
}  // namespace Raykout
