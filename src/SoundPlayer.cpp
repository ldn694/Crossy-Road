#include "SoundPlayer.hpp"

#include <SFML/Audio/Listener.hpp>

#include <cmath>


namespace
{
	// Sound coordinate system, point of view of a player in front of the screen:
	// X = left; Y = up; Z = back (out of the screen)
	const float ListenerZ = 0.f;
	const float Attenuation = 8.f;
	const float MinDistance2D = 200.f;
	const float MinDistance3D = std::sqrt(MinDistance2D*MinDistance2D + ListenerZ*ListenerZ);
}

SoundPlayer::SoundPlayer()
: mSoundBuffers()
, mSounds()
{
	mSoundBuffers.load(SoundEffect::Animal_Jump, "Assets/Sounds/animal_jump.wav");
    mSoundBuffers.load(SoundEffect::Water_Splash, "Assets/Sounds/water_splash.wav");
	mSoundBuffers.load(SoundEffect::Train_Incoming, "Assets/Sounds/train_incoming.wav");
	mSoundBuffers.load(SoundEffect::Train_Passing, "Assets/Sounds/train_passing.wav");

	// Listener points towards the screen (default in SFML)
	sf::Listener::setDirection(0.f, 0.f, -1.f);
}

void SoundPlayer::setVolume(float volume)
{
    mVolume = volume;
}

void SoundPlayer::stopAllSounds()
{
	for (auto& sound : mSounds)
	{
		sound.stop();
	}	
	// removeStoppedSounds();
}

sf::Sound& SoundPlayer::play(SoundEffect::ID effect)
{
	return play(effect, getListenerPosition());
}

sf::Sound& SoundPlayer::play(SoundEffect::ID effect, sf::Vector2f position)
{
	mSounds.push_back(sf::Sound());
	// std::cout << "sounds size: " << mSounds.size() << "\n";
	sf::Sound& sound = mSounds.back();

	sound.setBuffer(mSoundBuffers.get(effect));
	sound.setPosition(position.x, -position.y, 0.f);
	sound.setAttenuation(Attenuation);
	sound.setMinDistance(MinDistance3D);
    sound.setVolume(mVolume);

	sound.play();
	return sound;
}

void SoundPlayer::removeStoppedSounds()
{
	mSounds.remove_if([] (const sf::Sound& s)
	{
		return s.getStatus() == sf::Sound::Stopped;
	});
}

void SoundPlayer::setListenerPosition(sf::Vector2f position)
{
	sf::Listener::setPosition(position.x, -position.y, ListenerZ);
}

sf::Vector2f SoundPlayer::getListenerPosition() const
{
	sf::Vector3f position = sf::Listener::getPosition();
	return sf::Vector2f(position.x, -position.y);
}
