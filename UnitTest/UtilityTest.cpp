#include "UtilityTest.h"
#include <Timer.h>
#include <Pulse.h>
#include <iostream>

namespace UnitTest
{
	void UtilityTest::InitTest()
	{
		test.push_back(UnitTest::UtilityTest::TimerTest);	
	}

	bool UtilityTest::RunTest()
	{
		bool success = true;

		for(unsigned int i = 0; i < test.size(); ++i)
		{
			if(!test[i]())
			{
				success = false;
			}
		}

		return success;
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
}