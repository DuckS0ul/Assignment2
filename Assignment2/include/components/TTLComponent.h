#pragma once
#include "Components.h"

class TTLComponent : public Component {
private:
    int ttl;

public:
    TTLComponent(int initialTTL) : ttl(initialTTL) {}

    ComponentID getID() const override { return ComponentID::TTL; }

    void decreaseTTL() {
        if (ttl > 0) {
            ttl--;
        }
    }

    int getTTL() const {
        return ttl;
    }
};