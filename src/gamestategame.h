#ifndef GAMESTATEGAME_H
#define GAMESTATEGAME_H

#include "gamestate.h"
#include "sdl.hpp"
#include "music.h"
#include "soundeffects.h"
#include "sprite.h"
#include "window.h"
#include "inputmanager.h"
#include "log.h"
#include "player.h"
#include "npc.h"
#include "camera.h"
#include "block.h"
#include <vector>
#include <unordered_map>
#include "UI\Label.h"
#include "UI\uielement.h"
#include "tilemap.h"
#include "collisiondetector.h"

class GameStateGame: public GameState
{
    public:
        GameStateGame(Window* window);
        virtual ~GameStateGame();

        void load(int stack=0);
        int unload();
        GameState::StateCode update(float dt);

        void render();
    private:
        void updateInput();
        void checkCollisions();
        CollisionDetector collisionDetector;
        GameState::StateCode currentState;
        Window* window;
        Music* bgMusic;
        SoundEffects* soundEffects;
        Sprite* testSprite;
        Player* player;
        TileMap* tileMap;
        //Block* block;
        std::vector<GameObject*> objects;
        //std::vector<UIElement*> uiElements;
        std::unordered_map<std::string, UIElement*> uiElements;

        SDL_TimerID timerID;

        Rectangle* gameArea;
        Camera* camera;


        void midiFileTest();
};

#endif // !GAMESTATEGAME_H
