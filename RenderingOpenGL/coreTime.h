#pragma once


#include <winnt.h>
#include <profileapi.h>
#include "dllDefines.h"

class ENGINE_API coreTime
{
public:
	static void Init();

	static void Update();

	static void Reset();

	static double GetAverageFPS();
	static double GetDeltaTime() { return s_DeltaTime; }
	static double GetTotalTime() { return s_TotalTime; }
	static int GetFrameCount() { return s_FrameCount; }
	

private:
	static LARGE_INTEGER lastCounter;
	static double frequency;

	static double s_DeltaTime;
	static double s_TotalTime;
	static int s_FrameCount;
};



