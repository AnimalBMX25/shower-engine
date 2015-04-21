#include "TestBase.h"

#include <iostream>

namespace UnitTest
{
	bool TestBase::RunTest()
	{
		bool result = true;
		std::map<Utility::String, TestFunc>::iterator iter;

		for(iter = test.begin(); iter != test.end(); ++iter)
		{
			if(iter->second())
			{
				std::cout << iter->first <<": TEST SUCCESSFUL\n";
			}
			else
			{
				std::cout << iter->first <<": TEST FAILED\n";
				result = false;
			}
		}

		return result;
	}
}