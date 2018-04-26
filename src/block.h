#ifndef BLOCK_H
#define BLOCK_H

#include "GameObject.h"
#include "window.h"
#include "color.h"
#include "shapes.h"
#include "sprite.h"

class Block : public GameObject
{
    public:
        Block(Window* window, float x, float y, int w, int h, Sprite* newSprite, int speed);
        ~Block();

        void update(float dt);
        void render(float cameraX=0,float cameraY=0);

        int getNoteSpeed();

    private:
        Window* window;
        Sprite* sprite;

        int noteSpeed;
};

#endif // !BLOCK_H
