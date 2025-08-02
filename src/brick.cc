#include "brick.h"

namespace Raykout {

Brick::Brick(const Config& config)
    : config_(config), hp_(1) {}

void Brick::damage(unsigned int hp) {
  hp_ -= hp;
  if (hp_ < 0) hp_ = 0;
}
}  // namespace Raykout
