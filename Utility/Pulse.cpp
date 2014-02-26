#include "Pulse.h"

namespace Utility
{
	Pulse::Pulse(double _pulseTime) : pulseTime(_pulseTime), elapsedTime(0.0)
	{
	}

	void Pulse::SetPulseTime(double _pulseTime)
	{
		pulseTime = _pulseTime;
	}

	void Pulse::Update(double _updateTime)
	{
		elapsedTime += _updateTime;
	}

	bool Pulse::IsReady()
	{
		if(elapsedTime > pulseTime)
		{
			elapsedTime = 0.0;
			return true;
		}

		return false;
	}
}