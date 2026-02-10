#pragma once

class ICoreSystem
{
public:
	virtual ~ICoreSystem() = default;

	virtual bool Init() = 0;
	virtual void Shutdown() = 0;
};