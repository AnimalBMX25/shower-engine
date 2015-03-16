#include "DebugOutput.h"

namespace Debugger
{
	unsigned int				DebugOutput::flags = 0;
	std::vector<std::string>	DebugOutput::debugOutput;

	void DebugOutput::Init()
	{
		debugOutput.reserve(100);
	}

	void DebugOutput::SetDebugFlags(unsigned int _flags)
	{

	}

	void DebugOutput::AddDebugOutput(const char* _output)
	{
	}


}