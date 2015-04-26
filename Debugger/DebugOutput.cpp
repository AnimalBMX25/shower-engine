#include "DebugOutput.h"

namespace Debugger
{
	void DebugOutput::Init(const char* _filename)
	{
		static	std::ofstream file(_filename);

		// tbuf will write to both file and cout
		static	teebuf tbuf(file.rdbuf(), std::cout.rdbuf());

		// replace cout's streambuf with tbuf
		static scoped_streambuf_assignment ssa(std::cout, &tbuf);
	}
}