#ifndef PULSE_H
#define PULSE_H

namespace Utility
{
	class Pulse
	{
	public:
		Pulse(double _pulseTime);

		void StartPulse();
		void SetPulseTime(double _pulseTime);
		void Update(double _updateTime);
		bool IsReady();

	private:
		double elapsedTime;
		double pulseTime;
	};
}

#endif