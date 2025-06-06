#include <game.hpp>
#include <shader_utils.hpp>

#include <vector>

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
    // CPU
    const std::vector<GLfloat> vertexPositions =
    {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.3f, 0.76f,
        0.5f, -0.5f, 0.0f, 0.22f, 0.65f, 0.88f,
        0.0f, 0.5f, 0.0f, 0.98f, 0.82f, 0.34f,
        -0.5f, 0.5f, 0.0f, 0.51f, 0.75f, 0.23f,
        0.5f, 0.5f, 0.0f, 0.45f, 0.67f, 0.12f
    };

    const std::vector<GLuint> vertexIndices =
    {
        0, 1, 2,
        2, 3, 0,
        1, 4, 2,
    };

    // GPU
    glGenVertexArrays(1, &Game::VAO);
    glGenBuffers(1, &Game::VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(Game::VAO);

    glBindBuffer(GL_ARRAY_BUFFER, Game::VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexPositions.size() * sizeof(GLfloat), vertexPositions.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &Game::EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Game::EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexIndices.size() * sizeof(GLuint), vertexIndices.data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

bool Game::Init()
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

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

    if(!gladLoadGLLoader(SDL_GL_GetProcAddress))
    {
        SDL_Log("Failed to initialize GLAD! SDL_Error: %s", SDL_GetError());
        return false;
    }

    glViewport(0, 0, windowWidth, windowHeight);

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

void Game::PreRun()
{
    GLuint shaderProgram = CreateShaderProgram("../assets/shaders/vertex_shader.glsl", "../assets/shaders/fragment_shader.glsl");
   
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glViewport(0, 0, windowWidth, windowHeight);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
}

void Game::Run()
{
    while(running)
    {
        HandleEvents();

        PreRun();

        glBindVertexArray(Game::VAO);
        glBindBuffer(GL_ARRAY_BUFFER, Game::VBO);
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);

        SDL_GL_SwapWindow(window);
    }
}

void Game::Cleanup()
{
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
