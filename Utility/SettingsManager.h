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
		static void Init();
		static void ReadSettingsFile(const char* _filename);
		static void SaveSettings(unsigned int _flags);
		static const char* GetSettingsFilepath(const char* _settingsName);

	private:
		static std::map<String, String> settingsFiles;
		static void ParseSettingsFile(const char* _filename);
	};
}

#endif