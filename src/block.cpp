#include "block.h"

Block::Block(Window * window, float x, float y, int w, int h, Sprite* newSprite, int speed) : GameObject(x, y, w, h),
    window(window),
    noteSpeed(speed)
{
    sprite = newSprite;
}

Block::~Block()
{
    //delete sprite;
}

void Block::update(float dt)
{
    position->x -= (noteSpeed) * dt;
    box->setX(position->x);
}

void Block::render(float cameraX, float cameraY)
{
    sprite->setSize(box->w, box->h);
    sprite->render(position->x - cameraX,
                   position->y - cameraY);
}

int Block::getNoteSpeed()
{
    return noteSpeed;
}