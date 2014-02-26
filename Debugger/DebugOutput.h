#ifndef DEBUGOUTPUT_H
#define DEBUGOUTPUT_H

#include <vector>
#include <string>

namespace Debugger
{
	class DebugOutput
	{
	public:
		static void SetDebugFlags(unsigned int _flags);
		static void AddDebugOutput(const char const* _output);

	private:
		std::vector<std::string>> 
	};
}

#endif