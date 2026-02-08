#include "coreTime.h"

LARGE_INTEGER coreTime::s_LastCounter;
double coreTime::s_Frequency = 0.0f;
double coreTime::s_DeltaTime = 0.0f;
double coreTime::s_TotalTime = 0.0f;
int coreTime::s_FrameCount = 0;

void coreTime::Init()
{
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	s_Frequency = static_cast<double>(freq.QuadPart);

	Reset();
}

void coreTime::Update()
{
	LARGE_INTEGER now;
	QueryPerformanceCounter(&now);

	s_DeltaTime = static_cast<double>(now.QuadPart - s_LastCounter.QuadPart) / s_Frequency;
	s_LastCounter = now;

	s_TotalTime += s_DeltaTime;
	s_FrameCount++;
}

void coreTime::Reset() {

	QueryPerformanceCounter(&s_LastCounter);

	s_DeltaTime = 0.0f;
	s_TotalTime = 0.0f;
	s_FrameCount = 0; 
}

double coreTime::GetAverageFPS() {
	if (s_TotalTime > 0.0) {
		return static_cast<double>(s_FrameCount) / s_TotalTime;
	}
	return 0.0;
}