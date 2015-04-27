#ifndef DEBUGGERTEST_H
#define DEBUGGERTEST_H

#include "TestBase.h"

namespace UnitTest
{
	class DebuggerTest : public TestBase
	{
	public:
		DebuggerTest() : TestBase("Debugger Test"){InitTest();}
		DebuggerTest(std::vector<Utility::String> _strVec) : TestBase("Debugger Test"){InitTest(_strVec);}
		~DebuggerTest(){}
		bool RunTest();

	private:
		void InitTest();
		void InitTest(Utility::String::StringVec _strVec);
		void CheckAddTest(Utility::String _testName);

		static bool ChannelTest();
	};
}

#endif