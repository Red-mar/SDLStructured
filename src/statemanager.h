#ifndef StateManager_H
#define StateManager_H

#include "gamestate.h"
#include "window.h"

#include "inputmanager.h"

class StateManager
{
    public:
        StateManager(Window* window);

        virtual ~StateManager();

        void run();
    private:
        Window* window;
        GameState* currentState;
        int sharedInfo;
};

#endif // !StateManager_H
