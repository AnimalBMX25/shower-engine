#include "UtilityTest.h"
#include <Pulse.h>
#include <iostream>

namespace UnitTest
{
#pragma region SETUP
	void UtilityTest::InitTest()
	{
		AddTest("TimerTest", TimerTest);
		AddTest("StringSplitTest", StringSplitTest);
	}

	void UtilityTest::InitTest(Utility::String::StringVec _strVec)
	{
		for(unsigned int i = 0; i < _strVec.size(); ++i)
		{
			CheckAddTest(_strVec[i]);
		}
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

#pragma endregion

#pragma region TEST
	bool UtilityTest::TimerTest()
	{
		std::cout << "TIMER TEST" << std::endl;
		Utility::Timer timer;

		timer.StartTimer();

		TestHelperTimerTest(timer, 1.5);
		TestHelperTimerTest(timer, 11.25);
		TestHelperTimerTest(timer, 61.125);

		std::cout << "DONE" << std::endl;
		return true;
	}

	bool UtilityTest::StringSplitTest()
	{
		Utility::String testStr1("test,test,test");
		Utility::String testStr2("");
		Utility::String testStr3("test	test	test    test test test test test");

		std::cout << "SplitTest #1: Nothing to split" << std::endl;
		if(!TestHelperSplitTest(testStr1, '\t', 1))
		{
			return false;
		}

		std::cout << "SplitTest #2: Split on comma" << std::endl;
		if(!TestHelperSplitTest(testStr1, ',', 3))
		{
			return false;
		}

		std::cout << "SplitTest #3: Split on 't'" << std::endl;
		if(!TestHelperSplitTest(testStr1, 't', 5))
		{
			return false;
		}

		std::cout << "SplitTest #4: Empty String" << std::endl;
		if(!TestHelperSplitTest(testStr2, 't', 0))
		{
			return false;
		}

		std::cout << "SplitTest #5: Space" << std::endl;
		if(!TestHelperSplitTest(testStr3, ' ', 6))
		{
			return false;
		}

		std::cout << "SplitTest #6: Tab" << std::endl;
		if(!TestHelperSplitTest(testStr3, '\t', 3))
		{
			return false;
		}

		return TestHelperCharPtrSplitTest();
	}

#pragma endregion

#pragma region HELPERS
	bool UtilityTest::TestHelperSplitTest(Utility::String _testStr, char _delimiter, unsigned int _expected)
	{
		Utility::String::StringVec testStrVec(_testStr.Split(_delimiter));

		if(testStrVec.size() == _expected)
		{
			std::cout << "Sizes are equal" << std::endl;
			return true;
		}

		std::cout << "Sizes are not equal. vector.size() = " << testStrVec.size() << " Expected = " << _expected << std::endl;
		return false;
	}

	bool UtilityTest::TestHelperCharPtrSplitTest()
	{
		Utility::String::StringVec testStrVec(Utility::String::Split("Test,Split,String", ','));

		if(testStrVec.size() != 3)
		{
			std::cout << "Sizes are not equal. vector.size() = " << testStrVec.size() << " Expected = " << 3 << std::endl;
			return false;
		}

		if(testStrVec[0] != "Test")
		{
			std::cout << "Test strings not equal. Test != "<< testStrVec[0] << std::endl;
			return false;
		}

		if(testStrVec[1] != "Split")
		{
			std::cout << "Test strings not equal. Split != "<< testStrVec[1] << std::endl;
			return false;
		}

		if(testStrVec[2] != "String")
		{
			std::cout << "Test strings not equal. String != "<< testStrVec[2] << std::endl;
			return false;
		}

		std::cout << "All test strings correct" << std::endl;
		return true;
	}

	bool UtilityTest::TestHelperTimerTest(Utility::Timer& _timer, double _duration)
	{
		Utility::Pulse pulse(_duration);

		std::cout << "WAIT " << _duration <<" SECONDS" << std::endl;

		while(!pulse.IsReady())
		{
			_timer.TimeStep();
			pulse.Update(_timer.GetDeltaTime());
		}

		std::cout << "DONE" << std::endl;

		return true;
	}
#pragma endregion
}