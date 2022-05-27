#ifndef EX3_HealthPoints_H
#define EX3_HealthPoints_H

#include <iostream>

class HealthPoints{
    int m_maxHealthPoints;
    int m_healthPoints;

    public:
    class InvalidArgument{};
    HealthPoints(int m_maxHealthPoints = 100);

    HealthPoints(const HealthPoints& hp) = default;
    ~HealthPoints() = default;
    HealthPoints& operator=(const HealthPoints& hp) = default;

    HealthPoints& operator+=(const HealthPoints& hp);
    HealthPoints& operator-=(const HealthPoints& hp);

    friend bool operator==(const HealthPoints& hp1, const HealthPoints& hp2);
    friend bool operator>(const HealthPoints& hp1, const HealthPoints& hp2);
    friend bool operator<(const HealthPoints& hp1, const HealthPoints& hp2);
    friend std::ostream& operator<<(std::ostream& os, const HealthPoints& hp);
};

HealthPoints operator+(const HealthPoints& hp, const int num);
HealthPoints operator+(const int num, const HealthPoints& hp);
HealthPoints operator-(const HealthPoints& hp1, const HealthPoints& hp2);

bool operator!=(const HealthPoints& hp1, const HealthPoints& hp2);
bool operator>=(const HealthPoints& hp1, const HealthPoints& hp2);
bool operator<=(const HealthPoints& hp1, const HealthPoints& hp2);

#endif //EX3_HealthPoints_H