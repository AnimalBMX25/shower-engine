#include "UnitTestManager.h"

#include <iostream>
#include <fstream>

int main()
{
	UnitTest::UnitTestManager::Init("TEST");
	UnitTest::UnitTestManager::Run();
	UnitTest::UnitTestManager::Finish();

	system("PAUSE");
	return 0;
}