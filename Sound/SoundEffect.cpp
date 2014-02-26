#include "SoundEffect.h"

namespace Sound
{
	SoundEffect::SoundEffect(TCHAR* _filename) : sourceVoice(nullptr)
	{
		memset(&waveFormatExtensible, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&xAudioBuffer, 0, sizeof(XAUDIO2_BUFFER));

		HRESULT hr;		

		HANDLE hFile = CreateFile(_filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

		if( INVALID_HANDLE_VALUE == hFile)
		{
			hr = HRESULT_FROM_WIN32( GetLastError());
			return;
		}

		if( INVALID_SET_FILE_POINTER == SetFilePointer( hFile, 0, NULL, FILE_BEGIN ))
		{
			hr = HRESULT_FROM_WIN32( GetLastError());
			return;
		}

		DWORD dwChunkSize;
		DWORD dwChunkPosition;

		FindChunk(hFile,fourccRIFF,dwChunkSize, dwChunkPosition);
		DWORD filetype;
		ReadChunkData(hFile,&filetype,sizeof(DWORD),dwChunkPosition);
		if (filetype != fourccWAVE)
		{
			//error
			return;
		}

		FindChunk(hFile,fourccFMT, dwChunkSize, dwChunkPosition);
		ReadChunkData(hFile, &waveFormatExtensible, dwChunkSize, dwChunkPosition);

		FindChunk(hFile,fourccDATA,dwChunkSize, dwChunkPosition );
		BYTE * pDataBuffer = new BYTE[dwChunkSize];
		ReadChunkData(hFile, pDataBuffer, dwChunkSize, dwChunkPosition);

		xAudioBuffer.AudioBytes = dwChunkSize;
		xAudioBuffer.pAudioData = pDataBuffer;
		xAudioBuffer.Flags = XAUDIO2_END_OF_STREAM;
	}

	SoundEffect::~SoundEffect()
	{
		Cleanup();
	}

	void SoundEffect::Cleanup()
	{
		if(sourceVoice)
		{
			sourceVoice->DestroyVoice();
			sourceVoice = nullptr;
		}
	}

	void SoundEffect::Play(IXAudio2* _audioEngine)
	{
		HRESULT hr;
		if(FAILED(hr = _audioEngine->CreateSourceVoice(&sourceVoice, (WAVEFORMATEX*)&waveFormatExtensible))) 
		{
			//FAILED
			return;
		}

		if(FAILED(hr = sourceVoice->SubmitSourceBuffer(&xAudioBuffer)))
		{
			//FAILED
			return;
		}

		if(FAILED(hr = sourceVoice->Start(0)))
		{
			//FAILED
			return;
		}
	}

	HRESULT SoundEffect::FindChunk(HANDLE hFile, DWORD fourcc, DWORD & dwChunkSize, DWORD & dwChunkDataPosition)
	{
		HRESULT hr = S_OK;
		if( INVALID_SET_FILE_POINTER == SetFilePointer( hFile, 0, NULL, FILE_BEGIN ))
		{
			return HRESULT_FROM_WIN32( GetLastError());
		}

		DWORD dwChunkType;
		DWORD dwChunkDataSize;
		DWORD dwRIFFDataSize = 0;
		DWORD dwFileType;
		DWORD bytesRead = 0;
		DWORD dwOffset = 0;

		while (hr == S_OK)
		{
			DWORD dwRead;
			if( 0 == ReadFile( hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL ))
			{
				hr = HRESULT_FROM_WIN32( GetLastError());
			}

			if( 0 == ReadFile( hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL ))
			{
				hr = HRESULT_FROM_WIN32( GetLastError());
			}

			switch (dwChunkType)
			{
			case fourccRIFF:
				dwRIFFDataSize = dwChunkDataSize;
				dwChunkDataSize = 4;
				if( 0 == ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL))
				{
					hr = HRESULT_FROM_WIN32( GetLastError());
				}
				break;

			default:
				if(INVALID_SET_FILE_POINTER == SetFilePointer( hFile, dwChunkDataSize, NULL, FILE_CURRENT))
				{
					return HRESULT_FROM_WIN32(GetLastError()); 
				}
			}

			dwOffset += sizeof(DWORD) * 2;

			if (dwChunkType == fourcc)
			{
				dwChunkSize = dwChunkDataSize;
				dwChunkDataPosition = dwOffset;
				return S_OK;
			}

			dwOffset += dwChunkDataSize;

			if (bytesRead >= dwRIFFDataSize) 
			{
				return S_FALSE;
			}
		}

		return S_OK;
	}

	HRESULT SoundEffect::ReadChunkData(HANDLE hFile, void * buffer, DWORD buffersize, DWORD bufferoffset)
	{
		HRESULT hr = S_OK;
		if(INVALID_SET_FILE_POINTER == SetFilePointer(hFile, bufferoffset, NULL, FILE_BEGIN))
		{
			return HRESULT_FROM_WIN32(GetLastError());
		}

		DWORD dwRead;
		if(0 == ReadFile(hFile, buffer, buffersize, &dwRead, NULL))
		{
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		return hr;
	}
}