#ifndef MATCH_H
#define MATCH_H

#include <optional>

    class Match {
    Player& playerA;
    Player& playerB;
    std::optional<MatchResult> result;

public:
    Match(Player& a, Player& b) : playerA(a), playerB(b) {}

    Player& getPlayerA() const { return playerA; }
    Player& getPlayerB() const { return playerB; }

    const std::optional<MatchResult>& getResult() const { return result; }
    void setResult(const MatchResult& r) { result = r; }
};

#endif // MATCH_H
