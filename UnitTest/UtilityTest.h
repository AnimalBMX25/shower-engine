#ifndef UTILITYTEST_H
#define UTILITYTEST_H

#include "TestBase.h"
#include <Timer.h>

namespace UnitTest
{
	class UtilityTest : public TestBase
	{
	public:
		UtilityTest() : TestBase("Utility Test"){InitTest();}
		UtilityTest(std::vector<Utility::String> _strVec) : TestBase("Utility Test"){InitTest(_strVec);}
		~UtilityTest(){}

	private:
		void InitTest();
		void InitTest(Utility::String::StringVec _strVec);
		void CheckAddTest(Utility::String _testName);

		static bool TestHelperSplitTest(Utility::String _testStr, char _delimiter, unsigned int _expected);
		static bool TestHelperCharPtrSplitTest();
		static bool TestHelperTimerTest(Utility::Timer& _timer, double _duration);

		static bool TimerTest();
		static bool StringSplitTest();
	};
}

#endif