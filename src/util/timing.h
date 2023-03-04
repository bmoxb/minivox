#pragma once

namespace util {

class Timing {
 public:
  float tick();

 private:
  float last_time = 0.0f;
};

}  // namespace util
