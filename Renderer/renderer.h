#pragma once

#if defined(HELICON_RENDERER_USE_VULKAN) && defined(HELICON_RENDERER_USE_OPENGL)
	#error "You can only define one renderer API!"
#elif !defined(HELICON_RENDERER_USE_VULKAN) && !defined(HELICON_RENDERER_USE_OPENGL)
	#error "You must define a renderer API before including renderer.h"
#endif

#if defined(HELICON_RENDERER_USE_VULKAN)
	#include "renderer_vulkan.h"
#elif defined(HELICON_RENDERER_USE_OPENGL)
	// #include "renderer_opengl.h 
#endif

#if defined(HELICON_RENDERER_USE_VULKAN)

inline bool renderer_initialize() {
	return renderer_initialize_vulkan();
}

inline void renderer_shutdown() {
	return renderer_shutdown_vulkan();
}

inline void renderer_draw_frame() {
	return renderer_draw_frame_vulkan();
}

#elif defined(HELICON_RENDERER_USE_OPENGL)

// OpenGL implementation

#endif

