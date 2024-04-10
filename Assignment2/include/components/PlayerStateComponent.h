#pragma once

#include "../entities/Player.h"
#include <memory>
#include "Components.h"

class Fire;
class GraphicsComponent;
class Game;

class LogicComponent : public Component {
public:
    virtual ~LogicComponent() = default;
    virtual void update(Entity* entity, Game* game, float elapsed) = 0;
    ComponentID getID() const override { return ComponentID::LOGIC; }
};

class PlayerStateComponent : public LogicComponent {
public:
    PlayerStateComponent() : wood(0), attacking(false), shouting(false), shootCooldown(0) {}

    void update(Entity* entity, Game* game, float elapsed) override;

    bool isAttacking() const { return attacking; }
    bool isShouting() const { return shouting; }
    float getShootCooldown() const { return shootCooldown; }
    int getWood() const { return wood; }
    constexpr int getShootingCost() const { return shootingCost; }
    constexpr float getFireSpeed() const { return fireSpeed; }
    constexpr float getShootCooldownTime() const { return shootCooldownTime; }
    void setAttacking(bool at) { attacking = at; }
    void setShouting(bool sh) { shouting = sh; }
    void setCooldown(float cd) { shootCooldown = cd; }

    void addWood(int w);

protected:
    std::shared_ptr<Fire> createFire(Player& entity, std::shared_ptr<GraphicsComponent> graphics) const;

private:
    static constexpr int maxWood = 100;
    static constexpr int shootingCost = 1;
    static constexpr float fireSpeed = 150.0f;
    static constexpr float shootCooldownTime = 2.0f;

    int wood;
    bool attacking;
    bool shouting;
    float shootCooldown;
};

