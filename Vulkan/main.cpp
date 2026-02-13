// LLVM Formatting is on

#define VK_USE_PLATFORM_WIN32_KHR
#define NOMINMAX 
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <optional>
#include <set>
#include <cstdint>
#include <limits>
#include <algorithm>

// A constexpr variable must be initialized with value known at compile time
// Prevents runtime overhead and is safe because it throws an error if it is not initialized
constexpr uint32_t WIDTH = 800;
constexpr uint32_t HEIGHT = 600;

const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

const std::vector<const char*> deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
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
	VkSurfaceKHR surface;
	// This handle stores the graphics card we will select 
	// This handle will be implicitly destroyed when the VkInstance is destroyed 
	// Therfore you dont need to explicitly destroy in the cleanup function
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	// Store the logical device handle 
	VkDevice device;
	// Store a handle to the graphics queue
	// Device queues are implicitly cleaned up when the device is destroyed
	// so we dont need tp do anything in the cleanup function
	VkQueue graphicsQueue;
	VkQueue presentQueue;
	VkSwapchainKHR swapChain;
	std::vector<VkImage> swapChainImages;

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

	// The first thing you need to do to initialize vulkan is creating an
	// instance, the instance is the connection between the application
	// and the Vulkan library
	// Creating the instance invloves specifying details about the
	// application tot he driver 
	void initVulkan() {
		createInstance();
		setupDebugMessenger();
		createSurface();
		pickPhysicalDevice();
		createLogicalDevice();
		createSwapChain();
	}

	void createSwapChain() {
		SwapChainSupportDetails swapChainSupport = querySwapChainSupport(physicalDevice);

		VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
		VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
		VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);
		
		// Aside from these properties we also need to decide how many images we would like to have in the swap chain
		// Sticking to this minimum means we sometimes need to wait for the driver to complete internal operations before
		// we can aquire a new image to render to. it is recommended to request atleast one more image hence (+ 1)
		uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;

		if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
			imageCount = swapChainSupport.capabilities.maxImageCount;
		}

		// as tradition with Vulkan objects we start by filling the form of all the information about it 
		// imageUsage bit field specify what operations we will use the images in the swap chain for
		// we are going to render directly to the images, if you want to do postprocessing you should look at 
		// VK_IMAGE_USAGE_TRANSFER_DST_BIT
		// not doing that now though :)
		VkSwapchainCreateInfoKHR createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface = surface;
		createInfo.minImageCount = imageCount;
		createInfo.imageFormat = surfaceFormat.format;
		createInfo.imageColorSpace = surfaceFormat.colorSpace;
		createInfo.imageExtent = extent;
		createInfo.imageArrayLayers = 1;
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		QueueFamilyIndices indices = findQueueFamilies(physicalDevice);
		uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(), indices.presentFamily.value()};

		if (indices.graphicsFamily != indices.presentFamily) {
			createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = 2;
			createInfo.pQueueFamilyIndices = queueFamilyIndices;
		}
		else {
			createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
			createInfo.queueFamilyIndexCount = 0;
			createInfo.pQueueFamilyIndices = nullptr;
		}

		createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		createInfo.presentMode = presentMode;
		createInfo.clipped = VK_TRUE;

		// With vulkan it is possible that the swap chain becomes invalid or unoptimized while the app is running
		// example because the window was resized. then the swap chain needs to be recreated from scratch 
		// and a reference to the old one needs to be specficied in this field
		createInfo.oldSwapchain = VK_NULL_HANDLE;

		if (vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapChain) != VK_SUCCESS) {
			throw std::runtime_error("failed to create swap chain");
		}

		vkGetSwapchainImagesKHR(device, swapChain, &imageCount, nullptr);
		swapChainImages.resize(imageCount);
		vkGetSwapchainImagesKHR(device, swapChain, &imageCount, swapChainImages.data());
	}

	void createSurface() {
		if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
			throw std::runtime_error("failed to create window surface");
		}
	}

	// The currently available drivers will only allow us to to create a small number of queues for each queue family.
	// We dont really need more than one because you can create the command buffers on multiple threads 
	// And then submit them al lat once on the main thread with a low-overhead call. 
	// Vulkan lets you assign priorities to queues to influence the scheduling of command buffer execution using floating point numbers 0.0-1.0
	// This is required even if there is a single queue 
	void createLogicalDevice() {
		QueueFamilyIndices indices = findQueueFamilies(physicalDevice);

		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
		std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };

		float queuePriority = 1.0f;
		for (uint32_t queueFamily : uniqueQueueFamilies) {
			VkDeviceQueueCreateInfo queueCreateInfo{};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = queueFamily;
			queueCreateInfo.queueCount = 1;
			queueCreateInfo.pQueuePriorities = &queuePriority;
			queueCreateInfos.push_back(queueCreateInfo);
		}

		// Next we need to specify the set of device features we will be using 
		VkPhysicalDeviceFeatures deviceFeatures{};

		VkDeviceCreateInfo createInfo{};

		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
		createInfo.pQueueCreateInfos = queueCreateInfos.data();

		createInfo.pEnabledFeatures = &deviceFeatures;

		createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
		createInfo.ppEnabledExtensionNames = deviceExtensions.data();

		if (enableValidationLayers) {
			createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
			createInfo.ppEnabledLayerNames = validationLayers.data();
		}
		else {
			createInfo.enabledLayerCount = 0;
		}

		if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create logical device");
		}

		// With the logical device and queue handles wew can actually start using the graphics card to to things
		vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
		vkGetDeviceQueue(device, indices.presentFamily.value(), 0, &presentQueue);
	}

	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes) {
		for (const auto& avaiablePresentMode : availablePresentModes) {
			// if we find this mode we choose it for this app
			if (avaiablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
				return avaiablePresentMode;
			}
		}
		// Guarenteed to exist 
		return VK_PRESENT_MODE_FIFO_KHR;
	}

	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) {
		if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
			return capabilities.currentExtent;
		}
		else {
			int width, height;
			glfwGetFramebufferSize(window, &width, &height);

			VkExtent2D actualExtent = {
				static_cast<uint32_t>(width),
				static_cast<uint32_t>(height)
			};

			actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, 
				capabilities.maxImageExtent.width);
			actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, 
				capabilities.maxImageExtent.height);

			return actualExtent;
		}
	}

	struct SwapChainSupportDetails {
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device) {
		SwapChainSupportDetails details;

		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

		uint32_t formatCount;
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

		if (formatCount != 0) {
			details.formats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
		}

		uint32_t presentModeCount;
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

		if (presentModeCount != 0) {
			details.presentModes.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, 
				details.presentModes.data());
		}

		return details;
	}

	// Each VkSurfaceFormatKHR entry cotnains a format and a colorSpace member. the format member specifcies the color channels and types
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) {
		for (const auto& availableFormat : availableFormats) {
			if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB
				&& availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
				return availableFormat;
			}
		}

		return availableFormats[0];
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

		bool extensionSupported = checkDeviceExtensionSupport(device);

		bool swapChainAdequate = false; 
		if (extensionSupported) {
			SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device);
			swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
		}

		return indices.isComplete() && extensionSupported && swapChainAdequate;
	}

	bool checkDeviceExtensionSupport(VkPhysicalDevice device) {
		uint32_t extensionCount;
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

		std::vector<VkExtensionProperties> availableExtensions(extensionCount);
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());
		
		std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

		for (const auto& extension : availableExtensions) {
			requiredExtensions.erase(extension.extensionName);
		}

		return requiredExtensions.empty();
		
	}

	struct QueueFamilyIndices {
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		bool isComplete() {
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
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
		for (const auto& queueFamily : queueFamilies) 
		{
			if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
				indices.graphicsFamily = i;
			}

			VkBool32 presentSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

			if (presentSupport) {
				indices.presentFamily = i;
			}

			if (indices.isComplete()) {
				break;
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

		vkDestroySwapchainKHR(device, swapChain, nullptr);

		vkDestroyDevice(device, nullptr);

		if (enableValidationLayers && debugMessenger != VK_NULL_HANDLE) {
            DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
        }

		vkDestroySurfaceKHR(instance, surface, nullptr);
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

/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/////////////////////////////////
//				               //
// Logical Devices and queues  //
//					           //
/////////////////////////////////

// After selecting a physical device we need to set up at logical device to interface with it. 
// The creating process of the logical device is similar to the instance creation process it describes the features we want to use 
// We also need to specify which queues to create now that we have queried which queue families are available. 

/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

////////////////////
//				  //
// Window surface //
//				  //
////////////////////

// Since Vulkan is a platform angostic API, it can not interface directly with the windows system on its own. 
// To establish  connection between Vulkan and the window system to present results to the screen, we need to use the 
// WSI (Window System Integration) extensions 
// Window surfaces are optional in Vulkan, you create off-screen rendering.		

/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

////////////////////
//				  //
//   Swap chain   //
//				  //
////////////////////

// Since Vulkan is a platform angostic API, it can not interface directly with the windows system on its own. 
// To establish  connection between Vulkan and the window system to present results to the screen, we need to use the 
// WSI (Window System Integration) extensions 
// Window surfaces are optional in Vulkan, you create off-screen rendering.		

// Querying details of swapchain support
// There are three basic properties we need to check 
// Basic surface capabilities (min/max number of images in swap chain, min/max width and height of images)'
// surface format (pixel format, color space) 
// Available presentation modes s

// if the swapChainAdequate conditions are met the support is defenetly sufficient for the swap chain 
// but there are still many different modes of varying optimality. 
// there are three types of settings to determine:
// Surface format (color depth)
// Presentation mode (conditions for "swapping" images to the screen)
// Swap extent (resolution of images in swap chain)

// The presentation mode 
// it is arguably the most important setting for the swapchain because it represents the actual conditions for showing images on screen 
// Vulkan has 4 possible modes for this 
// 
// VK_PRESENT_MODE_IMMEDIATE_KHR: 
// (Images submitted by the app is transfered to the screen right away, which may result in tearing)
// 
// VK_PRESENT_MODE_FIFO_KHR: 
// (The swap chain is a queue where the display takes an image from the front of the queue 
// when the display is refreshed and the program inserts rendered images at the back of the queue. If the queue is full the the program has to wait
// this is most similar to vertical sync as found in modern games, the moment the display is refreshed is known as "Vertical blank"
// this mode is the only one guarenteed to be avialable)
// This mode is preferd for mobile 
// 
// VK_PRESENT_MODE_FIFO_RELAXED_KHR:
// (This mode only differs from the previous one if the app is late and the queue was empty at the last vertical blank. 
// instead of waiting for the next vertical blank, the image is transferred right away when it finally arrives, may result in visible tearing)
// 
// VK_PRESENT_MODE_MAILBOX_KHR:
// (This is another variation on the second mode. Instead of blocking the new ones this mode can be used to render frames as fast as possible
// while still avoiding tearing, resulting in fewer latency issues than standard vertical sync(vsync). this is commonly known as tripple buffering, 
// although the extistence of three buffers alone does not necessarily mean that the framrate is unlocked)
// This one is nice if energy usage is not a concern 

// Swap extent
// the swap extent is the resolution of the swap chain images and it is almost always exactly equal to the resolution of the window we are drawing in pixels 

