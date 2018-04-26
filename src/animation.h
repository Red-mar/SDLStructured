#ifndef ANIMATION_H
#define ANIMATION_H

#include "sprite.h"
#include <vector>

class Animation : public Sprite
{
    public:
        Animation(Window* window, int width, int height, std::string filepath, int maxFrames, int framesOnY, int loops=-1);
        ~Animation();

        Animation(const Animation &) = delete;
        Animation &operator=(const Animation &) = delete;

        virtual void update(float dt=0);
        void setAnimation(int width, int height, std::string filepath, int amount, int loops=-1);

        void nextframe();
        void prevFrame();
        void firstFrame();
        void lastFrame();
        void goTo(int frame);
        void start();
        void stop();
        void restart();
        bool isRunning();
        void setLoopAmount(int times=-1);
        void setAnimationSpeed(int speed);
        int getAnimationSpeed();


    private:
        std::vector<Rectangle*> spriteclip;
        int width;
        int height;

        float frametime;
        bool running;
        int curFrame;
        int maxFrames;
        int framesOnY;
        int animationSpeed;
        int loops;
        int timesLooped;
};

#endif // !ANIMATION_H
