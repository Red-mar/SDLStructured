#include "camera.h"

Camera::Camera(Player *target, Rectangle *gameArea, Rectangle *cameraView) : target(target),
                                                                                             gameArea(gameArea),
                                                                                             cameraView(cameraView),
                                                                                             keepInBounds(false),
                                                                                             acceleration(5.0f)
{
}

Camera::~Camera()
{
    delete cameraView;
}

void Camera::update(float dt)
{
    cameraView->x += (((target->getCenterX() - cameraView->w / 2) - cameraView->x) * acceleration)*dt;
    cameraView->y += (((target->getCenterY() - cameraView->h / 2) - cameraView->y) * acceleration)*dt;

    stayInBounds();
}

float Camera::getX()
{
    return cameraView->x;
}

float Camera::getY()
{
    return cameraView->y;
}

void Camera::stayInBounds()
{
    if (keepInBounds)
    {
        if (cameraView->x < 0)
        {
            cameraView->x = 0;
        }
        if (cameraView->y < 0)
        {
            cameraView->y = 0;
        }
        if (cameraView->x > gameArea->w - cameraView->w)
        {
            cameraView->x = (float)(gameArea->w - cameraView->w);
        }
        if (cameraView->y > gameArea->h - cameraView->h)
        {
            cameraView->y = (float)(gameArea->h - cameraView->h);
        }
    }
}

void Camera::setCameraView(Rectangle* view)
{
    delete cameraView;
    cameraView = view;
}