#pragma once

#include <memory>

#include "paddle.h"

namespace Raykout {
class Application {
 public:
  Application()                                = default;
  ~Application()                               = default;
  Application(const Application& o)            = default;
  Application& operator=(const Application& o) = default;

  void run();

 private:
  void initialize();
  void loop();
  void update();
  void draw();

 private:
  std::unique_ptr<Paddle> paddle;
};
}  // namespace Raykout