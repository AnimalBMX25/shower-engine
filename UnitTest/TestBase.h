#ifndef TESTBASE_H
#define TESTBASE_H

#include <StringUtil.h>
#include <map>
#include <vector>

namespace UnitTest
{
	typedef bool (*TestFunc)();

	class TestBase
	{
	public:
		TestBase(const char* _testClassName) : testClassName(_testClassName){}
		TestBase(const char* _testClassName, std::vector<Utility::String> _strVec) : testClassName(_testClassName){}
		virtual ~TestBase(){};

		virtual void InitTest() = 0;
		virtual void InitTest(std::vector<Utility::String> _strVec) = 0;
		bool RunTest();
		void AddTest(Utility::String _testName, TestFunc _testFunc) {test[_testName] = _testFunc;}

		std::string GetTestClassName() {return testClassName;}

	private:
		Utility::String testClassName;
		std::map<Utility::String, TestFunc> test; 
	};
}

#endif