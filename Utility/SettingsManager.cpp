#include "SettingsManager.h"
#include <iostream>
#include <fstream>

namespace Utility
{
	std::map<String, String> SettingsManager::settingsFiles;

	void SettingsManager::Init()
	{
		ReadSettingsFile("..\\Data\\Settings\\global_settings_files.txt");
	}

	void SettingsManager::ReadSettingsFile(const char* _filename)
	{
		std::ifstream ifstream;
		String directory;
		ifstream.open(_filename, std::ios_base::in);

		if(!ifstream.is_open())
		{
			return;
		}

		while(!ifstream.eof())
		{		
			char buffer[READ_BUFFER_SIZE] = {0};
			ifstream.getline(buffer, READ_BUFFER_SIZE, '\t');
			String name = buffer;

			ifstream.getline(buffer, READ_BUFFER_SIZE, '\n');
			String filepath = directory + buffer;

			settingsFiles[name.c_str()] = filepath;
		}
	}
}