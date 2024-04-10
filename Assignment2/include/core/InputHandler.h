#pragma once
#include <memory>
#include "Command.h"
#include "../../include/core/Game.h"

class Game;

class InputHandler {
private:
    std::shared_ptr<Command> pauseCommand;
    bool wasEscPressedLastFrame;

public:
    InputHandler();
    ~InputHandler();
    std::shared_ptr<Command> handleInput();
};

class PlayerInputHandler {
private:
    std::vector<std::shared_ptr<Command>> commands;
    std::shared_ptr<Command> moveRightCommand;
    std::shared_ptr<Command> moveLeftCommand;
    std::shared_ptr<Command> moveUpCommand;
    std::shared_ptr<Command> moveDownCommand;

    std::shared_ptr<Command> attackCommand;
    std::shared_ptr<Command> shootCommand;

    std::vector<std::shared_ptr<Command>> inputCommands;

public:
    PlayerInputHandler();
    ~PlayerInputHandler();

    std::vector<std::shared_ptr<Command>>& handleInput();
};