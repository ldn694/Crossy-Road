#include <fstream>

#include "Scoreboard.hpp"

Score::Score(std::string name, int score) {
    this->name = name;
    this->score = score;
}

bool Score::operator < (const Score& other) const {
    return this->score > other.score;
}

std::string difficultyToString(Difficulty difficulty) {
    switch (difficulty) {
    case Difficulty::Easy:
        return "easy";
    case Difficulty::Medium:
        return "medium";
    case Difficulty::Hard:
        return "hard";
    default:
        return "";
    }
}

Scoreboard::Scoreboard() {
    readFile();
}

void Scoreboard::readFile() {
    scores.clear();
    for (int diff = 0; diff < NumDifficulties; diff++) {
        std::ifstream fin(path + difficultyToString((Difficulty)diff) + ".txt");
        std::string name;
        int score;
        while (!fin.eof()) {
            fin >> name >> score;
            if (fin.eof()) break;
            scores[(Difficulty)diff].insert(Score(name, score));
        }
        fin.close();
        while (scores[(Difficulty)diff].size() > 5) {
            scores[(Difficulty)diff].erase(--scores[(Difficulty)diff].end());
        }
    }
}

void Scoreboard::addNewScore(Difficulty difficulty, std::string name, int score) {
    scores[difficulty].insert(Score(name, score));
    while (scores[difficulty].size() > 5) {
        scores[difficulty].erase(--scores[difficulty].end());
    }
    updateFile(difficulty);
}

void Scoreboard::updateFile(Difficulty difficulty) {
    std::ofstream fout(path + difficultyToString(difficulty) + ".txt");
    for (auto score : scores[difficulty]) {
        fout << score.name << '\n' << score.score << '\n';
    }
    fout.close();
}