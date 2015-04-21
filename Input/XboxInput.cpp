#include "XboxInput.h"

#if _DEBUG
	#include <StringUtil.h>
#endif

namespace Input
{
	DWORD XboxInput::packetNumber[XBOX_CONTROLLER_INDEX::MAX];

	bool XboxInput::IsConnected(XBOX_CONTROLLER_INDEX::INDEX _controllerIndex)
	{
	#if _DEBUG
		XboxInput::IsValidControllerIndex(_controllerIndex);
	#endif

		XINPUT_STATE state;
		DWORD result = XInputGetState(static_cast<DWORD>(_controllerIndex), &state);

		if(result == ERROR_SUCCESS)
		{
			packetNumber[static_cast<DWORD>(_controllerIndex)] = state.dwPacketNumber;

			return true;
		}

		return false;
	}

	void XboxInput::EnableInput()
	{
		XInputEnable(TRUE);
	}

	void XboxInput::DisableInput()
	{
		XInputEnable(FALSE);
	}

	XBOX_BATTERY_TYPE::TYPE XboxInput::GetBatteryStatus(XBOX_CONTROLLER_INDEX::INDEX _controllerIndex, BYTE _devType)
	{
	#if _DEBUG
		XboxInput::IsValidControllerIndex(_controllerIndex);
	#endif

		XINPUT_BATTERY_INFORMATION batteryInfo;
		XInputGetBatteryInformation(static_cast<DWORD>(_controllerIndex), _devType, &batteryInfo);
		return static_cast<XBOX_BATTERY_TYPE::TYPE>(batteryInfo.BatteryType);
	}

	XBOX_BATTERY_LIFE::STATUS XboxInput::GetBatteryLife(XBOX_CONTROLLER_INDEX::INDEX _controllerIndex, BYTE _devType)
	{
	#if _DEBUG
		XboxInput::IsValidControllerIndex(_controllerIndex);
	#endif

		XINPUT_BATTERY_INFORMATION batteryInfo;
		XInputGetBatteryInformation(static_cast<DWORD>(_controllerIndex), _devType, &batteryInfo);
		return static_cast<XBOX_BATTERY_LIFE::STATUS>(batteryInfo.BatteryLevel);
	}

	bool XboxInput::GetInput(XBOX_CONTROLLER_INDEX::INDEX _controllerIndex, XINPUT_GAMEPAD& _gamepad)
	{
	#if _DEBUG
		XboxInput::IsValidControllerIndex(_controllerIndex);
	#endif

		XINPUT_STATE controllerState;
		XINPUT_KEYSTROKE keystroke;

		DWORD result = XInputGetState(static_cast<DWORD>(_controllerIndex), &controllerState);
		XInputGetKeystroke(static_cast<DWORD>(_controllerIndex), 0, &keystroke);

		if(ERROR_SUCCESS == result && controllerState.dwPacketNumber != packetNumber[static_cast<DWORD>(_controllerIndex)])
		{
			packetNumber[static_cast<DWORD>(_controllerIndex)] = controllerState.dwPacketNumber;
			_gamepad = controllerState.Gamepad;
		}
		else if(ERROR_DEVICE_NOT_CONNECTED == result)
		{
			//TODO: Debug info
			return false;
		}

		return true;
	}

	void XboxInput::ReadGamepad(const XINPUT_GAMEPAD& _gamepad)
	{
		if(_gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
		{
		
		}

		if(_gamepad.wButtons & XINPUT_GAMEPAD_A)
		{

		}
		else
		{

		}
	}

	//TODO: Clean up and move into debug info class
	#if _DEBUG
	bool XboxInput::IsValidControllerIndex(XBOX_CONTROLLER_INDEX::INDEX _controllerIndex)
	{
		if(_controllerIndex >= XBOX_CONTROLLER_INDEX::ONE && _controllerIndex < XBOX_CONTROLLER_INDEX::MAX)
		{
			return true;
		}
		else
		{
			//TODO: Debug info 
			return false;
		}
	}

	const char* XboxInput::DebugOutputBatteryInformation(XBOX_CONTROLLER_INDEX::INDEX _controllerIndex, BYTE _devType)
	{
		XINPUT_BATTERY_INFORMATION batteryInfo;
		XInputGetBatteryInformation(static_cast<DWORD>(_controllerIndex), _devType, &batteryInfo);

		static Utility::String output = "Battery Status: ";

		switch(static_cast<XBOX_BATTERY_TYPE::TYPE>(batteryInfo.BatteryType))
		{
		case XBOX_BATTERY_TYPE::ALKALINE:
			{
				output += "ALKALINE";
			}
			break;

		case XBOX_BATTERY_TYPE::DISCONNECTED:
			{
				output += "DISCONNECTED";
			}
			break;

		case XBOX_BATTERY_TYPE::NIMH:
			{
				output += "NIMH";
			}
			break;

		case XBOX_BATTERY_TYPE::UNKNOWN:
			{
				output += "OUTPUT";
			}
			break;

		case XBOX_BATTERY_TYPE::WIRED:
			{
				output += "WIRED";
			}
			break;
		}

		output += "\tBattery Level: ";

		switch(static_cast<XBOX_BATTERY_LIFE::STATUS>(batteryInfo.BatteryLevel))
		{
		case XBOX_BATTERY_LIFE::EMPTY:
			{
				output += "EMPTY";
			}
			break;

		case XBOX_BATTERY_LIFE::FULL:
			{
				output += "FULL";
			}
			break;

		case XBOX_BATTERY_LIFE::LOW:
			{
				output += "LOW";
			}
			break;

		case XBOX_BATTERY_LIFE::MEDIUM:
			{
				output += "MEDIUM";
			}
			break;
		}

		output += "\n";

		return output.c_str();

	}
}

#endif