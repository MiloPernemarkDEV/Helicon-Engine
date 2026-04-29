#pragma once

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include "shader.h"
#include "vertex_array.h"
#include "vertex_buffer.h"
#include <vec3.h>


struct RendererInterface {
	shader shader{};
	VertexArray vertex_array{};
	VertexBuffer vertex_buffer{};
};

void renderer_init(GLFWwindow* window, RendererInterface* renderer_interface);
void renderer_swap_buffers(GLFWwindow* window);
void renderer_poll_events();
void renderer_draw_frame(GLFWwindow* window, RendererInterface* renderer_interface, float deltaTime);
void renderer_cleanup();

void renderer_set_wireframe(bool value);

inline vec3 vertices[] = {
	{-0.5f, -0.5, 0.0f},
	{0.0f, 0.5, 0.0f},
	{0.5f, -0.5f, 0.0f}
};

inline unsigned int indices[] = {
	0, 1, 2,
};


enum compileType {
	SHADER,
	PROGRAM
};

inline const int WIDTH = 800;
inline const int HEIGHT = 800;
inline bool is_wireframe = false;

static void rend_process_input(GLFWwindow* window);
void rend_framebuffer_resize_cb(GLFWwindow* window, int width, int height);
void rend_process_input(GLFWwindow* window);
void rend_check_compiletime(compileType type, GLuint shader);
static void enable_wireframe();