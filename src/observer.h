#ifndef OBSERVER_H
#define OBSERVER_H

struct CollisionHit
{
    bool left = false;
    bool right = false;
    bool top = false;
    bool bottom = false;
};

class Observer
{
    public:
        Observer();

        virtual void collision(Observer* object, CollisionHit hit);
};

#endif // !OBSERVER_H
