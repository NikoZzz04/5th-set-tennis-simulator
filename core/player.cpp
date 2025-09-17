#include"player.h"

float MatchSide::getMidUm() const{
    return (serve+forehand+backhand+volley+power+speed+stamina+movement+mentality+intelligence)/13
}
string MatchSide::getName() const
{
    return name;
}

void MatchSide::setName(const string &newName)
{
    name = newName;
}

string MatchSide::getSurname() const
{
    return surname;
}

void MatchSide::setSurname(const string &newSurname)
{
    surname = newSurname;
}

string MatchSide::getGender() const
{
    return gender;
}

void MatchSide::setGender(const string &newGender)
{
    gender = newGender;
}

int MatchSide::getAge() const
{
    return age;
}

void MatchSide::setAge(int newAge)
{
    age = newAge;
}

string MatchSide::getNationality() const
{
    return nationality;
}

void MatchSide::setNationality(const string &newNationality)
{
    nationality = newNationality;
}

float MatchSide::getServe() const
{
    return serve;
}

void MatchSide::setServe(float newServe)
{
    serve = newServe;
}

float MatchSide::getForehand() const
{
    return forehand;
}

void MatchSide::setForehand(float newForehand)
{
    forehand = newForehand;
}

float MatchSide::getBackhand() const
{
    return backhand;
}

void MatchSide::setBackhand(float newBackhand)
{
    backhand = newBackhand;
}

float MatchSide::getVolley() const
{
    return volley;
}

void MatchSide::setVolley(float newVolley)
{
    volley = newVolley;
}

float MatchSide::getPower() const
{
    return power;
}

void MatchSide::setPower(float newPower)
{
    power = newPower;
}

float MatchSide::getSpeed() const
{
    return speed;
}

void MatchSide::setSpeed(float newSpeed)
{
    speed = newSpeed;
}

float MatchSide::getStamina() const
{
    return stamina;
}

void MatchSide::setStamina(float newStamina)
{
    stamina = newStamina;
}

float MatchSide::getMovement() const
{
    return movement;
}

void MatchSide::setMovement(float newMovement)
{
    movement = newMovement;
}

float MatchSide::getMentality() const
{
    return mentality;
}

void MatchSide::setMentality(float newMentality)
{
    mentality = newMentality;
}

float MatchSide::getIntelligence() const
{
    return intelligence;
}

void MatchSide::setIntelligence(float newIntelligence)
{
    intelligence = newIntelligence;
}

MatchSide::MatchSide(const string &name, const string &surname, int age, const string &nationality, float serve, float forehand, float backhand, float volley, float power, float speed, float stamina, float movement, float mentality, float intelligence) : name(name),
    surname(surname),
    age(age),
    nationality(nationality),
    serve(serve),
    forehand(forehand),
    backhand(backhand),
    volley(volley),
    power(power),
    speed(speed),
    stamina(stamina),
    movement(movement),
    mentality(mentality),
    intelligence(intelligence)
{}

