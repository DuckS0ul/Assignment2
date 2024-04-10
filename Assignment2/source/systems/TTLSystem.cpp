#include "../../include/systems/Systems.h"
#include "../../include/components/Components.h"
#include "../../include/entities/Entity.h"


TTLSystem::TTLSystem() {
    componentMask.turnOnBit(static_cast<unsigned int>(ComponentID::TTL));

}

void TTLSystem::update(Game* game, Entity* entity, float elapsedTime) {
    auto ttlComponent = entity->getTTLComponent();

    if (!ttlComponent) {throw std::runtime_error("TTLComponent is nullptr in TTLSystem::update.");}

    ttlComponent->decreaseTTL();

    if (ttlComponent->getTTL() <= 0) {
        entity->deleteEntity();
    }
}
