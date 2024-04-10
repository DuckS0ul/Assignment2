#include "../../include/entities/Player.h"
#include "../../include/graphics/AnimBase.h"
#include "../../include/core/Game.h"
#include "../../include/core/InputHandler.h"
#include "../../include/core/Command.h"
#include "../../include/components/InputComponent.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/components/ColliderComponent.h"
#include "../../include/components/PlayerStateComponent.h"
#include <iostream>


Player::Player() : Entity(EntityType::PLAYER)
{
	input = std::make_shared<PlayerInputComponent>();
	addComponent(input);
	health = std::make_shared<HealthComponent>(startingHealth, maxHealth);
	//positionComponent = std::make_unique<PositionComponent>();
	//addComponent(positionComponent);
	velocity = std::make_shared<VelocityComponent>(playerSpeed);
	addComponent(velocity);
	colliderComponent = std::make_shared<BoxColliderComponent>();
	addComponent(colliderComponent);
	playerState = std::make_shared<PlayerStateComponent>();
	addComponent(playerState);

}

Player::~Player() {}

void Player::update(Game* game, float elapsed)
{
	//playerState->update(this, game, elapsed);
	//velocity->update(*this, elapsed);
	//colliderComponent->update(*this);
	//graphicsComponent->update(*this, elapsed);
}


//void Player::handleInput(Game& game) {
//	if (input) {
//		input->update(game);
//	}
//}

void Player::positionSprite(int row, int col, int spriteWH, float tileScale)
{
	sf::Vector2f scaleV2f = graphicsComponent->getSpriteScale();
	sf::Vector2i textureSize = graphicsComponent->getTextureSize();

	float x = col * spriteWH * tileScale;
	float y = row * spriteWH * tileScale;
	float spriteSizeY = scaleV2f.y * textureSize.y;
	float cntrFactorY = ((spriteWH * tileScale) - spriteSizeY);
	float cntrFactorX = cntrFactorY * 0.5f;					

	setPosition(x + cntrFactorX, y + cntrFactorY);

	velocity->setVelocity(0.0f, 0.0f);
}

bool Player::collidesWith(Entity& other) {
	return colliderComponent->collisions(other.getColliderComponent().get());
}