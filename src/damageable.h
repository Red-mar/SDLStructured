#ifndef DAMAGEABLE_H
#define DAMAGEABLE_H

class Damageable 
{
    public:
        Damageable(int hp);

        void heal(int hp);
        void damage(int hp);
        bool isDead();
        int getHitpoints();
    private:
        int maxHitpoints;
        int currentHitpoints;

};

#endif // !DAMAGEABLE_H
