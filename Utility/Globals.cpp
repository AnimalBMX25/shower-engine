#include "Globals.h"
#include <iostream>
#include <fstream>

namespace Globals
{
	//DEBUGGER
	unsigned int	DEBUGGER::MAX_LINES = 100;

	//GlobalsManager
	std::vector<std::string> GlobalsManager::globalSettingsFiles;

	void GlobalsManager::Init()
	{
		globalSettingsFiles.reserve(GLOBAL_SETTINGS_FILELIST_DEFAULT_SIZE);
	}

	void GlobalsManager::SetGlobals(const char* _filename)
	{
		SetGlobalSettingsFiles(_filename);

		for(unsigned int i = 0; i < globalSettingsFiles.size(); ++i)
		{
			ParseSettingsFile(globalSettingsFiles[i].c_str());
		}
	}

	void GlobalsManager::SetGlobalSettingsFiles(const char* _filename)
	{
		std::ifstream ifstream;
		std::string directory;
		ifstream.open(_filename, std::ios_base::in);

		if(!ifstream.is_open())
		{
			return;
		}

		directory = FindDirectory(_filename);

		while(!ifstream.eof())
		{			
			char file[READ_BUFFER_SIZE] = {0};
			ifstream.getline(file, READ_BUFFER_SIZE, '\n');
			
			std::string str = directory + file;
			globalSettingsFiles.push_back(str);
		}
	}

	void GlobalsManager::ParseSettingsFile(const char* _filename)
	{

	}

	std::string GlobalsManager::FindDirectory(const char* _filename)
	{
		unsigned int lengthOfDirectory = 0;
		char directory[READ_BUFFER_SIZE] = {0};

		for(unsigned int i = 0; static_cast<char>(*(_filename + i)) != '\0'; i++)
		{
			if(static_cast<char>(*(_filename + i)) == '/') 
			{
				lengthOfDirectory = i + 1; 
			}
		}

		memcpy(directory, _filename, lengthOfDirectory);

		return std::string(directory);
	}
}