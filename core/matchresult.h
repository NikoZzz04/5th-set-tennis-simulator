#ifndef MATCHRESULT_H
#define MATCHRESULT_H

#include "matchrules.h"   // MatchRules { setsToWin, gamesToSet, tieBreakInLastSet, tieBreakInOtherSets }
#include <vector>
#include <string>
#include <optional>

enum class Player { A, B };

struct GameScore {
    int pointsA{0};
    int pointsB{0};
};

struct SetScore {
    int gamesA{0};
    int gamesB{0};
    bool decidedByTieBreak{false};
};

class MatchResult {
private:
    std::vector<SetScore> finishedSets;
    SetScore currentSet{};
    GameScore currentGame{};
    MatchRules rules{};
    bool inTieBreak{false};

public:
    MatchResult(const MatchRules& r) : rules(r) {}

    void assignPointTo(Player player);

    const std::vector<SetScore>& getFinishedSets() const { return finishedSets; }
    const SetScore& getCurrentSet() const { return currentSet; }
    const GameScore& getCurrentGame() const { return currentGame; }
    const MatchRules& getRules() const { return rules; }

    int getSetsWonBy(Player player) const;
    std::optional<Player> getWinner() const; // wg rules.setsToWin
    std::string toString() const;
};
#endif // MATCHRESULT_H
