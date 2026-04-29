#pragma once

#define TINYOBJLOADER_IMPLEMENTATION
#define TINYOBJLOADER_USE_MAPBOX_EARCUT
#include <tiny_obj_loader.h>	

struct ObjectLoader {
	std::string input_path{};
	tinyobj::ObjReaderConfig reader_config{};
};

void object_loader_init(ObjectLoader* objectLoader);
