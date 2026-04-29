#include "render_interface.h"


void renderer_init(GLFWwindow* window, RendererInterface* renderer_interface)
{

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
		throw std::runtime_error("Failed to initialize glad!");
	}
		

	renderer_interface->shader.vertexPath = "shader.vert";
	renderer_interface->shader.fragmentPath = "shader.frag"; 
	auto result = shader_create(&renderer_interface->shader);
	std::cout << "Shader ID: " << renderer_interface->shader.ID << std::endl;

	create_vertex_array_object(&renderer_interface->vertex_array);
	create_vertex_buffer(&renderer_interface->vertex_buffer);

	bind_vertex_array(&renderer_interface->vertex_array);
	bind_vertex_buffer(&renderer_interface->vertex_buffer);
	
	add_data_vertex_buffer(&renderer_interface->vertex_buffer, vertices, sizeof(vertices));

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glViewport(0, 0, WIDTH, HEIGHT);
	glfwSetFramebufferSizeCallback(window, rend_framebuffer_resize_cb);
}

void renderer_draw_frame(GLFWwindow* window, RendererInterface* renderer_interface, float deltaTime)
{
	if (!is_wireframe) {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	}
	rend_process_input(window);
	glClear(GL_COLOR_BUFFER_BIT);


	shader_use(&renderer_interface->shader);
	shader_set_float(&renderer_interface->shader, "SomeUniform", 1.0f);
	bind_vertex_array(&renderer_interface->vertex_array);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void renderer_cleanup()
{
	glfwTerminate();
}

void renderer_set_wireframe(bool value)
{
}


void rend_framebuffer_resize_cb(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void rend_process_input(GLFWwindow* window) {
	static bool q_pressed_last_frame = false;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	const bool q_pressed_now = glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS;

	if (q_pressed_now && !q_pressed_last_frame) {
		is_wireframe = !is_wireframe;

		if (is_wireframe)
			enable_wireframe();
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	q_pressed_last_frame = q_pressed_now;
}

void rend_check_compiletime(compileType type, GLuint id)
{
	if (type == compileType::SHADER) {
		int success;
		char info_log[512];
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if (!success) {
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;
		}
	}
	else if (type == compileType::PROGRAM) {
		int success;
		char info_log[512];
		glGetProgramiv(id, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(id, 512, nullptr, info_log);
			std::cout << "ERROR::PROGRAM::COMPILATION_FAILED\n" << info_log << std::endl;
		}
	}
}

void enable_wireframe() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}


void renderer_swap_buffers(GLFWwindow* window)
{
	glfwSwapBuffers(window);
}

void renderer_poll_events()
{
	glfwPollEvents();
}
