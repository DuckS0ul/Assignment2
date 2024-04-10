#pragma once
#include "../graphics/Window.h"
#include "../core/Board.h"
#include "../entities/Player.h"

class InputHandler;
class GraphicsComponent;
class SpriteGraphicComponent;
class SpriteSheetGraphicComponent;
class System;

class Game
{
public:

	const int spriteWH = 50;
	const float tileScale = 2.0f;
	const float itemScale = 1.0f;

	Game();
	~Game();

	void init(std::vector<std::string> lines);
	void addEntity(std::shared_ptr<Entity> newEntity);

	void buildBoard(size_t width, size_t height);
	void initWindow(size_t width, size_t height);

	void handleInput();
	void update(float elapsed);
	void render(float elapsed);
	Window* getWindow() { return &window; }

	sf::Time getElapsed() const;
	void setFPS(int FPS);
	void togglePause() { paused = !paused; }
	bool isPaused() const { return paused; }

	std::shared_ptr<Player> getPlayer() { return player; }

	EntityID getIDCounter();
	std::shared_ptr<Entity> getEntity(unsigned int idx);

	template <typename T>
	std::shared_ptr<T> buildEntityAt(const std::string& filename, int col, int row);

	void bigArray(float elapsedTime);


private:

	Window window;
	bool paused;
	sf::Clock gameClock;
	sf::Time elapsed;

	std::unique_ptr<Board> board;

	void processPotionCollision(std::shared_ptr<Entity>& entity);
	void processLogCollision(std::shared_ptr<Entity>& entity);

	std::vector<std::shared_ptr<Entity>> entities;


	EntityID entityCounter;

	std::shared_ptr<Player> player;

	std::unique_ptr<InputHandler> inputHandler;

	std::vector<std::shared_ptr<System>> systems;
};

