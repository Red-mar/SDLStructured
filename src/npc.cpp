#include "npc.h"
#include "player.h"

Npc::Npc(Window *window, float x, float y, int w, int h, int hp, float acceleration) : FallingObject(x, y, w, h),
                                                                                       Damageable(hp),
                                                                                       window(window),
                                                                                       acceleration(acceleration),
                                                                                       stoppedThreshold(acceleration / 5.f),
                                                                                       facingDirection(RIGHT),
                                                                                       isJumping(false),
                                                                                       thrust(700),
                                                                                       currentAnimation(nullptr),
                                                                                       soundEffects(nullptr),
                                                                                       movingPlatform(nullptr),
                                                                                       equipment(nullptr),
                                                                                       frametime((float)(rand() % 10))
{
    addType(NPC_TYPE);
    addType(DAMAGEABLEOBJECT_TYPE);
    soundEffects = SoundEffects::getInstance();
    equipment = new Equipment();

    Item *item = nullptr;
    switch (rand() % 3)
    {
    case 0:
    {
        item = new Item(window, "cool hat", "assets/hat.png", 5, 10);
        item->setParticleEmitter(new ParticleEmitter(window, position->x, position->y));
        equipment->equip(EquipmentType::HEAD, item);
        break;
    }
    case 1:
        equipment->equip(EquipmentType::HEAD, new Item(window, "cool hat", "assets/hat2.png", 5, 27));
        break;
    case 2:
        break;
    default:
        break;
    }

    animations.resize(ANIMATION_MAX);
    animations[IDLE] = new Animation(window, w, h, "assets/idle.png", 3, 3);
    animations[RUNNING] = new Animation(window, w, h, "assets/walking.png", 4, 4);
    animations[JUMPING] = new Animation(window, w, h, "assets/jump.png", 1, 1);
    currentAnimation = animations[IDLE];
}

Npc::~Npc()
{
    for (std::vector<Animation *>::iterator it = animations.begin(); it != animations.end(); it++)
    {
        delete (*it);
    }
    delete equipment;
}

void Npc::update(float dt)
{
    preUpdate(dt);
    currentAnimation->update(dt);
    frametime += 1 * dt;

    doMovement();

    if (boundaryStatus == ON_GROUND)
    {
        //jump(false);
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
    if (targetVx > 0)
    {
        this->facingDirection = RIGHT;
        if (boundaryStatus == ON_GROUND)
            currentAnimation = animations[RUNNING];
    }
    else
    {
        this->facingDirection = LEFT;
        if (boundaryStatus == ON_GROUND)
            currentAnimation = animations[RUNNING];
    }

    float a = 8.0f * dt;
    this->vx = (a * this->targetVx) + ((1 - a) * this->vx);

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

    // isAlive?
    if (!isDead())
    {
        desiredPosition->addX(vx * dt);
        desiredPosition->addY(vy * dt);
    }
    equipment->update(dt, facingDirection);
}

void Npc::render(float cameraX, float cameraY)
{
    currentAnimation->setFlip((facingDirection == RIGHT) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);

    currentAnimation->render(position->x - cameraX,
                             position->y - cameraY);

    equipment->render(cameraX, cameraY, box->x, box->y);
}

void Npc::jump(bool willJump)
{
    soundEffects->play("jump");
    currentAnimation = animations[JUMPING];
    vy = (-1 * thrust);
}

bool Npc::isFalling()
{
    return (vy > 150.f ? true : false);
}

void Npc::setMovingPlatform(Block *platform)
{
    movingPlatform = platform;
}

void Npc::doMovement()
{
    if (actionState == NO_ACTION)
    {
        switch (rand() % 3)
        {
        case 0:
            actionState = WALK_LEFT;
            break;
        case 1:
            actionState = WALK_RIGHT;
            break;
        case 2:
            actionState = STAND_STILL;
            break;
        default:
            break;
        }
    }

    switch (actionState)
    {
    case WALK_LEFT:
        targetVx = acceleration / -2;
        break;
    case WALK_RIGHT:
        targetVx = acceleration / 2;
        break;
    case STAND_STILL:
        targetVx = 0;
        break;
    default:
        break;
    }

    if (frametime > 10)
    {
        actionState = NO_ACTION;
        frametime = (float)(rand() % 5);
    }
}

void Npc::collision(Observer *observer, CollisionHit hit)
{
    
    //lastCollisionHit = hit;
    //damaging = true;
}
