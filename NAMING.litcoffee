# Naming Conventions

To maintain readability and consistency across Helicon, follow these rules when contributing code.

---

## Classes & Structs
- `class_name` — snake_case for classes and structs  

## Functions & Methods
- `function_name` — snake_case for member and free functions  

## Member Variables
- `member_variables` — snake_case for member variables

## Local Variables
- `localVariable` — plain camelCase for function-local variables  

## Static Variables
- `s_staticVariable` — prefix with `s_`  

## Macros & Constants
- `MACRO_NAME` — all uppercase  
- `CONSTANT_NAME`

## Enums
- Use **enum_value** snake_case for enum names and their values  

## Namespaces
- `NamespaceName` — PascalCase  

## File Names
- Match the main class: `snake_case.h` / `snake_case.cpp` 
- prefer writing prefixing with the context of the file 
- Example: `core_window.h` / `core_window.cpp`

---

**Note:** Following these conventions helps keep the codebase consistent, readable, and maintainable for all contributors.
