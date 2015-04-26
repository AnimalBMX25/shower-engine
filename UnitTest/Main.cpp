#include "UnitTestManager.h"

#include <iostream>
#include <fstream>

int main()
{
	UnitTest::UnitTestManager::Init();
	UnitTest::UnitTestManager::Run();
	UnitTest::UnitTestManager::Finish();

	system("PAUSE");
	return 0;
}