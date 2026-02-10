////////////
// Time.h //
////////////

// 2026-02-10 - Milo
// Filename changed from coreTime.h to Time.h
// Added class to Helicon namespace

#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include "Windows.h"

#include "DllDefines.h"
#include "../core/Logger.h"

namespace Helicon 
{
	class ENGINE_API Time
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
}




