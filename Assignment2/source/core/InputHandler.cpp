#include "../../include/core/InputHandler.h"
#include <SFML/Window.hpp>


InputHandler::InputHandler() {
    pauseCommand = std::make_shared<PauseCommand>();
}

InputHandler::~InputHandler()
{
}

std::shared_ptr<Command> InputHandler::handleInput() {
    bool isEscPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
    if (isEscPressed && !wasEscPressedLastFrame) {
        wasEscPressedLastFrame = true;
        return pauseCommand;
    }
    else if (!isEscPressed) {
        wasEscPressedLastFrame = false;
    }
    return nullptr;
}

PlayerInputHandler::PlayerInputHandler() {
    moveRightCommand = std::make_shared<MoveRightCommand>();
    moveLeftCommand = std::make_shared<MoveLeftCommand>();
    moveUpCommand = std::make_shared<MoveUpCommand>();
    moveDownCommand = std::make_shared<MoveDownCommand>();

    attackCommand = std::make_shared<AttackCommand>();
    shootCommand = std::make_shared<ShootCommand>();
}

PlayerInputHandler::~PlayerInputHandler()
{
}

std::vector<std::shared_ptr<Command>>& PlayerInputHandler::handleInput() {
    commands.clear();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        commands.emplace_back(moveRightCommand);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        commands.emplace_back(moveLeftCommand);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        commands.emplace_back(moveUpCommand);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        commands.emplace_back(moveDownCommand);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        commands.emplace_back(attackCommand);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
        commands.emplace_back(shootCommand);
    }

    return commands;
}