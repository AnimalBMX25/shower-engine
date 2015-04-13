#include "UnitTestManager.h"
#include "UtilityTest.h"
#include <fstream>
#include <iostream>
#include <SettingsManager.h>

namespace UnitTest
{
	std::vector<TestBase*> UnitTestManager::testClasses;

	void UnitTestManager::Init(const char* _filename)
	{
		Utility::SettingsManager::Init();

		if(_filename)
		{
			ConfigureTestPlan(Utility::SettingsManager::GetSettingsFilepath("UnitTestSettings"));
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
			std::cout << testClasses[i]->GetTestClassName() << ": BEGIN TEST\n";
			if(testClasses[i]->RunTest())
			{
				std::cout << testClasses[i]->GetTestClassName() <<": TEST SUCCESSFUL\n";
			}
			else
			{
				std::cout << testClasses[i]->GetTestClassName() <<": TEST FAILED\n";
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
}