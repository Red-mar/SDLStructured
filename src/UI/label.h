#ifndef LABEL_H
#define LABEL_H

#include "uielement.h"
#include "text.h"

class Label : public UIElement
{
    public:
        Label(Window* window, float x, float y, int w, int h, std::string text);
        ~Label();

        Label(const Label &) = delete;
        Label &operator=(const Label &) = delete;

        void setText(std::string text);
        void setFontSize(int size);

        void update(float dt);
        void render(float cameraX = 0.0f, float cameraY = 0.0f);

        bool isDead();

    private:
        Window* window;
        Text* labelText;
        float timeAlive;
};

#endif // !LABEL_H
