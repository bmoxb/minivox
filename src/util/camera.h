#pragma once

#include <bx/math.h>

#include <array>

namespace util {

class Camera {
 public:
  Camera(bx::Vec3 position);

  void set_position(bx::Vec3 position);

  void move_forward(float speed);
  void move_backward(float speed);
  void strafe_left(float speed);
  void strafe_right(float speed);

  void rotate(float yaw_update, float pitch_update);

 private:
  void update_view();

  // position of the camera in world space
  bx::Vec3 position;

  // the direction in which the camera is facing
  bx::Vec3 direction = {0.0f, 0.0f, -1.0f};

  bx::Vec3 up = {0.0f, 1.0f, 0.0f};

  float yaw = -90.0f;
  float pitch = 0.0f;

  std::array<float, 16> view;
  std::array<float, 16> projection;
};

}  // namespace util
