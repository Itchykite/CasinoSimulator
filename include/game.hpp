#pragma once

#include <SDL2/SDL.h>
#include <GL/glew.h>

class Game 
{
public:
    static int windowWidth;
    static int windowHeight;

    static bool Init();
    static void Run();
    static void HandleEvents();
    static void Cleanup();

    static SDL_Window* window;
    static SDL_GLContext glContext;
    static bool running;
};
