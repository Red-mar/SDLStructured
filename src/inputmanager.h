#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "sdl.hpp"
#include "inputdefinitions.h"
#include "shapes.h"

class InputManager
{
    public:

    static InputManager* getInstance();

    void update(float cameraX=0, float cameraY=0);

    bool isKeyDown(int key);
    bool isKeyUp(int key);
    bool shift();
    bool ctrl();
    bool alt();

    bool isMouseDown(MouseButton button);
    bool isMouseUp(MouseButton button);

    bool isKeyPressed(KeyboardKey key);
    bool isMousePressed(MouseButton button);

    bool quitRequested();

    int getMouseX();
    int getMouseY();

    void lock();
    void unlock();

    bool isMouseInside(Rectangle rectangle);
    //static bool isPrintable(SDL_KeyCode key);

    //bool isPrintableKeyDown();
    //std::string getCurPrintableKey();

    InputManager();

    //InputManager(InputManager const&) {};
    //void operator=(InputManager const&) {};

    private:
        static InputManager* instance;
        const uint8_t* keyboard;
        uint32_t mouse;
        int mouseX;
        int mouseY;
        bool keyDown[KEYBOARD_SIZE];
        bool keyUp[KEYBOARD_SIZE];
        bool mouseDown[MOUSE_MAX];
        bool mouseUp[MOUSE_MAX];
        bool will_quit;
        bool isLocked;

    //bool isMouseInside(Rectangle rectangle);
};

#endif // !INPUTMANAGER_H
