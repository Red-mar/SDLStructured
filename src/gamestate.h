#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "window.h"

class GameState
{
    public:
        enum StateCode
        {
            QUIT, CONTINUE, MAIN_MENU, GAME_START, GAME_INSTRUCTION, GAME_OVER
        };

        virtual void load(int stack=0) = 0;
        virtual int unload() = 0;

        virtual StateCode update(float dt) = 0;

        virtual void render() = 0;
    private:
};

#endif // !GAMESTATE_H
