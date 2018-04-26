#include "inputmanager.h"
#include "window.h"
#include "log.h"

InputManager* InputManager::instance = nullptr;

InputManager::InputManager():
    keyboard(nullptr),
    mouse(0),
    mouseX(0),
    mouseY(0),
    will_quit(false),
    isLocked(false)
{}

InputManager* InputManager::getInstance()
{
    if (!instance){
        instance = new InputManager();
    }

    return instance;
}

void InputManager::update(float cameraX, float cameraY)
{
    int i;
    for (i = 0; i < KEYBOARD_SIZE; i++)
    {
        keyDown[i] = false;
        keyUp[i] = false;
    }

    for (i = 0; i < MOUSE_MAX; i++)
    {
        mouseDown[i] = false;
        mouseUp[i] = false;
    }

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                will_quit = true;
                break;
            case SDL_TEXTINPUT:
                break;
            case SDL_KEYDOWN:
            {
                keyboard = SDL_GetKeyboardState(nullptr);
                int index = event.key.keysym.scancode;
                keyDown[index] = true;
            }
                break;
            case SDL_KEYUP:
            {
                keyboard = SDL_GetKeyboardState(nullptr);
                int index = event.key.keysym.scancode;
                keyUp[index] = true;
            }
                break;
            case SDL_MOUSEMOTION:
                mouseX = event.motion.x + (int)cameraX;
                mouseY = event.motion.y + (int)cameraY;
                break;
            case SDL_MOUSEBUTTONDOWN:
                mouse = SDL_GetMouseState(&mouseX, & mouseY);
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    mouseDown[MOUSE_LEFT] = true;
                } else if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    mouseDown[MOUSE_RIGHT] = true;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                mouse = SDL_GetMouseState(&mouseX, & mouseY);
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    mouseUp[MOUSE_LEFT] = true;
                } else if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    mouseUp[MOUSE_RIGHT] = true;
                }
                break;
            case SDL_MOUSEWHEEL:
                break;

        default:
            break;
        }
    }

}

bool InputManager::quitRequested()
{
    return will_quit;
}

bool InputManager::isKeyDown(int key)
{
    if (isLocked)
    {
        return false;
    }

    if (key < 0 || key >= KEYBOARD_SIZE)
    {
        return false;
    }

    return keyDown[key];
}

bool InputManager::isKeyUp(int key)
{
    if (isLocked)
    {
        return false;
    }

    if (key < 0 || key >= KEYBOARD_SIZE)
    {
        return false;
    }

    return keyUp[key];
}

bool InputManager::isKeyPressed(KeyboardKey key)
{
    if (isLocked)
    {
        return false;
    }

    if (!keyboard)
    {
        return false;
    }

    int sdl_key = static_cast<int>(key);

    if (keyboard[sdl_key])
    {
        return true;
    }

    return false;
}

bool InputManager::shift()
{
	return (instance->isKeyPressed(KEY_LEFT_SHIFT) ||
	        instance->isKeyPressed(KEY_RIGHT_SHIFT));
}
bool InputManager::ctrl()
{
	return (instance->isKeyPressed(KEY_LEFT_CTRL) ||
	        instance->isKeyPressed(KEY_RIGHT_CTRL));
}
bool InputManager::alt()
{
	return (instance->isKeyPressed(KEY_LEFT_ALT) ||
	        instance->isKeyPressed(KEY_RIGHT_ALT));
}

void InputManager::lock()
{
	this->isLocked = true;
}
void InputManager::unlock()
{
	this->isLocked = false;
}

bool InputManager::isMouseDown(MouseButton button)
{
    if (isLocked)
    {
        return false;
    }

    if (button == MOUSE_MAX)
    {
        return false;
    }

    return mouseDown[button];
}

bool InputManager::isMouseUp(MouseButton button)
{
        if (isLocked)
    {
        return false;
    }

    if (button == MOUSE_MAX)
    {
        return false;
    }

    return mouseUp[button];
}

bool InputManager::isMousePressed(MouseButton button)
{
	if (isLocked) return false;

	switch (button)
	{
	case MOUSE_LEFT:
		if (mouse & SDL_BUTTON(1))
			return true;
		break;

	case MOUSE_RIGHT:
		if (mouse & SDL_BUTTON(3))
			return true;
		break;

	default:
		break;
	}

	return false;
}

int InputManager::getMouseX()
{
    return mouseX;
}

int InputManager::getMouseY()
{
    return mouseY;
}

bool InputManager::isMouseInside(Rectangle rectangle)
{
    	if ((this->mouseX >= rectangle.x) &&
	    (this->mouseX <= rectangle.x + rectangle.w)
	    &&
	    (this->mouseY >= rectangle.y) &&
	    (this->mouseY <= rectangle.y + rectangle.h))
		return true;

	return false;
}