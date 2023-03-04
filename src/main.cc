#include <bgfx/bgfx.h>
#include <bx/math.h>

#include <iostream>

#include "fs.sc.essl.bin.h"
#include "fs.sc.glsl.bin.h"
#include "fs.sc.spv.bin.h"
#include "gfx/indexbuffer.h"
#include "gfx/program.h"
#include "gfx/shader.h"
#include "gfx/vertexbuffer.h"
#include "util/camera.h"
#include "util/debug.h"
#include "util/timing.h"
#include "util/window.h"
#include "vs.sc.essl.bin.h"
#include "vs.sc.glsl.bin.h"
#include "vs.sc.spv.bin.h"

struct PositionColour {
  float x;
  float y;
  float z;
  uint32_t colour;
};

void handle_framebuffer_resize(util::Window& window, util::Camera& camera);
void handle_input(float delta, util::Window& window, util::Camera& camera, util::Debug& debug);
void handle_rendering(const gfx::VertexBuffer<PositionColour>& vertex_buffer, const gfx::IndexBuffer& index_buffer,
                      const gfx::Program& program);

int main() {
  util::Window window("minivox", 800, 600);
  util::Camera camera({0.0f, 0.0f, 10.0f}, 800.0f / 600.0f);
  util::Timing timing;
  util::Debug debug;

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

  gfx::Shader vs(SHADER_SOURCES(vs));
  gfx::Shader fs(SHADER_SOURCES(fs));
  gfx::Program program(vs, fs);

  while (window.is_open()) {
    float delta = timing.tick();

    handle_framebuffer_resize(window, camera);
    handle_input(delta, window, camera, debug);
    handle_rendering(vertex_buffer, index_buffer, program);

    bgfx::frame();
    glfwPollEvents();
  }

  return EXIT_SUCCESS;
}

void handle_framebuffer_resize(util::Window& window, util::Camera& camera) {
  auto new_fb_size = window.framebuffer_size_change();
  if (new_fb_size) {
    std::cout << "framebuffer resized: " << new_fb_size->width << ", " << new_fb_size->height
              << std::endl;

    bgfx::setViewRect(0, 0, 0, new_fb_size->width, new_fb_size->height);
    bgfx::reset(new_fb_size->width, new_fb_size->height);

    auto aspect_ratio = static_cast<float>(new_fb_size->width) / static_cast<float>(new_fb_size->height);
    camera.update_aspect_ratio(aspect_ratio);
  }
}

void handle_input(float delta, util::Window& window, util::Camera& camera, util::Debug& debug) {
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

  if (window.was_key_pressed(GLFW_KEY_F1)) {
    debug.toggle_wireframe();
  }
  if (window.was_key_pressed(GLFW_KEY_F2)) {
    debug.toggle_stats();
  }

  if (window.is_key_down(GLFW_KEY_ESCAPE)) {
    window.close();
  }
}

void handle_rendering(const gfx::VertexBuffer<PositionColour>& vertex_buffer, const gfx::IndexBuffer& index_buffer,
                      const gfx::Program& program) {
  float mtx[16];
  bx::mtxRotateY(mtx, 0.0f);
  mtx[12] = 0.0f;
  mtx[13] = 0.0f;
  mtx[14] = 0.0f;
  bgfx::setTransform(mtx);

  vertex_buffer.use();
  index_buffer.use();
  program.submit();
}
