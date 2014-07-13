#ifndef GLOBALS_H
#define GLOBALS_H

#include <vector>
#include <string>

namespace Globals
{
	enum Settings{READ_BUFFER_SIZE = 128, GLOBAL_SETTINGS_FILELIST_DEFAULT_SIZE = 64};

	struct DEBUGGER
	{
		static unsigned int MAX_LINES;

	};

	//TODO:
	//Setup typedef for vector of parser functions

	class GlobalsManager
	{
	public:
		static void Init();
		static void SetGlobals(const char* _filename);
		static void SaveGlobalSettings(unsigned int _flags);

	private:
		static std::vector<std::string> globalSettingsFiles;

		static void SetGlobalSettingsFiles(const char* _filename);
		static void ParseSettingsFile(const char* _filename);
		static std::string FindDirectory(const char* _filename); 

	};
}

#endif