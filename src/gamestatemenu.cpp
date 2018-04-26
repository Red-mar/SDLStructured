#include "gamestatemenu.h"
#include "log.h"

GameStateMenu::GameStateMenu(Window *window) : window(window),
                                               currentStateCode(GameState::CONTINUE)
{
}

GameStateMenu::~GameStateMenu()
{
}

void GameStateMenu::load(int stack)
{
    UNUSED(stack);
    Button* btnTest = new Button(window, 250, 350, 50, 20);
    Label* lblTest = new Label(window, 200, 200, 5, 5, "WELCOME to the main menu");
    uiElements.push_back(btnTest);
    uiElements.push_back(lblTest);
}

int GameStateMenu::unload()
{
    for(std::vector<UIElement*>::iterator it = uiElements.begin(); it != uiElements.end(); it++ )
    {
        delete (*it);
    }

    return 0;
}

GameState::StateCode GameStateMenu::update(float dt)
{
    updateInput();
    for(auto element : uiElements)
    {
        element->update(dt);
    }

    return currentStateCode;
}

void GameStateMenu::render()
{
    for(auto element : uiElements)
    {
        element->render(0, 0);   
    }
}

void GameStateMenu::updateInput()
{
    InputManager *inputManager = InputManager::getInstance();

    inputManager->update();
    if (inputManager->quitRequested())
    {
        currentStateCode = GameState::QUIT;
    }
    if (inputManager->isKeyDown(KEY_0))
    {
        if (Label* label = dynamic_cast<Label*>(uiElements[1]))
        {
            label->setFontSize(72);
            label->setText("text!");
        }
    }
    if (inputManager->isKeyDown(KEY_5))
    {
        if (window->getFramerateLimit() == 0)
        {
            window->setFramerateLimit(60);
        } else {
            window->setFramerateLimit(0);
        }
    }
    if (inputManager->isMouseUp(MOUSE_LEFT) && inputManager->isMouseInside(uiElements[0]->box))
    {
        Log::debug("Clicked the button!");
        currentStateCode = GameState::GAME_START;
    }
}