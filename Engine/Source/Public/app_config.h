#pragma once
struct AppConfig
{
	int width{};
	int height{};
	const char* title;
};

void app_config_init(AppConfig* appConfig);

