#ifndef BUTTON_H
#define BUTTON_H

#include "uielement.h"
#include "..\sprite.h"

class Button : public UIElement
{
    public:
        Button(Window* window, float x, float y, int w, int h);
        ~Button();

        void update(float dt);
        void render(float cameraX = 0.0f, float cameraY = 0.0f);
    private:
        Sprite* image;
        Window* window;
};

#endif // !BUTTON_H
