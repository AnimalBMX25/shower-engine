#include "DebugChannel.h"
#include <iostream>

namespace Debugger
{
	DebugChannel::DebugChannel(const char* _channelName, unsigned int _bufferSize) : channelName(_channelName)
	{
		buffer = (0 == _bufferSize ? new char[DEFAULT_BUFFER_SIZE] : new char[_bufferSize]);
	}

	DebugChannel::~DebugChannel()
	{
		if(buffer)
		{
			delete[] buffer;
			buffer = nullptr;
		}
	}

	void DebugChannel::Output(const char* _string, ...)
	{
		va_list args;
		va_start (args, _string);
		vsprintf_s(buffer, DEFAULT_BUFFER_SIZE, _string, args); 
		std::cout << "[" << channelName << "]\t" << buffer << std::endl;
		va_end (args);
	}

	void DebugChannel::Output(DEBUG_LEVEL _debugLevel, const char* _string, ...)
	{
		if(DebugManager::CanOutput(channelName, _debugLevel))
		{
			va_list args;
			va_start (args, _string);
			vsprintf_s(buffer, DEFAULT_BUFFER_SIZE, _string, args); 
			std::cout << "[" << channelName << "]\t" << buffer << std::endl;
			va_end (args);
		}
	}
}