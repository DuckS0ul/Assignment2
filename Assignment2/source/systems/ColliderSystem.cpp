#include "../../include/systems/Systems.h"
#include "../../include/components/Components.h"
#include "../../include/components/ColliderComponent.h"
#include "../../include/components/PositionComponent.h"


ColliderSystem::ColliderSystem()
{
	componentMask.turnOnBit(static_cast<int>(ComponentID::COLLIDER));
	componentMask.turnOnBit(static_cast<int>(ComponentID::POSITION));
}


void ColliderSystem::update(Game* game, Entity* entity, float elapsed)
{
	auto colliderComponent = entity->getColliderComponent();
	auto position = entity->getPositionComponent();

	if (!colliderComponent ){throw std::exception("colliderComponent is nullptr in ColliderSystem::update.");}
	if (!position ){throw std::exception("Position component of entity is not properly validated for use by Collider system\n");}

	colliderComponent->getBoundingBox().setTopLeft(position->getPosition());
	colliderComponent->getBoundingBox().setBottomRight({ position->getPosition().x + colliderComponent->getSize().x, position->getPosition().y + colliderComponent->getSize().y });
}

