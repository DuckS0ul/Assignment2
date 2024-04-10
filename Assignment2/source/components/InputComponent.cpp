#include "../../include/components/InputComponent.h"
#include "../../include/core/Game.h"
#include "../../include/core/InputHandler.h"
#include "../../include/components/Components.h" 

PlayerInputComponent::PlayerInputComponent() {
    playerInputHandler = std::make_unique<PlayerInputHandler>();
}

//void PlayerInputComponent::update(Game& game) {
	/*game.getPlayer()->getVelocityComp()->setVelocity(0.f, 0.f);

	auto commands = playerInputHandler->handleInput();
	for (auto& command : commands) {
		command->execute(game);
	}*/
//}