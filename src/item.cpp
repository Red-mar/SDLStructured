#include "item.h"

Item::Item(Window* window, std::string name, std::string filename, int xOffset, int yOffset) :
    name(name),
    xOffset(xOffset),
    yOffset(yOffset),
    sprite(nullptr),
    particleEmitter(nullptr),
    posX(0),
    posY(0)
{
    sprite = new Sprite(window, filename);
}

Item::~Item()
{
    delete sprite;
    delete particleEmitter;
}

void Item::update(float dt, float x, float y)
{
    if(particleEmitter) {particleEmitter->update(dt); particleEmitter->setPosition(posX + sprite->getWidth()/2 + xOffset, posY + sprite->getHeight()/2 + yOffset);}

    posX = x - xOffset;
    posY = y - yOffset;
}

void Item::render(float cameraX, float cameraY)
{
    sprite->render(posX - cameraX, posY - cameraY);

    if(particleEmitter) particleEmitter->render(cameraX, cameraY);
}

int Item::getXOffset()
{
    return xOffset;
}

int Item::getYOffset()
{
    return yOffset;
}

void Item::setFacingDirection(FacingDirection fd)
{
    sprite->setFlip((fd == RIGHT) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void Item::setParticleEmitter(ParticleEmitter* pe)
{
    particleEmitter = pe;
}