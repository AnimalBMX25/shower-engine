#ifndef DEBUGMANAGER_H
#define DEBUGMANAGER_H

#include <map>
#include <bitset>
#include <StringUtil.h>
#include <Timer.h>

namespace Debugger
{
	enum DEBUG_LEVEL {DEBUG_INFO = 0, DEBUG_WARNING = 1 , DEBUG_ERROR = 2, DEBUG_BITCOUNT = 3};

	class DebugManager
	{
	public:
		static void Init();
		static bool CanOutput(Utility::String _channel, DEBUG_LEVEL _debugLevel);
		static double GetTimestamp() {return timestamp.GetElapsedTime();}

	private:
		static void ReadSettingsFile(const char* _filepath);

		static std::map<Utility::String, std::bitset<DEBUG_BITCOUNT>> channels;
		static Utility::Timer timestamp;
	};
}

#endif