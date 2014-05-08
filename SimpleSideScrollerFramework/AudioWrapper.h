
#include "stdafx.h"
#include <windows.h>
#include <xaudio2.h>
#include <strsafe.h>
#include <shellapi.h>
#include <mmsystem.h>
#include <conio.h>
#include "SDKwavefile.h"




class AudioWrapper
{
public:
	AudioWrapper();
	~AudioWrapper();
	void playSound(wstring fileName, bool loop);
	bool audioStillPlaying();
	void stopAllAudio();
	void stopLoopingAudio();
	
	
private:
	
	static const int NUM_VOICES = 30;

	IXAudio2* audioEngine;
	IXAudio2SourceVoice* sourceVoices[NUM_VOICES];
	vector<int> loopingVoices;
	map<int, BYTE*> memoryFix;
	IXAudio2MasteringVoice* masterVoice;

	int playPCM(IXAudio2* audioEngine, WCHAR *path, bool infiniteLoop);

	int initAudio();

};