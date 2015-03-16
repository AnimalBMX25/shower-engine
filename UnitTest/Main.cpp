#include "UnitTestManager.h"

int main()
{
	UnitTest::UnitTestManager::Init(nullptr);
	UnitTest::UnitTestManager::Run();
	UnitTest::UnitTestManager::Finish();

	system("PAUSE");
	return 0;
}