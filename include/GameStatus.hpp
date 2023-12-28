class Entity;
struct GameStatus {
    enum Status {
        GameWon,
        GameLost
    };
    Status mStatus;
    Entity* mEntity;
    GameStatus(Status status, Entity* entity) : mStatus(status), mEntity(entity) {}
};