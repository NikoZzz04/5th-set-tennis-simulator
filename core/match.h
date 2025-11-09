#ifndef MATCH_H
#define MATCH_H

#include "matchresult.h"
#include <optional>
#include "player.h"
#include <random>


class Match {
    Player& playerA;
    Player& playerB;
    std::optional<MatchResult> result);
    std::mt19937 rng;
    MatchRules rules;
    std::pair<float,float> getScale();
public:
    Match(Player& a, Player& b, MatchRules r) : playerA(a), playerB(b), rules(r), rng(std::random_device{}()) {}

    MatchSide simulatePoint();
    Player& getPlayerA() const { return playerA; }
    Player& getPlayerB() const { return playerB; }
    bool isNotEnded();
    const std::optional<MatchResult>& getResult() const { return result; }
};

#endif // MATCH_H
