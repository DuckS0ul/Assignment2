#include "../../include/systems/Systems.h"
#include "../../include/components/Components.h"
#include "../../include/components/InputComponent.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/core/Command.h"
#include "../../include/core/Game.h"
#include "../../include/core/InputHandler.h"


InputSystem::InputSystem()
{

	componentMask.turnOnBit(static_cast<unsigned int>(ComponentID::INPUT));
	componentMask.turnOnBit(static_cast<unsigned int>(ComponentID::VELOCITY));
}

void InputSystem::update(Game* game, Entity* entity, float elapsed)
{

	auto inputComponent = entity->getInputComponent();
	auto velocityComponent = entity->getVelocityComponent();

	if (!inputComponent ) { throw std::runtime_error("InputComponent is nullptr in InputSystem::update."); }
	if (!velocityComponent ) { throw std::exception("VelocityComponent is nullptr in InputSystem::update."); }

	velocityComponent->setVelocity(0.f, 0.f);
	auto playerInput = std::static_pointer_cast<PlayerInputComponent>(inputComponent);
	auto commands = playerInput->getPlayerInputHandler()->handleInput();
	for (auto& command : commands) {
		command->execute(*game);

	}
}