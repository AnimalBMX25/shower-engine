#include "DebuggerTest.h"

#include <DebugChannel.h>
#include <ostream>
#include <sstream>

namespace UnitTest
{
#pragma region SETUP
	void DebuggerTest::InitTest()
	{
		AddTest("ChannelTest", ChannelTest);
	}

	void DebuggerTest::InitTest(Utility::String::StringVec _strVec)
	{
		for(unsigned int i = 0; i < _strVec.size(); ++i)
		{
			CheckAddTest(_strVec[i]);
		}
	}

	void DebuggerTest::CheckAddTest(Utility::String _testName)
	{
		if("ChannelTest" == _testName)
		{
			AddTest(_testName, ChannelTest);
		}
	}
#pragma endregion

	bool DebuggerTest::ChannelTest()
	{
		Debugger::DebugChannel channel("[TEST CHANNEL]");
		std::ostringstream oss;
		channel.Output(oss << "Stream");
		channel.Output(oss << "Stream2");

		return true;
	}
}