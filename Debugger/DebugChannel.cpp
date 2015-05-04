#include "DebugChannel.h"
#include <iostream>

namespace Debugger
{
	DebugChannel::DebugChannel(const char* _channelName) : channelName(_channelName)
	{
	}

	void DebugChannel::Output(const char* _string, ...)
	{
		if(DebugManager::CanOutput(channelName, DEBUG_ALL))
		{
			char buffer[256];
			va_list args;
			va_start (args, _string);
			vsprintf_s(buffer,_string,args); 
			std::cout << "[" <<channelName << "]\t" << buffer << std::endl;
			va_end (args);
		}
	}

	void DebugChannel::Output(DEBUG_LEVEL _debugLevel, const char* _string, ...)
	{
		if(DebugManager::CanOutput(channelName, _debugLevel))
		{
			char buffer[256];
			va_list args;
			va_start (args, _string);
			vsprintf_s(buffer,_string,args); 
			std::cout << "[" <<channelName << "]\t" << buffer << std::endl;
			va_end (args);
		}
	}
}