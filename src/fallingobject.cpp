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
    addType(FALLINGOBJECT_TYPE);
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

void FallingObject::setVX(float nvx)
{
    vx = nvx;
}

void FallingObject::setVY(float nyx)
{
    vy = nyx;
}