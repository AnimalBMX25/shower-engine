#include "DebuggerTest.h"
#include <DebugChannel.h>
#include <DebugManager.h>
#include <ostream>
#include <sstream>
#include <iostream>

namespace UnitTest
{
#pragma region SETUP
	void DebuggerTest::InitTest()
	{
		Debugger::DebugManager::Init();
		AddTest("TokenTest", TokenTest);
		AddTest("ChannelTest", ChannelTest);
		AddTest("MaskTest", MaskTest);
	}

	void DebuggerTest::InitTest(Utility::String::StringVec _strVec)
	{
		Debugger::DebugManager::Init();
		for(unsigned int i = 0; i < _strVec.size(); ++i)
		{
			CheckAddTest(_strVec[i]);
		}
	}

	void DebuggerTest::CheckAddTest(Utility::String _testName)
	{
		if("TokenTest" == _testName)
		{
			AddTest(_testName, TokenTest);
		}
		else if("ChannelTest" == _testName)
		{
			AddTest(_testName, ChannelTest);
		}
		else if("MaskTest" == _testName)
		{
			AddTest(_testName, MaskTest);
		}
	}
#pragma endregion

	bool DebuggerTest::TokenTest()
	{
		Debugger::DebugChannel channel("TEST CHANNEL");
		channel.Output("TEST 1 - int: %d", 1000);
		channel.Output("TEST 2 - float to int: %d", 3.14f);
		channel.Output("TEST 3 - unsigned int: %u", 1000);
		channel.Output("TEST 4 - negative to unsigned int: %u", -1000);
		channel.Output("TEST 5 - octal: %o", 821);
		channel.Output("TEST 6 - hex to octal: %o", 0x7FA);
		channel.Output("TEST 7 - hex lower: %x", 1234);
		channel.Output("TEST 8 - hex upper: %X", 1234);
		channel.Output("TEST 9 - float: %f", 3.14f);
		channel.Output("TEST 10 - long long/double: %llu", 4294967295000);
		channel.Output("TEST 11 - Scientific Notation: %e", 3.14f);
		channel.Output("TEST 12 - Scientific notation uppercase: %E", 3.14f);
		channel.Output("TEST 13 - Shortest representation: %g %g % g", 3.14f, 100000, 0.00100);
		channel.Output("TEST 14 - Shortest representation uppercase: %G %G %G", 3.14f, 100000, 0.00100);
		channel.Output("TEST 15 - Hex float: %a", 3.14f);
		channel.Output("TEST 16 - Hex float uppercase: %A", 3.14f);
		channel.Output("TEST 17 - Char: %c %c", 55, 'F');
		channel.Output("TEST 18 - String: %s", "string");
		channel.Output("TEST 19 - Pointer address: %p", channel);
		channel.Output("TEST 20 - Percent: %d%%", 10);

		return true;
	}

	bool DebuggerTest::ChannelTest()
	{
		Debugger::DebugChannel channel1("CHANNEL 1");
		Debugger::DebugChannel channel2("CHANNEL 2");
		Debugger::DebugChannel channel3("CHANNEL 3");

		channel1.Output("Testing Channel 1");
		channel2.Output("Testing Channel 2");
		channel3.Output("Testing Channel 3");

		return true;
	}

	bool DebuggerTest::MaskTest()
	{
		Debugger::DebugChannel infoChannel("INFO");
		Debugger::DebugChannel errorChannel("ERROR");
		Debugger::DebugChannel warningChannel("WARNING");
		Debugger::DebugChannel errWarnChannel("ERRWARN");
		Debugger::DebugChannel infoWarnChannel("INFOWARN");
		Debugger::DebugChannel infoErrChannel("INFOERR");
		Debugger::DebugChannel allChannel("ALL");

		std::cout << "INFO TEST" << std::endl;
		infoChannel.Output("INFO TEST ALL");
		infoChannel.Output(Debugger::DEBUG_INFO, "INFO TEST INFO");
		infoChannel.Output(Debugger::DEBUG_WARNING, "INFO TEST WARNING");
		infoChannel.Output(Debugger::DEBUG_ERROR, "INFO TEST ERROR");

		std::cout << "ERROR TEST" << std::endl;
		errorChannel.Output("ERROR TEST ALL");
		errorChannel.Output(Debugger::DEBUG_INFO, "ERROR TEST INFO");
		errorChannel.Output(Debugger::DEBUG_WARNING, "ERROR TEST WARNING");
		errorChannel.Output(Debugger::DEBUG_ERROR, "ERROR TEST ERROR");

		std::cout << "WARNING TEST" << std::endl;
		warningChannel.Output("WARNING TEST ALL");
		warningChannel.Output(Debugger::DEBUG_INFO, "WARNING TEST INFO");
		warningChannel.Output(Debugger::DEBUG_WARNING, "WARNING TEST WARNING");
		warningChannel.Output(Debugger::DEBUG_ERROR, "WARNING TEST ERROR");

		std::cout << "ERROR+WARNING TEST" << std::endl;
		errWarnChannel.Output("ERROR+WARNING TEST ALL");
		errWarnChannel.Output(Debugger::DEBUG_INFO, "ERROR+WARNING TEST INFO");
		errWarnChannel.Output(Debugger::DEBUG_WARNING, "ERROR+WARNING TEST WARNING");
		errWarnChannel.Output(Debugger::DEBUG_ERROR, "ERROR+WARNING TEST ERROR");

		std::cout << "INFO+WARNING TEST" << std::endl;
		infoWarnChannel.Output("INFO+WARNING TEST ALL");
		infoWarnChannel.Output(Debugger::DEBUG_INFO, "INFO+WARNING TEST INFO");
		infoWarnChannel.Output(Debugger::DEBUG_WARNING, "INFO+WARNING TEST WARNING");
		infoWarnChannel.Output(Debugger::DEBUG_ERROR, "INFO+WARNING TEST ERROR");

		std::cout << "INFO+ERROR TEST" << std::endl;
		infoErrChannel.Output("INFO+ERROR TEST ALL");
		infoErrChannel.Output(Debugger::DEBUG_INFO, "INFO+ERROR TEST INFO");
		infoErrChannel.Output(Debugger::DEBUG_WARNING, "INFO+ERROR TEST WARNING");
		infoErrChannel.Output(Debugger::DEBUG_ERROR, "INFO+ERROR TEST ERROR");

		std::cout << "ALL TEST" << std::endl;
		allChannel.Output("INFO+ERROR TEST ALL");
		allChannel.Output(Debugger::DEBUG_INFO, "INFO+ERROR TEST INFO");
		allChannel.Output(Debugger::DEBUG_WARNING, "INFO+ERROR TEST WARNING");
		allChannel.Output(Debugger::DEBUG_ERROR, "INFO+ERROR TEST ERROR");

		return true;
	}
}				