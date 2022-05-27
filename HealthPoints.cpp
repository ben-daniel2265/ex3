#ifndef EX3_HealthPoints_Source
#define EX3_HealthPoints_Source

#include "HealthPoints.h"

HealthPoints::HealthPoints(int maxHealthPoints)
{
    if(maxHealthPoints <= 0){
        throw InvalidArgument();
    }

    this->m_maxHealthPoints = maxHealthPoints;
    this->m_healthPoints = maxHealthPoints;
}


HealthPoints& HealthPoints::operator+=(const HealthPoints& hp)
{
    this->m_healthPoints += hp.m_healthPoints;
    if(this->m_healthPoints > this->m_maxHealthPoints){
        this->m_healthPoints = this->m_maxHealthPoints;
    }

    return *this;
}


HealthPoints& HealthPoints::operator-=(const HealthPoints& hp)
{
    this->m_healthPoints -= hp.m_healthPoints;
    if(this->m_healthPoints < 0){
        this->m_healthPoints = 0;
    }

    return *this;
}


bool operator==(const HealthPoints& hp1, const HealthPoints& hp2)
{
    return hp1.m_healthPoints == hp2.m_healthPoints;
}


bool operator>(const HealthPoints& hp1, const HealthPoints& hp2)
{
    return hp1.m_healthPoints > hp2.m_healthPoints;
}


bool operator<(const HealthPoints& hp1, const HealthPoints& hp2)
{
    return hp1.m_healthPoints < hp2.m_healthPoints;
}


std::ostream& operator<<(std::ostream& os, const HealthPoints& hp)
{
    os << hp.m_healthPoints << '(' << hp.m_maxHealthPoints << ')';
    return os;
}


HealthPoints operator+(const HealthPoints& hp, const int num)
{
    HealthPoints result = hp;
    result += num;
    return result;
}


HealthPoints operator+(const int num, const HealthPoints& hp)
{
    HealthPoints result = hp;
    result += num;
    return result;
}


HealthPoints operator-(const HealthPoints& hp1, const HealthPoints& hp2)
{
    HealthPoints result = hp1;
    result -= hp2;
    return result;
}


bool operator!=(const HealthPoints& hp1, const HealthPoints& hp2)
{
    return !(hp1 == hp2);
}


bool operator>=(const HealthPoints& hp1, const HealthPoints& hp2)
{
    return (hp1 == hp2)||(hp1 > hp2);
}


bool operator<=(const HealthPoints& hp1, const HealthPoints& hp2)
{
    return (hp1 == hp2)||(hp1 < hp2);
}


#endif //EX3_HealthPoints_Source