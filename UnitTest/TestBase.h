#ifndef TESTBASE_H
#define TESTBASE_H

#include <string>
#include <vector>

namespace UnitTest
{
	class TestBase
	{
	public:
		TestBase(const char* _testClassName) : testClassName(_testClassName){}
		virtual ~TestBase(){};

		virtual void InitTest() = 0;
		virtual bool RunTest() = 0;

		std::string GetTestClassName() {return testClassName;}

	private:
		std::string testClassName;
	};
}

#endif