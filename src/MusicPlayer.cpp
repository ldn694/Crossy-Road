#include "MusicPlayer.hpp"


MusicPlayer::MusicPlayer()
    : mMusic()
    , mFilenames()
    , mVolume(100.f)
{
    mFilenames[Music::TitleTheme] = "Assets/Music/TitleTheme.mp3";
    mFilenames[Music::MenuTheme] = "Assets/Music/MenuTheme.mp3";
    mFilenames[Music::IngameTheme] = "Assets/Music/IngameTheme.mp3";
    mFilenames[Music::GameOverTheme] = "Assets/Music/GameOverTheme.mp3";
    mFilenames[Music::CountDown] = "Assets/Music/CountDown.mp3";
    for (std::size_t i = 0; i < Music::NumMusic; ++i) {
        Music::ID theme = static_cast<Music::ID>(i);
        std::string filename = mFilenames[theme];
        mMusic.push_back(std::make_unique<sf::Music>());
        if (!mMusic.back()->openFromFile(filename))
            throw std::runtime_error("Music " + filename + " could not be loaded.");
        mMusic.back()->setRelativeToListener(true);
    }
}

void MusicPlayer::play(Music::ID theme, bool loop)
{
    mMusic[theme]->setVolume(mVolume);
    mMusic[theme]->setLoop(loop);
    mMusic[theme]->stop();
    mMusic[theme]->play();
}

void MusicPlayer::stop(Music::ID theme)
{
    mMusic[theme]->stop();
}

void MusicPlayer::stopAllMusic()
{
    for (auto& music : mMusic)
    {
        music->stop();
    }
}

sf::Music::Status MusicPlayer::getStatus(Music::ID theme)
{
    return mMusic[theme]->getStatus();
}

void MusicPlayer::setVolume(float volume)
{
    mVolume = volume;
    for (auto& music : mMusic)
    {
        music->setVolume(mVolume);
    }
}

void MusicPlayer::setPaused(Music::ID theme, bool paused)
{
    if (paused)
        mMusic[theme]->pause();
    else
        mMusic[theme]->play();
}
