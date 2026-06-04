//#pragma once
//
//#include <string>
//#include <vector>
//#include <SDL3/SDL.h>
//#include <SDL3_mixer/SDL_mixer.h>
//
//struct AudioEntry {
//	std::string path;
//	auto sound = nullptr;
//	int refcount = 0;
//};
//
//class AudioManager {
//	std::vector<AudioEntry> audio_list;
//	// Что-то еще, связанное с миксером
//public:
//	void Init(...);
//	void FreeAudio(const std::string& path);
//};
//
//extern AudioManager g_AudioManager;