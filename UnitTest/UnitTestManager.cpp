#include "UnitTestManager.h"
#include "UtilityTest.h"
#include "DebuggerTest.h"
#include <fstream>
#include <iostream>
#include <SettingsManager.h>
#include <DebugOutput.h>

namespace UnitTest
{
	std::vector<TestBase*> UnitTestManager::testClasses;

	void UnitTestManager::Init()
	{
		Utility::SettingsManager::Init();
		Debugger::DebugOutput::Init("E:\\Visual Studio 2010\\Projects\\shower-engine\\trunk\\Logs\\unit_test.log");

		const char* testSettingsPath = Utility::SettingsManager::GetSettingsFilepath("UnitTestSettings");

		if(testSettingsPath)
		{
			ConfigureTestPlan(testSettingsPath);
		}
		else
		{
			ConfigureAllTest();
		}
	}

	void UnitTestManager::Run()
	{
		for(unsigned int i = 0; i < testClasses.size(); ++i)
		{
			std::cout << testClasses[i]->GetTestClassName() << ": BEGIN TEST" << std::endl;
			if(testClasses[i]->RunTest())
			{
				std::cout << testClasses[i]->GetTestClassName() <<": ALL TEST SUCCESSFUL" << std::endl;
			}
			else
			{
				std::cout << testClasses[i]->GetTestClassName() <<": REPORTED TEST FAILURES" << std::endl;
			}
		}
	}

	void UnitTestManager::Finish()
	{
		for(unsigned int i = 0; i < testClasses.size(); ++i)
		{
			if(testClasses[i])
			{
				delete testClasses[i];
				testClasses[i] = nullptr;
			}

			testClasses.clear();
		}
	}

	void UnitTestManager::ConfigureTestPlan(const char* _filename)
	{
		std::ifstream ifstream;
		ifstream.open(_filename, std::ios_base::in);

		if(!ifstream.is_open())
		{
			return;
		}

		while(!ifstream.eof())
		{		
			char testClassName[Utility::READ_BUFFER_SIZE] = {0};
			char testList[Utility::READ_BUFFER_SIZE] = {0};

			ifstream.getline(testClassName, Utility::READ_BUFFER_SIZE, '\t');
			ifstream.getline(testList, Utility::READ_BUFFER_SIZE, '\n');

			LoadTest(testClassName, testList);
		}
	}

	void UnitTestManager::ConfigureAllTest()
	{
		UtilityTest* utilityTest = new UtilityTest();

		testClasses.push_back(utilityTest);
	}

	void UnitTestManager::InitTest()
	{
		for(unsigned int i = 0; i < testClasses.size(); ++i)
		{
			testClasses[i]->InitTest();
		}
	}

	void UnitTestManager::LoadTest(Utility::String _testClassName, Utility::String _testList)
	{
		Utility::String::StringVec strVec(_testList.Split(' '));

		if("UtilityTest" == _testClassName)
		{
			UtilityTest* utilityTest;
			if(strVec.size() > 0)
			{
				utilityTest = new UtilityTest(strVec);
			}
			else
			{
				utilityTest = new UtilityTest();
			}

			testClasses.push_back(utilityTest);
		}
		else if("DebuggerTest" == _testClassName)
		{
			DebuggerTest* debuggerTest;
			if(strVec.size() > 0)
			{
				debuggerTest = new DebuggerTest(strVec);
			}
			else
			{
				debuggerTest = new DebuggerTest();
			}

			testClasses.push_back(debuggerTest);
		}
	}
}