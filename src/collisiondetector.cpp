#include "collisiondetector.h"
#include "fallingobject.h"
#include "player.h"

CollisionDetector::CollisionDetector()
{
}

void CollisionDetector::update() // this sucks
{
    for (auto object : observers)
    {
        if (object->isType(FALLINGOBJECT_TYPE))
        {
            CollisionHit collisionHit = {false, false, false, false};
            auto fObj = (FallingObject *)object;

            float oldX = fObj->desiredPosition->x;
            float oldY = fObj->desiredPosition->y;
            float oldBoxX = fObj->box->x;
            float oldBoxY = fObj->box->y;

            fObj->position->x -= fObj->box->x - fObj->desiredPosition->x;
            fObj->desiredPosition->setX(fObj->position->x);
            fObj->box->setX(fObj->desiredPosition->x);

            for (auto object : observers)
            {
                if (object->isType(NPC_TYPE)) continue;
                if (fObj != object && fObj->collidedWith(object))
                {
                    fObj->setVX(0);
                    fObj->position->x += oldBoxX - oldX;
                    fObj->desiredPosition->setX(fObj->position->x);
                    fObj->box->setX(fObj->desiredPosition->x);

                    if (fObj->box->center.x < object->box->center.x)
                    {
                        collisionHit.left = true;
                        if (fObj->isType(NPC_TYPE) && object->isType(PLAYER_TYPE))
                        {
                            Player *player = (Player *)object;
                            player->collision(fObj, collisionHit);
                        }
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
                        collisionHit.right = true;
                        if (fObj->isType(NPC_TYPE) && object->isType(PLAYER_TYPE))
                        {
                            Player *player = (Player *)object;
                            player->collision(fObj, collisionHit);
                        }
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

            fObj->position->y -= fObj->box->y - fObj->desiredPosition->y;
            fObj->desiredPosition->setY(fObj->position->y);
            fObj->box->setY(fObj->desiredPosition->y);

            for (auto object : observers)
            {
                if (object->isType(NPC_TYPE)) continue;
                if (fObj != object && fObj->collidedWith(object))
                {
                    fObj->setVY(0);
                    fObj->position->y += oldBoxY - oldY;
                    fObj->desiredPosition->setY(fObj->position->y);
                    fObj->box->setY(fObj->desiredPosition->y);

                    if (fObj->box->center.y < object->box->center.y)
                    {
                        // others bottom
                        fObj->boundaryStatus = ON_GROUND;
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

            fObj->box->copy(fObj->desiredPosition);

            fObj->actOnBoundaries();
        }
    }
}

void CollisionDetector::registerObserver(GameObject *observer)
{
    observers.push_back(observer);
}

void CollisionDetector::unregisterObserver(GameObject *observer)
{
    for (std::vector<GameObject *>::iterator it = observers.begin(); it != observers.end(); it++)
    {
        if ((*it) == observer)
        {
            observers.erase(it);
            return;
        }
    }
}

void CollisionDetector::notifyCollision(GameObject *observer)
{
    //observer->collision()
}
