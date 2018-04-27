#ifndef FALLINGOBJECT_H
#define FALLINGOBJECT_H

#include "gameobject.h"
#include <vector>
#include "block.h"

class FallingObject : public GameObject
{
    public:
        FallingObject(float x, float y, int w, int h);
        virtual ~FallingObject();

        void preUpdate(float dt);
        void setVX(float nvx);
        void setVY(float nyx);

        Rectangle* desiredPosition;
    private:
        
    protected:
        float vx;
        float vy;
        float ax;
        float ay;

        float targetVx;
};

#endif // !FALLINGOBJECT_H
