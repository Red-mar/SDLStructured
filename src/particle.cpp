#include "particle.h"
#include "log.h"

Particle::Particle(Window* window, float x, float y, Sprite* sprite) :
    window(window),
    posX(x - 15 + (rand() % 39)),
    posY(y - 30 + (rand() % 64)),
    frametime(rand() % 5),
    sprite(sprite),
    vx((rand() % 10) - 5),
    vy((rand() % 30)- 15)
{
}

Particle::~Particle()
{
    //delete sprite;
}

void Particle::update(float dt)
{
    frametime += 25 * dt;
    posY -= vy * dt;
    posX += vx * dt;
}

void Particle::render(float cameraX, float cameraY)
{
    sprite->render(posX - cameraX, posY - cameraY);
    //if (frametime % 2 == 0) sprite->render(posX - cameraX, posY - cameraY);
}

bool Particle::isDead()
{
    return frametime > 10;
}