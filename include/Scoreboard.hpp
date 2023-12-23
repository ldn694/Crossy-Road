#pragma once

#include "Difficulty.hpp"

#include <map>
#include <unordered_map>
#include <set>

struct Score {
    std::string name;
    int score;
    bool operator < (const Score& other) const;
    Score(std::string name, int score);
};

class Scoreboard {
private:
    std::unordered_map<Difficulty, std::set<Score>> scores;
    std::string path = "Assets/score/";
public:
    Scoreboard();
    void readFile();
    void addNewScore(Difficulty difficulty, std::string name, int score);
    void updateFile(Difficulty difficulty);
};