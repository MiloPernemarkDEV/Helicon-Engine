#pragma once


#include "Windows.h"
#include "dllDefines.h"

class ENGINE_API coreTime
{
public:
	 void Init();

	 void Update();

	 void Reset();
	 void Shutdown();

	 double GetAverageFPS();
	 double GetDeltaTime() { return m_DeltaTime; }
	 double GetTotalTime() { return m_TotalTime; }
	 int GetFrameCount() { return m_FrameCount; }
	

private:
	LARGE_INTEGER m_LastCounter = { 0 };
	double m_Frequency = 0.0;
	double m_DeltaTime = 0.0;
	double m_TotalTime = 0.0;
	int m_FrameCount = 0;
};



