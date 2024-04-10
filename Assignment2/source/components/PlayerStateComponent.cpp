#include "../../include/components/PlayerStateComponent.h"
#include "../../include/core/Game.h"
#include "../../include/entities/Fire.h"
#include "../../include/components/GraphicsComponent.h"
#include <iostream>

void PlayerStateComponent::addWood(int w)
{
	wood += w;
	if (wood > maxWood) wood = maxWood;
	if (wood < 0) wood = 0;
}

std::shared_ptr<Fire> PlayerStateComponent::createFire(Player& entity, std::shared_ptr<GraphicsComponent> graphics) const
{
	auto fireEntity = std::make_shared<Fire>();
	Vector2f pos{ entity.getPosition().x + entity.getTextureSize().x * 0.5f,  entity.getPosition().y + entity.getTextureSize().y * 0.5f };
	fireEntity->init("img/fire.png", std::make_shared<SpriteGraphicsComponent>(1.0f));
	fireEntity->setPosition(pos.x, pos.y);
	Vector2f vel(fireSpeed, 0.f);
	if (entity.getGraphicsComponent()->getSpriteDirection() == Direction::Left) vel.x = vel.x * -1.0f;

	fireEntity->getVelocityComponent()->setVelocity(vel.x, vel.y);

	return fireEntity;
}

void PlayerStateComponent::update(Entity* entity, Game* game, float elapsed) {
    Player* player = dynamic_cast<Player*>(entity);
    auto velocity = player->getVelocityComponent()->getVelocity();
    auto spriteSheet = player->getGraphicsComponent()->getSpriteSheet();

    if (!attacking && !shouting) {
        if (velocity.magnitude() != 0) {
            spriteSheet->setAnimation("Walk", true, true);
            spriteSheet->setSpriteDirection(velocity.x > 0 ? Direction::Right : Direction::Left);
        }
        else {
            spriteSheet->setAnimation("Idle", true, true);
        }
    }

    bool isPlaying = spriteSheet->getCurrentAnim()->isPlaying();

    if (attacking) {
        spriteSheet->setAnimation("Attack", attacking, false);
        attacking = isPlaying;
    }

    if (shouting) {
        spriteSheet->setAnimation("Shout", shouting, false);
        if (!isPlaying && wood > shootingCost && shootCooldown <= 0) {
            game->addEntity(createFire(*player, player->getGraphicsComponent()));
            wood -= shootingCost;
            std::cout << "shout" << std::endl;
            shootCooldown = shootCooldownTime;
        }
        shouting = isPlaying;
    }

    if (shootCooldown > 0) {
        shootCooldown -= elapsed;
    }
}