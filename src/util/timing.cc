#include "util/timing.h"

#include <GLFW/glfw3.h>

namespace util {

float Timing::tick() {
  float current_time = static_cast<float>(glfwGetTime());
  float delta = current_time - last_time;
  last_time = current_time;
  return delta;
}

}  // namespace util
