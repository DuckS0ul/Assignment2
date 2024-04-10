#include "../../include/components/ColliderComponent.h"
#include <iostream>

void BoxColliderComponent::init(const Vector2f& sz) {
	size = sz;
}

//void BoxColliderComponent::update(const Entity& entity) {
//	boundingBox.setTopLeft(entity.getPosition());
//	boundingBox.setBottomRight({ entity.getPosition().x + size.x, entity.getPosition().y + size.y });
//}

void BoxColliderComponent::draw(Window* window) {
	window->draw(boundingBox.getDrawableRect());
}

bool BoxColliderComponent::collisions(BoxColliderComponent* bcc) {
	return boundingBox.intersects(bcc->getBoundingBox());
}

void BoxColliderComponent::setBoundingBox(const Vector2f& topLeft, const Vector2f& bottomRight) {
	boundingBox.setTopLeft(topLeft);
	boundingBox.setBottomRight(bottomRight);
}