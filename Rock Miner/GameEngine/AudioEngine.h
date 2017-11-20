#pragma once
#include <SDL_Mixer.h>

#include <string>
#include <map>

namespace SPH {

	class SoundEffect {
	public:
		friend class AudioEngine; // Allows AudioEngine to use SoundEffects private variables

		void play(int loops = 0);
	private:
		Mix_Chunk* _chuck = nullptr;
	};

	class Music {
	public:
		friend class AudioEngine;

		void play(int loops = 1);

		static void pause();
		static void stop();
		static void resume();
	private:
		Mix_Music* _music = nullptr;
	};

	class AudioEngine
	{
	public:
		AudioEngine();
		~AudioEngine();

		void init();
		void destroy();

		SoundEffect loadSoundEffect(const std::string& filePath);
		Music loadMusic(const std::string& filePath);

	private:
		bool _isInit = false;
		std::map<std::string, Mix_Chunk*> _effectMap;
		std::map<std::string, Mix_Music*> _musicMap;
	};

}