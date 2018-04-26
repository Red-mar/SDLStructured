#include "Window.h"
#include "Log.h"

Window::Window(uint32_t width, uint32_t height, std::string title) : window(nullptr),
                                                                     //surface(nullptr),
                                                                     renderer(nullptr),
                                                                     mWidth(width),
                                                                     mHeight(height),
                                                                     originalWidth(width),
                                                                     originalHeight(height),
                                                                     isFullscreen(false),
                                                                     mTitle(title),
                                                                     bg_color(0, 0, 0),
                                                                     framerate(60),
                                                                     frame_delay(0),
                                                                     current_frame_delta(0)
{
    create(title, width, height);

    if (!window || !renderer)
    {
        Log::error("Window: could not create window");
        throw "Window failed";
    }
    //maximize();
    frame_delay = 1000 / framerate;
    framerateTimer.start();
    deltaTimer.start();

    setIcon("assets/icon.bmp");

    clear();
    refresh();
    SDL_Delay(500);
}

Window::~Window()
{
    destroy();
}

void Window::create(std::string title, int width, int height, int windowFlags, int rendererFlags)
{
    destroy();

    window = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, windowFlags);
    if (window == NULL)
    {
        Log::error("Window: Could not create window");
    }
    rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    this->renderer = SDL_CreateRenderer(window, -1, rendererFlags);
    //SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
    if (renderer == NULL)
    {
        Log::error("Could not create renderer");
    }

    //SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    setTitle(title);

    //need surface?
    mWidth = width;
    mHeight = height;
    //SDL_GetWindowSize(window, &mWidth, &mHeight);
}

void Window::destroy()
{
    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
}

void Window::renderImage(SDL_Texture *texture, SDL_Rect* clip, SDL_Rect* renderQuad, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    if (!texture)
    {
        Log::warning("Window::render: tried to render nullptr");
        return;
    }

    SDL_RenderCopyEx(renderer, texture, clip, renderQuad, angle, center, flip);
}

void Window::refresh()
{
    SDL_RenderPresent(renderer);
}

SDL_Texture *Window::loadImage(std::string filename)
{
    SDL_Texture *newTexture = IMG_LoadTexture(renderer, filename.c_str());

    if (newTexture == NULL)
    {
        Log::error("SDL_CreateTextureFromSurface: could not create texture from surface, error: ");
    }
    return newTexture;
}

void Window::freeImage(SDL_Texture *image)
{
    if (image)
    {
        SDL_DestroyTexture(image);
    }
}

void Window::minimize()
{
    SDL_MinimizeWindow(window);
}

void Window::maximize()
{
    SDL_MaximizeWindow(window);
    SDL_GetWindowSize(window, &mWidth, &mHeight);
}

void Window::restore()
{
    SDL_RestoreWindow(window);
}

void Window::fill(Color color)
{
    SDL_SetRenderDrawColor(renderer,
                           color.r(),
                           color.g(),
                           color.b(),
                           color.a());
    SDL_RenderClear(renderer);
}

void Window::clear()
{
    fill(bg_color);
}

void Window::setBackgroundColor(Color color)
{
    bg_color = color;
}

void Window::delayFramerateIfNeeded()
{
    unsigned int frameTicks = deltaTimer.getTicks();

    if (frameTicks < frame_delay)
    {
        SDL_Delay(frame_delay - frameTicks);
    }

    deltaTimer.start();
}

float Window::getDelta()
{
    return deltaTimer.getTicks() / 1000.000f;
}

unsigned int Window::getTicks()
{
    return framerateTimer.getTicks();
}

void Window::setTitle(std::string title)
{
    if (window)
    {
        SDL_SetWindowTitle(window, title.c_str());
    }
}

void Window::setFramerateLimit(int limit)
{
    framerate = limit;
    if (limit <= 0)
    {
        frame_delay = 0;
    }
    else
    {
        frame_delay = 1000 / framerate;
    }
}

int Window::getFramerateLimit()
{
    return framerate;
}

void Window::setIcon(std::string filepath)
{
    SDL_Surface *icon = IMG_Load(filepath.c_str());
    if (icon == NULL)
    {
        Log::error("could not load icon, error: ");
    }
    SDL_SetWindowIcon(window, icon);
    SDL_FreeSurface(icon);
}

void Window::print(std::string text, int x, int y, Color color)
{
}

void Window::resize(int width, int height, int windowFlags)
{
    SDL_SetWindowSize(window, width, height);
    SDL_SetWindowFullscreen(window, windowFlags);
    mWidth = width;
    mHeight = height;
}
