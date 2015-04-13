#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <map>
#include <string>

namespace Utility
{
	enum Settings{READ_BUFFER_SIZE = 128};

	class SettingsManager
	{
	public:
		static void Init();
		static void ReadSettingsFile(const char* _filename);
		static void SaveSettings(unsigned int _flags);
		static const char* GetSettingsFilepath(const char* _settingsName) {return settingsFiles[_settingsName].c_str();}

	private:
		static std::map<std::string, std::string> settingsFiles;
		static void ParseSettingsFile(const char* _filename);
	};
}

#endif