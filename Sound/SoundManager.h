#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "SoundEffect.h"

namespace Sound
{
	class SoundManager
	{
	public:
		static bool Init();
		static bool Play();
		static void Cleanup();
		static SoundEffect testEffect;

	private:
		static IXAudio2MasteringVoice* masterVoice;
		static IXAudio2* audioEngine;

		static unsigned int GetPreferredDevice();

	};
}

#endif