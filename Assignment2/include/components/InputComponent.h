#pragma once
#include <memory>
#include "Components.h"

class Game;

class InputComponent : public Component {
public:
    virtual ~InputComponent() = default;
    //virtual void update(Game& game) = 0;

    ComponentID getID() const override { return ComponentID::INPUT; }
};

class PlayerInputHandler;

class PlayerInputComponent : public InputComponent {
public:
    PlayerInputComponent();
    //void update(Game& game) override;
    //ComponentID getID() const override;
    std::shared_ptr<PlayerInputHandler> getPlayerInputHandler() { return playerInputHandler; }
    ComponentID getID() const override { return ComponentID::INPUT; }

private:
    std::shared_ptr<PlayerInputHandler> playerInputHandler;
};
