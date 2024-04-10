#pragma once
#include "Components.h"

class HealthComponent:public Component {
protected:
    int currentHealth;
    int maxHealth;

public:
    HealthComponent(int startingHealth, int maximumHealth)
        : currentHealth(startingHealth), maxHealth(maximumHealth) {}

    int getHealth() const { return currentHealth; }

    void changeHealth(int change) {
        currentHealth += change;
        if (currentHealth > maxHealth) currentHealth = maxHealth;
        if (currentHealth < 0) currentHealth = 0;
    }
    ComponentID getID() const override { return ComponentID::HEALTH; }
};