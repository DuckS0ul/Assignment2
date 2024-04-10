#pragma once

#include "../utils/Rectangle.h"
#include "../entities/Entity.h"
#include "../graphics/Window.h"
#include "Components.h"

class BoxColliderComponent : public Component {
public:
	BoxColliderComponent() = default;
	~BoxColliderComponent() = default;

	void init(const Vector2f& sz);
	//void update(const Entity& entity);
	void draw(Window* window);

	bool collisions(BoxColliderComponent* BCC);

	void setBoundingBox(const Vector2f& topLeft, const Vector2f& bottomRight);
	Rectangle& getBoundingBox() { return boundingBox; }
	const Vector2f& getSize() const { return size; }
	ComponentID getID() const override { return ComponentID::COLLIDER; }

private:
	Rectangle boundingBox;
	Vector2f size;
};
