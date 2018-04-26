#ifndef UIELEMENT_H
#define UIELEMENT_H

#include "..\shapes.h"

class UIElement
{
    public:
        UIElement(float x = 0.0f, float y = 0.0f, int w = 0, int h = 0);
        virtual ~UIElement();

        UIElement(const UIElement &) = delete;
        UIElement &operator=(const UIElement &) = delete;

        virtual void update(float dt) = 0;
        virtual void render(float cameraX, float cameraY) = 0;
        
        float getX();
        float getY();
        float getCenterX();
        float getCenterY();
        int getWidth();
        int getHeight();

        Point* position;

        Rectangle* box;
};

#endif // !UIELEMENT_H
