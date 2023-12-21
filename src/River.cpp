#include "River.hpp"
#include "Utility.hpp"
#include "FloatingLog.hpp"
#include "ResourceHolder.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

River::River(const TextureHolder& textures, Difficulty difficulty) : Road(Textures::River, textures, Road::Type::River, Zone::Safety::Unsafe, difficulty), textures(textures) {
    switch (difficulty) {
        case Difficulty::Easy:
            mPeriod = sf::seconds(3.0f);
            break;
        case Difficulty::Medium:
            mPeriod = sf::seconds(2.0f);
            break;
        case Difficulty::Hard:
            mPeriod = sf::seconds(1.0f);
            break;
    }
    bool movingLeftToRight = rand() % 2;
    movementSign = movingLeftToRight ? 1 : -1;
    std::unique_ptr<SceneNode> mediate(new SceneNode());
    mediateNode = mediate.get();
    requestAttach(std::move(mediate));
    mTimeSinceLastSpawn = sf::Time::Zero;
    float minimumDistance = WITDH_SIZE / ((maximumLog + 1) * 2);
    int numLog = rand() % maximumLog + 1;
    float x = rand() % (int)minimumDistance, y = (HEIGHT_SIZE - 50) / 2;
    for (int i = 0; i < numLog; i++) {
        int type = rand() % FloatingLog::NumTypes;
        FloatingLog::Type logType = static_cast<FloatingLog::Type>(type);
        float offsetToNextLog = rand() % (int)minimumDistance;
        FloatingLog* log = addLog(logType, sf::Vector2f(x, y));
        float newX = x + log->getHitbox().width + minimumDistance + offsetToNextLog;
        x = newX;
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
    mTimeSinceLastSpawn += dt;
    if (mTimeSinceLastSpawn > mPeriod) {
        mTimeSinceLastSpawn = sf::Time::Zero;
        int type = rand() % FloatingLog::NumTypes;
        sf::Vector2f position;
        if (movementSign == 1) {
            position = sf::Vector2f(0, (HEIGHT_SIZE - 50) / 2) - mediateNode->getPosition();
        }
        else {
            position = sf::Vector2f(WITDH_SIZE, (HEIGHT_SIZE - 50) / 2) - mediateNode->getPosition();
        
        }
        addLog(static_cast<FloatingLog::Type>(type), position);
        mediateNode->attachChildren();
    }
    while (true) {
        int index = -1;
        for (int i = 0; i < logs.size(); i++) {
            if (logs[i]->getWorldPosition().x + logs[i]->getHitbox().width < 0 || logs[i]->getWorldPosition().x > WITDH_SIZE) {
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
    mediateNode->move(dt / mPeriod * 300 * movementSign, 0);
}