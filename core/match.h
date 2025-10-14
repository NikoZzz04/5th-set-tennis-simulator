#ifndef MATCH_H
#define MATCH_H

#include "matchresult.h"
#include <optional>
#include "player.h"
#include <random>


class Match {
    Player& playerA;
    Player& playerB;
    std::optional<MatchResult> result;
    std::mt19937 rng;
    MatchRules rules;
    std::pair<float,float> getScale();
public:
    Match(Player& a, Player& b) : playerA(a), playerB(b), rng(std::random_device{}()) {} // UWAGA -> literówka tutaj, brak zamknięcia nawiasu

    MatchSide simulatePoint();
    Player& getPlayerA() const { return playerA; }
    Player& getPlayerB() const { return playerB; }

    const std::optional<MatchResult>& getResult() const { return result; }
};

#endif // MATCH_H
