// ==========================================
//                 NOTES
// ==========================================

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
// Presentation mode (conditions for "swapping" images to the screen)	s
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

/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------*/


////////////////////
//				  //
//   Image Views  //
//				  //
////////////////////

// In order to use any VkImage we need to create a VkImageView object
// An image view is quite litterly a view onto a image it describes how to acess the image, which part to access, if it should be treated as a 2D texture depth texture 
// withouht mipmapping levels and a lot of more shit i dont understand 
// we want to create image view for every image in the swap chain so that we can use them as color targets later on 

/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------*/


///////////////////////
//				     //
// Graphics Pipeline //
//					 //
///////////////////////

// The graphics pipeline is the sequence of operations that take vertices and textures of your meshes all the way to the pixels in the render targets. 

// A simplified overview:
// Input assembler -> Vertex shader -> Tesselation -> Geometry shader -> Rasterization -> Fragment shader -> Color blending -> Framebuffer

// Input assembler:
// Collects the raw vertex data from the buffers we specify and may also use an 
// index buffer to repeat certain elements withouth having to duplicate the vertex data 

// Vertex shader:
// run for every vertex and generally applies transformations to turn vertex positions from model space to screen space. 
// it also passes per-vertex data down to the pipeline

// Tesselation:
// the tesselation shaders allow you to subdivide geomtry based on certain rules to increase mesh quality
// This is often used to make surfaces like brick walls and staircases look less flat when they are nearby

// Geomtry shader:
// is run on every primitive (triangle, line, point) and can discard it or outpout more primitives than came in. 
// similar to tesselation shader, but more flexibale, its not used much in todays apps because performance is not that good,
// execpt on intels integrated GPUs

// Rasterization:
// discretizes the primitives into fragments aka brakes the primitives into pixel size pieces. These are the pixel elements they fill on the frambuffer.
// if part of the primitive is offscreen it is discarded, 
// the attributes outputted by the vertex shaders are interpolated across the fragments

// Fragment shader:
// Is invoked for every fragment that survies the rasterization and determines which framebuffers the fragments are written to and with which color and depth values

// Color blending:
// Applies operations to mix different fragments that map to the same pixel in the framebuffer. Fragments can overwrite eachother
// add up or be mixed based upon transparency

//----------------------------//

// Fixed function stagese = Input assembler, Rasterization, Color blending.
// Operations in these stages can only be tweaked using parameters but the way they work is predefined 

// Programmable stages = Vertex shader, Tesselation, Geometry shader, Fragment shader.
// Means we can upload our own code to the graphics card to apply exact operations we want
// This allows us to use fragment shaders for example to implement anything from texturing and lightning to ray tracers. 
// these programs run on many GPU cores simultaneously to process many objects like vertices and fragments in parallel. 

// The graphics pipeline in Vulkan is completely immutable. we need to recreate the pipeline from scratch if we want to change,
// shaders, bind different framebuffers, or change the blend function. The disadvantage is that we will have to create 
// a number of pipelines to represent all the different combinations of states we want to use in our rendering operations.
// On the other hand the driver can optimize the pipeline much better because of that. 

/*------------------------------------*/

///////////////////////
//				     //
//   Shader modules  //
//					 //
///////////////////////

// Unlike alot of other APIs shader code in Vulkan has to be specified in bytecode format as opposed to human readable syntax
// Like GLSL and HLSL. This bytecode format is called SPIR-V and is designed to be used with both Vulkan and OpenGL
// It is a format that can be used to write graphics and compute shaders.

// bytecode format can help avoid the GPU vendors compilers to reject shader code 

// We will turn shader code written in GLSL into SPIR-V using Khronos group vendor independent compiler. 
// We can also include the compiler as a library to produce SPIR-V at runtime. 

// GLSL is a shading language with a C-style syntax. Programs written in it have a main function that is invoked for every object 

//----------------------------//

// Vertex shader
// The vertex shader processes each incoming vertex. it takes its attributes like model space position, color, normal and texture coordinates as input.
// The output is the final position in clip coordinates and the attributes that need to be passed on to the fragment shader, like color and texture coordinates. 
// These values will then be interpolated over the fragments by the rasterizer to produce a smooth gradient 

// A clip coordinate is a four dimensional vector from the vertex shader that is turned into a normalized device coordinate by dividing the whole vector by its last component
// yeah wtf 
// These normalized device coordinates are homogeneous coordinates

//----------------------------//

// Dynamic state
// while most of the pipeline state needs to be baked into the pipeline state, a limited amount of the state can be changed withouth 
// recreating the pipeline at draw time. Examples are size of the viewport, line width and blend constants.

///////////////////////
//				     //
//  PIPELINE LAYOUT  //
//					 //
///////////////////////

// You can use uniform values in shaders, which are globals similar to dynamic state variables that can be changed at drawing time	
// To alter the behavoiur of the shaders withouth having to recreate them.
// Commonly used to pass transformation matrix to the vertex shader or texture samplers to the fragment shader 
// The uniform values need to be specified during pipeline creation by creating a VkPipelineLayout object.

/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

////////////////////
//				  //
//  RENDER PASSES //
//				  //
////////////////////

// A render pass in Vulkan describes how framebuffer attachments are used during rendering.
// It does NOT perform rendering itself.
// Instead, it defines the structure and rules for a rendering operation.

// You can think of it as a contract:
//
// "These images will be used in this way, in this order, with these layout transitions."

// A render pass describes:

// 1. Attachments
//    Images that will be used during rendering.
//    These can be:
//    - Color attachments (what you see on screen)
//    - Depth attachments (depth testing)
//    - Stencil attachments
//    - Resolve attachments (for MSAA)

// Each attachment specifies:
//    - Format (must match the swapchain format for color)
//    - Load operation (clear, load, or don't care)
//    - Store operation (store result or discard it)
//    - Initial layout (layout before render pass begins)
//    - Final layout (layout after render pass ends)

// 2. Subpasses
//    A render pass can contain multiple subpasses.
//    Each subpass represents one logical phase of rendering.
//
//    For example:
//    Subpass 0: Geometry rendering
//    Subpass 1: Post-processing
//
//    In our simple case we only use ONE subpass.
//
//    A subpass defines:
//      - Which attachments are used as color targets
//      - Which attachment is used as depth
//      - Which are input attachments

/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

///////////////////////////////
//				             //
//  VERTEX INPUT DESCRIPTION //
//				             //
///////////////////////////////

/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

////////////////////////
//				      //
//  SYNCHRONIZATION   //
//			          //
////////////////////////

// Synchronization Methods:
// Wait Idle Operations
// Fences
// Semaphores, Binary/Timeline Semaphores
// Pipeline Barriers, Execution/Timeline barriers
// Render Pass Subpass Dependencies
// Events


