#pragma once

#include "Entity.h"
#include "../../include/components/ColliderComponent.h"

class Potion : public Entity {
public:
    Potion() : Entity(EntityType::POTION) {
        colliderComponent = std::make_shared<BoxColliderComponent>();
        addComponent(colliderComponent);
    }

    ~Potion() {}

    void init(const std::string& textureFile, std::shared_ptr<GraphicsComponent> gc) override {
        Entity::init(textureFile, gc);
        colliderComponent->setBoundingBox(getPosition(),
            { getPosition().x + colliderComponent->getSize().x, getPosition().y + colliderComponent->getSize().y });
    }

    void update(Game* game, float elapsed = 1.0f) override {}

    int getHealth() const { return potionHealth; }

    std::shared_ptr<BoxColliderComponent> getColliderComponent() override { return colliderComponent; }

protected:
    const int potionHealth = 10;
};

class Log : public Entity {
public:
    Log() : Entity(EntityType::LOG) {
        colliderComponent = std::make_shared<BoxColliderComponent>();
        addComponent(colliderComponent);
    }

    ~Log() {}

    void init(const std::string& textureFile, std::shared_ptr<GraphicsComponent> gc) override {
        Entity::init(textureFile, gc);
        //colliderComponent->update(*this);
    }

    void update(Game* game, float elapsed = 1.0f) override {}

    int getWood() const { return woodAdded; }

    std::shared_ptr<BoxColliderComponent> getColliderComponent() override { return colliderComponent; }

protected:
    const int woodAdded = 15;
};