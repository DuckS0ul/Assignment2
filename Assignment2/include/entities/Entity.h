#pragma once
#include "../graphics/Window.h"
#include "../graphics/SpriteSheet.h"
#include "../utils/Rectangle.h"
#include "../utils/Bitmask.h"
#include "../components/Components.h"
#include "../components/TTLComponent.h"
#include "../components/InputComponent.h"
#include "../../include/components/PositionComponent.h"
#include <memory>

class PositionComponent;
class GraphicsComponent;
class BoxColliderComponent;
class VelocityComponent;
class PlayerStateComponent;

using EntityID = unsigned int;
enum class EntityType
{
	UNDEFINED = -1,
	PLAYER = 0,
	POTION = 1,
	LOG = 2,
	FIRE = 3
};

class Game;

class Entity
{
public:

	Entity();
	Entity(EntityType et);
	~Entity();

	void setID(EntityID entId) { id = entId; }
	EntityID getID() const { return id; }

	void setPosition(float x, float y);
	const Vector2f& getPosition() const;

	bool hasComponent(Bitmask mask) const;
	void addComponent(std::shared_ptr<Component> component);

	Bitmask componentSet;
	EntityType getEntityType() const { return type; }
	const Bitmask& getComponentSet() const { return componentSet; }

	virtual void init(const std::string& textureFile, std::shared_ptr<GraphicsComponent> gc);
	virtual void update(Game* game, float elapsed = 1.0f);

	void draw(Window* window);

	const sf::Vector2f& getSpriteScale() const;
	sf::Vector2i getTextureSize() const;
	const SpriteSheet* getSpriteSheet() const;

	bool isDeleted() const { return deleted; }
	void deleteEntity() { deleted = true; }


	virtual std::shared_ptr<TTLComponent> getTTLComponent() { return nullptr; }
	virtual std::shared_ptr<InputComponent> getInputComponent() { return nullptr; }
	virtual std::shared_ptr<BoxColliderComponent> getColliderComponent() { return nullptr; }
	virtual std::shared_ptr<VelocityComponent> getVelocityComponent() { return nullptr; }
	virtual std::shared_ptr<PositionComponent> getPositionComponent() { return positionComponent; }
	virtual std::shared_ptr<GraphicsComponent> getGraphicsComponent() { return graphicsComponent; }
	virtual std::shared_ptr<PlayerStateComponent> getLogicComponent()  { return nullptr; }

protected:

	EntityType type;
	EntityID id;

	std::shared_ptr<PositionComponent> positionComponent;
	std::shared_ptr<GraphicsComponent> graphicsComponent;
	std::shared_ptr<BoxColliderComponent> colliderComponent;

	bool deleted;
};
