#include "animation.h"
#include "log.h"

Animation::Animation(Window* window, int width, int height, std::string filename, int maxFrames, int framesOnY, int loops):
    Sprite(window, filename),
    running(true),
    curFrame(0),
    maxFrames(maxFrames),
    framesOnY(framesOnY),
    loops(loops),
    timesLooped(0),
    frametime(0),
    width(width),
    height(height),
    animationSpeed(5)
    {
        int widthX = 0;
        int heightY = 0;
        int yFrames = 0;
        for (size_t i = 0; i < maxFrames; i++)
        {
            yFrames++;
            spriteclip.push_back(new Rectangle((float)widthX,(float)heightY, width, height));
            widthX += width;
            if (yFrames >= framesOnY)
            {
                yFrames = 0;
                widthX = 0;
                heightY += height;
            }
        }
        crop(spriteclip[0]);
        Log::debug("Animation::load " + filename);
    }

Animation::~Animation()
{
    //delete currentClip;
    for(std::vector<Rectangle*>::iterator it = spriteclip.begin(); it != spriteclip.end(); it++ )
    {
        delete (*it);
    }
    spriteclip.clear();
}

void Animation::stop()
{
}

void Animation::start()
{
}

bool Animation::isRunning()
{
    return running;
}

void Animation::update(float dt)
{
    crop(spriteclip[((int)frametime)]);

    frametime += animationSpeed * dt;
    if (frametime >= maxFrames) frametime = 0;
}

void Animation::setAnimationSpeed(int speed){
    if (speed <= 0) return;
    animationSpeed = speed;
}

int Animation::getAnimationSpeed()
{
    return animationSpeed;
}