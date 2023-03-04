#pragma once

namespace util {

class Debug {
 public:
  void toggle_wireframe();
  void toggle_stats();

 private:
  void update() const;

  bool wireframe = false, stats = false;
};

}  // namespace util
