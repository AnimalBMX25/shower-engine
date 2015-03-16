#ifndef TESTBASE_H
#define TESTBASE_H

#include <string>
#include <vector>
using std::string;
using std::vector;

namespace UnitTest
{
	class TestBase
	{
	public:
		TestBase(const char* _testClassName) : testClassName(_testClassName){}
		virtual ~TestBase(){};

		virtual void InitTest() = 0;
		virtual bool RunTest() = 0;

		string GetTestClassName() {return testClassName;}

	protected:
		//typedef bool (*TestFunc)();

		string testClassName;
		//vector<TestFunc> test;
	};
}

#endif