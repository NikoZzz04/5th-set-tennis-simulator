#ifndef MATCHRULES_H
#define MATCHRULES_H
#include <optional>

struct MatchRules {
    int setsToWin;
    int gamesToSet;
    std::optional<int> tieBreakInLastSet;
    std::optional<int> tieBreakInOtherSets;
};


#endif // MATCHRULES_H
