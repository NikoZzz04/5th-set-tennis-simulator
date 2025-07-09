#ifndef TENNIS_H
#define TENNIS_H

#include <string>
#include <vector>
#include <set>
#include <unordered_map>

class Zawodnik {
    int lp, ranking, wiek;
    std::string imie, nazwisko, narodowosc;
    float umiejetnoscTeoretyczna, umiejetnoscRealna;
    std::vector<int> tournamentpts;

public:
    std::string seeding;
    int gpts;

    Zawodnik();
    Zawodnik(int rnk, std::string nm, std::string srnm, int age, std::string nat, float skill, int pts, std::vector<int> tpts);

    void getRealna(std::string sx);
    std::string infork() const;
    void setRank();
    int getRank() const;
    std::string info() const;
    float getUm() const;
    std::string getImie() const;
    std::string getNazwisko() const;
    std::string getNarodowosc() const;
    int getAge() const;
    float getUmiejetnoscTeoretyczna() const;
    float getUmiejetnoscRealna() const;
    void resRealna();
    int getId() const;
    bool operator <(const Zawodnik& a) const;
    void addPts(int pts, int week);
    void resPts(int week);
    int getPtsByWeek(int week) const;
    void updateSkillsAfterWonMatch();
    void updateSkillsAfterLostMatch();
    void setTeo();
};

struct Mecz {
    Zawodnik* playerF;
    Zawodnik* playerS;
    Zawodnik* winner;
};

class Turniej {
    int turn, lp, n, qil, qpass, p, qp, zaw = 0;
    std::string countr, city, nm, rng, seed, brck, sx;
    std::vector<int> seedy, seedyq, byes, points;

public:
    Turniej() = default;
    Turniej(int turn, int lp, int n, int qil, std::string countr, std::string city, std::string nm,
            std::string rng, std::string seed, std::string brck, std::string sx);

    void setInfos();
    void setMain();
    void setQual();

    int getN() const;
    int getQpass() const;
    int getQil() const;
    int getZaw() const;
    int getP() const;
    int getQP() const;
    int getTydzien() const;
    std::string getSx() const;
    std::string getRng() const;
    std::vector<int> getSeedy() const;
    std::vector<int> getSeedyQ() const;
    std::vector<int> getByes() const;
    std::vector<int> getPoints() const;
    std::string info() const;
};

// Symulacja i pomocnicze funkcje
void simSet(int& matchF, int& matchS, float przedzialF, float przedzialS,
            float borderF, float borderS, Zawodnik& first, Zawodnik& second, std::string& res);

void simMecz(Mecz& a, std::vector<int> points, int week, int p, std::string sx);
Zawodnik* tbreak(Zawodnik* x, Zawodnik* y, std::vector<Mecz> mecze);
void simFinals(std::vector<Zawodnik>& zawodnicy, Turniej& cup, std::vector<Mecz>& turniej, int i);
void simTurniej(std::vector<Zawodnik>& zawodnicy, Turniej& cup,
                std::vector<Mecz>& kwali, std::vector<Mecz>& turniej,
                int i, std::unordered_map<int, std::set<int>>& wystepy);


#endif // TENNIS_H
