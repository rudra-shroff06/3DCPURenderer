# 🖥️ CPU-Based 3D Renderer
A custom **3D Renderer built completely from scratch in C++**, without using OpenGL, DirectX, or Vulkan.
This project implements the entire graphics pipeling manually from 3D transformations to rasterization running fully on CPU.
This project as of now is **not a standalone software** instead, it acts as a **library / API** that you can integrate into your own programs
to draw 3D models, scenes, and custom graphics.

# ✨ Features
* **Manual 3D Transformation** (Model, View, Projection matrices implemented from first principles)
* **Quaternion-Based Camera** (smooth rotation & orientation handling without gimbal lock)
* **Perspective-Correct Barycentric Interpolation** (for depth, colors, and UVs)
* **Clipping and Frustum Culling** (to handle polygon intersections with camera/view and the screen boundary essentially the whole frustum)
* **Z-Buffer Implementation** (hidden surface removal)
* **Triangle Rasterization** (using Scanline algorithm)
* **Software Rendering Only** (no GPU APIs)

# 📸 Demo
![Example Image](ghassets/demo.bmp?raw=true "A Rotated Cube with Interpolated Colors along the constituent triangle surfaces")

# 🔬 Technical Highlights
Some of the key math & computer graphics concepts applied in this renderer:
* **Quaternions** → Used for camera orientation and rotation to avoid gimbal lock.
* **View Transform** → Constructed from quaternion rotation + camera translation.
* **Projection Matrix** → Manual perspective division using homogeneous coordinates (`1/w`).
* **Barycentric Coordinates** → Used for:
	* Inside-triangle test during rasterization.
	* Perspective-correct interpolation of attributes (depth, colors, texture coords).
* **Homogeneous Clipping** → Triangles clipped against the view frustum in 4D space before division.
* **Z-Buffer** → Stores depth values per pixel correctly render overlapping geometry.
* **Scanline Rasterizations** → Efficient filling triangles row-by-row using edge functions.
* **Depth-Correct Interpolation** → Ensures textures/colors don't wrap due to perspective.
* **Clipping** → Ensures clipped geometry is viewed correctly on the screen using **modified Sutherland-Hodgeman Polygon Clipping Algorithm**.

# 🛠️ How it Works
The Renderer mimics the traditional **graphics pipeline:**
**1. Model Transform** → Apply object’s local transformations (scale, rotate, translate).
**2. View Transform** → Convert world coordinates to camera space using quaternions.
**3. Projection Transform** → Apply perspective projection matrix.
**4. Clipping** → Remove geometry outside the view frustum.
**5. Perspective Divide** → Normalize Coordinates (`x/w`, `y/w`, `z/w`).
**6. Viewport Transform** → Map NDC → screen space.
**7. Rasterization** → Fill triangles using barycentric interpolation and scanline algorithm (also known as bounding box algo).
**8. Depth Text** → Compare Z-buffer values to resolve occlusion.
**9. Interpolation** → Apply UV (texture) & color using perspective-correct barycentric weights.

# 🚀 Getting Started
**Prerequisites**
* C++17 (or later).

As of now the Renderer is purely a library/API so no need to build.

# 📂 Project Structure

```bash
3DCPURenderer/
|-- camera/
|	|-- camera.hpp				# Camera logic, you can inherit from this to create your own camera
|	|-- FPSCamera.hpp			# FPSCamera, a readymade FPSCamera who does not want to build their own.
|	|-- FPSCamera.cpp			# FPSCamera logic
|-- graphics/
|	|-- Clipper.hpp				# Clipping logic using Sutherland-Hodgeman
|	|-- ClipperUtils.hpp		# Utilities for clipping logic
|	|-- drawFlow.hpp			# The whole draw pipeline made into one function call
|	|-- FrameBuffer.hpp			# FrameBuffer for depth test and storing pixel colors
|	|-- Mesh.hpp				# Contains the Vertices and Triangles of the model
|	|-- Model.hpp				# Model contains mesh and transform.
|	|-- Rasterizer.hpp			# Rasterization logic for triangles using Scanline Algo
|	|-- Triangle.hpp			# Triangle struct
|	|-- Vertex.hpp				# Vertex struct
|	|-- vertexInterpolation.hpp	# Interpolation logic of vertices for clipping
|-- math/
|	|-- Barycentric.hpp			# Contains logic to obtain Barycentric coordinates of a pixel inside a triangle
|	|-- LERP.hpp				# Linear Interpolation logic
|	|-- Quaternion.hpp			# Quaternion (4D Complex numbers) logic
|	|-- Transform.hpp			# Transform functions for models
|	|-- Vector.hpp				# Full vector math logic
|-- ghassets/
|	|-- demo.bmp				# Demo Image of the Renderer output of a cube with different vertex colors
|-- README.md
```


# 🧠 Learning Outcomes
* Applied linear algebra & quaternions in graphics.
* Built a software rasterizer from scratch.
* Understood the mathematical foundation of barycentric interpolation.
* Gained insight into how real GPUs implement the pipeline.

# 🔮 Future Improvements
* Loading `.obj` models.
* Lighting (using per-pixel normals).
* Phong Shading (using per-pixel normals so that model appears smooth).
* Multithreaded rasterization to speed up the frame generation process.
* Order Independent Transparency (OIT) for adding alpha channel into the pixels.
* Anti-Aliasing (specifically MSAA (MultiSample Anti-Aliasing)) so to smooth out sharp edges.
* Loading texture on a model.