#ifndef UTILITYTEST_H
#define UTILITYTEST_H

#include "TestBase.h"

namespace UnitTest
{
	class UtilityTest : public TestBase
	{
	public:
		UtilityTest() : TestBase("Utility Test"){InitTest();}
		UtilityTest(std::vector<Utility::String> _strVec) : TestBase("Utility Test"){InitTest(_strVec);}
		~UtilityTest(){}
		bool RunTest();

	private:
		void InitTest();
		void InitTest(std::vector<Utility::String> _strVec);
		void CheckAddTest(Utility::String _testName);
		static bool TimerTest();
	};
}

#endif