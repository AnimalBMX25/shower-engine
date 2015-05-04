#include "DebugManager.h"
#include <SettingsManager.h>
#include <iostream>
#include <fstream>

namespace Debugger
{
	std::map<Utility::String, char> DebugManager::channels;
	Utility::Timer					DebugManager::timestamp;

	void DebugManager::Init()
	{
		timestamp.StartTimer();
		std::cout << "Initializing Debug Manager" << std::endl;
		Utility::SettingsManager::Init();
		ReadSettingsFile(Utility::SettingsManager::GetSettingsFilepath("DebuggerSettings"));
	}

	bool DebugManager::CanOutput(Utility::String _channel, DEBUG_LEVEL _debugLevel)
	{	
		std::map<Utility::String,char>::const_iterator iter = channels.find(_channel);

		if(iter == channels.end())
		{
			timestamp.TimeStep();
			return true;
		}

		char bitfield = iter->second;

		if(bitfield & _debugLevel)
		{
			timestamp.TimeStep();
			return true;
		}

		return false;
	}

	void DebugManager::ReadSettingsFile(const char* _filepath)
	{
		std::ifstream ifstream;
		ifstream.open(_filepath, std::ios_base::in);
		std::cout << "Opening: " << _filepath << std::endl;

		if(!ifstream.is_open())
		{
			std::cout << "Failed to open: " << _filepath << std::endl;
			return;
		}

		while(!ifstream.eof())
		{		
			char buffer[Utility::READ_BUFFER_SIZE] = {0};
			ifstream.getline(buffer, Utility::READ_BUFFER_SIZE, '\t');
			Utility::String name = buffer;
			std::cout << "Channel name = " << name << std::endl;

			ifstream.getline(buffer, Utility::READ_BUFFER_SIZE, '\n');
			Utility::String bitfield = buffer;
			std::cout << "Channel bitfield = " << bitfield << std::endl;

			channels[name.c_str()] = DebugLevelBitfield(bitfield);
		}

		std::cout << std::endl;
	}

	char DebugManager::DebugLevelBitfield(Utility::String _bitfield)
	{
		char bitfield = 0;

		for(unsigned int i = 0; i < _bitfield.size(); ++i)
		{
			char bit = (_bitfield[i] - '0');

			if(DEBUG_NONE == bit)
			{
				return DEBUG_NONE;
			}
			else if(DEBUG_ALL == bit)
			{
				return DEBUG_ALL;
			}
			else if(DEBUG_INFO == bit || DEBUG_WARNING == bit || ERROR == bit)
			{
				bitfield |= bit;
			}
		}

		return bitfield;
	}
}