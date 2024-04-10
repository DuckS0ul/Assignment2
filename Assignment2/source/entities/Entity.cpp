#include "../../include/entities/Entity.h"
#include "../../include/graphics/Window.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/ColliderComponent.h"

#include <iostream>


Entity::Entity() : 
	id(0),
	type(EntityType::UNDEFINED),
	deleted(false)
{
	positionComponent = std::make_shared<PositionComponent>();
	addComponent(positionComponent);
	//graphicsComponent = std::make_shared<GraphicsComponent>();
	//addComponent(graphicsComponent);
	colliderComponent = std::make_shared<BoxColliderComponent>();
}

Entity::Entity(EntityType et) : 
	id(0),
	type (et),
	deleted(false)
{
	positionComponent = std::make_unique<PositionComponent>();
	addComponent(positionComponent);
	//graphicsComponent = std::make_shared<GraphicsComponent>();
	//addComponent(graphicsComponent);
	colliderComponent = std::make_shared<BoxColliderComponent>();
}

Entity::~Entity()
{
}

void Entity::update(Game* game, float elapsed)
{
	//graphicsComponent->update(*this, elapsed);
}



void Entity::draw(Window* window)
{
	graphicsComponent->draw(window);
	colliderComponent->draw(window);
}

void Entity::init(const std::string& textureFile, std::shared_ptr<GraphicsComponent> gc)
{
	graphicsComponent = gc;
	graphicsComponent->init(textureFile);
	addComponent(gc);
	//graphicsComponent->update(*this, 0);
	colliderComponent->init(Vector2f(graphicsComponent->getTextureSize().x * graphicsComponent->getSpriteScale().x, graphicsComponent->getTextureSize().y * graphicsComponent->getSpriteScale().y));
}

const SpriteSheet* Entity::getSpriteSheet() const { return graphicsComponent->getSpriteSheet(); }

void Entity::setPosition(float x, float y)
{
	positionComponent->setPosition(x, y);
}	

const Vector2f& Entity::getPosition() const {
	return positionComponent->getPosition();
}


const sf::Vector2f& Entity::getSpriteScale() const
{
	return graphicsComponent->getSpriteScale();
}

sf::Vector2i Entity::getTextureSize() const
{
	return graphicsComponent->getTextureSize();
}

//std::unique_ptr<PositionComponent>& Entity::getPositionComp() {
//	return position;
//}

void Entity::addComponent(std::shared_ptr<Component> component) {
	unsigned int id = static_cast<unsigned int>(component->getID());
	componentSet.turnOnBit(id);
}

bool Entity::hasComponent(Bitmask mask) const {
	return componentSet.contains(mask);
}

//std::shared_ptr<TTLComponent> Entity::getTTLComponent() const {
//	return nullptr;
//}

//std::shared_ptr<InputComponent> Entity::getInputComponent() const {
//	return nullptr;
//}