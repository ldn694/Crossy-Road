#include "River.hpp"
#include "Utility.hpp"
#include "FloatingLog.hpp"
#include "ResourceHolder.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

Textures::ID toTextureID(River::Variant variant)
{
    switch (variant) {
    case River::LeftToRight:
        return Textures::RiverLeftToRight;
    case River::RightToLeft:
        return Textures::RiverRightToLeft;
    case River::Stable:
        return Textures::RiverLeftToRight;
    }
}

FloatingLog::Type getRandLogType(int movementSign) {
    if (movementSign == 0) {
        return static_cast<FloatingLog::Type>(FloatingLog::Lily);
    }
    else {
        int typeList[2] = {FloatingLog::SmallLog, FloatingLog::BigLog};
        return static_cast<FloatingLog::Type>(typeList[rand() % 2]);
    }

}

River::River(const TextureHolder& textures, Difficulty difficulty, int variant) : Road(toTextureID(static_cast<River::Variant>(variant)), textures, Road::Type::River, Zone::Safety::Unsafe, difficulty), textures(textures) {
    sf::Time basePeriodTime = sf::seconds(2.5f);
    int numPartionPeriod;
    switch (difficulty) {
    case Difficulty::Easy:
        numPartionPeriod = Rand(70, 90);
        break;
    case Difficulty::Medium:
        numPartionPeriod = Rand(50, 70);
        break;
    case Difficulty::Hard:
        numPartionPeriod = Rand(30, 50);
        break;
    }
    mPeriod = basePeriodTime * (numPartionPeriod / 100.f);
    switch (variant) {
    case River::LeftToRight:
        movementSign = 1;
        break;
    case River::RightToLeft:
        movementSign = -1;
        break;
    case River::Stable:
        movementSign = 0;
        break;
    default:
        movementSign = 0;
        break;
    }
    std::unique_ptr<SceneNode> mediate(new SceneNode());
    mediateNode = mediate.get();
    requestAttach(std::move(mediate));
    mTimeSinceLastSpawn = sf::Time::Zero;
    float minimumDistance = (WITDH_SIZE - maximumLog * 50) / (maximumLog - 1);
    if (movementSign == 0) {
        int numLog = Rand(4, 8);
        std::vector <int> index = randomIntSampling(NUM_ZONE, numLog);
        for (int i = 0; i < numLog; i++) {
            FloatingLog::Type logType = getRandLogType(movementSign);
            sf::Vector2f position = mZones[index[i]]->getPosition();
            position.y = (HEIGHT_SIZE - 50) / 2;
            position.x -= WITDH_SIZE / NUM_ZONE / 2  + 60;
            FloatingLog* log = addLog(logType, position);
        }
    }
    else {
        int numLog = movementSign == 0 ? 4 : 5;
        float x = rand() % (int)minimumDistance, y = (HEIGHT_SIZE - 50) / 2;
        for (int i = 0; i < numLog; i++) {
            FloatingLog::Type logType = getRandLogType(movementSign);
            float offsetToNextLog = rand() % (int)minimumDistance;
            FloatingLog* log = addLog(logType, sf::Vector2f(x, y));
            float newX = x + log->getHitbox().width + minimumDistance + offsetToNextLog;
            x = newX;
        }
    }
    attachChildren();
    mediateNode->attachChildren();
}

River::~River() {
    // std::cerr << "---------------------\n";
    // std::cerr << "River destroyed\n";
    // for (int i = 0; i < zones.size(); i++) {
    //     mediateNode->requestDetach(zones[i]->getParent());
    // }
}

FloatingLog* River::addLog(FloatingLog::Type logType, sf::Vector2f position)
{
    std::unique_ptr<FloatingLog> log(new FloatingLog(logType, position, textures, this));
    logs.push_back(log.get());
    log->setPosition(position);
    std::vector <Zone*> zones = log->getZones();
    for (int j = 0; j < zones.size(); j++) {
        addZone(zones[j]);
    }
    FloatingLog* logPtr = log.get();
    mediateNode->requestAttach(std::move(log));
    return logPtr;
}

void River::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}

void River::updateCurrent(sf::Time dt)
{
    Road::updateCurrent(dt);
    if (movementSign != 0) {
        mTimeSinceLastSpawn += dt;
    }
    while (true) {
        int index = -1;
        for (int i = 0; i < logs.size(); i++) {
            if ((logs[i]->getWorldPosition().x + logs[i]->getHitbox().width < 0 && movementSign == -1) || (logs[i]->getWorldPosition().x > WITDH_SIZE && movementSign == 1)) {
                index = i;
                break;
            }
        }
        if (index == -1) break;
        FloatingLog* log = logs[index];
        for (int i = 0; i < log->getZones().size(); i++) {
            removeZone(log->getZones()[i]);
        }
        logs.erase(logs.begin() + index);
        mediateNode->requestDetach(log);
    }
    if (mTimeSinceLastSpawn > mPeriod) {
        mTimeSinceLastSpawn = sf::Time::Zero;
        FloatingLog::Type type = getRandLogType(movementSign);
        sf::Vector2f position;
        if (movementSign == 1) {
            position = sf::Vector2f(-160 - (rand() % 50), (HEIGHT_SIZE - 50) / 2) - mediateNode->getPosition();
        }
        else {
            position = sf::Vector2f(WITDH_SIZE + (rand() % 50) + 160, (HEIGHT_SIZE - 50) / 2) - mediateNode->getPosition();

        }
        addLog(type, position);
        mediateNode->attachChildren();
    }
    mediateNode->move(dt / mPeriod * 300 * movementSign, 0);
}