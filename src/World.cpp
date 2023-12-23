#include "World.hpp"
#include "GameStatus.hpp"
#include "AirEntity.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <algorithm>
#include <cmath>


SceneNode& World::getSceneGraph()
{
	return mSceneGraph;
}

World::World(sf::RenderWindow& window, Animal::Type playerType, std::string playerName, Difficulty difficulty)
	: mWindow(window)
	, mWorldView(window.getDefaultView())
	, mTextures()
	, mSceneGraph()
	, mSceneLayers()
	, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, mWorldView.getSize().y)
	, mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f)
	//, mScrollSpeed(-50.f)
	, mScrollSpeed(0.f)
	, mPlayerAnimal(nullptr)
	, mDifficulty(difficulty)
	, mPlayerName(playerName)
	, mPlayerType(playerType)
{
	loadTextures();
	buildScene();

	// Prepare the view
	mWorldView.setCenter(mSpawnPosition);
	// mWorldView.setRotation(45);
	// mWorldView.move(200, 0);
}

void World::update(sf::Time dt)
{
	// std::cerr << "num scenenode: " << mSceneGraph.countChildren() << "\n";
	//std::cerr << (mSceneGraph.findChildrenByCategory<Entity>(Category::Player)).size();
	// Scroll the world, reset player velocity
	mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());
	mPlayerAnimal->setVelocity(0.f, 0.f);

	// Forward commands to scene graph, adapt velocity (scrolling, diagonal correction)
	while (!mCommandQueue.isEmpty())
		mSceneGraph.onCommand(mCommandQueue.pop(), dt);
	adaptPlayerVelocity();
	// Regular update step, adapt position (correct if outside view)
	mSceneGraph.update(dt);
	adaptPlayerPosition();
}

void World::draw()
{
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
}

CommandQueue& World::getCommandQueue()
{
	return mCommandQueue;
}

void World::loadTextures()
{
	mTextures.load(Textures::CatDown, "Assets/Images/ForGame/character/cat/front/front0.png");
	mTextures.load(Textures::CatUp, "Assets/Images/ForGame/character/cat/back/back0.png");
	mTextures.load(Textures::CatLeft, "Assets/Images/ForGame/character/cat/left/left0.png");
	mTextures.load(Textures::CatRight, "Assets/Images/ForGame/character/cat/right/right0.png");
	mTextures.load(Textures::ChickenDown, "Assets/Images/ForGame/character/chicken/front/front0.png");
	mTextures.load(Textures::ChickenUp, "Assets/Images/ForGame/character/chicken/back/back0.png");
	mTextures.load(Textures::ChickenLeft, "Assets/Images/ForGame/character/chicken/left/left0.png");
	mTextures.load(Textures::ChickenRight, "Assets/Images/ForGame/character/chicken/right/right0.png");
	mTextures.load(Textures::LionDown, "Assets/Images/ForGame/character/lion/front.png");
	mTextures.load(Textures::LionUp, "Assets/Images/ForGame/character/lion/back.png");
	mTextures.load(Textures::LionLeft, "Assets/Images/ForGame/character/lion/left.png");
	mTextures.load(Textures::LionRight, "Assets/Images/ForGame/character/lion/right.png");
	mTextures.load(Textures::PigDown, "Assets/Images/ForGame/character/pig/front.png");
	mTextures.load(Textures::PigUp, "Assets/Images/ForGame/character/pig/back.png");
	mTextures.load(Textures::PigLeft, "Assets/Images/ForGame/character/pig/left.png");
	mTextures.load(Textures::PigRight, "Assets/Images/ForGame/character/pig/right.png");
	mTextures.load(Textures::FoxDown, "Assets/Images/ForGame/character/fox/front.png");
	mTextures.load(Textures::FoxUp, "Assets/Images/ForGame/character/fox/back.png");
	mTextures.load(Textures::FoxLeft, "Assets/Images/ForGame/character/fox/left.png");
	mTextures.load(Textures::FoxRight, "Assets/Images/ForGame/character/fox/right.png");
	mTextures.load(Textures::Eagle, "Assets/Images/Eagle.png");
	mTextures.load(Textures::Raptor, "Assets/Images/Raptor.png");
	mTextures.load(Textures::Desert, "Assets/Images/Desert.png");
	mTextures.load(Textures::Railways, "Assets/Images/Railways.png");
	mTextures.load(Textures::RiverLeftToRight, "Assets/Images/ForGame/river_log/river0.png");
	mTextures.load(Textures::RiverRightToLeft, "Assets/Images/ForGame/river_log/river1.png");
	mTextures.load(Textures::SRoad_Default, "Assets/Images/ForGame/road_car/default.png");
	mTextures.load(Textures::SRoad_Line, "Assets/Images/ForGame/road_car/line.png");
	mTextures.load(Textures::SRoad_Stripe, "Assets/Images/ForGame/road_car/stripe.png");
	mTextures.load(Textures::BlueCarLeft, "Assets/Images/ForGame/road_car/blue_left.png");
	mTextures.load(Textures::BlueCarRight, "Assets/Images/ForGame/road_car/blue_right.png");
	mTextures.load(Textures::RedCarLeft, "Assets/Images/ForGame/road_car/red_left.png");
	mTextures.load(Textures::RedCarRight, "Assets/Images/ForGame/road_car/red_right.png");
	mTextures.load(Textures::StartLand, "Assets/Images/ForGame/sidewalk_stuff/sidewalk_light_shadow.png");
	mTextures.load(Textures::NormalLand, "Assets/Images/ForGame/sidewalk_stuff/sidewalk_light.png");
	mTextures.load(Textures::Rock1, "Assets/Images/ForGame/sidewalk_stuff/rock.png");
	mTextures.load(Textures::SmallTree, "Assets/Images/ForGame/sidewalk_stuff/tree_small.png");
	mTextures.load(Textures::MediumTree, "Assets/Images/ForGame/sidewalk_stuff/tree_medium.png");
	mTextures.load(Textures::BigTree, "Assets/Images/ForGame/sidewalk_stuff/tree_big.png");
	mTextures.load(Textures::BigLog, "Assets/Images/ForGame/river_log/log_big.png");
	mTextures.load(Textures::SmallLog, "Assets/Images/ForGame/river_log/log_small.png");
	mTextures.load(Textures::Lily, "Assets/Images/ForGame/river_log/lily.png");
}

void World::buildScene()
{
	// Initialize the different layers
	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = layer.get();

		//mSceneGraph.attachChild(std::move(layer));
		mSceneGraph.requestAttach(std::move(layer));
	}

	// Prepare the tiled background
	sf::Texture& texture = mTextures.get(Textures::Desert);
	sf::IntRect textureRect(mWorldBounds);
	texture.setRepeated(true);

	// // Add the background sprite to the scene
	// std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	// backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
	// //mSceneLayers[Background]->attachChild(std::move(backgroundSprite));
	// mSceneLayers[Background]->requestAttach(std::move(backgroundSprite));

	std::unique_ptr<Entity> airEntity(new AirEntity());
	SceneNode* airNode = airEntity.get();
	mSceneLayers[Air]->requestAttach(std::move(airEntity));

	mPlayerAnimal = new Animal(mPlayerType, mTextures, airNode);
	mPlayerAnimal->setPosition(0, 0);

	std::unique_ptr<RoadList> roadList(new RoadList(mTextures, mWorldView, 12, mPlayerAnimal, mDifficulty));
	roadList->setPosition(0, mWorldView.getSize().y - 50);
	mRoadList = roadList.get();
	mSceneLayers[Road]->requestAttach(std::move(roadList));



	// std::unique_ptr<Aircraft> leftEscort(new Aircraft(Aircraft::AllyRaptor, mTextures));
	// // leftEscort->setPosition(-80.f, 50.f);
	// // mPlayerAircraft->attachChild(std::move(leftEscort));	
	// leftEscort->setPosition(mSpawnPosition.x - 80.f, mSpawnPosition.y + 200.f);
	// //mSceneLayers[Air]->attachChild(std::move(leftEscort));
	// mSceneLayers[Air]->requestAttach(std::move(leftEscort));

	// std::unique_ptr<Aircraft> rightEscort(new Aircraft(Aircraft::EnemyRaptor, mTextures));
	// // rightEscort->setPosition(80.f, 50.f);
	// // mPlayerAircraft->attachChild(std::move(rightEscort));
	// rightEscort->setPosition(mSpawnPosition.x + 80.f, mSpawnPosition.y + 200.f);
	// //mSceneLayers[Air]->attachChild(std::move(rightEscort));
	// mSceneLayers[Air]->requestAttach(std::move(rightEscort));


}

void World::adaptPlayerPosition()
{
	// Keep player's position inside the screen bounds, at least borderDistance units from the border
	sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
	const float borderDistance = 40.f;

	if (mPlayerAnimal->getWorldPosition().y < viewBounds.top + viewBounds.height * 0.3f) {
		mWorldView.move(0.f, mPlayerAnimal->getWorldPosition().y - (viewBounds.top + viewBounds.height * 0.3f));
	}

	if (intersection(mPlayerAnimal->getHitbox(), viewBounds) < 1) {
		throw GameStatus::GAME_LOST;
	}
	// position.x = std::max(position.x, viewBounds.left + borderDistance);
	// position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
	// position.y = std::max(position.y, viewBounds.top + borderDistance);
	// position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
	// mPlayerAnimal->setPosition(position);
}

void World::adaptPlayerVelocity()
{
	sf::Vector2f velocity = mPlayerAnimal->getVelocity();

	// If moving diagonally, reduce velocity (to have always same velocity)
	if (velocity.x != 0.f && velocity.y != 0.f)
		mPlayerAnimal->setVelocity(velocity / std::sqrt(2.f));

	// Add scrolling velocity
	mPlayerAnimal->accelerate(0.f, mScrollSpeed);
}


int World::getCurrentScore() {
	return mRoadList->getCurrentScore();
}