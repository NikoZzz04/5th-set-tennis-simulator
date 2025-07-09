#include "tennis.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

// ------------------------------
// Zawodnik implementations
// ------------------------------

Zawodnik::Zawodnik()
    : lp(0), ranking(0), wiek(0),
    imie(), nazwisko(), narodowosc(),
    umiejetnoscTeoretyczna(0), umiejetnoscRealna(0),
    tournamentpts(), seeding(), gpts(0)
{}

Zawodnik::Zawodnik(int rnk, string nm, string srnm, int age, string nat,
                   float skill, int pts, vector<int> tpts)
    : lp(rnk), ranking(pts), wiek(age),
    imie(std::move(nm)), nazwisko(move(srnm)), narodowosc(move(nat)),
    umiejetnoscTeoretyczna(skill), umiejetnoscRealna(skill),
    tournamentpts(move(tpts)), seeding(), gpts(0)
{}

void Zawodnik::getRealna(string sx) {
    float x = (sx == "M" ? 3.5f : 5.5f);
    float minSkill = max(0.0f, umiejetnoscTeoretyczna - x);
    float maxSkill = min(100.0f, umiejetnoscTeoretyczna + x);
    umiejetnoscRealna = (static_cast<float>(rand()) / RAND_MAX) * (maxSkill - minSkill) + minSkill;
    umiejetnoscRealna = round(umiejetnoscRealna * 100) / 100.0f;
}

string Zawodnik::infork() const {
    return to_string(lp) + ". " + imie + " " + nazwisko + " " +
           to_string(wiek) + " (" + narodowosc + ") (" + seeding + ")";
}

void Zawodnik::setRank() {
    sort(tournamentpts.rbegin(), tournamentpts.rend());
    int suma = 0;
    for (int i = 0; i < 16 && i < (int)tournamentpts.size(); ++i)
        suma += tournamentpts[i];
    ranking = suma;
}

int Zawodnik::getRank() const {
    return ranking;
}

string Zawodnik::info() const {
    return imie + " " + nazwisko + " " + to_string(wiek) +
           " (" + narodowosc + ") (" + seeding + ")";
}

float Zawodnik::getUm() const {
    return umiejetnoscRealna;
}

string Zawodnik::getImie() const {
    return imie;
}

string Zawodnik::getNazwisko() const {
    return nazwisko;
}

string Zawodnik::getNarodowosc() const {
    return narodowosc;
}

int Zawodnik::getAge() const {
    return wiek;
}

float Zawodnik::getUmiejetnoscTeoretyczna() const {
    return umiejetnoscTeoretyczna;
}

float Zawodnik::getUmiejetnoscRealna() const {
    return umiejetnoscRealna;
}

void Zawodnik::resRealna() {
    umiejetnoscRealna = umiejetnoscTeoretyczna;
}

int Zawodnik::getId() const {
    return lp;
}

bool Zawodnik::operator<(const Zawodnik& a) const {
    return ranking > a.ranking;
}

void Zawodnik::addPts(int pts, int week) {
    if (week >= 0 && week < (int)tournamentpts.size())
        tournamentpts[week] += pts;
}

void Zawodnik::resPts(int week) {
    if (week >= 0 && week < (int)tournamentpts.size())
        tournamentpts[week] = 0;
}

int Zawodnik::getPtsByWeek(int week) const {
    if (week >= 0 && week < (int)tournamentpts.size())
        return tournamentpts[week];
    return 0;
}

void Zawodnik::updateSkillsAfterWonMatch() {
    float x = 0.8f;
    float minSkill = max(0.0f, umiejetnoscTeoretyczna - 0.0f);
    float maxSkill = min(100.0f, umiejetnoscTeoretyczna + x);
    umiejetnoscTeoretyczna =
        (static_cast<float>(rand()) / RAND_MAX) * (maxSkill - minSkill) + minSkill;
    umiejetnoscTeoretyczna = round(umiejetnoscTeoretyczna * 100) / 100.0f;
}

void Zawodnik::updateSkillsAfterLostMatch() {
    float x = 1.5f;
    float minSkill = max(0.0f, umiejetnoscTeoretyczna - x);
    float maxSkill = min(100.0f, umiejetnoscTeoretyczna + 0.0f);
    umiejetnoscTeoretyczna =
        (static_cast<float>(rand()) / RAND_MAX) * (maxSkill - minSkill) + minSkill;
    umiejetnoscTeoretyczna = round(umiejetnoscTeoretyczna * 100) / 100.0f;
}

void Zawodnik::setTeo() {
    float x = 6.0f;
    float minSkill = max(0.0f, umiejetnoscTeoretyczna - 1.0f);
    float maxSkill = min(100.0f, umiejetnoscTeoretyczna + 1.0f);
    umiejetnoscTeoretyczna =
        (static_cast<float>(rand()) / RAND_MAX) * (maxSkill - minSkill) + minSkill;
    umiejetnoscTeoretyczna = round(umiejetnoscTeoretyczna * 100) / 100.0f;
}

// ------------------------------
// Turniej implementations
// ------------------------------

Turniej::Turniej(int turn, int lp, int n, int qil,
                 string countr, string city, string nm,
                 string rng, string seed, string brck, string sx)
    : turn(turn), lp(lp), n(n), qil(qil),
    countr(move(countr)), city(move(city)), nm(move(nm)),
    rng(move(rng)), seed(move(seed)), brck(move(brck)), sx(move(sx)),
    qpass(0), p(0), qp(0), zaw(0)
{}

void Turniej::setInfos() {
    if (rng == "GrandSlam") {
        p = 0; qp = 10;
        points = {0, 8, 16, 25, 10, 45, 90, 180, 360, 720, 1200, 2000};
    }
    else if (rng == "Masters1000") {
        p = 0; qp = 20;
        if (n > 64)
            points = {0, 8, 16, 5, 10, 45, 90, 180, 360, 600, 1000};
        else
            points = {0, 8, 16, 10, 45, 90, 180, 360, 600, 1000};
    }
    else if (rng == "ATP500" || rng == "WTA500") {
        p = 35; qp = 65;
        if (n > 32)
            points = {0, 5, 10, 0, 20, 45, 90, 180, 300, 500};
        else
            points = {0, 5, 10, 0, 45, 90, 180, 300, 500};
    }
    else if (rng == "ATP250" || rng == "WTA250") {
        p = 60; qp = 75;
        if (n > 32)
            points = {0, 5, 10, 0, 10, 20, 45, 90, 150, 250};
        else
            points = {0, 5, 10, 0, 20, 45, 90, 150, 250};
    }
    else if (rng == "Challenger175") {
        zaw = 91; p = 55; qp = 70;
        if (n > 32)
            points = {0, 3, 8, 2, 5, 16, 35, 60, 100, 175};
        else
            points = {0, 3, 8, 5, 16, 35, 60, 100, 175};
    }
    else if (rng == "Challenger125") {
        zaw = 91; p = 65; qp = 80;
        if (n > 32)
            points = {0, 3, 7, 2, 5, 11, 25, 45, 75, 125};
        else
            points = {0, 3, 7, 5, 11, 25, 45, 75, 125};
    }
    else if (rng == "Challenger100") {
        zaw = 101; p = 65; qp = 80;
        if (n > 32)
            points = {0, 3, 6, 2, 4, 9, 20, 36, 60, 100};
        else
            points = {0, 3, 6, 4, 9, 20, 36, 60, 100};
    }
    else if (rng == "Challenger75") {
        zaw = 111; p = 70; qp = 80;
        if (n > 32)
            points = {0, 3, 6, 2, 4, 9, 20, 36, 60, 100};
        else
            points = {0, 2, 5, 3, 7, 15, 26, 44, 75};
    }
    else if (rng == "Challenger50") {
        zaw = 121; p = 75; qp = 85;
        if (n > 32)
            points = {0, 2, 4, 0, 1, 3, 7, 16, 30, 50};
        else
            points = {0, 2, 4, 0, 3, 7, 16, 30, 50, 70};
    }
}

void Turniej::setMain() {
    switch (n) {
    case 8:   seedy = {0,7}; break;
    case 16:  seedy = {0,15,8,7}; break;
    case 24:  seedy = {0,31,16,15,8,23,24,7}; byes = {1,6,9,14,17,22,25,30}; break;
    case 28:  seedy = {0,31,16,15,8,23,24,7}; byes = {1,14,17,30}; break;
    case 30:  seedy = {0,31,16,15,8,23,24,7}; byes = {1,30}; break;
    case 32:  seedy = {0,31,16,15,8,23,24,7}; break;
    case 48:  seedy = {0,63,32,31,16,47,48,15,8,55,40,23,25,39,56,7};
        byes = {1,6,9,14,17,22,25,30,33,38,41,46,49,54,57,62};
        break;
    case 56:  seedy = {0,63,32,31,16,47,48,15,8,55,40,23,25,39,56,7};
        byes = {1,14,17,30,33,46,49,62};
        break;
    case 64:  seedy = {0,63,32,31,16,47,48,15,8,55,40,23,25,39,56,7}; break;
    case 96:  seedy = {0,127,64,63,32,95,96,31,16,111,80,47,48,79,112,15,8,119,72,55,40,87,104,23,24,103,88,39,56,71,120,7};
        byes = {1,6,9,14,17,22,25,30,33,38,41,46,49,54,57,62,65,70,73,78,81,86,89,94,97,102,105,110,113,118,121,126};
        break;
    case 128: seedy = {0,127,64,63,32,95,96,31,16,111,80,47,48,79,112,15,8,119,72,55,40,87,104,23,24,103,88,39,56,71,120,7};
        break;
    }
}

void Turniej::setQual() {
    switch (qil) {
    case 8:  seedyq = {0,7,4,3}; qpass = 4; break;
    case 16: seedyq = {0,15,8,7,4,11,12,3}; qpass = 4; break;
    case 24: seedyq = {0,23,12,11,4,19,16,7,8,15,20,3}; qpass = 6; break;
    case 28: seedyq = {0,27,12,11,4,19,23,20,16,7,8,15,24,3}; qpass = 7; break;
    case 32: seedyq = {0,31,16,15,8,23,24,7}; qpass = 8; break;
    case 48: seedyq = {0,47,24,23,12,35,36,11,4,43,28,19,16,31,40,7,8,39,32,15,20,27,44,3}; qpass = 12; break;
    case 128: seedyq = {0,127,64,63,32,95,96,31,16,111,80,47,48,79,112,15,8,119,72,55,40,87,104,23,24,103,88,39,56,71,120,7}; qpass = 16; break;
    }
}

int Turniej::getN() const           { return n; }
int Turniej::getQpass() const      { return qpass; }
int Turniej::getQil() const        { return qil; }
int Turniej::getZaw() const        { return zaw; }
int Turniej::getP() const          { return p; }
int Turniej::getQP() const         { return qp; }
int Turniej::getTydzien() const    { return turn; }
string Turniej::getSx() const      { return sx; }
string Turniej::getRng() const     { return rng; }
vector<int> Turniej::getSeedy() const  { return seedy; }
vector<int> Turniej::getSeedyQ() const { return seedyq; }
vector<int> Turniej::getByes() const   { return byes; }
vector<int> Turniej::getPoints() const { return points; }
string Turniej::info() const {
    return nm + " " + city + " " + countr + " " + rng + " " + seed + " " + brck + " " + sx + " " + to_string(n);
}

// ------------------------------
// Helper functions
// ------------------------------

void simSet(int& matchF, int& matchS,
            float przedzialF, float przedzialS,
            float borderF, float borderS,
            Zawodnik& first, Zawodnik& second,
            string& res)
{
    int setF = 0, setS = 0;
    while (true) {
        float game = round(((float)rand() / RAND_MAX) * przedzialF * 100) / 100.0f;
        if (game > borderF) ++setS;
        else ++setF;
        if (((setF == 6 || setS == 6) && abs(setF - setS) >= 2) || setF == 7 || setS == 7)
            break;
        if (setF == 6 && setS == 6) {
            float tie = round(((float)rand() / RAND_MAX) * (first.getUm() + second.getUm()) * 100) / 100.0f;
            if (tie > first.getUm()) ++setS;
            else ++setF;
            break;
        }
        // second player serves
        game = round(((float)rand() / RAND_MAX) * przedzialS * 100) / 100.0f;
        if (game > borderS) ++setS;
        else ++setF;
        if (((setF == 6 || setS == 6) && abs(setF - setS) >= 2) || setF == 7 || setS == 7)
            break;
        if (setF == 6 && setS == 6) {
            float tie = round(((float)rand() / RAND_MAX) * (first.getUm() + second.getUm()) * 100) / 100.0f;
            if (tie > first.getUm()) ++setS;
            else ++setF;
            break;
        }
    }
    res += to_string(setF) + "-" + to_string(setS) + " ";
    if (setF > setS) ++matchF;
    else ++matchS;
}

void simMecz(Mecz& a, vector<int> points, int week, int p, string sx) {
    float przedzialF = a.playerF->getUm() * 1.5f + a.playerS->getUm();
    float przedzialS = a.playerS->getUm() + a.playerF->getUm() * 1.5f;
    float borderF = a.playerF->getUm() * 1.5f;
    float borderS = a.playerF->getUm();
    int matchF = 0, matchS = 0;
    string res;
    while (true) {
        int los = rand() % 2;
        if (los == 0)
            simSet(matchF, matchS, przedzialF, przedzialS, borderF, borderS, *a.playerF, *a.playerS, res);
        else
            simSet(matchF, matchS, przedzialS, przedzialF, borderS, borderF, *a.playerF, *a.playerS, res);
        if (matchF == 2 || matchS == 2) {
            a.playerF->resRealna();
            a.playerS->resRealna();
            cout << a.playerF->info() << " " << res << " " << a.playerS->info() << endl;
            if (matchF == 2) {
                a.playerS->addPts(points[p], week);
                a.playerF->updateSkillsAfterWonMatch();
                a.playerS->updateSkillsAfterLostMatch();
                a.winner = a.playerF;
            } else {
                a.playerF->addPts(points[p], week);
                a.playerS->updateSkillsAfterWonMatch();
                a.playerF->updateSkillsAfterLostMatch();
                a.winner = a.playerS;
            }
            break;
        } else {
            a.playerF->getRealna(sx);
            a.playerS->getRealna(sx);
            przedzialF = a.playerF->getUm() * 1.5f + a.playerS->getUm();
            przedzialS = a.playerS->getUm() + a.playerF->getUm() * 1.5f;
            borderF = a.playerF->getUm() * 1.5f;
            borderS = a.playerF->getUm();
        }
    }
}

Zawodnik* tbreak(Zawodnik* x, Zawodnik* y, vector<Mecz> mecze) {
    for (auto& m : mecze) {
        bool involvesX = (m.playerF == x || m.playerS == x);
        bool involvesY = (m.playerF == y || m.playerS == y);
        if (involvesX && involvesY)
            return m.winner;
    }
    return nullptr;
}

void simFinals(vector<Zawodnik>& zawodnicy, Turniej& cup,
               vector<Mecz>& turniej, int i)
{
    auto cmp = [&](Zawodnik* a, Zawodnik* b){ return a->gpts > b->gpts; };
    int n = cup.getN();
    string sx = cup.getSx();
    vector<int> points;
    int pt;
    vector<Zawodnik*> uczestnicy;
    vector<Zawodnik*> A, B;
    if (cup.getRng() == "ATPFinals" || cup.getRng() == "WTAFinals") {
        points = {0, 400, 500};
        pt = 200;
        for (int j = 0; j < n; ++j) uczestnicy.push_back(&zawodnicy[j]);
    } else {
        points = {0, 200, 250};
        pt = 100;
        for (auto& z : zawodnicy)
            if (z.getAge() <= 21)
                uczestnicy.push_back(&z);
    }
    int week = cup.getTydzien() - 1;
    cout << i+1 << ". " << cup.info() << endl;
    srand(time(NULL));
    for (int j = 0; j < 8; ++j) {
        uczestnicy[j]->getRealna(sx);
        uczestnicy[j]->seeding = to_string(j+1);
        uczestnicy[j]->gpts = 0;
    }
    // ... dalsza część symulacji ATP/WTA Finals,
    // analogiczna do oryginalnego kodu
}

void simTurniej(vector<Zawodnik>& zawodnicy, Turniej& cup,
                vector<Mecz>& kwali, vector<Mecz>& turniej,
                int i, unordered_map<int, set<int>>& wystepy)
{
    if (cup.getRng().find("Finals") != string::npos) {
        simFinals(zawodnicy, cup, turniej, i);
        return;
    }
    cup.setInfos();
    cup.setMain();
    cup.setQual();
    int n = cup.getN(), qil = cup.getQil(), week = cup.getTydzien() - 1;
    vector<int> seedy    = cup.getSeedy();
    vector<int> seedyq   = cup.getSeedyQ();
    vector<int> byes     = cup.getByes();
    vector<int> points   = cup.getPoints();
    vector<Zawodnik*> uczestnicy, qualp;
    cout << i+1 << ". " << cup.info() << endl;

    // ... dalsza część symulacji kwalifikacji i turnieju głównego,
    // analogiczna do oryginalnego kodu
}

// ------------------------------
// Global containers
// ------------------------------

vector<Zawodnik> atp;
vector<Zawodnik> wta;
vector<Mecz> turniej;
vector<Mecz> kwali;
vector<Turniej> season;
