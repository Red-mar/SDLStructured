#ifndef PARTICLE_H
#define PARTICLE_H

#include "sprite.h"

class Particle
{
    public:
        Particle(Window* window, float x, float y, Sprite* sprite);
        ~Particle();

        void render(float cameraX, float cameraY);
        void update(float dt);

        bool isDead();

    private:
        Window* window;
        float posX, posY;
        float frametime;
        Sprite* sprite;

        float vx;
        float vy;

};

#endif // !PARTICLE_H
