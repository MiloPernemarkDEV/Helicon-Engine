#include "application.h"
#include "engine_arena.h"
#include "engine_config.h"
#include <stdexcept>

int main() {
	EngineConfig engine_config{ 
		.frame_memory_size{16 * MB},
		.global_storage_size{256 * MB}
	};

	Arena global_storage{ .total_size = engine_config.global_storage_size };
	Arena frame_storage{ .total_size = engine_config.frame_memory_size };
	
	engine_create_arena(&global_storage);
	engine_create_arena(&frame_storage);

	Application* app = engine_allocate<Application>(&global_storage);
	
	if (!application_init(app, &global_storage)) {
		return EXIT_FAILURE;
	}
	application_run(app, &frame_storage);
	application_end(app);
	
	engine_destroy_arena(&global_storage);
	engine_destroy_arena(&frame_storage);
	return 0;
}