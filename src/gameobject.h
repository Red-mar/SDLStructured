#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "shapes.h"
#include "observer.h"
#include "log.h"

enum ObjectType
{
    FALLINGOBJECT_TYPE = 1,
    DAMAGEABLEOBJECT_TYPE = 2,
    PLAYER_TYPE = 4,
    NPC_TYPE = 8
};

enum BoundaryStatus
{
    ON_GROUND,
    OFF_GROUND
};

class GameObject : public Observer
{
    public:
        GameObject(float x= 0.0f, float y = 0.0f, int w = 0, int h = 0);
        virtual ~GameObject();

        virtual void update(float dt) = 0;
        virtual void render(float cameraX, float cameraY) = 0;
        bool collidedWith(GameObject* other);
        void placeOnTop(GameObject* other);
        void setBoundary(Rectangle boundarySet);
        void actOnBoundaries();

        float getX();
        float getY();
        float getCenterX();
        float getCenterY();
        int getWidth();
        int getHeight();

        void setCollision(bool collision);
        bool isCollidable();

        Point* position;

        Rectangle* box;
        Rectangle boundary;
        BoundaryStatus boundaryStatus;
        bool isType(ObjectType type);
        void addType(ObjectType type);

    private:
        bool canCollide;
        int objectType = 0;
};

#endif // !GAMEOBJECT_H
