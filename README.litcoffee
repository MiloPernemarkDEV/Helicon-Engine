# Helicon Engine

Helicon is a modular C++ game engine built around a core-and-module architecture, designed to provide explicit control, flexibility, and scalability.

The engine consists of a central core statically linked library and optional subsystems called modules. The core provides foundational systems required for all applications, while modules can be selectively included depending on project needs. This design prioritizes modularity, separation of concerns, and long-term maintainability.

## Architecture Overview

Helicon is split into two main parts:

### Core
The core is always included and provides essential engine functionality. It is compiled as a statically linked library and acts as the foundation for all projects.

### Modules
Modules are optional subsystems implemented as separate statically linked libraries. They can be included as needed, allowing developers to tailor the engine to their specific use case.

## Development Prerequisites

- C++20
- Visual Studio / CLion / Rider
- Git
- **Vulkan SDK**: Download from: [https://vulkan.lunarg.com/sdk/home](https://vulkan.lunarg.com/sdk/home)

## External Libraries

- STL
- Win32 (Windows platform layer)
- X11 (Linux platform layer)
- Vulkan Graphics API
- stb_image
- Assimp 
- Dear ImGui (UI)
These are the current external libraries, this list will grow :)

## Contributing

Contributions are welcome, especially from students or developers interested in engine architecture and systems programming.

### Getting Started

1. Fork the repository  
2. Create a new branch: git checkout -b feature/your-feature-name  
3. Make your changes with clear, focused commits  
4. Push your branch and open a pull request  

### Guidelines

- Have fun!
- Follow existing naming conventions and code style (found below)
- An article on "clean" code by Casey Muratori - https://www.computerenhance.com/p/clean-code-horrible-performance
- Prefer clarity and explicit behavior

### Areas for Contribution

- Engine modules (rendering, UI, tools, etc.)  
- Platform layer improvements  
- Debugging and profiling tools  
- Documentation and examples  
- Almost anything you want to do 

### View Naming Conventions

[Naming Conventions](https://github.com/MiloPernemarkDEV/Helicon-Engine/blob/main/NAMING.litcoffee)

## Design Goals

- **Modularity** — Systems are decoupled and can be added or removed without affecting the core.  
- **Explicit Control** — Low-level access is preferred over heavy abstraction.  
- **Scalability** — Designed to support both small and large projects.  
- **Maintainability** — Clear system boundaries to reduce long-term complexity.
