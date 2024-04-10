#include "../../include/systems/Systems.h"
#include "../../include/components/Components.h"
#include "../../include/components/PlayerStateComponent.h"

GameplaySystem::GameplaySystem()
{
	
	componentMask.turnOnBit(static_cast<int>(ComponentID::LOGIC));
}

void GameplaySystem::update(Game* game, Entity* entity, float elapsed)
{
	auto logicComponent = entity->getLogicComponent();
	if (!logicComponent ) { throw std::exception("logicComponent is nullptr in GameplaySystem::update."); }

	logicComponent->update(entity, game, elapsed);

}