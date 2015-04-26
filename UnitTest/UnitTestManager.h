#ifndef UNITTESTMANAGER_H
#define UNITTESTMANAGER_H

#include "TestBase.h"

#include <vector>
#include <StringUtil.h>

namespace UnitTest
{
	class UnitTestManager
	{
	public:
		static void Init();
		static void Run();
		static void Finish();

	private:
		static void ConfigureTestPlan(const char* _filename);
		static void ConfigureAllTest();
		static void InitTest();
		static void LoadTest(Utility::String _testClassName, Utility::String _testList);

		static std::vector<TestBase*> testClasses;
	};
}

#endif