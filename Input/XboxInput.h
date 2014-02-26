#ifndef XBOX_INPUT_H
#define XBOX_INPUT_H

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
#include <XInput.h> 
#pragma comment(lib,"xinput.lib") 

namespace Input
{
	namespace XBOX_CONTROLLER_INDEX
	{
		enum INDEX { ONE = 0, TWO, THREE, FOUR, MAX };
	}

	namespace XBOX_BATTERY_TYPE
	{
		enum TYPE { DISCONNECTED = BATTERY_TYPE_DISCONNECTED, 
			WIRED = BATTERY_TYPE_WIRED, 
			ALKALINE = BATTERY_TYPE_ALKALINE, 
			NIMH = BATTERY_TYPE_NIMH, 
			UNKNOWN = BATTERY_TYPE_UNKNOWN };
	}
	
	namespace XBOX_BATTERY_LIFE
	{
		enum STATUS { EMPTY = BATTERY_LEVEL_EMPTY, 
			LOW = BATTERY_LEVEL_LOW, 
			MEDIUM = BATTERY_LEVEL_MEDIUM, 
			FULL = BATTERY_LEVEL_FULL };
	}

	namespace XBOX_BUTTON
	{
		enum BUTTON {DPAD_UP = XINPUT_GAMEPAD_DPAD_UP, 
			DPAD_DOWN = XINPUT_GAMEPAD_DPAD_DOWN, 
			DPAD_LEFT = XINPUT_GAMEPAD_DPAD_LEFT, 
			DPAD_RIGHT = XINPUT_GAMEPAD_DPAD_RIGHT,
			START = XINPUT_GAMEPAD_START, 
			BACK = XINPUT_GAMEPAD_BACK, 
			LEFT_THUMBSTICK = XINPUT_GAMEPAD_LEFT_THUMB, 
			RIGHT_THUMBSTICK = XINPUT_GAMEPAD_RIGHT_THUMB,
			LEFT_SHOULDER = XINPUT_GAMEPAD_LEFT_SHOULDER, 
			RIGHT_SHOULDER = XINPUT_GAMEPAD_RIGHT_SHOULDER, 
			A = XINPUT_GAMEPAD_A, 
			B = XINPUT_GAMEPAD_B,  
			X = XINPUT_GAMEPAD_X,
			Y = XINPUT_GAMEPAD_Y};
	}

	class XboxInput
	{
	public:
		static void DisableInput();
		static void EnableInput();

		static XBOX_BATTERY_TYPE::TYPE GetBatteryStatus(XBOX_CONTROLLER_INDEX::INDEX _controllerIndex, BYTE _devType = BATTERY_DEVTYPE_GAMEPAD);
		static XBOX_BATTERY_LIFE::STATUS GetBatteryLife(XBOX_CONTROLLER_INDEX::INDEX _controllerIndex, BYTE _devType = BATTERY_DEVTYPE_GAMEPAD);

		static bool IsConnected(XBOX_CONTROLLER_INDEX::INDEX _controllerIndex);
		
		static bool GetInput(XBOX_CONTROLLER_INDEX::INDEX _controllerIndex, XINPUT_GAMEPAD& _gamepad);


#if  _DEBUG
		static const char* DebugOutputBatteryInformation(XBOX_CONTROLLER_INDEX::INDEX _controllerIndex, BYTE _devType  = BATTERY_DEVTYPE_GAMEPAD);
		static bool IsValidControllerIndex(XBOX_CONTROLLER_INDEX::INDEX _controllerIndex);
#endif

	private:
		static DWORD packetNumber[XBOX_CONTROLLER_INDEX::MAX];

		static void ReadGamepad(const XINPUT_GAMEPAD& _gamepad);
	};
}

#endif