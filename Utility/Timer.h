#ifndef TIMER_H
#define TIMER_H

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>

namespace Utility
{
	class Timer
	{
	public:
		Timer();

		void TimeStep();
		void Reset();
		void StartTimer();

		double GetElapsedTime()	const {return elapsedTime;}
		double GetDeltaTime() const {return deltaTime;}
		static LONGLONG GetFrequency() {return frequency.QuadPart;}
		static void ResetFrequency() {QueryPerformanceFrequency(&frequency);}
		void OutputElapsedTime();

	private:
		LARGE_INTEGER previousTime;
		LARGE_INTEGER startTime;
		static LARGE_INTEGER frequency;

		double elapsedTime;
		double deltaTime;

		double LargeIntegerToSeconds(const LARGE_INTEGER& L);
	};
}

#endif