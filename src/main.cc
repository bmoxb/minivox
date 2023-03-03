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
      {-1.0f, 1.0f, 1.0f, 0xff000000},
      {1.0f, 1.0f, 1.0f, 0xff0000ff},
      {-1.0f, -1.0f, 1.0f, 0xff00ff00},
      {1.0f, -1.0f, 1.0f, 0xff00ffff},
      {-1.0f, 1.0f, -1.0f, 0xffff0000},
      {1.0f, 1.0f, -1.0f, 0xffff00ff},
      {-1.0f, -1.0f, -1.0f, 0xffffff00},
      {1.0f, -1.0f, -1.0f, 0xffffffff},
  };
  gfx::VertexBuffer vertex_buffer(std::move(vertices), layout);

  std::vector<uint16_t> indices = {
      0, 1, 2, 1, 3, 2,  //
      4, 6, 5, 5, 6, 7,  //
      0, 2, 4, 4, 2, 6,  //
      1, 5, 3, 5, 7, 3,  //
      0, 4, 1, 4, 5, 1,  //
      2, 3, 6, 6, 3, 7,  //
  };
  gfx::IndexBuffer index_buffer(std::move(indices));

  gfx::Shader vs(vs_glsl, sizeof(vs_glsl));
  gfx::Shader fs(fs_glsl, sizeof(fs_glsl));
  gfx::Program program(vs, fs);

  util::Camera camera({0.0f, 0.0f, 10.0f}, 800.0f / 600.0f);

  float delta = 0.0f, last_time = 0.0f, current_time = 0.0f;

  while (window.is_open()) {
    current_time = static_cast<float>(glfwGetTime());
    delta = current_time - last_time;
    last_time = current_time;

    auto new_fb_size = window.framebuffer_size_change();
    if (new_fb_size) {
      std::cout << "framebuffer resized: " << new_fb_size->width << ", " << new_fb_size->height
                << std::endl;

      bgfx::setViewRect(0, 0, 0, new_fb_size->width, new_fb_size->height);
      bgfx::reset(new_fb_size->width, new_fb_size->height);

      auto aspect_ratio = static_cast<float>(new_fb_size->width) / static_cast<float>(new_fb_size->height);
      camera.update_aspect_ratio(aspect_ratio);
    }

    bgfx::touch(0);

    float mtx[16];
    bx::mtxRotateY(mtx, 0.0f);

    mtx[12] = 0.0f;
    mtx[13] = 0.0f;
    mtx[14] = 0.0f;

    bgfx::setTransform(mtx);

    vertex_buffer.use();
    index_buffer.use();

    bgfx::setState(BGFX_STATE_DEFAULT);

    program.submit();

    bgfx::frame();

    glfwPollEvents();

    if (window.is_key_down(GLFW_KEY_UP)) {
      camera.move_forward(3.0f * delta);
    }
    if (window.is_key_down(GLFW_KEY_DOWN)) {
      camera.move_backward(3.0f * delta);
    }
    if (window.is_key_down(GLFW_KEY_LEFT)) {
      camera.strafe_left(3.0f * delta);
    }
    if (window.is_key_down(GLFW_KEY_RIGHT)) {
      camera.strafe_right(3.0f * delta);
    }

    if (window.is_key_down(GLFW_KEY_W)) {
      camera.rotate(0.0f, 40.0f * delta);
    }
    if (window.is_key_down(GLFW_KEY_S)) {
      camera.rotate(0.0f, -40.0f * delta);
    }
    if (window.is_key_down(GLFW_KEY_A)) {
      camera.rotate(80.0f * delta, 0.0f);
    }
    if (window.is_key_down(GLFW_KEY_D)) {
      camera.rotate(-80.0f * delta, 0.0f);
    }

    if (window.is_key_down(GLFW_KEY_ESCAPE)) {
      window.close();
    }
  }

  return EXIT_SUCCESS;
}
