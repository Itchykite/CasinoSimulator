#include <game.hpp>
#include <shader_utils.hpp>

SDL_Window* Game::window = nullptr;
SDL_GLContext Game::glContext = nullptr;
bool Game::running = true;

int Game::windowWidth = 800;
int Game::windowHeight = 600;

GLuint Game::VAO = 0;
GLuint Game::VBO = 0;
GLuint Game::EBO = 0;

void setup()
{
    float vertices[] = 
    {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    
    unsigned int indices[] = 
    { 
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };  
   
    glGenVertexArrays(1, &Game::VAO);
    glGenBuffers(1, &Game::VBO);
    glGenBuffers(1, &Game::EBO);

    glBindVertexArray(Game::VAO);

    glBindBuffer(GL_ARRAY_BUFFER, Game::VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Game::EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

bool Game::Init()
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_Log("SDL could not initialize! SDL_Error: %s", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("Casino Simulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if(!window)
    {
        SDL_Log("Window could not be created! SDL_Error: %s", SDL_GetError());
        return false;
    }

    glContext = SDL_GL_CreateContext(window);
    if(!glContext)
    {
        SDL_Log("OpenGL context could not be created! SDL_Error: %s", SDL_GetError());
        return false;
    }

    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
    {
        SDL_Log("Failed to initialize GLEW");
        return false;
    }

    glViewport(0, 0, windowWidth, windowHeight);
    glEnable(GL_DEPTH_TEST);


    setup();

    return true;
}

void Game::HandleEvents()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
        {
            running = false;
        }
    }
}

void Game::Run()
{
    GLuint shaderProgram = CreateShaderProgram("../assets/shaders/vertex_shader.glsl", "../assets/shaders/fragment_shader.glsl");

    while(running)
    {
        HandleEvents();
    
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(Game::VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
       
        SDL_GL_SwapWindow(window);
    }
}

void Game::Cleanup()
{
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
