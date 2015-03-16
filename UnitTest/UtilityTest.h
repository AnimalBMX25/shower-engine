#ifndef UTILITYTEST_H
#define UTILITYTEST_H

#include "TestBase.h"

namespace UnitTest
{
	class UtilityTest : public TestBase
	{
	public:
		UtilityTest() : TestBase("Utility Test"){InitTest();}
		~UtilityTest(){}
		bool RunTest();

	private:
		void InitTest();
		static bool TimerTest();

		typedef bool (*TestFunc)();
		vector<TestFunc> test;
	};
}

#endif