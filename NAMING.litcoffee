# Naming Conventions

To maintain readability and consistency across Helicon, follow these rules when contributing code.

---

## Classes & Structs
- `ClassName` — PascalCase for classes and structs  
- Example: `Renderer`, `PhysicsSystem`

## Functions & Methods
- `functionName` — camelCase for member and free functions  
- Example: `updateFrame()`, `loadTexture()`

## Member Variables
- `m_memberVariable` — prefix with `m_`  
- Example: `m_position`, `m_velocity`

## Local Variables
- `localVariable` — plain camelCase for function-local variables  
- Example: `deltaTime`, `loopIndex`

## Static Variables
- `s_staticVariable` — prefix with `s_`  
- Example: `s_instanceCount`

## Boolean Variables
- Use descriptive prefixes: `is`, `has`, `can`  
- Example: `isVisible`, `hasFocus`, `canExecute`

## Macros
- `MACRO_NAME` — all uppercase  
- Example: `MAX_BUFFER_SIZE`

## Constants
- `CONSTANT_NAME` — all uppercase  
- Example: `PI`, `DEFAULT_SCREEN_WIDTH`

## Enum Values
- `ENUM_VALUE` — all uppercase with underscores  
- Example: `RENDER_MODE_WIREFRAME`

## Namespaces
- `NamespaceName` — PascalCase  
- Example: `Helicon::Renderer`

## File Names
- Match the main class: `ClassName.h` / `ClassName.cpp`  
- Example: `Renderer.h` / `Renderer.cpp`

---

**Note:** Following these conventions helps keep the codebase consistent, readable, and maintainable for all contributors.
