#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include "StringUtil.h"
#include <map>

namespace Utility
{
	enum Settings{READ_BUFFER_SIZE = 128};

	class SettingsManager
	{
	public:
		static void Init(const char* _filepath = "..\\Data\\Settings\\global_settings_files.txt");
		static void Refresh(const char* _filepath = "..\\Data\\Settings\\global_settings_files.txt");		
		static void SaveSettings(unsigned int _flags);
		static const char* GetSettingsFilepath(const char* _settingsName);

	private:
		static std::map<String, String> settingsFiles;
		static void ReadSettingsFile(const char* _filepath);
		static bool initialized;
	};
}

#endif