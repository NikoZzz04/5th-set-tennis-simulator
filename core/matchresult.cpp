#include "matchresult.h"
#include<stream>

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
void MatchResult::assignPointTo(MatchSide player) {
    int& scoringPlayerPoints = (player == MatchSide::A ? currentGame.pointsA : currentGame.pointsB);
    int& opponentPoints      = (player == MatchSide::A ? currentGame.pointsB : currentGame.pointsA);
    int& scoringPlayerGames  = (player == MatchSide::A ? currentSet.gamesA : currentSet.gamesB);
    int& opponentGames       = (player == MatchSide::A ? currentSet.gamesB : currentSet.gamesA);

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
std::string MatchResult::toString() const {
    std::ostringstream out;

    for (const auto& set : finishedSets) {
        out << set.gamesA << ":" << set.gamesB;
        if (set.decidedByTieBreak) out << " (TB)";
        out << " ";
    }

    out << currentSet.gamesA << ":" << currentSet.gamesB << " ";

    if (inTieBreak) {
        out << "TB " << currentGame.pointsA << "-" << currentGame.pointsB;
    } else {
        out << formatTennisPoints(currentGame.pointsA, currentGame.pointsB)
        << "-"
        << formatTennisPoints(currentGame.pointsB, currentGame.pointsA);
    }

    return out.str();
}
int MatchResult::getSetsWonBy(MatchSide player) const{
    int sets=0;
    for(const auto& set : finishedSets) {
        if ((player==MatchSide::A && set.gamesA>set.gamesB)||(player==MatchSide::B && set.gamesB>set.gamesA))
            sets++;
    }
    return sets;
}

optional<MatchSide> MatchResult::getWinner() const{
    if(getSetsWonBy(A)==setsToWin) return A;
    if(getSetsWonBy(B)==setsToWin) return B;
    return nullopt;
}
