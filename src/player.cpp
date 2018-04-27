#include <cmath>
#include "player.h"
#include "inputmanager.h"
#include "gamestategame.h"
#include "log.h"

Player::Player(Window *window, float x, float y, int w, int h, int hp, float acceleration) : FallingObject(x, y, w, h),
                                                                                             Damageable(hp),
                                                                                             window(window),
                                                                                             acceleration(acceleration),
                                                                                             stoppedThreshold(acceleration / 5.f),
                                                                                             facingDirection(RIGHT),
                                                                                             isJumping(false),
                                                                                             isDoubleJumping(false),
                                                                                             win(false),
                                                                                             thrust(600),
                                                                                             damaging(false),
                                                                                             currentAnimation(nullptr),
                                                                                             soundEffects(nullptr),
                                                                                             movingPlatform(nullptr),
                                                                                             equipment(nullptr)
{
    addType(PLAYER_TYPE);
    addType(DAMAGEABLEOBJECT_TYPE);
    soundEffects = SoundEffects::getInstance();
    equipment = new Equipment();
    equipment->equip(EquipmentType::HEAD, new Item(window, "cool hat", "assets/hat.png", 5, 10));

    animations.resize(ANIMATION_MAX);
    animations[IDLE] = new Animation(window, w, h, "assets/idle.png", 3, 3);
    animations[RUNNING] = new Animation(window, w, h, "assets/walking.png", 4, 4);
    animations[JUMPING] = new Animation(window, w, h, "assets/jump.png", 1, 1);
    animations[LAYING] = new Animation(window, w, h, "assets/down.png", 1, 1);
    currentAnimation = animations[IDLE];
}

Player::~Player()
{
    for (std::vector<Animation *>::iterator it = animations.begin(); it != animations.end(); it++)
    {
        delete (*it);
    }
    delete equipment;
}

void Player::update(float dt)
{
    preUpdate(dt);
    currentAnimation->update(dt);

    if (boundaryStatus == ON_GROUND)
    {
        jump(false);
        currentAnimation = animations[IDLE];
    }

    if (isFalling())
    {
        boundaryStatus = OFF_GROUND;
        currentAnimation = animations[JUMPING];
    }
    if (box->bottom == boundary.bottom)
    {
        boundaryStatus = ON_GROUND;
        currentAnimation = animations[IDLE];
    }

    updateInput();

    float a = 8.0f * dt;
    if (boundaryStatus == OFF_GROUND)
        a *= 0.07f;

    // http://higherorderfun.com/blog/2012/05/20/the-guide-to-implementing-2d-platformers/
    this->vx = (a * this->targetVx) + ((1 - a) * this->vx);

    // Method 2 of accelerating
    //
    // http://earok.net/sections/articles/game-dev/theory/simplified-acceleration-games
    //this->vx += ((this->targetVx - this->vx) * a);

    if (fabs(vx) < (stoppedThreshold * dt))
    {
        vx = 0;
        if (boundaryStatus == ON_GROUND)
            currentAnimation = animations[IDLE];
    }

    if (movingPlatform != NULL)
    {
        position->x -= movingPlatform->getNoteSpeed() * dt;
    }
    if (boundaryStatus == OFF_GROUND && movingPlatform != NULL)
    {
        vx -= (movingPlatform->getNoteSpeed() * 5) * dt;
        movingPlatform = NULL;
    }

    if (damaging)
    {
        if (lastCollisionHit.right)
        {
            boundaryStatus = OFF_GROUND;
            currentAnimation = animations[JUMPING];
            vx = -300;
            vy = -250;
        }
        else if (lastCollisionHit.left)
        {
            boundaryStatus = OFF_GROUND;
            currentAnimation = animations[JUMPING];
            vx = 300;
            vy = -250;
        }

        damaging = false;
        lastCollisionHit = {false, false, false, false};
    }

    if (!isDead())
    {
        desiredPosition->addX(vx * dt);
        desiredPosition->addY(vy * dt);
    }
}

void Player::render(float cameraX, float cameraY)
{
    currentAnimation->setFlip((facingDirection == RIGHT) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);

    currentAnimation->render(position->x - cameraX,
                             position->y - cameraY);

    equipment->update(0.f, facingDirection, position->x, position->y);
    equipment->render(cameraX, cameraY);
}

void Player::updateInput()
{
    InputManager *input = InputManager::getInstance();

    float turbo = 1.7f;
    if (damaging)
    {
        return;
    }

    if (input->isKeyPressed(KEY_A) || input->isKeyPressed(KEY_LEFT))
    {
        targetVx = (-1 * acceleration);
        facingDirection = LEFT;
        if (boundaryStatus == ON_GROUND)
            currentAnimation = animations[RUNNING];

        if (input->shift())
        {
            targetVx *= turbo;
        }
    }

    if (input->isKeyPressed(KEY_D) ||
        input->isKeyPressed(KEY_RIGHT))
    {
        this->targetVx = (this->acceleration);
        this->facingDirection = RIGHT;
        if (boundaryStatus == ON_GROUND)
            currentAnimation = animations[RUNNING];

        if (input->shift())
            this->targetVx *= turbo;
    }

    if (input->isKeyDown(KEY_W) ||
        input->isKeyDown(KEY_UP) ||
        input->isKeyPressed(KEY_Z))
    {
        this->jump();
        //this->jumpSFX->play();
    }

    if ((input->isKeyDown(KEY_DOWN) ||
         input->isKeyDown(KEY_S)) &&
        boundaryStatus == ON_GROUND)
    {
        currentAnimation = animations[LAYING];
    }

    if ((input->isKeyUp(KEY_DOWN) ||
         input->isKeyUp(KEY_S)) &&
        boundaryStatus == ON_GROUND)
    {
        currentAnimation = animations[IDLE];
    }

    if (input->isKeyDown(KEY_DELETE))
    {
        this->die();
    }

    if (input->isKeyDown(KEY_KEYPAD_PLUS))
    {
        currentAnimation->setAnimationSpeed(currentAnimation->getAnimationSpeed() + 1);
    }

    if (input->isKeyDown(KEY_KEYPAD_MINUS))
    {
        currentAnimation->setAnimationSpeed(currentAnimation->getAnimationSpeed() - 1);
    }

    if (input->isKeyDown(KEY_INSERT))
    {
        damage(10);
        Log::debug(std::to_string(getHitpoints()));
    }
    if (input->isKeyDown(KEY_HOME))
    {
        heal(10);
        Log::debug(std::to_string(getHitpoints()));
    }
}

void Player::jump(bool willJump)
{
    if (willJump && boundaryStatus == ON_GROUND)
    {
        if (isDoubleJumping)
        {
            return;
        }

        if (isJumping)
        {
            return;
            //isDoubleJumping = true;
        }
        soundEffects->play("jump");
        currentAnimation = animations[JUMPING];
        boundaryStatus = OFF_GROUND;
        isJumping = true;
        vy = (-1 * thrust);
    }
    else
    {
        isJumping = false;
        isDoubleJumping = false;
    }
}

void Player::fall()
{
}

void Player::die()
{
    damage(100000);
}

bool Player::isFalling()
{
    return (vy > 150.f ? true : false);
}

bool Player::hasWon()
{
    return win;
}

void Player::setMovingplatform(Block *platform)
{
    movingPlatform = platform;
}

void Player::collision(Observer *observer, CollisionHit hit)
{
    lastCollisionHit = hit;
    damaging = true;
    damage(10);
}