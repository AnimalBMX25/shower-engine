#include "AudioDeviceManager.h"

namespace Sound
{
	vector<XAUDIO2_DEVICE_DETAILS>	DeviceManager::audioDevices;
	int								DeviceManager::currentDevice;

	bool DeviceManager::Init(IXAudio2* _audioEngine)
	{
		currentDevice = NO_DEVICE;

		unsigned int deviceCount = 0;
		_audioEngine->GetDeviceCount(&deviceCount);
		audioDevices.reserve(deviceCount);

		for(unsigned int i = 0; i < deviceCount; ++i)
		{
			XAUDIO2_DEVICE_DETAILS deviceDetails;
			_audioEngine->GetDeviceDetails(i, &deviceDetails);
			audioDevices.push_back(deviceDetails);
		}

		ChooseDefaultDevice();

		return true;
	}


	void DeviceManager::ChooseDefaultDevice()
	{
		for(unsigned int i = 0; i < audioDevices.size(); ++i)
		{
			if(GlobalDefaultDevice == audioDevices[i].Role)
			{
				currentDevice = static_cast<int>(i);
			}
		}
	}

#if _DEBUG
	void DeviceManager::OutputDeviceDetails()
	{

	}

#endif
}