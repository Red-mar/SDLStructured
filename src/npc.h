#ifndef NPC_H
#define NPC_H

#include "fallingobject.h"
#include "window.h"
#include "block.h"
#include "animation.h"
#include "particleemitter.h"
#include <vector>
#include "soundeffects.h"
#include "facingdirection.h"
#include "equipment.h"

class NPC : public FallingObject
{
    public: 
        enum AnimationState { IDLE, RUNNING, JUMPING, ANIMATION_MAX};
        enum ActionState { WALK_LEFT, WALK_RIGHT, STAND_STILL, NO_ACTION, ACTION_MAX};

        NPC(Window * window, float x, float y, int w, int h, int hp, float acceleration);
        virtual ~NPC();

        void update(float dt);
        void render(float cameraX, float cameraY);
        void setMovingPlatform(Block* platform);
        void jump(bool willJump = true);
        void fall();

        bool isHittable();
        bool dashing();
        bool isFalling();
        
        void die();
        void died();

    private:
        void doMovement();

        Window* window;
        float acceleration;
        float stoppedThreshold;
        float frametime;

        Equipment* equipment;
        Animation* currentAnimation;
        std::vector<Animation*> animations;

        SoundEffects* soundEffects;
        Block* movingPlatform;
        FacingDirection facingDirection;
        ActionState actionState = NO_ACTION; 

        bool isJumping;
        float thrust;
};

#endif // !NPC_H
