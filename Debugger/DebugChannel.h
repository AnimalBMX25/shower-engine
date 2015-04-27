#ifndef DEBUGCHANNEL_H
#define DEBUGCHANNEL_H

#include <StringUtil.h>

#include <sstream>

namespace Debugger
{
	class DebugChannel
	{
	public:
		DebugChannel(const char* _channelName);

		void Output(std::ostream& _outputStream);

	private:
		Utility::String channelName;
	};
}

#endif