#include "gamestategame.h"
#include "statemanager.h"
#include "log.h"
#include "ui\messagelog.h"
#include "MidiFile.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <memory>

enum GameStateGameCommands
{
    COMMAND_QUIT,
    COMMAND_ADD_PLATFORM,
    COMMAND_INVERT_GRAVITY,
    COMMAND_FLY,
    COMMAND_ADD_CLOUD,
    COMMAND_HELP,
    COMMAND_CONTROLS,
    COMMAND_GIVE_UP
};

GameStateGame::GameStateGame(Window *window) : window(window),
                                               currentState(GameState::CONTINUE),
                                               bgMusic(nullptr),
                                               soundEffects(nullptr),
                                               testSprite(nullptr),
                                               gameArea(nullptr),
                                               player(nullptr),
                                               camera(nullptr)
{
}

GameStateGame::~GameStateGame()
{
}

void GameStateGame::load(int stack)
{
    UNUSED(stack);

    bgMusic = new Music("assets/test.mid");
    soundEffects = SoundEffects::getInstance();
    testSprite = new Sprite(window, "assets/bg.png");
    tileMap = new TileMap(window, "assets/firstMap");

    gameArea = new Rectangle(0, 0, 2560, 1920);

    int playerW = 39;
    int playerH = 64;

    float playerX = 39.f;
    float playerY = 64.f;

    player = new Player(window, playerX, playerY, playerW, playerH, 100, 250.0f);
    player->setBoundary(gameArea);

    Rectangle *cameraView = new Rectangle(0, 0, window->mWidth, window->mHeight);
    camera = new Camera(player, gameArea, cameraView);

    //NPC *newNPC = new NPC(window, 500.f, 500.f, 39, 64, 100, 250.0f);
    //newNPC->setBoundary(gameArea);
    //objects.push_back(newNPC);

    fallingObjects.push_back(player);
    for (auto tile : tileMap->getTiles())
    {
        objects.push_back(tile);
    }

    MessageLog *log = new MessageLog(window, 0, 0, 100, 100);
    uiElements["messageLog"] = log;
    Label *lblPlayerpos = new Label(window, window->mWidth / 2.0f, 0.f, 5, 5, "Pos");
    uiElements["lblPlayerpos"] = lblPlayerpos;
}

int GameStateGame::unload()
{
    delete bgMusic;
    //delete soundEffects;
    delete testSprite;
    delete camera;
    delete gameArea;
    delete tileMap;
    for (std::vector<GameObject *>::iterator it = objects.begin(); it != objects.end(); it++)
    {
        delete (*it);
    }
    objects.clear();
    for (std::vector<FallingObject *>::iterator it = fallingObjects.begin(); it != fallingObjects.end(); it++)
    {
        delete (*it);
    }
    fallingObjects.clear();
    for (std::vector<Block *>::iterator it = blocks.begin(); it != blocks.end(); it++)
    {
        delete (*it);
    }
    blocks.clear();

    for (std::unordered_map<std::string, UIElement *>::iterator it = uiElements.begin(); it != uiElements.end(); it++)
    {
        delete (it->second);
    }
    uiElements.clear();

    return 0;
}

GameState::StateCode GameStateGame::update(float dt)
{
    updateInput();
    for (auto object : objects)
    {
        object->update(dt);
    }
    for (auto fallingObject : fallingObjects)
    {
        fallingObject->update(dt);
    }
    for (auto block : blocks)
    {
        block->update(dt);
    }
    for (auto element : uiElements)
    {
        element.second->update(dt);
    }

    //((Label *)uiElements["lblPlayerpos"])->setText("x:" + std::to_string(player->position->x) + " y:" + std::to_string(player->position->y));

    camera->update(dt);
    checkCollisions();

    return currentState;
}

void GameStateGame::checkCollisions()
{
    for (auto fallingObject : fallingObjects)
    {
        fallingObject->commitMovement(objects, fallingObjects, blocks);
    }
}

void GameStateGame::render()
{
    testSprite->render(0 - camera->getX(), 0 - camera->getY());
    testSprite->render(1280 - camera->getX(), 0 - camera->getY());
    testSprite->render(0 - camera->getX(), 960 - camera->getY());
    testSprite->render(1280 - camera->getX(), 960 - camera->getY());

    for (auto fallingObject : fallingObjects)
    {
        fallingObject->render(camera->getX(), camera->getY());
    }
    for (auto block : blocks)
    {
        block->render(camera->getX(), camera->getY());
    }
    tileMap->render(camera->getX(), camera->getY());

    for (auto element : uiElements)
    {
        element.second->render(0, 0);
    }
}

void GameStateGame::updateInput()
{
    InputManager *input = InputManager::getInstance();

    input->update();
    if (input->quitRequested())
    {
        currentState = GameState::QUIT;
    }

    if ((input->isKeyDown(KEY_ESCAPE)) ||
        (input->isKeyDown(KEY_Q)))
        currentState = GameState::QUIT;

    if (input->isKeyDown(KEY_1))
    {
        currentState = GameState::MAIN_MENU;
    }

    if (input->isMouseDown(MOUSE_LEFT))
    {
        Log::debug("Left mouse click");
        Log::debug(std::to_string(input->getMouseX()));
    }

    if (input->isKeyUp(KEY_4))
    {
        for (size_t i = 0; i < 100; i++)
        {
                    NPC *newNPC = new NPC(window, 39.f, 64.f, 39, 64, 100, 250.0f);
        newNPC->setBoundary(gameArea);
        fallingObjects.push_back(newNPC);   
        }
    }

    if (input->isKeyDown(KEY_5))
    {
        Log::debug(std::to_string(window->getFramerateLimit()));
        if (window->getFramerateLimit() == 0)
        {
            Log::debug("Setting framelimit to 60");
            window->setFramerateLimit(60);
        }
        else
        {
            Log::debug("Setting framelimit to infinity");
            window->setFramerateLimit(0);
        }
    }

    if (input->isKeyDown(KEY_6))
    {
        player->setCollision(!player->isCollidable());
        ((MessageLog *)uiElements["messageLog"])->AddMessage("Collision set to " + std::to_string(player->isCollidable()));
    }
    if (input->isKeyDown(KEY_7))
    {
        if (!bgMusic->isPlaying())
        {
            bgMusic->play(-1, 1000);
            ((MessageLog *)uiElements["messageLog"])->AddMessage("Playing music.");
        }
        else
        {
            bgMusic->fadeOut(1000);
            ((MessageLog *)uiElements["messageLog"])->AddMessage("Stoping music.");
        }

        Color bgcolor;
        bgcolor.randomize();
        window->setBackgroundColor(bgcolor);
    }

    if (input->isKeyDown(KEY_8))
    {
        std::string filename;
        if (tileMap->getMapFilename() == "assets/firstMap")
        {
            filename = "assets/secondMap";
        }
        else
        {
            filename = "assets/firstMap";
        }
        delete tileMap;

        std::vector<GameObject *>::iterator it;
        for (it = objects.begin(); it != objects.end();)
        {
            if (Tile *tile = dynamic_cast<Tile *>(*it))
            {
                delete tile;
                it = objects.erase(it);
            }
            else
                it++;
        }

        tileMap = new TileMap(window, filename);

        for (auto tile : tileMap->getTiles())
        {
            objects.push_back(tile);
        }
    }

    if (input->isKeyDown(KEY_9))
    {
        // temp
        if (window->mHeight == 1080)
        {
            window->resize(800, 600, 0);
        }
        else
        {
            window->resize(1920, 1080, SDL_WINDOW_FULLSCREEN_DESKTOP);
        }

        camera->setCameraView(new Rectangle(camera->getX(), camera->getY(), window->mWidth, window->mHeight));
    }

    if (input->isKeyDown(KEY_0))
    {
        Log::debug(std::to_string(soundEffects->getVolume()));
        soundEffects->play("test");
    }

    if (input->isKeyDown(KEY_MINUS))
    {
        midiFileTest();
    }
}

void GameStateGame::midiFileTest()
{
    Sprite *spr = new Sprite(window, "assets/hello.bmp");

    smf::MidiFile midifile;
    std::ifstream file("assets/test.mid");
    if (!file.is_open())
        Log::error("Unable to load file: assets/test.mid");
    midifile.read(file);

    midifile.doTimeAnalysis();
    midifile.linkNotePairs();
    //midifile.joinTracks();

    int tracks = midifile.getTrackCount();
    int tpq = midifile.getTicksPerQuarterNote();

    for (int track = 0; track < tracks; track++)
    {
        for (int event = 0; event < midifile[track].size(); event++)
        {
            if (midifile[track][event].isNoteOn())
            {

                int notenumber = 0;
                notenumber = midifile[track][event][1]; //+ midifile[track][event][1];
                objects.push_back(new Block(window,
                                            midifile[track][event].tick,                         // X
                                            (notenumber * 23),                                   // Y
                                            midifile[track][event].getDurationInSeconds() * 300, // W
                                            30,                                                  // Height
                                            spr,                                                 // Sprite
                                            tpq * 1.725)                                         // Speed
                );
            }
        }
    }

    file.close();
    Log::log("closed file");
    if (!bgMusic->isPlaying())
    {
        bgMusic->play(-1, 1000);
        ((MessageLog *)uiElements["messageLog"])->AddMessage("Playing music.");
    }
}