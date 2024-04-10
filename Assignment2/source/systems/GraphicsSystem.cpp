#include "../../include/systems/Systems.h"
#include "../../include/components/Components.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/components/PositionComponent.h"

GraphicsSystem::GraphicsSystem()
{
	componentMask.turnOnBit(static_cast<int>(ComponentID::GRAPHICS));
	componentMask.turnOnBit(static_cast<int>(ComponentID::POSITION));
}

void GraphicsSystem::update(Game* game, Entity* entity, float elapsed)
{
	auto graphicsComponent = entity->getGraphicsComponent();
	auto positionComponent = entity->getPositionComponent();

	if (!graphicsComponent ) { throw std::runtime_error("graphicsComponent is nullptr in GraphicsSystem::update."); }
	if (!positionComponent ) { throw std::runtime_error("positionComponent is nullptr in GraphicsSystem::update."); }

	if (entity->getEntityType() == EntityType::PLAYER) {
		graphicsComponent->getSpriteSheet()->setSpritePosition(sf::Vector2f(positionComponent->getPosition().x, positionComponent->getPosition().y));
		graphicsComponent->getSpriteSheet()->update(elapsed);
	}
	else {
		auto spriteGraphicsComponent = std::static_pointer_cast<SpriteGraphicsComponent>(graphicsComponent);
		spriteGraphicsComponent->getSprite()->setPosition(sf::Vector2f(positionComponent->getPosition().x, positionComponent->getPosition().y));

	}

}