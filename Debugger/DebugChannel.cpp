#include "DebugChannel.h"

#include <iostream>

namespace Debugger
{
	DebugChannel::DebugChannel(const char* _channelName) : channelName(_channelName)
	{
	}

	void DebugChannel::Output(std::ostream& _outputStream)
	{
		std::ostream os(_outputStream);

		std::cout << channelName << '\t' << _outputStream << std::endl;
	}
}