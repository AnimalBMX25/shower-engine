#include "SoundManager.h"
#include "AudioDeviceManager.h"

namespace Sound
{
	SoundEffect					SoundManager::testEffect(L"../Assets/Sound/affirmative.wav");
	IXAudio2MasteringVoice*		SoundManager::masterVoice(nullptr);
	IXAudio2*					SoundManager::audioEngine(nullptr);

	bool SoundManager::Init()
	{
		CoInitialize(nullptr);
		HRESULT hr;

		if (FAILED(hr = XAudio2Create(&audioEngine, XAUDIO2_DEBUG_ENGINE, XAUDIO2_DEFAULT_PROCESSOR )))
		{
			return false;
		}

		DeviceManager::Init(audioEngine);

		if (FAILED(hr = audioEngine->CreateMasteringVoice(&masterVoice, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, GetPreferredDevice(), NULL)))
		{
			return false;
		}

		return true;
	}

	void SoundManager::Cleanup()
	{
		testEffect.Cleanup();

		if(masterVoice)
		{
			masterVoice->DestroyVoice();
			masterVoice = nullptr;
		}

		if(audioEngine)
		{
			audioEngine->Release();
			audioEngine = nullptr;
		}

		CoUninitialize();
	}

	bool SoundManager::Play()
	{
		testEffect.Play(audioEngine);

		return true;
	}

	unsigned int SoundManager::GetPreferredDevice()
	{
		unsigned int deviceCount = 0;
		audioEngine->GetDeviceCount(&deviceCount);

		XAUDIO2_DEVICE_DETAILS deviceDetails;

		for(unsigned int i = 0; i < deviceCount; ++i)
		{
			audioEngine->GetDeviceDetails(i, &deviceDetails);

			if(GlobalDefaultDevice == deviceDetails.Role)
			{
				return i;
			}
		}

		return 0;
	}
}