#include "messagelog.h"

MessageLog::MessageLog(Window *window, float x, float y, int w, int h) : window(window),
                                                                         UIElement(x, y, w, h)
{
}

MessageLog::~MessageLog()
{
    for(std::vector<Label*>::iterator it = log.begin(); it != log.end(); it++ )
    {
        delete (*it);
    }
    log.clear();
}

void MessageLog::AddMessage(std::string message)
{
    float lineY = this->getY();
    for (auto line : log)
    {
        lineY = lineY + line->getHeight();
    }
    Label *newMessage = new Label(window, getX(), lineY, 5, 5, message);
    log.push_back(newMessage);
}

void MessageLog::update(float dt)
{
    for (int i = 0; i < log.size(); ++i)
    {
        log[i]->update(dt);
        if (log[i]->isDead())
        {
            delete (log[i]);
            log.erase(log.begin() + i);
            resetPosition();
        }
    }
}

void MessageLog::render(float cameraX, float cameraY)
{
    for (auto line : log)
    {
        line->render(cameraX,
                     cameraY);
    }
}

void MessageLog::resetPosition()
{
    float lineY = this->getY();
    for (auto line : log)
    {
        line->position->y = lineY;
        lineY = lineY + line->getHeight();
    }
}