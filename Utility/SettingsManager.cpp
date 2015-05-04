#include "SettingsManager.h"
#include <iostream>
#include <fstream>

namespace Utility
{
	std::map<String, String>	SettingsManager::settingsFiles;
	bool						SettingsManager::initialized = false;

	void SettingsManager::Init(const char* _filepath)
	{
		if(!initialized)
		{
			std::cout << "Initializing Settings Manager" << std::endl;
			ReadSettingsFile(_filepath);
			initialized = true;
		}
	}

	void SettingsManager::Refresh(const char* _filepath)
	{
		std::cout << "Refreshing Settings Manager" << std::endl;
		settingsFiles.clear();
		ReadSettingsFile(_filepath);
	}

	const char* SettingsManager::GetSettingsFilepath(const char* _settingsName) 
	{
		if(settingsFiles[_settingsName].size() > 0)
		{
			return settingsFiles[_settingsName].c_str();
		}
			
		return nullptr;
	}

	void SettingsManager::ReadSettingsFile(const char* _filepath)
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
			char buffer[READ_BUFFER_SIZE] = {0};
			ifstream.getline(buffer, READ_BUFFER_SIZE, '\t');
			String name = buffer;
			std::cout << "Settings name = " << name << std::endl;

			ifstream.getline(buffer, READ_BUFFER_SIZE, '\n');
			String filepath = buffer;
			std::cout << "Settings filepath = " << filepath << std::endl;

			settingsFiles[name.c_str()] = filepath;
		}

		std::cout << std::endl;
	}
}