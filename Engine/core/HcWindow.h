#include "Defines.h"

#include <GLFW/glfw3.h>

#include <stdexcept>

class ENGINE_API HcWindow {
public:
	bool hcInitializeWindow();
	void hcShutdownWindow();
	void hcPollEvents();
	GLFWwindow* m_Window;

};