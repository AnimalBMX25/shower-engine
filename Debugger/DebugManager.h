#ifndef DEBUGMANAGER_H
#define DEBUGMANAGER_H

#include <map>
#include <StringUtil.h>
#include <Timer.h>

namespace Debugger
{
	enum DEBUG_LEVEL {DEBUG_NONE, DEBUG_INFO = 1, DEBUG_WARNING = 2 , DEBUG_ERROR = 4, DEBUG_ALL = 7};

	class DebugManager
	{
	public:
		static void Init();
		static bool CanOutput(Utility::String _channel, DEBUG_LEVEL _debugLevel);
		static double GetTimestamp() {return timestamp.GetElapsedTime();}

	private:
		static void ReadSettingsFile(const char* _filepath);
		static char DebugLevelBitfield(Utility::String _bitfield);

		static std::map<Utility::String, char> channels;
		static Utility::Timer timestamp;
	};
}

#endif