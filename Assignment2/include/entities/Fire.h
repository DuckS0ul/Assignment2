#pragma once
#include "../components/TTLComponent.h"
#include "../components/VelocityComponent.h"
#include "Entity.h"
#include <memory>

class Fire : public Entity
{
public:
	const int startTimeToLive = 150;

	Fire();
	~Fire();

	virtual void update(Game* game, float elapsed = 1.0f) override;

	int getTTL() const { return ttl->getTTL(); }

	std::shared_ptr<TTLComponent> getTTLComponent() override { return ttl; }
	std::shared_ptr<VelocityComponent> getVelocityComponent() override { return velocityComponent; }

private:

	std::shared_ptr<TTLComponent> ttl;
	std::shared_ptr<VelocityComponent> velocityComponent;
};