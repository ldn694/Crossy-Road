#ifndef BOOK_SOUNDPLAYER_HPP
#define BOOK_SOUNDPLAYER_HPP

#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

#include <list>


class SoundPlayer : private sf::NonCopyable
{
	public:
									SoundPlayer();

		void 						load(SoundEffect::ID effect, const std::string& filename);

		sf::Sound&					play(SoundEffect::ID effect);
		sf::Sound&					play(SoundEffect::ID effect, sf::Vector2f position);

		void 						stopAllSounds();
		void						pauseAllSounds();
		void						playAllSounds();

		void                        setVolume(float volume);
		float					    getVolume() const;
        void						removeStoppedSounds();
		void						setListenerPosition(sf::Vector2f position);
		sf::Vector2f				getListenerPosition() const;
		void 						setPosition(sf::Sound& sound, sf::Vector2f position);


	private:
        float                       mVolume;
		SoundBufferHolder			mSoundBuffers;
		std::list<sf::Sound>		mSounds;
};

#endif // BOOK_SOUNDPLAYER_HPP
