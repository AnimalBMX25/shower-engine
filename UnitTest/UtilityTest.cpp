#include "UtilityTest.h"
#include <Timer.h>
#include <Pulse.h>
#include <iostream>

namespace UnitTest
{
	void UtilityTest::InitTest()
	{
		AddTest("TimerTest", TimerTest);
		AddTest("StringSplitTest", StringSplitTest);
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

	bool UtilityTest::StringSplitTest()
	{
		Utility::String testStr1("test,test,test");
		Utility::String testStr2("");
		Utility::String testStr3("test	test	test    test test test test test");

		std::cout << "SplitTest #1: Nothing to split\n";
		if(!TestHelperSplitTest(testStr1, '\t', 1))
		{
			return false;
		}

		std::cout << "SplitTest #2: Split on comma\n";
		if(!TestHelperSplitTest(testStr1, ',', 3))
		{
			return false;
		}

		std::cout << "SplitTest #3: Split on 't'\n";
		if(!TestHelperSplitTest(testStr1, 't', 5))
		{
			return false;
		}

		std::cout << "SplitTest #4: Empty String\n";
		if(!TestHelperSplitTest(testStr2, 't', 0))
		{
			return false;
		}

		std::cout << "SplitTest #5: Space\n";
		if(!TestHelperSplitTest(testStr3, ' ', 6))
		{
			return false;
		}

		std::cout << "SplitTest #6: Tab\n";
		if(!TestHelperSplitTest(testStr3, '\t', 3))
		{
			return false;
		}

		return true;
	}

	void UtilityTest::CheckAddTest(Utility::String _testName)
	{
		if("TimerTest" == _testName)
		{
			AddTest(_testName, TimerTest);
		}
		else if("StringSplitTest" == _testName)
		{
			AddTest(_testName, StringSplitTest);
		}
	}

	bool UtilityTest::TestHelperSplitTest(Utility::String _testStr, char _delimiter, unsigned int _expected)
	{
		std::vector<Utility::String> testStrVec;

		testStrVec = _testStr.Split(_delimiter);

		if(testStrVec.size() == _expected)
		{
			std::cout << "Sizes are equal\n";
			return true;
		}

		std::cout << "Sizes are not equal. vector.size() = " << testStrVec.size() << " Expected = " << _expected << "\n";
		return false;
	}
}