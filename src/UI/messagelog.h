#ifndef MESSAGELOG_H
#define MESSAGELOG_H

#include "label.h"
#include <vector>

class MessageLog : public UIElement
{
    public:
        MessageLog(Window* window, float x, float y, int w, int h);
        ~MessageLog();

        void AddMessage(std::string message);
        void clearLog();

        void update(float dt);
        void render(float cameraX = 0.0f, float cameraY = 0.0f);

    private:
        Window* window;
        std::vector<Label*> log;
        int lines;

        void resetPosition();
};

#endif // !MESSAGELOG_H
