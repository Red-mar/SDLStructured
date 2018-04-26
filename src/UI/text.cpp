#include "text.h"
#include "..\log.h"

Text::Text(Window* window) :
    window(window),
    currentFont("assets/helvetidoodle.ttf"),
    textSize(28),
    font(nullptr),
    textTexture(nullptr)
{
    loadFont(currentFont);
}

Text::~Text()
{
    TTF_CloseFont(font);
    freeMemory();
}

void Text::freeMemory()
{
    if (textTexture != NULL)
    {
        SDL_DestroyTexture( textTexture);
        textTexture = nullptr;
    }

}

bool Text::loadText(std::string text, SDL_Color color)
{
    freeMemory();
    //causes acces violations?
    /*if (textTexture != NULL)
    {
        SDL_DestroyTexture(textTexture);
    }*/
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (textSurface == NULL)
    {
        Log::error("TTF_RenderText_Solid: Unable to render text surface. Error:");
    } else 
    {
        //freeMemory();
        textTexture = SDL_CreateTextureFromSurface(window->renderer, textSurface);
        if (textTexture == NULL)
        {
            Log::error("SDL_CreateTextureFromSurface: Unable to create texture from surface.");
        } else {
            textWidth = textSurface->w;
            textHeight = textSurface->h;
        }
        SDL_FreeSurface(textSurface);
    }
    
    return textTexture != NULL;
}

void Text::loadFont(std::string file)
{
    font = TTF_OpenFont(file.c_str(), textSize);
    if (font == NULL)
    {
        Log::error("TTF_OpenFont: Could not open " + file + ", Error:" + TTF_GetError());
        return;
    }
    currentFont = file;
}

void Text::setTextSize(int size)
{
    textSize = size;
    loadFont(currentFont);
}

void Text::render(float x, float y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
        SDL_Rect renderQuad = { (int)x, (int)y, textWidth, textHeight};

    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    window->renderImage(textTexture, clip, &renderQuad, angle, NULL, flip);
}

int Text::getTextHeight()
{
    return textHeight;
}

int Text::getTextWidth()
{
    return textWidth;
}