#include "SoundPlayer.hpp"

#include <SFML/Audio/Listener.hpp>

#include <cmath>

namespace
{
	// Sound coordinate system, point of view of a player in front of the screen:
	// X = left; Y = up; Z = back (out of the screen)
	const float ListenerZ = 50.f;
	const float Attenuation = 15.f;
	const float MinDistance2D = 100.f;
	const float MinDistance3D = std::sqrt(MinDistance2D * MinDistance2D + ListenerZ * ListenerZ);
}

SoundPlayer::SoundPlayer() :
	mSoundBuffers()
	, mSounds()
	, mVolume(100.f)
{
	// Listener points towards the screen (default in SFML)
	// sf::Listener::setDirection(0.f, 0.f, -1.f);
}

void SoundPlayer::load(SoundEffect::ID effect, const std::string& filename)
{
	mSoundBuffers.load(effect, filename);
}

void SoundPlayer::setVolume(float volume)
{
	volume = std::max(0.f, std::min(100.f, volume));
	mVolume = volume;
}

float SoundPlayer::getVolume() const
{
	return mVolume;
}

void SoundPlayer::stopAllSounds()
{
	for (auto& sound : mSounds)
	{
		sound.stop();
	}
	removeStoppedSounds();
}

void SoundPlayer::pauseAllSounds()
{
	for (auto& sound : mSounds)
	{
		if (sound.getStatus() == sf::Sound::Playing)
			sound.pause();
	}
}

void SoundPlayer::playAllSounds()
{
	for (auto& sound : mSounds)
	{
		if (sound.getStatus() == sf::Sound::Paused)
			sound.play();
	}
}

sf::Sound& SoundPlayer::play(SoundEffect::ID effect, float volumePercentage)
{
	return play(effect, getListenerPosition(), volumePercentage);
}

sf::Sound& SoundPlayer::play(SoundEffect::ID effect, sf::Vector2f position, float volumePercentage)
{
	mSounds.push_back(sf::Sound());
	// std::cout << "sounds size: " << mSounds.size() << "\n";
	sf::Sound& sound = mSounds.back();

	sound.setBuffer(mSoundBuffers.get(effect));
	sound.setPosition(position.x, -position.y, 0.f);
	sound.setAttenuation(Attenuation);
	sound.setMinDistance(MinDistance3D);
	sound.setVolume(mVolume * volumePercentage);

	sound.play();
	return sound;
}

void SoundPlayer::removeStoppedSounds()
{
	mSounds.remove_if([](const sf::Sound& s)
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

void SoundPlayer::setPosition(sf::Sound& sound, sf::Vector2f position)
{
	sound.setPosition(position.x, -position.y, 0.f);
}