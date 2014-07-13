#ifndef DEBUGOUTPUT_H
#define DEBUGOUTPUT_H

#include <vector>
#include <string>

namespace Debugger
{
	class DebugOutput
	{
	public:
		static void Init();
		static void SetDebugFlags(unsigned int _flags);
		static void AddDebugOutput(const char* _output);

	private:
		static std::vector<std::string> debugOutput;
		static unsigned int flags;
	};
}

#endif