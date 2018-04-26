#ifndef GAMESTATEMENU_H
#define GAMESTATEMENU_H

#include "gamestate.h"
#include "sprite.h"
#include "window.h"
#include "inputmanager.h"
#include <vector>
#include "UI\uielement.h"
#include "UI\button.h"
#include "UI\label.h"

class GameStateMenu : public GameState
{
    public:
        GameStateMenu(Window* window);
        ~GameStateMenu();

        void load(int stack=0);
        int unload();

        GameState::StateCode update(float dt);

        void render();
    private:
        void updateInput();
        GameState::StateCode currentStateCode;
        Window* window;
        std::vector<UIElement*> uiElements;
};

#endif // GAMESTATEMENU_H
