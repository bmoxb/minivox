# minivox

`minivox` is a voxel rendering engine implemented in C++20 using the [bfgx](https://github.com/bkaradzic/bgfx) library for rendering.

An emphasis is placed on keeping code simple and explicit while also utilising 'modern' C++ features. The [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) is loosely followed.

## Build Instructions

All required libraries are included as Git submodules so you should clone the `minivox` repository using the `--recursive` option.

CMake is used to build the application (including all libraries, code, and shaders).

```
$ git clone https://github.com/bmoxb/minivox --recursive

$ mkdir build && cd build

$ cmake -DCMAKE_BUILD_TYPE=Release .. && make

$ ./minivox
```
