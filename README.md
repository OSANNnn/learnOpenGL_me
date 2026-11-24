# OpenGL Renderer

A real-time 3D renderer written in C++ and OpenGL 3.3, built while working through the [LearnOpenGL](https://learnopengl.com) guide.

I followed the guide's techniques but designed my own architecture around them. Buffers, vertex arrays, framebuffers, textures, cubemaps and shaders are wrapped in C++ classes, so the render loop reads like a description of the scene instead of a wall of raw API calls. It was my first real object-oriented project, and it grew one chapter at a time.

![Renderer screenshot](docs/screenshot1.png)

## Features

- **Lighting:** Phong shading with directional, point and spot lights, emission maps and a set of material presets
- **Models:** 3D model loading through Assimp, with diffuse and specular textures
- **Environment:** cubemap skybox, with reflection and refraction shaders
- **Geometry shaders:** mesh "explode" effect and normal visualization
- **Post-processing:** off-screen rendering to framebuffers with blur, grayscale, edge detection and sharpen filters, chainable through two buffers
- **Transparency:** alpha-blended foliage, sorted by distance from the camera
- **Camera:** free-fly camera with mouse look and scroll-wheel zoom

## Architecture

| Class / file | What it does |
| --- | --- |
| `VAO`, `VBO`, `EBO` | Wrap vertex arrays and buffers |
| `FBO` | Framebuffer with color and render-buffer attachments, renders itself to a screen quad through any shader |
| `Texture`, `CubeMap` | Load images with stb_image and manage texture state |
| `Shader` | Compiles vertex, fragment and optional geometry shaders, with helpers for uniforms, materials and lights |
| `Mesh`, `Model` | Assimp-based model loading with texture caching |
| `Fly_Camera` | View matrix, movement and field of view |
| `Keyboard`, `Mouse` | Input state built on GLFW callbacks |
| `primitives.hpp` | Ready-made cube, plane, quad, skybox and screen-quad geometry |

## Controls

| Input | Action |
| --- | --- |
| W / A / S / D | Move |
| Q / E | Move down / up |
| Mouse | Look around |
| Scroll wheel | Zoom |
| Esc | Quit |

## Building

The project targets Windows with Visual Studio. Open `Chapter_12.sln` and build.

Dependencies are included in the `dep` folder:

- [GLFW](https://www.glfw.org/) for windowing and input
- [GLAD](https://glad.dav1d.de/) for loading OpenGL functions
- [GLM](https://github.com/g-truc/glm) for math
- [stb_image](https://github.com/nothings/stb) for image loading
- [Assimp](https://github.com/assimp/assimp) for model loading

Assets (models and textures) are loaded from the `assets` folder, relative to the working directory.

## Credits

Techniques and assets are based on [LearnOpenGL](https://learnopengl.com) by Joey de Vries. The architecture and class design are my own.
