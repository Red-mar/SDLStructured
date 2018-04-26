#include "FallingObject.h"
#include "physicsmanager.h"
#include "block.h"
#include "player.h"
#include "npc.h"

FallingObject::FallingObject(float x, float y, int w, int h) : GameObject(x, y, w, h),
                                                               desiredPosition(nullptr),
                                                               vx(0), vy(0),
                                                               ax(0), ay(0)
{
    desiredPosition = new Rectangle();
}

FallingObject::~FallingObject()
{
    delete desiredPosition;
}

void FallingObject::preUpdate(float dt)
{
    desiredPosition->copy(box);

    ay = 0;
    targetVx = 0;

    vy += (PhysicsManager::gravityAcceleration * dt);
}

void FallingObject::commitMovement(std::vector<GameObject *> objects, std::vector<FallingObject*> fallingObjects, std::vector<Block*> blocks)
{
    float oldX = desiredPosition->x;
    float oldY = desiredPosition->y;
    float oldBoxX = box->x;
    float oldBoxY = box->y;

    position->x -= box->x - desiredPosition->x;
    desiredPosition->setX(position->x);
    box->setX(desiredPosition->x);

    for (auto object : objects)
    {

        if (this != object && collidedWith(object))
        {
            vx = 0;
            position->x += oldBoxX - oldX;
            desiredPosition->setX(position->x);
            box->setX(desiredPosition->x);

            if (box->center.x < object->box->center.x)
            {
                // others right
                /* NOTE use for moving platform do not use dynamic cast for performance
                if (Block *note = dynamic_cast<Block *>(object))
                {
                    vx = 0;
                    position->x = (note->box->leftmost - box->w) - 2;
                    box->setX(position->x);
                }
                */
            }
            else
            {
                /*
                if (Block *note = dynamic_cast<Block *>(object))
                {
                    vx = 0;
                    position->x = (note->box->rightmost) + 2;
                    box->setX(position->x);
                }
                */
                // others left
            }
        }
    }

    position->y -= box->y - desiredPosition->y;
    desiredPosition->setY(position->y);
    box->setY(desiredPosition->y);

    for (auto object : objects)
    {
        if (this != object && collidedWith(object))
        {
            vy = 0;
            position->y += oldBoxY - oldY;
            desiredPosition->setY(position->y);
            box->setY(desiredPosition->y);

            if (box->center.y < object->box->center.y)
            {
                // others bottom
                boundaryStatus = ON_GROUND;
                /*
                if (Block *note = dynamic_cast<Block *>(object))
                {
                    if (Player *player = dynamic_cast<Player *>(this))
                    {
                        player->setMovingplatform(note);
                    }
                }
                */
            }
            else
            {
                // others top
            }
        }
    }

    box->copy(desiredPosition);

    actOnBoundaries();
}