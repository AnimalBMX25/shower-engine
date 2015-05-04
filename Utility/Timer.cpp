#include "Timer.h"
#include <iostream>

namespace Utility
{
	LARGE_INTEGER	Timer::frequency = {0};

	Timer::Timer() : deltaTime(0), elapsedTime(0)
	{
		previousTime.QuadPart = 0;
		startTime.QuadPart = 0;

		if(!frequency.QuadPart)
		{
			QueryPerformanceFrequency(&frequency);
		}
	}

	void Timer::StartTimer()
	{
		QueryPerformanceCounter(&startTime);
		previousTime = startTime;
	}

	void Timer::Reset()
	{
		previousTime.QuadPart = 0;
		startTime.QuadPart = 0;
	}

	void Timer::TimeStep()
	{
		LARGE_INTEGER currentTime;
		LARGE_INTEGER dt;
		LARGE_INTEGER et;

		QueryPerformanceCounter(&currentTime);

		et.QuadPart = currentTime.QuadPart - startTime.QuadPart;
		elapsedTime = LargeIntegerToSeconds(et);

		dt.QuadPart = currentTime.QuadPart - previousTime.QuadPart;
		deltaTime = LargeIntegerToSeconds(dt);

		previousTime = currentTime;
	}

	double Timer::LargeIntegerToSeconds(const LARGE_INTEGER& L)
	{
		return (static_cast<double>(L.QuadPart) / static_cast<double>(frequency.QuadPart));
	}

	void Timer::OutputElapsedTime()
	{
		std::cout << static_cast<int>(elapsedTime/3600) << ":" << static_cast<int>(elapsedTime/60) % 60 << ":" << modf(60, &elapsedTime) << std::endl;
	}
}