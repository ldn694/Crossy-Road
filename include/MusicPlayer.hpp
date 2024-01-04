#pragma once

#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/Audio/Music.hpp>

#include <map>
#include <string>
#include <vector>

const bool NO_LOOP = false;
const bool WITH_LOOP = true;

class MusicPlayer
{
	public:
									MusicPlayer();

		void						play(Music::ID theme, bool loop = true);
		void						stop(Music::ID theme);
		
		void						stopAllMusic();
		sf::Music::Status			getStatus(Music::ID theme);

		void						setPaused(Music::ID theme, bool paused);
		void						setVolume(float volume);


	private:
		std::vector <std::unique_ptr<sf::Music>>			mMusic;
		std::map<Music::ID, std::string>					mFilenames;
		float												mVolume;
};