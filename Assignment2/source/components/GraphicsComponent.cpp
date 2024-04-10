#include "../../include/components/GraphicsComponent.h"
#include <iostream>

auto throwUnsupportedOperation = [](const std::string& operation) {
	throw std::runtime_error("Unsupported operation: " + operation + " is not applicable for this component");
	};

void SpriteGraphicsComponent::init(const std::string& file) {
	texture.loadFromFile(file);
	textureSize = { static_cast<int>(texture.getSize().x), static_cast<int>(texture.getSize().y) };
	sprite.setTexture(texture);
	sprite.setScale(scale, scale);
}

//void SpriteGraphicsComponent::update(const Entity& entity, float elapsed) {
//	sprite.setPosition(sf::Vector2f(entity.getPosition().x, entity.getPosition().y));
//}

void SpriteGraphicsComponent::draw(Window* window) {
	window->draw(sprite);
}

const sf::Vector2f& SpriteGraphicsComponent::getSpriteScale() const {
	return sprite.getScale();
}

const sf::Vector2i& SpriteGraphicsComponent::getTextureSize() const {
	return textureSize;
}

void SpriteGraphicsComponent::setAnimation(const std::string& animationName, bool play, bool loop) {
	throwUnsupportedOperation("setAnimation");
}

bool SpriteGraphicsComponent::isCurrentAnimation(const std::string& animationName) const {
	throwUnsupportedOperation("isCurrentAnimation");
	return false;
}

const Direction SpriteGraphicsComponent::getSpriteDirection() {
	throwUnsupportedOperation("getSpriteDirection");
	return static_cast<Direction>(0);
}

void SpriteGraphicsComponent::setSpriteDirection(Direction d) {
	throwUnsupportedOperation("setSpriteDirection");
}

bool SpriteGraphicsComponent::isAnimationPlaying() const {
	throwUnsupportedOperation("isAnimationPlaying");
	return false;
}

bool SpriteGraphicsComponent::isAnimationInAction() const {
	throwUnsupportedOperation("isAnimationInAction");
	return false;
}

SpriteSheet* SpriteGraphicsComponent::getSpriteSheet() {
	throwUnsupportedOperation("getSpriteSheet");
	return nullptr;
}

void SpriteGraphicsComponent::setPosition(float x, float y) {
	sprite.setPosition(x, y);
}


void SpriteSheetGraphicsComponent::init(const std::string& file) {
	spriteSheet.loadSheet(file);
	spriteSheet.setAnimation("Idle", true, true);
}

//void SpriteSheetGraphicsComponent::update(const Entity& entity, float elapsed) {
//	spriteSheet.setSpritePosition(sf::Vector2f(entity.getPosition().x, entity.getPosition().y));
//	spriteSheet.update(elapsed);
//}

void SpriteSheetGraphicsComponent::draw(Window* window) {
	sf::Sprite* sp = &spriteSheet.getSprite();
	const sf::Vector2f pos = sp->getPosition();
	window->draw(spriteSheet.getSprite());
}

const sf::Vector2f& SpriteSheetGraphicsComponent::getSpriteScale() const {
	return spriteSheet.getSpriteScale();
}

const sf::Vector2i& SpriteSheetGraphicsComponent::getTextureSize() const {
	return spriteSheet.getSpriteSize();
}

void SpriteSheetGraphicsComponent::setAnimation(const std::string& animationName, bool play, bool loop) {
	spriteSheet.setAnimation(animationName, play, loop);
}

bool SpriteSheetGraphicsComponent::isCurrentAnimation(const std::string& animationName) const {
	if (spriteSheet.getCurrentAnim()->getName() == animationName) return true;
	return false;
}

const Direction SpriteSheetGraphicsComponent::getSpriteDirection() {
	return spriteSheet.getSpriteDirection();
}

void SpriteSheetGraphicsComponent::setSpriteDirection(Direction d) {
	spriteSheet.setSpriteDirection(d);
}

bool SpriteSheetGraphicsComponent::isAnimationPlaying() const {
	if (spriteSheet.getCurrentAnim()->isPlaying()) return true;
	return false;
}

bool SpriteSheetGraphicsComponent::isAnimationInAction() const {
	if (spriteSheet.getCurrentAnim()->isInAction()) return true;
	return false;
}
SpriteSheet* SpriteSheetGraphicsComponent::getSpriteSheet() {
	return &spriteSheet;
}
void SpriteSheetGraphicsComponent::setPosition(float x, float y) {
	spriteSheet.getSprite().setPosition(x, y);
}