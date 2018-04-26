#include "uielement.h"

UIElement::UIElement(float x, float y, int w, int h):
    position(nullptr),
    box(nullptr)
{ 
    position = new Point(x, y);
    box = new Rectangle(x, y, w, h);
}

UIElement::~UIElement()
{ 
    delete position;
    delete box;
}

float UIElement::getX()
{
    return box->x;
}

float UIElement::getY()
{
    return box->y;
}

float UIElement::getCenterX()
{
    return box->center.x;
}

float UIElement::getCenterY()
{
    return box->center.y;
}

int UIElement::getWidth()
{
    return box->w;
}

int UIElement::getHeight()
{
    return box->h;
}

