#include "particleemitter.h"
#include "log.h"

ParticleEmitter::ParticleEmitter(Window* window, float x, float y):
    window(window),
    posX(x),
    posY(y),
    particleAmount(10)
{
    particleSprites["red"] = new Sprite(window, "assets/red.png");
    particleSprites["green"] = new Sprite(window, "assets/green.png");
    particleSprites["blue"] = new Sprite(window, "assets/blue.png");
    particles.resize(particleAmount);
    for (size_t i = 0; i < particleAmount; i++)
    {
        Sprite* sprite = particleSprites["red"];
            switch (rand() % 3)
           {
                case 0: sprite = particleSprites["red"]; break;
                case 1: sprite = particleSprites["blue"]; break;
                case 2: sprite = particleSprites["green"]; break;

                default:
                    break;
            }
        particles[i] = new Particle(window, posX, posY, sprite);
    }
}

ParticleEmitter::~ParticleEmitter()
{
    for (std::unordered_map<std::string, Sprite*>::iterator it = particleSprites.begin(); it != particleSprites.end(); it++ )
    {
        delete (it->second);
    }
    particleSprites.clear();

    for(std::vector<Particle*>::iterator it = particles.begin(); it != particles.end(); it++)
    {
        delete (*it);
    }
    particles.clear();
}

void ParticleEmitter::update(float dt)
{
    for (size_t i = 0; i < particles.size(); i++)
    {
        particles[i]->update(dt);
        if (particles[i]->isDead())
        {
            delete particles[i];
                    Sprite* sprite = particleSprites["red"];
            switch (rand() % 3)
           {
                case 0: sprite = particleSprites["red"]; break;
                case 1: sprite = particleSprites["blue"]; break;
                case 2: sprite = particleSprites["green"]; break;

                default:
                    break;
            }
            particles[i] = new Particle(window, posX, posY,sprite);
        }
    }
}

void ParticleEmitter::render(float cameraX, float cameraY)
{

    for(auto particle : particles)
    {
        particle->render(cameraX, cameraY);
    }
}

void ParticleEmitter::setPosition(float x, float y)
{
    posX = x;
    posY = y;
}