#include"player.h"

float Player::getMidUm() const{
    return (serve+forehand+backhand+volley+power+speed+stamina+movement+mentality+intelligence)/13;
}
string Player::getName() const
{
    return name;
}

void Player::setName(const string &newName)
{
    name = newName;
}

string Player::getSurname() const
{
    return surname;
}

void Player::setSurname(const string &newSurname)
{
    surname = newSurname;
}

string Player::getGender() const
{
    return gender;
}

void Player::setGender(const string &newGender)
{
    gender = newGender;
}

int Player::getAge() const
{
    return age;
}

void Player::setAge(int newAge)
{
    age = newAge;
}

string Player::getNationality() const
{
    return nationality;
}

void Player::setNationality(const string &newNationality)
{
    nationality = newNationality;
}

float Player::getServe() const
{
    return serve;
}

void Player::setServe(float newServe)
{
    serve = newServe;
}

float Player::getForehand() const
{
    return forehand;
}

void Player::setForehand(float newForehand)
{
    forehand = newForehand;
}

float Player::getBackhand() const
{
    return backhand;
}

void Player::setBackhand(float newBackhand)
{
    backhand = newBackhand;
}

float Player::getVolley() const
{
    return volley;
}

void Player::setVolley(float newVolley)
{
    volley = newVolley;
}

float Player::getPower() const
{
    return power;
}

void Player::setPower(float newPower)
{
    power = newPower;
}

float Player::getSpeed() const
{
    return speed;
}

void Player::setSpeed(float newSpeed)
{
    speed = newSpeed;
}

float Player::getStamina() const
{
    return stamina;
}

void Player::setStamina(float newStamina)
{
    stamina = newStamina;
}

float Player::getMovement() const
{
    return movement;
}

void Player::setMovement(float newMovement)
{
    movement = newMovement;
}

float Player::getMentality() const
{
    return mentality;
}

void Player::setMentality(float newMentality)
{
    mentality = newMentality;
}

float Player::getIntelligence() const
{
    return intelligence;
}

void Player::setIntelligence(float newIntelligence)
{
    intelligence = newIntelligence;
}

Player::Player(const string &name, const string &surname, int age, const string &nationality, float serve, float forehand, float backhand, float volley, float power, float speed, float stamina, float movement, float mentality, float intelligence) : name(name),
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

