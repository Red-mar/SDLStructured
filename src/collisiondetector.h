#ifndef COLLISIONDETECTOR_H
#define COLLISIONDETECTOR_H

#include "gameobject.h"
#include <vector>

class CollisionDetector
{
    public:
        CollisionDetector();

        void update();

        void registerObserver(GameObject* observer);
        void unregisterObserver(GameObject* observer);
        void notifyCollision(GameObject* observer);

    private:
        std::vector<GameObject*> observers;
};

#endif // !COLLISIONDETECTOR_H
