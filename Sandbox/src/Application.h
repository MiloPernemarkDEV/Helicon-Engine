#pragma once

#include "window.h"
#include "core/coreTime.h"
#include "core/Logger.h"
#include <iostream>

// We are not using the constructors for initializing the sytems because
// it is hard to be sure the systems initilize in the correct order in constructor/destructor
// therefore we state the correct order inside the member functions instead 
// some systems might depend on eachother thats why this is important 

class Application
{
public:

	enum class InitResult
	{
		Success,
		Error
	};

	Application() = default;

	// Initialize systems in correct order and flag if they cant initialize
	InitResult Launch();
		
	// Game loop
	void Run();

	// Shutdown sytems in reverse order
	void End();

private:
	// add the systems as member variables 
	window m_Window{};
	coreTime m_CoreTime{};
	
};

