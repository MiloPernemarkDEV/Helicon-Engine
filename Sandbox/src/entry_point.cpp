#include "sandbox_app.h"
#include <iostream>

int main()
{
	sandbox_app app{};
	if (!app_launch(&app, "Game Title")) {
		std::cerr << "Failed to launch application" << std::endl;
		return EXIT_FAILURE;
	}

	app_game_loop(&app);
	app_shutdown(&app);

	return EXIT_SUCCESS;
}