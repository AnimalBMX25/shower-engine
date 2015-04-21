#include "UtilityTest.h"
#include <Timer.h>
#include <Pulse.h>
#include <iostream>

namespace UnitTest
{
	void UtilityTest::InitTest()
	{
		AddTest("TimerTest", TimerTest);
	}

	void UtilityTest::InitTest(std::vector<Utility::String> _strVec)
	{
		for(unsigned int i = 0; i < _strVec.size(); ++i)
		{
			CheckAddTest(_strVec[i]);
		}
	}

	bool UtilityTest::TimerTest()
	{
		std::cout << "TIMER TEST\n";
		Utility::Timer timer;

		timer.StartTimer();

		Utility::Pulse pulse(5.0);

		std::cout << "WAIT 5 SECONDS\n";

		while(!pulse.IsReady())
		{
			timer.TimeStep();
			pulse.Update(timer.GetDeltaTime());
		}

		std::cout << "DONE\n";
		std::cout << "WAIT 2 SECONDS\n";

		pulse.SetPulseTime(2.0);

		while(!pulse.IsReady())
		{
			timer.TimeStep();
			pulse.Update(timer.GetDeltaTime());
		}

		std::cout << "DONE\n";
		return true;
	}

	void UtilityTest::CheckAddTest(Utility::String _testName)
	{
		if("TimerTest" == _testName)
		{
			AddTest(_testName, TimerTest);
		}
	}
}