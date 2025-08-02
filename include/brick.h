#pragma once

#include "transform2d.h"
#include "physics.h"
#include "renderer.h"

namespace Raykout {
class Brick {
 public:
  struct Config {
    float width;
    float height;
  };

  Transform2d transform;

 public:
  Brick(const Config& config);
  Brick()                          = delete;
  ~Brick()                         = default;
  Brick(const Brick& o)            = default;
  Brick& operator=(const Brick& o) = default;

  void damage(unsigned int hp);

  float scaledWidth() const { return config_.width * transform.scale.x; }
  float scaledHeight() const { return config_.height * transform.scale.y; }

  Renderer::PriRectangle primitive() const {
    return {transform.position.x, transform.position.y, scaledWidth(), scaledHeight()};
  }

  AABB aabb() const {
    float half_width  = scaledWidth() / 2.0f;
    float half_height = scaledHeight() / 2.0f;

    return AABB{
        Vector2{transform.position.x - half_width, transform.position.y - half_height},
        Vector2{transform.position.x + half_width, transform.position.y + half_height}};
  }

  bool enabled() const { return hp_ > 0; }

 private:
  Config config_;
  int hp_;
};
}  // namespace Raykout
