#pragma once

#include "Window.h"
#include "core/Time.h"
#include "core/Logger.h"
#include <iostream>

// We are not using the constructors for initializing the sytems because
// it is hard to be sure the systems initilize in the correct order in constructor/destructor
// therefore we state the correct order inside the member functions instead 
// some systems might depend on eachother thats why this is important 

class Application
{
public:

	enum class LaunchState
	{
		Success,
		Error
	};

	Application() = default;

	// Initialize systems in correct order and flag if they cant initialize
	LaunchState LaunchCoreSystems();

	LaunchState LaunchModules();
		
	// Game loop
	void RunGame();

	// Shutdown sytems in reverse order

	void ShutdownModules();

	void ShutdownCoreSystems();

private:
	// add the systems as member variables 
	Helicon::Window m_Window{};
	Helicon::Time m_Time{};
	
};

