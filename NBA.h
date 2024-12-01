#pragma once
#include <string>
#include <iostream>

class NBAPlayer {
public:
    std::string playerName;
    std::string team;
    std::string position;
    int gamesPlayed;
    double pointsPerGame;
    double fieldGoalPercentage;

    NBAPlayer() = default;

    NBAPlayer(const std::string& name, const std::string& team, const std::string& position,
        int games, double points, double fgPercent)
        : playerName(name), team(team), position(position), gamesPlayed(games),
        pointsPerGame(points), fieldGoalPercentage(fgPercent) {}

    bool operator<(const NBAPlayer& other) const {
        return playerName < other.playerName;
    }

    bool operator==(const NBAPlayer& other) const {
        return playerName == other.playerName;
    }

    friend std::ostream& operator<<(std::ostream& os, const NBAPlayer& player) {
        os << "Player: " << player.playerName
            << " | Team: " << player.team
            << " | Position: " << player.position
            << " | Games Played: " << player.gamesPlayed
            << " | Points/Game: " << player.pointsPerGame
            << " | FG%: " << player.fieldGoalPercentage;
        return os;
    }
};
