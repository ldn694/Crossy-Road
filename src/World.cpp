#include "World.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <algorithm>
#include <cmath>


SceneNode& World::getSceneGraph()
{
	return mSceneGraph;
}

World::World(sf::RenderWindow& window)
: mWindow(window)
, mWorldView(window.getDefaultView())
, mTextures() 
, mSceneGraph()
, mSceneLayers()
, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 2000.f)
, mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f)
//, mScrollSpeed(-50.f)
, mScrollSpeed(0.f)
, mPlayerAircraft(nullptr)
{
	loadTextures();
	buildScene();

	// Prepare the view
	mWorldView.setCenter(mSpawnPosition);
}

void World::update(sf::Time dt)
{
	// Scroll the world, reset player velocity
	mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());	
	mPlayerAircraft->setVelocity(0.f, 0.f);

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
	mTextures.load(Textures::Eagle, "Assets/Images/Eagle.png");
	mTextures.load(Textures::Raptor, "Assets/Images/Raptor.png");
	mTextures.load(Textures::Desert, "Assets/Images/Desert.png");
	mTextures.load(Textures::Railways, "Assets/Images/Railways.png");
	mTextures.load(Textures::River, "Assets/Images/River.png");
	mTextures.load(Textures::SRoad, "Assets/Images/SRoad.png");
	mTextures.load(Textures::Land, "Assets/Images/Land.png");
}

void World::buildScene()
{
	// Initialize the different layers
	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = layer.get();

		mSceneGraph.attachChild(std::move(layer));
	}

	// Prepare the tiled background
	sf::Texture& texture = mTextures.get(Textures::Desert);
	sf::IntRect textureRect(mWorldBounds);
	texture.setRepeated(true);

	// Add the background sprite to the scene
	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
	mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

	std::unique_ptr<Road> railways(new Railways(mTextures));
	railways->setPosition(mSpawnPosition + sf::Vector2f(0.f, -50.f));
	mSceneLayers[Air]->attachChild(std::move(railways));

	std::unique_ptr<Road> river(new River(mTextures));
	river->setPosition(mSpawnPosition + sf::Vector2f(0.f, -100.f));
	mSceneLayers[Air]->attachChild(std::move(river));

	std::unique_ptr<Road> land(new Land(mTextures));
	land->setPosition(mSpawnPosition + sf::Vector2f(0.f, +50.f));
	mSceneLayers[Air]->attachChild(std::move(land));

	std::unique_ptr<Road> sroad(new SRoad(mTextures));
	sroad->setPosition(mSpawnPosition + sf::Vector2f(0.f, +100.f));
	mSceneLayers[Air]->attachChild(std::move(sroad));

	// Add player's aircraft
	std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::Eagle, mTextures));
	mPlayerAircraft = leader.get();
	mPlayerAircraft->setPosition(mSpawnPosition);
	mSceneLayers[Air]->attachChild(std::move(leader));

	std::unique_ptr<Aircraft> leftEscort(new Aircraft(Aircraft::AllyRaptor, mTextures));
	// leftEscort->setPosition(-80.f, 50.f);
	// mPlayerAircraft->attachChild(std::move(leftEscort));	
	leftEscort->setPosition(mSpawnPosition.x - 80.f, mSpawnPosition.y + 50.f);
	mSceneLayers[Air]->attachChild(std::move(leftEscort));

	std::unique_ptr<Aircraft> rightEscort(new Aircraft(Aircraft::EnemyRaptor, mTextures));
	// rightEscort->setPosition(80.f, 50.f);
	// mPlayerAircraft->attachChild(std::move(rightEscort));
	rightEscort->setPosition(mSpawnPosition.x + 80.f, mSpawnPosition.y + 50.f);
	mSceneLayers[Air]->attachChild(std::move(rightEscort));


}

void World::adaptPlayerPosition()
{
	// Keep player's position inside the screen bounds, at least borderDistance units from the border
	sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
	const float borderDistance = 40.f;

	sf::Vector2f position = mPlayerAircraft->getPosition();
	position.x = std::max(position.x, viewBounds.left + borderDistance);
	position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
	position.y = std::max(position.y, viewBounds.top + borderDistance);
	position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
	mPlayerAircraft->setPosition(position);
}

void World::adaptPlayerVelocity()
{
	sf::Vector2f velocity = mPlayerAircraft->getVelocity();

	// If moving diagonally, reduce velocity (to have always same velocity)
	if (velocity.x != 0.f && velocity.y != 0.f)
		mPlayerAircraft->setVelocity(velocity / std::sqrt(2.f));

	// Add scrolling velocity
	mPlayerAircraft->accelerate(0.f, mScrollSpeed);
}
