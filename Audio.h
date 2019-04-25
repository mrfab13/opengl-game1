#pragma once
#include <iostream>
#include <windows.h>
#include <fmod.hpp>


class Audio
{
	public:
		Audio();
		~Audio();
		bool AudioInit();
		void Create(const char* file, int sound);
		void playSound(int sound);
		void update();

	private:

		FMOD::System* audioSystem;
		FMOD::Sound* fxThump;
		FMOD::Sound* trackBackground;
};
