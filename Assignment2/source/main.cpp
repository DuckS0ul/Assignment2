#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "../include/core/Game.h"

void adaptiveLoop(Game& game, float& lastTime, float updateTarget = 0)
{
    float current = game.getElapsed().asSeconds();
    float elapsedSeconds = current - lastTime;

    game.handleInput();
    game.update(elapsedSeconds);
    game.render(elapsedSeconds);

    float frameTime = game.getElapsed().asSeconds() - current;
    if (updateTarget > frameTime)
    {
        sf::sleep(sf::seconds(updateTarget - frameTime));
        elapsedSeconds = updateTarget;
    }

    int fps = static_cast<int>(1.0f / elapsedSeconds);

    game.setFPS(fps);
    //std::cout << "Current FPS: " << fps << std::endl;

    lastTime = current;
}

int main(int argc, char** argv[])
{
    std::ifstream levelRead{ "levels/lvl0.txt" };
    if (!levelRead)
    {
        throw std::exception("File not found\n");
    }

    std::vector<std::string> lines;
    while (levelRead)
    {
        std::string strInput;
        std::getline(levelRead, strInput);
        lines.emplace_back(strInput);
    }

    Game game;
    game.init(lines);

    float updateTarget = 0.016f;
    float lastTime = game.getElapsed().asSeconds();

    while (!game.getWindow()->isWindowDone())
    {
        adaptiveLoop(game, lastTime, updateTarget);
    }

    
    return 0;
}