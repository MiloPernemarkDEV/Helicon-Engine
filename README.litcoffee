# Helicon Engine

Helicon is a modular C++ game engine built around a core-and-module architecture, designed to provide explicit control, flexibility, and scalability.

The engine consists of a central core dll and optional subsystems called modules. The core provides foundational systems required for all applications, while modules can be selectively included depending on project needs. This design prioritizes modularity, separation of concerns, and long-term maintainability.

---

## Design Goals

- **Modularity** — Systems are decoupled and can be added or removed without affecting the core.
- **Explicit Control** — Low-level access is preferred over heavy abstraction.
- **Scalability** — Designed to support both small and large projects.
- **Maintainability** — Clear system boundaries to reduce long-term complexity.

---

## Architecture Overview

Helicon is split into two main parts:

### Core
The core is always included and provides essential engine functionality. It is compiled as a dynamic library and acts as the foundation for all projects.

### Modules
Modules are optional subsystems implemented as separate dynamic libraries. They can be included as needed, allowing developers to tailor the engine to their specific use case.

---

## Development Prerequisites

- C++20
- Visual Studio / CLion / Rider
- Git
- **Vulkan SDK**: Download from: [https://vulkan.lunarg.com/sdk/home](https://vulkan.lunarg.com/sdk/home)

---

## External Libraries

- STL
- Win32 (Windows platform layer)
- X11 (Linux platform layer)
- Vulkan Graphics API
- stb_image
- Assimp 
- Dear ImGui (UI)

---

## Naming Conventions

To maintain readability and consistency across Helicon, follow these rules:

### Classes & Structs
- `ClassName` — PascalCase for classes and structs  
- Example: `Renderer`, `PhysicsSystem`

### Functions & Methods
- `functionName` — camelCase for member and free functions  
- Example: `updateFrame()`, `loadTexture()`

### Member Variables
- `m_memberVariable` — prefix with `m_`  
- Example: `m_position`, `m_velocity`

### Local Variables
- `localVariable` — plain camelCase for function-local variables  
- Example: `deltaTime`, `loopIndex`

### Static Variables
- `s_staticVariable` — prefix with `s_`  
- Example: `s_instanceCount`

### Boolean Variables
- Use descriptive prefixes: `is`, `has`, `can`  
- Example: `isVisible`, `hasFocus`, `canExecute`

### Macros
- `MACRO_NAME` — all uppercase  
- Example: `MAX_BUFFER_SIZE`

### Constants
- `CONSTANT_NAME` — all uppercase  
- Example: `PI`, `DEFAULT_SCREEN_WIDTH`

### Enum Values
- `ENUM_VALUE` — all uppercase with underscores  
- Example: `RENDER_MODE_WIREFRAME`

### Namespaces
- `NamespaceName` — PascalCase  
- Example: `Helicon::Renderer`

### File Names
- Match the main class: `ClassName.h` / `ClassName.cpp`  
- Example: `Renderer.h` / `Renderer.cpp`

---

## Contributing

Contributions are welcome, especially from students or developers interested in engine architecture and systems programming.

### Getting Started

1. Fork the repository  
2. Create a new branch: git checkout -b feature/your-feature-name
3. Make your changes with clear, focused commits  
4. Push your branch and open a pull request  

---

### Guidelines

- Keep systems modular and decoupled from the core  
- Follow existing naming conventions and code style  
- Avoid unnecessary abstractions  
- Prefer clarity and explicit behavior over “clever” solutions  

---

### Areas for Contribution

- Engine modules (rendering, UI, tools, etc.)  
- Platform layer improvements  
- Debugging and profiling tools  
- Documentation and examples  

---

### Notes

This project is primarily developed as a learning and exploration platform for engine development. Contributions should align with the overall design goals of modularity, simplicity, and explicit control.
