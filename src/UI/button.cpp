#include "button.h"

Button::Button(Window *window, float x, float y, int w, int h) : window(window),
                                                                 UIElement(x, y, w, h),
                                                                 image(nullptr)
{
    image = new Sprite(window, "assets/button.png");
}

Button::~Button()
{
    delete image;
}

void Button::update(float dt)
{
}

void Button::render(float cameraX, float cameraY)
{
    image->render(position->x - cameraX,
                  position->y - cameraY);
}