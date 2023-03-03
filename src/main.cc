#include <bgfx/bgfx.h>
#include <bx/math.h>
#include <fs.sc.glsl.bin.h>
#include <vs.sc.glsl.bin.h>

#include <iostream>

#include "gfx/indexbuffer.h"
#include "gfx/program.h"
#include "gfx/shader.h"
#include "gfx/vertexbuffer.h"
#include "util/camera.h"
#include "util/window.h"

struct PositionColour {
  float x;
  float y;
  float z;
  uint32_t colour;
};

int main() {
  util::Window window("minivox", 800, 600);

  bgfx::VertexLayout layout;
  layout
      .begin()
      .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
      .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
      .end();

  std::vector<PositionColour> vertices = {
      {0.5f, 0.5f, 0.0f, 0xff0000ff},
      {0.5f, -0.5f, 0.0f, 0xff0000ff},
      {-0.5f, -0.5f, 0.0f, 0xff00ff00},
      {-0.5f, 0.5f, 0.0f, 0xff00ff00},
  };
  gfx::VertexBuffer vertex_buffer(std::move(vertices), layout);

  std::vector<uint16_t> indices = {0, 1, 3, 1, 2, 3};
  gfx::IndexBuffer index_buffer(std::move(indices));

  gfx::Shader vs(vs_glsl, sizeof(vs_glsl));
  gfx::Shader fs(fs_glsl, sizeof(fs_glsl));
  gfx::Program program(vs, fs);

  util::Camera camera({0.0f, 0.0f, 10.0f});

  float delta = 0.0f, last_time = 0.0f, current_time = 0.0f;

  while (window.is_open()) {
    current_time = static_cast<float>(glfwGetTime());
    delta = current_time - last_time;
    last_time = current_time;

    bgfx::touch(0);

    float mtx[16];
    bx::mtxRotateY(mtx, 0.0f);

    // position x,y,z
    mtx[12] = 0.0f;
    mtx[13] = 0.0f;
    mtx[14] = 0.0f;

    // Set model matrix for rendering.
    bgfx::setTransform(mtx);

    vertex_buffer.use();
    index_buffer.use();

    // Set render states.
    bgfx::setState(BGFX_STATE_DEFAULT);

    program.submit();

    bgfx::frame();

    glfwPollEvents();

    if (window.is_key_down(GLFW_KEY_UP)) {
      camera.move_forward(2.0f * delta);
    }
    if (window.is_key_down(GLFW_KEY_DOWN)) {
      camera.move_backward(2.0f * delta);
    }
    if (window.is_key_down(GLFW_KEY_LEFT)) {
      camera.strafe_left(2.0f * delta);
    }
    if (window.is_key_down(GLFW_KEY_RIGHT)) {
      camera.strafe_right(2.0f * delta);
    }

    if (window.is_key_down(GLFW_KEY_ESCAPE)) {
      window.close();
    }
  }

  return EXIT_SUCCESS;
}
