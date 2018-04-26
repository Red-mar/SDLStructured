#ifndef TEXT_H
#define TEXT_H

#include "..\sdl.hpp"
#include "..\window.h"

class Text
{
    public:
        Text(Window* window);
        ~Text();

        Text(const Text &) = delete;
        Text &operator=(const Text &) = delete;

        void freeMemory();

        void setColor(Uint8 red, Uint8 green, Uint8 blue);
        void setBlendMode(SDL_BlendMode blending);
        void setAlpha(Uint8 alpha);

        void loadFont(std::string file);
        bool loadText(std::string text, SDL_Color color);

        int getTextWidth();
        int getTextHeight();

        void setTextSize(int size);

        void render(float x, float y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

    private:
        Window* window;
        SDL_Texture* textTexture;
        TTF_Font* font;
        std::string currentFont;

        int textWidth;
        int textHeight;
        int textSize;
};

#endif // !TEXT_H
