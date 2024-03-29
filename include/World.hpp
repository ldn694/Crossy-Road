#pragma once

#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "SceneNode.hpp"
#include "SpriteNode.hpp"
#include "Animal.hpp"
#include "Railways.hpp"
#include "River.hpp"
#include "SRoad.hpp"
#include "Land.hpp"
#include "CommandQueue.hpp"
#include "Command.hpp"
#include "Player.hpp"
#include "RoadList.hpp"
#include "Rain.hpp"
#include "Context.hpp"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

#include <array>
#include <queue>


// Forward declaration
namespace sf
{
	class RenderWindow;
}

class World : private sf::NonCopyable
{
	public:
		explicit							World(sf::RenderWindow& window, Context context, int numPlayer, std::vector <Animal::Type> playerTypes, std::vector <std::string> playerNames, Difficulty difficulty);
		void								update(sf::Time dt);
		void								draw();
		
		CommandQueue&						getCommandQueue();
		SceneNode&							getSceneGraph();
		SoundPlayer&						getSoundPlayer();

		int									getCurrentScore();
		void 								setRaining(bool raining);
		int 								getLostPlayerID(Entity* lostPlayer);


	private:
		void								loadTextures();
		void								loadSounds();
		void								buildScene();
		void								adaptPlayerPosition();
		void								adaptPlayerVelocity();


	private:
		enum Layer
		{
			Background,
			Road,
			Air,
			LayerCount
		};


	private:
		sf::RenderWindow&					mWindow;
		sf::View							mWorldView;
		TextureHolder						mTextures;
		SoundPlayer 						mSounds;
		Context								mContext;

		SceneNode							mSceneGraph;
		std::array<SceneNode*, LayerCount>	mSceneLayers;
		CommandQueue						mCommandQueue;

		sf::FloatRect						mWorldBounds;
		sf::Vector2f						mSpawnPosition;
		float								mScrollSpeed;
		RoadList*							mRoadList;
		Difficulty							mDifficulty;
		int 								mNumPlayer;
		std::vector <Animal*>				mPlayers;
		Animal*								lostPlayer;
		std::vector <std::string>			mPlayerNames;
		std::vector <Animal::Type>			mPlayerTypes;
		int									mCurrentScore;
		Rain								mRain;
		bool								isRaining;
		sf::Time 							mRainTimer;
		const sf::Time 						mRainPeriod = sf::seconds(10.f);
};
