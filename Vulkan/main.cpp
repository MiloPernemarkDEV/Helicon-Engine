// LLVM Formatting is on

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <optional>
#include <iostream>

// A constexpr variable must be initialized with value known at compile time
// Prevents runtime overhead and is safe because it throws an error if it is not initialized
constexpr uint32_t WIDTH = 800;
constexpr uint32_t HEIGHT = 600;

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

	// Handle to tell vulkan about our message callback function
    VkDebugUtilsMessengerEXT debugMessenger = VK_NULL_HANDLE;

	// This handle stores the graphics card we will select 
	// This handle will be implicitly destroyed when the VkInstance is destroyed 
	// Therfore you dont need to explicitly destroy in the cleanup function
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;


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
          setupDebugMessenger();

	}

	void pickPhysicalDevice() {

		// Listing devices is similar to listing extensions, start by querying just the number 
		// vkEnumeratePhysicalDevices adds the number of devices with vulkan support at the adress of the second parameter 
		// in this case our deviceCount variable
		uint32_t deviceCount = 0;
          vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

		  if (deviceCount == 0) {
            throw std::runtime_error("failed to find GPUs with Vulkan support!");
          }

		  // If we find devices with support of vulkan we can allocate an array to hold all of the VkPhysicalDevice handles
		  std::vector<VkPhysicalDevice> devices(deviceCount);
          vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());
		  
		  // then evaluate each of the devices and check if they are suitable for the operations we want to perform 
		  // because not all graphics cards are created equal 
		  for (const auto &device : devices) {
            if (isDeviceSuitable(device)) {
              physicalDevice = device;
              break;
            }
          }

		  if (physicalDevice == VK_NULL_HANDLE) {
            throw std::runtime_error("failed to find suitable GPU!");
          }
	}

	// To evaluate the suitability of a device we can start by querying for some details. 
	// Basic properties such as name, type, supported vulkan version can be queried using 
	// vkGetPhysicalDeviceProperties
	// the support of optional features such as texture compression, 64 bit floats and multi viewport renderering(useful for VR)
	// can be queried using vkGetPhysicalDeviceFeatures
	bool isDeviceSuitable(VkPhysicalDevice device) {
		QueueFamilyIndices indices = findQueueFamilies(device);

		return indices.graphicsFamily.has_value();
	}

	struct QueueFamilyIndices {
		std::optional<uint32_t> graphicsFamily;
	};

	// the VkQueueFamilyProperties contains some details about the queue family, type of operations
	// that are supported, and number of queues that can be created based on that family
	// we need to find atleast one queue family that supports VK_QUEUE_GRAPHICS_BIT
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) {
		QueueFamilyIndices indices;

		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		int i = 0;
		for (const auto& queueFamily : queueFamilies) {
			if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
				indices.graphicsFamily = i;
			}

			i++;
		}

		return indices;
	}

	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo) {
          createInfo = {};
		createInfo.sType =
              VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
          createInfo.messageSeverity =
              VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
              VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
              VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
          createInfo.messageType =
              VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
              VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
              VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
          createInfo.pfnUserCallback = debugCallback;
          createInfo.pUserData = nullptr;
	}

	void setupDebugMessenger() { 
		   if (!enableValidationLayers) return;

           VkDebugUtilsMessengerCreateInfoEXT createInfo;
           populateDebugMessengerCreateInfo(createInfo);
		   
		   if (CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
                     throw std::runtime_error("failed to set up debug messenger!");
		   }

	}

	VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
		const VkAllocationCallbacks* pAllocator,
		VkDebugUtilsMessengerEXT* pDebugMessenger) {
          auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
              instance, "vkCreateDebugUtilsMessengerEXT");
          if (func != nullptr) {
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
          } else {
			  return VK_ERROR_EXTENSION_NOT_PRESENT;
          }
	}

	static void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
										const VkAllocationCallbacks *pAllocator) {

          auto func =(PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
          
		  if (func != nullptr) {
            func(instance, debugMessenger, pAllocator);
          }
    }

	// The general pattern to object creation function paramters
    // are is, a pointer to a struct with creation info, a pointer
    // to custom allocator callbacks (nullptr rn), pointer to the
    // variable that stores the handle to the new object
    // Nearly all Vulkan functions return a value of type VkResult
    // that is either VK_SUCESS or an error code.

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
		 
		  auto glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		  auto extensions = getRequiredExtensions();
		  createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		  createInfo.ppEnabledExtensionNames = extensions.data();

		
		  VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo {};
		  if (enableValidationLayers) {
				createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
				createInfo.ppEnabledLayerNames = validationLayers.data();

				populateDebugMessengerCreateInfo(debugCreateInfo);
				createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;
		  } 
		  else {
				createInfo.enabledLayerCount = 0;

				createInfo.pNext = nullptr;
		  }

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

	// Setting up Vulkan message callback to display error messages during errors 
	// the macro prevents typos as it is equal to the literal string "VK_EXT_debug_utils" 
	std::vector<const char*> getRequiredExtensions() {
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

		if (enableValidationLayers) {
                  extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		}

		return extensions;
	}

	void mainLoop(){ 
		  while (!glfwWindowShouldClose(window)) {
              glfwPollEvents();
          }
	}

	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType, 
	    const VkDebugUtilsMessengerCallbackDataEXT* pCallBackData, 
	    void* pUserData) {
		
		std::cerr << "Validation layer: " << pCallBackData->pMessage << std::endl;
		
		return VK_FALSE;
	}



	// dont pass by reference here because you want to destroy the objects
    // All Vulkan resources should be cleaned up before the Vulkan instance is destroyed
	void cleanup(){ 
		if (enableValidationLayers && debugMessenger != VK_NULL_HANDLE) {
            DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
        }

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

// Even the callbacks need a handle in vulkan to tell Vulkan about the function 
// it needs to be explicitly created and destroyed
// 

/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

// How to set up a message callback ----

// 1. declare this function: static VKAPI_ATTR VkBool32 VKAPI_CALL functionName(parameters below)
// VKAPI_ATTR & VKAPI_CALL ensures the function has the right signature for Vulkan to call it 


// 2. first Parameters: vkDebugUtilsMessageSeverityFlagBitsEXT (Message Severity): 

// The first parameter specify the severity of the message, it is one of
// following flags, 
// VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
// VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT
// VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
// VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT
// The values of these enumerations are set up in a way that you can do comparison checks 
// For example using if statements to check if something is worth to show

// 3. Second Parameter: VkDebugUtilsMessageTypeFlagsEXT messageType,
// Can have the following values
// VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT, (Some event has happened that is unrelated to the specification or performance)
// VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT (Something has happened that violates the specification or indicates a possible mistake)
// VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT (Potential non-optimal use of Vulkan)

// 4. VkDebugUtilsMessengerCallbackDataEXT* pCallBackData 
// refers to a struct containing details of the message itself, 
// most important members being pMessage, pObjetcs, pObjectCount

// 5. void* pUserData
// contains a pointer that was specifiecd during the setup of the callback and allows you to pass your own data to it 

/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

//////////////////////
//					//
// Queue famillies  //
//				    //
//////////////////////

// Almost every operation in Vulkan, from drawing to uploading textures, requires commands to be submitted to a queue. 
// There are different types of queues that originate from different queue families and each family only allows 
// A subset of commands. There could be a queue family that only allows processing compute commands or one that
// Only allows memory transfer related commands
// we need to check which queue families are supported by the device and which of these supports the commands that we want to use 