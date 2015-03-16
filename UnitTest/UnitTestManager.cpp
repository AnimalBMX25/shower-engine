#include "UnitTestManager.h"
#include <fstream>
#include <iostream>
using std::cout;

#include "UtilityTest.h"

namespace UnitTest
{
	vector<TestBase*> UnitTestManager::testClasses;

	void UnitTestManager::Init(const char* _filename)
	{
		if(_filename)
		{
			ConfigureTestPlan(_filename);
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
			cout << testClasses[i]->GetTestClassName() << ": BEGIN TEST\n";
			if(testClasses[i]->RunTest())
			{
				cout << testClasses[i]->GetTestClassName() <<": TEST SUCCESSFUL\n";
			}
			else
			{
				cout << testClasses[i]->GetTestClassName() <<": TEST FAILED\n";
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