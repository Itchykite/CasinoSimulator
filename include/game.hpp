#pragma once

#include <glad.h>
#include <SDL2/SDL.h>

class Game 
{
public:
    static int windowWidth;
    static int windowHeight;

    static GLuint VAO;
    static GLuint VBO;
    static GLuint EBO;

    static bool Init();
    static void PreRun();
    static void Run();
    static void HandleEvents();
    static void Cleanup();

    static SDL_Window* window;
    static SDL_GLContext glContext;
    static bool running;
};
