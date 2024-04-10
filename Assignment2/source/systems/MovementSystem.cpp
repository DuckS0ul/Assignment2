#include "../../include/systems/Systems.h"
#include "../../include/components/Components.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/components/PositionComponent.h"


MovementSystem::MovementSystem()
{

	componentMask.turnOnBit(static_cast<int>(ComponentID::POSITION));
	componentMask.turnOnBit(static_cast<int>(ComponentID::VELOCITY));
}

void MovementSystem::update(Game* game, Entity* entity, float elapsed)
{
	auto positionComponent = entity->getPositionComponent();
	if (!positionComponent )
	{
		throw std::exception("positionComponent is nullptr in MovementSystem::update. ");
	}
	auto velocityComponent = entity->getVelocityComponent();
	if (!velocityComponent )
	{
		throw std::exception("velocityComponent is nullptr in MovementSystem::update. ");
	}

	float x = positionComponent->getPosition().x + velocityComponent->getVelocity().x * velocityComponent->getSpeed()* elapsed;
	float y = positionComponent->getPosition().y + velocityComponent->getVelocity().y * velocityComponent->getSpeed() * elapsed;
	positionComponent->setPosition(x, y);
}