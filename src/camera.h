#ifndef CAMERA_H
#define CAMERA_H

#include "shapes.h"
#include "player.h"

class Camera
{
    public:
        Camera(Player* target, Rectangle* gameArea, Rectangle* cameraView);
        ~Camera();

        void update(float dt);
        void setKeepInBounds(bool keepInBounds);
        void setCameraView(Rectangle* view);
        float getX();
        float getY();

    private:
        void stayInBounds();

        Player* target;
        Rectangle* gameArea;
        Rectangle* cameraView;
        bool keepInBounds;
        float acceleration;
};

#endif // !CAMERA_H
