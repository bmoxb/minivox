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

void Camera::move_forward(float speed) {
  position = bx::sub(position, bx::Vec3{0.0f, 0.0f, speed});
  update_view();
}

void Camera::move_backward(float speed) {
  position = bx::add(position, bx::Vec3{0.0f, 0.0f, speed});
  update_view();
}

void Camera::strafe_left(float speed) {
  auto translation = bx::normalize(bx::cross(direction, up));
  position = bx::add(position, bx::mul(translation, speed));
  update_view();
}

void Camera::strafe_right(float speed) {
  auto translation = bx::normalize(bx::cross(direction, up));
  position = bx::sub(position, bx::mul(translation, speed));
  update_view();
}

void Camera::update_view() {
  bx::mtxLookAt(view.data(), position, bx::add(position, direction), up);
  bgfx::setViewTransform(0, view.data(), projection.data());
}

}  // namespace util
