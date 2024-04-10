#include "../../include/entities/Fire.h"
#include <iostream>

Fire::Fire()
    : Entity(EntityType::FIRE)
{
    ttl = std::make_shared<TTLComponent>(startTimeToLive);
    addComponent(ttl);

    velocityComponent = std::make_shared<VelocityComponent>();
    //velocityComponent->setVelocity(1.0f, 0);
    addComponent(velocityComponent);
    //positionComponent = std::make_unique<PositionComponent>();
    //addComponent(positionComponent);
}

Fire::~Fire()
{}

void Fire::update(Game* game, float elapsed) 
{
    Entity::update(game, elapsed);
    //velocityComponent->update(*this, elapsed);

}

