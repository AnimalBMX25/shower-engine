#ifndef UNITTESTMANAGER_H
#define UNITTESTMANAGER_H

#include "TestBase.h"

#include <vector>
using std::vector;

namespace UnitTest
{
	class UnitTestManager
	{
	public:
		static void Init(const char* _filename);
		static void Run();
		static void Finish();

	private:
		static void ConfigureTestPlan(const char* _filename);
		static void ConfigureAllTest();
		static void InitTest();

		static vector<TestBase*> testClasses;
	};
}

#endif