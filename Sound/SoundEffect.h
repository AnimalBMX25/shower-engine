#ifndef SOUNDEFFECT_H
#define SOUNDEFFECT_H

#include <XAudio2.h>

#ifdef _XBOX //Big-Endian
#define fourccRIFF 'RIFF'
#define fourccDATA 'data'
#define fourccFMT 'fmt '
#define fourccWAVE 'WAVE'
#define fourccXWMA 'XWMA'
#define fourccDPDS 'dpds'
#endif

#ifndef _XBOX //Little-Endian
#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'
#endif

namespace Sound
{
	class SoundEffect
	{
	public:
		SoundEffect(TCHAR* _filename);
		~SoundEffect();

		void Cleanup();
		void Play(IXAudio2* _audioEngine);

	private:
		WAVEFORMATEXTENSIBLE waveFormatExtensible;
		XAUDIO2_BUFFER xAudioBuffer;
		IXAudio2SourceVoice* sourceVoice;

		HRESULT FindChunk(HANDLE hFile, DWORD fourcc, DWORD & dwChunkSize, DWORD & dwChunkDataPosition);
		HRESULT ReadChunkData(HANDLE hFile, void * buffer, DWORD buffersize, DWORD bufferoffset);
	};
}

#endif