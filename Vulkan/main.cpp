

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <cstring>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

// NDEBUG is part of the C++ standard means "Not debug"
#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else 
	const bool enableValidationLayers = true;
#endif

class HelloTriangleApplication {
public:
	void run() {
		  initWindow();
		  initVulkan();
		  mainLoop();
		  cleanup();
	}

private:
	GLFWwindow* window;
	VkInstance instance;

	void initWindow() 
	{

		  // Initializes the library
		  glfwInit();

		  // Tell glfw to not create an OpenGL context
		  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); 

		  // Disabling for now as it needs special care to resize window 
		  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		  // The first three parameters specify the width, height and title of the window 
		  // The fourth allows you to optionally specify monitor to open window and the last parameter is only relevant to OpenGL
		  window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
	}

	
	void initVulkan(){
          // The first thing you need to do to initialize vulkan is creating an
          // instance, the instance is the connection between the application
          // and the Vulkan library
          // Creating the instance invloves specifying details about the
          // application tot he driver 
		  createInstance();

	}

	void createInstance() {
          if (enableValidationLayers && !checkValidationLayerSupport()) {
            throw std::runtime_error("Validation layers requested, but not available");
          
		  }
		  // VkApplicationInfo is a struct with info about the application, It
          // is technically optional It may provide useful info to the driver in
          // order to optimize our specific application Many structs in vulkan
          // require you to explicity specify the type in the sType member. A
          // lot of information in Vulkan is passed through sturcts instead of
          // function parameters
          VkApplicationInfo appInfo{};
          appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
          appInfo.pApplicationName = "Hello Triangle";
          appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
          appInfo.pEngineName = "No Engine";
          appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
          appInfo.apiVersion = VK_API_VERSION_1_0;

		  // This structure is not optional, it tells the Vulkan driver which
          // global extensions and validation layers we want to use Global here
          // means they apply to the whole program and not a specific device
		  VkInstanceCreateInfo createInfo {};
		  createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		  createInfo.pApplicationInfo = &appInfo;

		  uint32_t glfwExtensionCount = 0;
		  const char** glfwExtensions;

		  glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		  createInfo.enabledExtensionCount = glfwExtensionCount;
		  createInfo.ppEnabledExtensionNames = glfwExtensions;

		  if (enableValidationLayers) {
              createInfo.enabledLayerCount =
              static_cast<uint32_t>(validationLayers.size());
              createInfo.ppEnabledLayerNames = validationLayers.data();
          } else {
              createInfo.enabledLayerCount = 0;
          }

		  // The general pattern to object creation function paramters
          // are is, a pointer to a struct with creation info, a pointer
          // to custom allocator callbacks (nullptr rn), pointer to the
          // variable that stores the handle to the new object
				// Nearly all Vulkan functions return a value of type VkResult
				// that is either VK_SUCESS or an error code. 
				// 
		  // VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

		  if (vkCreateInstance(&createInfo, nullptr, &instance) !=VK_SUCCESS) {
                    throw std::runtime_error("failed to create instance!");
					
          }
	}

	// Check if all of the requested layers are availables
	bool checkValidationLayerSupport() {
		  uint32_t layerCount;
          vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		  std::vector<VkLayerProperties> availableLayers(layerCount);
          vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

		  for (const char *layerName : validationLayers) {
              bool layerFound = false;

              for (const auto &layerProperties : availableLayers) {
                  if (strcmp(layerName, layerProperties.layerName) == 0) {
                      layerFound = true;
                      break;
                  }
              }

              if (!layerFound) {
                  return false;
              }
          }

          return true;
	}

	void mainLoop(){ 
		  while (!glfwWindowShouldClose(window)) {
              glfwPollEvents();
          }
	}

	void cleanup(){ 
		
		// dont pass by reference here because you want to destroy the instance not reference it
		// All other Vulkan resources should be cleaned up before the Vulkan instance is destroyed
		vkDestroyInstance(instance, nullptr);

		glfwDestroyWindow(window);

        glfwTerminate();
	 
	}

};

int main() {
	HelloTriangleApplication app;

	try {
		app.run();
        } catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
			return EXIT_FAILURE;
		}

		return EXIT_SUCCESS;
}


/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

///////////////////////
//				     //
// Validation Layers //
//					 //
///////////////////////

// What are validation layers? 
// The Vulkan API is designed around the idea of minimal driver overhead and therefore there is very limited error checking in the API by default 
// Simple mistakes as setting enums incorrect or passing nullptrs to required parameters are generally not explicitly handled and will simply crash or result in UB
// Vulkan requires you to be very explicit with everything you are doing 
// However you can add these checks to the API through validation layers 
// They are optional components that hook into Vulkan function calls to apply additional operations, 
// such as:
// Checking the values of parameters against the specification to detect misues 
// Tracking creation and destruction of objects
// Checking thread safety
// Logging every call and its paramters to the standard outpout 
// TracingVUlkan calls for profiling and replaying 

/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

//////////////////////
//					//
// Message Callback //
//				    //
//////////////////////

// The validation layers will print debug messages to the standard outpout by default but we can also handle that by ourselves
// By providing a explicit callback in our program, this will also let you decide which kind of messages you would like to see,
// Because not all are necessarily (fatal) erros. 