#include "../../include/core/Command.h"
#include "../../include/core/Game.h"
#include "../../include/components/PlayerStateComponent.h"

void MoveRightCommand::execute(Game& game) {
    auto player = game.getPlayer();
    auto velocityComp = player->getVelocityComponent();
    auto currentVelocity = velocityComp->getVelocity();
    velocityComp->setVelocity(currentVelocity.x + 1.0f, currentVelocity.y);
}

void MoveLeftCommand::execute(Game& game) {
    auto player = game.getPlayer();
    auto velocityComp = player->getVelocityComponent();
    auto currentVelocity = velocityComp->getVelocity();
    velocityComp->setVelocity(currentVelocity.x - 1.0f, currentVelocity.y);
}


void MoveUpCommand::execute(Game& game) {
    auto player = game.getPlayer();
    auto velocityComp = player->getVelocityComponent();
    auto currentVelocity = velocityComp->getVelocity();
    velocityComp->setVelocity(currentVelocity.x, currentVelocity.y - 1.0f);
}

void MoveDownCommand::execute(Game& game) {
    auto player = game.getPlayer();
    auto velocityComp = player->getVelocityComponent();
    auto currentVelocity = velocityComp->getVelocity();
    velocityComp->setVelocity(currentVelocity.x, currentVelocity.y + 1.0f);
}

void AttackCommand::execute(Game& game) {
    game.getPlayer()->getPlayerStateComponent()->setAttacking(true);
}

void ShootCommand::execute(Game& game) {
    game.getPlayer()->getPlayerStateComponent()->setShouting(true);
}