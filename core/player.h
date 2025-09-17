#ifndef PLAYER_H
#define PLAYER_H

#include<string>
using namespace std;

class MatchSide
{
    string name;
    string surname;
    string gender;
    int age;
    string nationality;
    float serve;
    float forehand;
    float backhand;
    float volley;
    float power;
    float speed;
    float stamina;
    float movement;
    float mentality;
    float intelligence;
public:
    MatchSide(const string &name, const string &surname, int age, const string &nationality, float serve, float forehand, float backhand, float volley, float power, float speed, float stamina, float movement, float mentality, float intelligence);
    float getMidUm() const;
    string getName() const;
    void setName(const string &newName);
    string getSurname() const;
    void setSurname(const string &newSurname);
    string getGender() const;
    void setGender(const string &newGender);
    int getAge() const;
    void setAge(int newAge);
    string getNationality() const;
    void setNationality(const string &newNationality);
    float getServe() const;
    void setServe(float newServe);
    float getForehand() const;
    void setForehand(float newForehand);
    float getBackhand() const;
    void setBackhand(float newBackhand);
    float getVolley() const;
    void setVolley(float newVolley);
    float getPower() const;
    void setPower(float newPower);
    float getSpeed() const;
    void setSpeed(float newSpeed);
    float getStamina() const;
    void setStamina(float newStamina);
    float getMovement() const;
    void setMovement(float newMovement);
    float getMentality() const;
    void setMentality(float newMentality);
    float getIntelligence() const;
    void setIntelligence(float newIntelligence);
};

#endif // PLAYER_H
