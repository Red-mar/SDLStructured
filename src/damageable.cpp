#include "damageable.h"

Damageable::Damageable(int hp) : maxHitpoints(hp),
    currentHitpoints(hp)
{
}

void Damageable::heal(int hp)
{
    if((currentHitpoints + hp) >= maxHitpoints) currentHitpoints = maxHitpoints;
    else currentHitpoints += hp;
}

void Damageable::damage(int hp)
{
    if ((currentHitpoints - hp) <= 0) currentHitpoints = 0;
    else currentHitpoints -= hp;
}

int Damageable::getHitpoints()
{
    return currentHitpoints;
}

bool Damageable::isDead()
{
    return currentHitpoints <= 0;
}