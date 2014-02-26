#ifndef AUDIODEVICEMANAGER_H
#define AUDIODEVICEMANAGER_H

#include <XAudio2.h>
#include <vector>
using std::vector;

#define NO_DEVICE -1

namespace Sound
{
	class DeviceManager
	{
	public:	
		static int currentDevice;

		static bool Init(IXAudio2* _audioEngine);

	private:
		static vector<XAUDIO2_DEVICE_DETAILS> audioDevices;

		static void ChooseDefaultDevice();
#if _DEBUG
		static void OutputDeviceDetails();
#endif
	};
}

#endif