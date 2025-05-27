#include <game.hpp>

int main()
{
    if (!Game::Init()) return -1;
    Game::Run();
    Game::Cleanup();

    return 0;
}
