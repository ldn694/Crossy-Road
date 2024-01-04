#pragma once

class Entity;
struct GameStatus {
    enum Status {
        GameWon,
        GameLost
    };
    enum EndReason {
        OutOfMap,
        Crashed,
        Drowned,
    };
    Status mStatus;
    EndReason mReason;
    Entity* mEntity;
    GameStatus(Status status, EndReason endReason, Entity* entity) : mStatus(status), mReason(endReason), mEntity(entity) {}
};