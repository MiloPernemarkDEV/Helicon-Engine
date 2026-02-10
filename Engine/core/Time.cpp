	#include "Time.h"

	void Helicon::Time::Init()
	{
		LARGE_INTEGER freq;

		if (!QueryPerformanceFrequency(&freq))
		{
			// Log Error 
		}
	
		m_Frequency = static_cast<double>(freq.QuadPart);

		Reset();

		HEL_DEBUG("Initialized coreTime.");
	}

	void Helicon::Time::Update()
	{
		LARGE_INTEGER now;
		QueryPerformanceCounter(&now);

		m_DeltaTime = static_cast<double>(now.QuadPart - m_LastCounter.QuadPart) / m_Frequency;
		m_LastCounter = now;

		m_TotalTime += m_DeltaTime;
		m_FrameCount++;
	}

	void Helicon::Time::Reset() {

		QueryPerformanceCounter(&m_LastCounter);

		m_DeltaTime = 0.0;
		m_TotalTime = 0.0;
		m_FrameCount = 0; 
	}

	double Helicon::Time::GetAverageFPS() {
		if (m_TotalTime > 0.0) {
			return static_cast<double>(m_FrameCount) / m_TotalTime;
		}
		return 0.0;
	}

	void Helicon::Time::Shutdown()
	{
		Reset();
		HEL_DEBUG("Shutdown coreTime.");

	}