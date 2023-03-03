#include "util/camera.h"

#include <bgfx/bgfx.h>

namespace util {

Camera::Camera(bx::Vec3 position) : position(position) {
  bx::mtxProj(
      projection.data(),
      90.0f,
      800.0f / 600.0f,
      0.1f,
      100.0f,
      bgfx::getCaps()->homogeneousDepth);

  update_view();
}

void Camera::set_position(bx::Vec3 position) {
  this->position = position;
  update_view();
}

void Camera::move_forward(float speed) {
  position = bx::sub(position, bx::Vec3{0.0f, 0.0f, speed});
  update_view();
}

void Camera::move_backward(float speed) {
  position = bx::add(position, bx::Vec3{0.0f, 0.0f, speed});
  update_view();
}

void Camera::strafe_left(float speed) {
  auto translation = bx::normalize(bx::cross(direction, bx::Vec3{0.0f, 1.0f, 0.0f}));
  position = bx::add(position, bx::mul(translation, speed));
  update_view();
}

void Camera::strafe_right(float speed) {
  auto translation = bx::normalize(bx::cross(direction, bx::Vec3{0.0f, 1.0f, 0.0f}));
  position = bx::sub(position, bx::mul(translation, speed));
  update_view();
}

void Camera::rotate(float yaw_update, float pitch_update) {
  yaw += yaw_update;
  pitch += pitch_update;

  float rad_yaw = bx::toRad(yaw), rad_pitch = bx::toRad(pitch);
  bx::Vec3 new_direction = {bx::cos(rad_yaw) * bx::cos(rad_pitch), bx::sin(rad_pitch), bx::sin(rad_yaw) * bx::cos(rad_pitch)};
  direction = bx::normalize(new_direction);
  update_view();
}

void Camera::update_view() {
  bx::mtxLookAt(view.data(), position, bx::add(position, direction));
  bgfx::setViewTransform(0, view.data(), projection.data());
}

}  // namespace util
