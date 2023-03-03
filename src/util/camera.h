#pragma once

#include <bx/math.h>

#include <array>

namespace util {

class Camera {
 public:
  Camera(bx::Vec3 initial_position, float aspect_ratio);

  void set_position(bx::Vec3 new_position);

  void move_forward(float speed);
  void move_backward(float speed);
  void strafe_left(float speed);
  void strafe_right(float speed);

  void rotate(float yaw_update, float pitch_update);

  void update_aspect_ratio(float aspect_ratio);

 private:
  void update_projection(float aspect_ratio);
  void update_view();

  // position of the camera in world space
  bx::Vec3 position;

  // the direction in which the camera is facing
  bx::Vec3 direction = {0.0f, 0.0f, -1.0f};

  float yaw = -90.0f;
  float pitch = 0.0f;

  std::array<float, 16> projection;
  std::array<float, 16> view;
};

}  // namespace util
