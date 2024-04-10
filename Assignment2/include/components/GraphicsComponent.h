#pragma once

#include "../entities/Entity.h"
#include "../graphics/Window.h"
#include "../graphics/SpriteSheet.h"
#include "Components.h"

class GraphicsComponent : public Component {
public:
    virtual ~GraphicsComponent() = default;

    virtual void init(const std::string& file) = 0;
    //virtual void update(const Entity& entity, float elapsed) = 0;
    virtual void draw(Window* window) = 0;

    virtual void setAnimation(const std::string& animationName, bool play, bool loop) = 0;
    virtual bool isCurrentAnimation(const std::string& animationName) const = 0;
    virtual void setSpriteDirection(Direction d) = 0;
    virtual const Direction getSpriteDirection() = 0;
    virtual bool isAnimationPlaying() const = 0;
    virtual bool isAnimationInAction() const = 0;
    virtual SpriteSheet* getSpriteSheet() = 0;
    virtual void setPosition(float x, float y) = 0;

    virtual const sf::Vector2f& getSpriteScale() const = 0;
    virtual const sf::Vector2i& getTextureSize() const = 0;
    ComponentID getID() const override { return ComponentID::GRAPHICS; }
};

class SpriteGraphicsComponent : public GraphicsComponent {
public:
    explicit SpriteGraphicsComponent(float spriteScale) : scale(spriteScale) {}
    virtual ~SpriteGraphicsComponent() = default;

    void init(const std::string& file) override;
    //void update(const Entity& entity, float elapsed) override;
    void draw(Window* window) override;

    void setAnimation(const std::string& animationName, bool play, bool loop) override;
    bool isCurrentAnimation(const std::string& animationName) const override;
    void setSpriteDirection(Direction d) override;
    const Direction getSpriteDirection() override;
    bool isAnimationPlaying() const override;
    bool isAnimationInAction() const override;
    SpriteSheet* getSpriteSheet() override;
    void setPosition(float x, float y) override;

    const sf::Vector2f& getSpriteScale() const override;
    const sf::Vector2i& getTextureSize() const override;
    sf::Sprite* getSprite() { return &sprite; }

    ComponentID getID() const override { return ComponentID::GRAPHICS; }

protected:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2i textureSize;
    float scale;
};

class SpriteSheetGraphicsComponent : public GraphicsComponent {
public:
    SpriteSheetGraphicsComponent() = default;
    virtual ~SpriteSheetGraphicsComponent() = default;

    void init(const std::string& file) override;
    //void update(const Entity& entity, float elapsed) override;
    void draw(Window* window) override;

    void setAnimation(const std::string& animationName, bool play, bool loop) override;
    bool isCurrentAnimation(const std::string& animationName) const override;
    void setSpriteDirection(Direction d) override;
    const Direction getSpriteDirection() override;
    bool isAnimationPlaying() const override;
    bool isAnimationInAction() const override;
    SpriteSheet* getSpriteSheet() override;
    void setPosition(float x, float y) override;

    const sf::Vector2f& getSpriteScale() const override;
    const sf::Vector2i& getTextureSize() const override;
    ComponentID getID() const override { return ComponentID::GRAPHICS; }

protected:
    SpriteSheet spriteSheet;
};
