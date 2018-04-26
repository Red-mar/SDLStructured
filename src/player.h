#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "fallingobject.h"
#include "animation.h"
#include "window.h"
#include "soundeffects.h"
#include "block.h"
#include "particleemitter.h"
#include "equipment.h"
#include "facingdirection.h"
#include "damageable.h"

class Player: public FallingObject, public Damageable
{
    public:
        enum AnimationState { IDLE, RUNNING, JUMPING, LAYING, ANIMATION_MAX };

        Player(Window* window, float x, float y, int w, int h, int hp, float acceleration);
        virtual ~Player();

        void update(float dt);
        void render(float cameraX=0, float cameraY=0);
        void updateInput();
        void setHorizontalLimit(int left, int right);
        void setVerticalLimit(int top, int bottom);
        void setMovingplatform(Block * platform);

        void jump(bool willJump = true);

        void fall();

        bool isHittable();
        bool Dashing();
        bool isFalling();
        bool hasWon();

        void die();
        void died();

        void dealDamage();
    private:
        Window* window;
        float acceleration;
        float stoppedThreshold;

        Equipment* equipment;
        Animation* currentAnimation;
        std::vector<Animation*> animations;

        SoundEffects* soundEffects;
        Block* movingPlatform;

        FacingDirection facingDirection;
        bool hasHorizontalLimit;
        int rightmostLimitX;
        int leftmostLimitX;

        bool hasVerticalLimit;
        int topLimitY;
        int bottomLimitY;

        bool isJumping;
        bool isDoubleJumping;

        bool win;

        float thrust;
        bool damaging;
};

#endif // !PLAYER_H
