#include "UtilityTest.h"
//#include <Timer.h>
//#include <Pulse.h>
#include "../Utility/Timer.h"
#include "../Utility/Pulse.h"

#include <iostream>
using std::cout;

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
		cout << "TIMER TEST\n";
		Utility::Timer timer;

		timer.StartTimer();

		Utility::Pulse pulse(5.0);

		cout << "WAIT 5 SECONDS\n";

		while(!pulse.IsReady())
		{
			timer.TimeStep();
			pulse.Update(timer.GetDeltaTime());
		}

		cout << "DONE\n";
		cout << "WAIT 2 SECONDS\n";

		pulse.SetPulseTime(2.0);

		while(!pulse.IsReady())
		{
			timer.TimeStep();
			pulse.Update(timer.GetDeltaTime());
		}

		cout << "DONE\n";
		return true;
	}
}