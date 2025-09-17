#include "match.h"

Match::Match() {

}
int Match::getScale(float umA, float umB){
    scaleAtServeA=umA*1,50+umB;
    scaleAtServeB=umA+umB*1,50;

    return scaleAtServeA, scaleAtServeB;
}
MatchSide Match::simulatePoint()
{
    std::uniform_int_distribution<int> int_dist(1, 100);
    auto randomInt = int_dist(rng);

    MatchSide side;
    if(randomInt<=50) side=MatchSide::A;
    else side=MatchSide::B;

    if(!result.has_value()) {
        result.emplace(rules);
    }

    // Jak jesteśmy już pewni, że istnieje wartość w std::optional, to możemy użyć jak wskaźnika, czyli przez strzałkę
    // result->assignPointTo(side);
    result.value().assignPointTo(side);

    return side;
}
