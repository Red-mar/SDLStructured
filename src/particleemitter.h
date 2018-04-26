#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

#include "particle.h"
#include <vector>
#include <unordered_map>

class ParticleEmitter
{
    public:
        ParticleEmitter(Window* window, float x, float y);
        ~ParticleEmitter();

        void render(float cameraX, float cameraY);
        void update(float dt);

        void setPosition(float x, float y);

    private:
        Window* window;
        std::vector<Particle*> particles;
        std::unordered_map<std::string, Sprite*> particleSprites;
        float posX, posY;
        int particleAmount;
};

#endif // !PARTICLEEMITTER_H
