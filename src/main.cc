#include <bgfx/bgfx.h>
#include <bx/math.h>
#include <fs.sc.glsl.bin.h>
#include <vs.sc.glsl.bin.h>

#include <iostream>

#include "gfx/indexbuffer.h"
#include "gfx/program.h"
#include "gfx/shader.h"
#include "window.h"

struct PositionColour {
  float x;
  float y;
  float z;
  uint32_t colour;
};

int main() {
  window::Window window("minivox", 800, 600);

  bgfx::VertexLayout layout;
  layout
      .begin()
      .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
      .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
      .end();

  PositionColour vertices[] = {
      {0.5f, 0.5f, 0.0f, 0xff0000ff},
      {0.5f, -0.5f, 0.0f, 0xff0000ff},
      {-0.5f, -0.5f, 0.0f, 0xff00ff00},
      {-0.5f, 0.5f, 0.0f, 0xff00ff00},
  };

  auto vertex_buffer = bgfx::createVertexBuffer(bgfx::makeRef(vertices, sizeof(vertices)), layout);

  std::vector<uint16_t> indices = {0, 1, 3, 1, 2, 3};
  gfx::IndexBuffer index_buffer(std::move(indices));

  gfx::Shader vs(vs_glsl, sizeof(vs_glsl));
  gfx::Shader fs(fs_glsl, sizeof(fs_glsl));
  gfx::Program program(vs, fs);

  while (window.is_open()) {
    const bx::Vec3 at = {0.0f, 0.0f, 0.0f};
    const bx::Vec3 eye = {0.0f, 0.0f, 10.0f};

    // Set view and projection matrix for view 0.
    float view[16];
    bx::mtxLookAt(view, eye, at);

    float proj[16];
    bx::mtxProj(proj,
                60.0f,
                float(800) / float(600),
                0.1f, 100.0f,
                bgfx::getCaps()->homogeneousDepth);

    bgfx::setViewTransform(0, view, proj);

    bgfx::touch(0);

    float mtx[16];
    bx::mtxRotateY(mtx, 0.0f);

    // position x,y,z
    mtx[12] = 0.0f;
    mtx[13] = 0.0f;
    mtx[14] = 0.0f;

    // Set model matrix for rendering.
    bgfx::setTransform(mtx);

    // Set vertex and index buffer.
    bgfx::setVertexBuffer(0, vertex_buffer);
    index_buffer.use();

    // Set render states.
    bgfx::setState(BGFX_STATE_DEFAULT);

    program.submit();

    bgfx::frame();

    glfwPollEvents();

    if (window.is_key_down(GLFW_KEY_ESCAPE)) {
      window.close();
    }
  }

  return EXIT_SUCCESS;
}
