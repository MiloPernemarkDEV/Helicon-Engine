#include "Time.h"

namespace Helicon 
{
	bool Time::Init()
	{
		LARGE_INTEGER freq;

		if (!QueryPerformanceFrequency(&freq))
		{
			return false;
		}

		m_Frequency = static_cast<double>(freq.QuadPart);

		Reset();

		HE_LOG_DEBUG("Time Init.");
		return true;
	}

	void Time::Update()
	{
		LARGE_INTEGER now;
		QueryPerformanceCounter(&now);

		m_DeltaTime = static_cast<double>(now.QuadPart - m_LastCounter.QuadPart) / m_Frequency;
		m_LastCounter = now;

		m_TotalTime += m_DeltaTime;
		m_FrameCount++;
	}

	void Time::Reset() {

		QueryPerformanceCounter(&m_LastCounter);

		m_DeltaTime = 0.0;
		m_TotalTime = 0.0;
		m_FrameCount = 0;
	}

	double Time::GetAverageFPS() {
		if (m_TotalTime > 0.0) {
			return static_cast<double>(m_FrameCount) / m_TotalTime;
		}
		return 0.0;
	}

	void Time::Shutdown()
	{
		Reset();
		HE_LOG("Time shutdown.");

	}
}
	
