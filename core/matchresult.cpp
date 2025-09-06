#include "matchresult.h"

MatchResult::MatchResult() {

}
namespace {
std::string formatTennisPoints(int scoringPlayerPoints, int opponentPoints) {
    if (scoringPlayerPoints >= 3 && opponentPoints >= 3) {
        if (scoringPlayerPoints == opponentPoints) return "40";
        if (scoringPlayerPoints == opponentPoints + 1) return "Ad";
        return "40";
    }
    switch (scoringPlayerPoints) {
    case 0: return "0";
    case 1: return "15";
    case 2: return "30";
    default: return "40";
    }
}
bool setHasWinner(const SetScore& set, int gamesToWin) {
    if (set.gamesA >= gamesToWin && set.gamesA >= set.gamesB + 2) return true;
    if (set.gamesB >= gamesToWin && set.gamesB >= set.gamesA + 2) return true;
    return false;
}

bool isDecidingSet(const MatchResult& match) {
    int maxSets = match.getRules().setsToWin * 2 - 1;
    int currentSetNumber = static_cast<int>(match.getFinishedSets().size()) + 1;
    return currentSetNumber == maxSets;
}
}
void MatchResult::assignPointTo(Player player) {
    int& scoringPlayerPoints = (player == Player::A ? currentGame.pointsA : currentGame.pointsB);
    int& opponentPoints      = (player == Player::A ? currentGame.pointsB : currentGame.pointsA);
    int& scoringPlayerGames  = (player == Player::A ? currentSet.gamesA : currentSet.gamesB);
    int& opponentGames       = (player == Player::A ? currentSet.gamesB : currentSet.gamesA);

    scoringPlayerPoints++;

    if (inTieBreak) {
        auto tieBreakRule = isDecidingSet(*this) ? rules.tieBreakInLastSet : rules.tieBreakInOtherSets;
        int targetPoints = tieBreakRule.value_or(7);
        if (scoringPlayerPoints >= targetPoints && scoringPlayerPoints >= opponentPoints + 2) {
            scoringPlayerGames++;
            currentSet.decidedByTieBreak = true;
            finishedSets.push_back(currentSet);
            currentSet = {};
            currentGame = {};
            inTieBreak = false;
        }
        return;
    }

    if (scoringPlayerPoints >= 4 && scoringPlayerPoints >= opponentPoints + 2) {
        scoringPlayerGames++;
        currentGame = {};

        if (setHasWinner(currentSet, rules.gamesToSet)) {
            finishedSets.push_back(currentSet);
            currentSet = {};
            return;
        }

        if (currentSet.gamesA == rules.gamesToSet && currentSet.gamesB == rules.gamesToSet) {
            bool lastSet = isDecidingSet(*this);
            auto tieBreakRule = lastSet ? rules.tieBreakInLastSet : rules.tieBreakInOtherSets;
            if (tieBreakRule.has_value()) {
                inTieBreak = true;
            }
        }
    }
}
