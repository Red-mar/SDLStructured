#ifndef SPRITE_H
#define SPRITE_H

#include <iostream>
#include "sdl.hpp"
#include "color.h"
#include "window.h"

class Sprite
{
  public:
    Sprite(Window *window, std::string filename);
    virtual ~Sprite();

    void crop(Rectangle rect);
    virtual void render(float x, float y);
    int getWidth();
    int getHeight();
    void setSize(int w, int h);

    void setFlip(SDL_RendererFlip setFlip);

    void restore();
    void reload();

  protected:
    Window *window;
    std::string filename;
    SDL_Texture* image;
    Rectangle* clipRect;
    SDL_RendererFlip flip;
    float angle;
    float scaleX;
    float scaleY;
    
    int width;
    int height;
};

#endif // !SPRITE_H
