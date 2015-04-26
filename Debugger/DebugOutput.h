#ifndef DEBUGOUTPUT_H
#define DEBUGOUTPUT_H

#include "TeeBuffer.h"

namespace Debugger
{  
	class DebugOutput
	{
	public:
		static void Init(const char* _filename);
	};
}

#endif