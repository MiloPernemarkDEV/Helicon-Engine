	#include "coreTime.h"

	void coreTime::Init()
	{
		LARGE_INTEGER freq;

		if (!QueryPerformanceFrequency(&freq))
		{
			// Log Error 
		}
	
		m_Frequency = static_cast<double>(freq.QuadPart);

		Reset();
	}

	void coreTime::Update()
	{
		LARGE_INTEGER now;
		QueryPerformanceCounter(&now);

		m_DeltaTime = static_cast<double>(now.QuadPart - m_LastCounter.QuadPart) / m_Frequency;
		m_LastCounter = now;

		m_TotalTime += m_DeltaTime;
		m_FrameCount++;
	}

	void coreTime::Reset() {

		QueryPerformanceCounter(&m_LastCounter);

		m_DeltaTime = 0.0;
		m_TotalTime = 0.0;
		m_FrameCount = 0; 
	}

	double coreTime::GetAverageFPS() {
		if (m_TotalTime > 0.0) {
			return static_cast<double>(m_FrameCount) / m_TotalTime;
		}
		return 0.0;
	}

	void coreTime::Shutdown() 
	{
		Reset();
	}