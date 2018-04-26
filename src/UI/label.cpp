#include "label.h"
#include "..\log.h"

Label::Label(Window* window, float x, float y, int w, int h, std::string text):
    UIElement(x, y, w, h),
    window(window)
{
    labelText = new Text(window);
    setText(text);
    timeAlive = 10;
}

Label::~Label()
{
    delete labelText;
}

void Label::setText(std::string text)
{
    labelText->loadText(text, {255,255,255,255});
    box->copy(new Rectangle(getX(), getY(), labelText->getTextWidth(), labelText->getTextHeight()));
}

void Label::setFontSize(int size)
{
    labelText->setTextSize(size);
}

void Label::update(float dt)
{
    timeAlive -= 1 * dt;
}

void Label::render(float cameraX, float cameraY)
{
    labelText->render(position->x - cameraX, position->y - cameraY);
}

bool Label::isDead()
{
    return timeAlive < 0;
}