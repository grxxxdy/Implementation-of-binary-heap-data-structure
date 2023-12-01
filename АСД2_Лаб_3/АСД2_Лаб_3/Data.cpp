#include <cstdlib>

struct Data
{
    int health;
    int damage;
    int level;

    Data()
    {
        health = rand() % 101;
        damage = rand() % 201;
        level = rand() % 101;
    }

    bool operator<(const Data& element) const
    {
        if (this->damage != element.damage)
        {
            return this->damage < element.damage;
        }

        if (this->level != element.level)
        {
            return this->level < element.level;
        }

        return this->health < element.health;
    }

    bool operator>(const Data& element) const
    {
        return element < *this;
    }

    bool operator==(const Data& element) const
    {
        return this->damage == element.damage && this->level == element.level && this->health == element.health;
    }
};