#ifndef ITEM_H
#define ITEM_H

#include "sprite.h"
#include "FacingDirection.h"
#include "particleemitter.h"

class Item
{
    public:
        Item(Window* window, std::string name, std::string filename, int xOffset, int yOffset);
        ~Item();

        void update(float dt);
        void render(float cameraX, float cameraY, float posX, float posY);

        void setFacingDirection(FacingDirection fd);
        void setPosition(float x, float y);
        void setParticleEmitter(ParticleEmitter* pe);

        int getXOffset();
        int getYOffset();

    private:
        Sprite* sprite;
        FacingDirection facingDirection;
        std::string name;
        float posX, posY;

        ParticleEmitter* particleEmitter;

        int xOffset; // maybe should just match it in the picture idk
        int yOffset;
};

#endif // !ITEM_H
