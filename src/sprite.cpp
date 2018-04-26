#include "sprite.h"
#include "log.h"

Sprite::Sprite(Window *window, std::string filename) : window(window),
                                                       filename(filename),
                                                       image(nullptr),
                                                       clipRect(nullptr),
                                                       width(0),
                                                       height(0),
                                                       angle(0),
                                                       flip(SDL_FLIP_NONE)
{
    image = window->loadImage(filename);
    if (image == NULL)
    {
        Log::error("Sprite::load failed to load " + filename);
    }
    else
    {
        Log::log("Sprite::load loaded " + filename);

        int w, h;

        SDL_QueryTexture(image, nullptr, nullptr, &w, &h);

        width = w;
        height = h;

        crop(Rectangle(0, 0, width, height));
    }
}

Sprite::~Sprite()
{
    if (image)
    {
        window->freeImage(image);
    }
    if (clipRect)
    {
        delete clipRect;
    }
}

void Sprite::crop(Rectangle rect)
{
    if (!clipRect)
    {
        clipRect = new Rectangle();
    }

    clipRect->copy(&rect);
}

void Sprite::render(float x, float y)
{
    SDL_Rect renderQuad = {(int)x, (int)y, width, height};

    if (clipRect != NULL)
    {
        renderQuad.w = clipRect->w;
        renderQuad.h = clipRect->h;
    }

    SDL_Rect clip = {(int)clipRect->x, (int)clipRect->y, clipRect->w, clipRect->h};
    SDL_Point center = {(int)clipRect->center.x, (int)clipRect->center.y};

    window->renderImage(image, &clip, &renderQuad, angle, &center, flip);
}

int Sprite::getWidth()
{
    return clipRect->w;
}

int Sprite::getHeight()
{
    return clipRect->h;
}

void Sprite::restore()
{
    crop(Rectangle(0, 0, width, height));
}

void Sprite::setFlip(SDL_RendererFlip setFlip)
{
    flip = setFlip;
}
void Sprite::setSize(int w, int h)
{
    if (clipRect)
    {
        //delete clipRect;
    }
    width = w;
    height = h;
    crop(Rectangle(0, 0, width, height));
}

void Sprite::reload()
{
    if (image)
    {
        window->freeImage(image);
    }
    if (clipRect)
    {
        delete clipRect;
    }
    image = window->loadImage(filename);
    if (image == NULL)
    {
        Log::error("Sprite::load failed to load " + filename);
    }
    else
    {
        //Log::log("Sprite::load loaded " + filename);

        int w, h;

        SDL_QueryTexture(image, nullptr, nullptr, &w, &h);

        width = w;
        height = h;

        crop(Rectangle(0, 0, width, height));
    }
}