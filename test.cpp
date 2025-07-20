#include<bits/stdc++.h>
using namespace std;
class Match{
    Zawodnik* playerF;
    Zawodnik* playerS;
    void simGame(){
        int ptsF, ptsS;
        while(true){
            point=((float)rand()/RAND_MAX)*przedzialF;
            point = round(point * 100) / 100.0;
            if(point>borderF) ptsS++;
            else ptsF++;
            if(ptsF==4 && ptsS<3){
                break;
            }
            else if(ptsS==4 && ptsF<3){
                break;
            }
            else if(ptsF==5){
                break;
            }
            else if(ptsS==5){
                break;
            }
            else if(ptsF==4 && ptsS==4){
                ptsF=3;
                ptsS=3;
            }
        }
    }
    void simSet(){
        float compartmentFServe = a.playerF->getUm() * 1.50 + a.playerS->getUm();
        float compartmentSServe = a.playerS->getUm() + a.playerF->getUm() * 1.50;
        float borderFServe = a.playerF->getUm() * 1.50;
        float borderSServe = a.playerF->getUm();
        int gamesF, gamesS;
        while(true){
            simGame();
            if(gamesF==winningNumOfGames || gamesS==winningNumOfGames){
                break;
            }
            else{
                playerF->updateSkills();
                playerS->updateSkills();
                compartmentFServe = playerF->getSkills() * 1.50 + playerS->getSkills();
                compartmentSServe = playerS->getSkills() + playerF->getSkills() * 1.50;
                borderFServe = playerF->getSkills() * 1.50;
                borderSServe = playerF->getSkills();
            }
        }
    }
    void simMatch(){
        int toss=rand()%2+1;
        int setsF, setsS;
        string res="";
        while(true){
            if(toss==1){
                simSet();
            }
            else{
                simSet();
            }
            if(setsF==winningNumOFSets || setsS==winningNumOfSets){
                playerF->resSkill();
                playerS->resRealna();
                break;
            }
        }
    }

}

};
class Round(){
    int playersCount;
    bool operator <(const Round& another)const{
        return playersCount<another.playersCount;
    }
};
struct TournamentSettings{

};
class Tournament(){
    TorunamentSettings tournmentOptions;
    unique_ptr<RoundRobin> roundRobin;
    unique_ptr<Bracket> qBracket;
    unique_ptr<Bracket> mainBracket;
};
class Bracket(){
    map<Round,vector<Match>> matches;
    Match getMatches inPhase(char phase){
        return matches(phase);
    }
};
class RoundRobin(){
    map<Group,vector<<vector>Match>>>groupRounds;
    Match getMatchesInPhase(char group, int stage){
        return groupRounds(group, stage);
    }
};
int main(){


}
