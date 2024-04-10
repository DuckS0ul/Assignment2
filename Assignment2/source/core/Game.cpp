#include "../../include/core/Game.h"
#include "../../include/entities/Fire.h"
#include "../../include/entities/StaticEntities.h"
#include "../../include/core/InputHandler.h"
#include "../../include/core/Command.h"
#include "../../include/entities/Fire.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/components/PlayerStateComponent.h"

#include "../../include/systems/Systems.h"
#include <iostream>

Game::Game() : paused(false), entityCounter(0)
{
	inputHandler = std::make_unique<InputHandler>();

	auto ttlSystem = std::make_shared<TTLSystem>();
	systems.push_back(ttlSystem);
	auto inputSystem = std::make_shared<InputSystem>();
	systems.push_back(inputSystem);
	auto movementSystem = std::make_shared<MovementSystem>();
	systems.push_back(movementSystem);
	auto graphicsSystem = std::make_shared<GraphicsSystem>();
	systems.push_back(graphicsSystem);
	auto colliderSystem = std::make_shared<ColliderSystem>();
	systems.push_back(colliderSystem);
	auto gameplaySystem = std::make_shared<GameplaySystem>();
	systems.push_back(gameplaySystem);
}

Game::~Game()
{
}

template <typename T>
std::shared_ptr<T> Game::buildEntityAt(const std::string& filename, int col, int row)
{
	auto ent = std::make_shared<T>();
	float x = col * spriteWH * tileScale;
	float y = row * spriteWH * tileScale;
	float cntrFactor = (tileScale - itemScale) * spriteWH * 0.5f;

	ent->setPosition(x + cntrFactor, y + cntrFactor);
	ent->init(filename, std::make_shared<SpriteGraphicsComponent>(itemScale));
	
	return ent;
}

void Game::buildBoard(size_t width, size_t height)
{
	board = std::make_unique<Board>(width, height);
}

void Game::initWindow(size_t width, size_t height)
{
	int wdt = static_cast<int>(width * spriteWH * tileScale);
	int hgt = static_cast<int>(height * spriteWH * tileScale);
	window.setSize(sf::Vector2u(wdt, hgt));
	window.redraw();
}

void Game::init(std::vector<std::string> lines)
{
	size_t h = lines.size() - 1;
	if (h < 0)
		throw std::exception("No data in level file");
	size_t w = -1;

	window.loadFont("font/AmaticSC-Regular.ttf");
	window.setTitle("Mini-Game");
	
	auto it = lines.cbegin();
	int row = 0;
	while (it != lines.cend())
	{
		int col = 0;

		if(w == -1)
		{
			w = it->size();
			buildBoard(w, h);
			initWindow(w, h);		
		}
		
		std::string::const_iterator is = it->cbegin();
		while (is != it->cend())
		{
			switch (*is)
			{
			case '.':
			{
				board->addTile(col, row, tileScale, TileType::CORRIDOR);

				break;
			}
			case 'w':
			{
				board->addTile(col, row, tileScale, TileType::WALL);
				break;
			}
			case 'x':
			{
				auto log = buildEntityAt<Log>("img/log.png", col, row);
				addEntity(log);

				board->addTile(col, row, tileScale, TileType::CORRIDOR);
				break;
			}
			case 'p':
			{
				auto potion = buildEntityAt<Potion>("img/potion.png", col, row);
				addEntity(potion);
				board->addTile(col, row, tileScale, TileType::CORRIDOR);
				break;
			}
			case '*':
				{
				player = std::make_shared<Player>();

				player->init("img/DwarfSpriteSheet_data.txt", std::make_shared<SpriteSheetGraphicsComponent>());

				player->positionSprite(row, col, spriteWH, tileScale);

				addEntity(player);

				board->addTile(col, row, tileScale, TileType::CORRIDOR);
				break;
				}
			}

			col++; is++;
		}
		row++; it++;
	}
}

void Game::addEntity(std::shared_ptr<Entity> newEntity)
{
	if (newEntity) {
		newEntity->setID(++entityCounter);
		entities.push_back(newEntity);
	}
}

void Game::handleInput()
{
	auto command = inputHandler->handleInput();
	if (command) {
		command->execute(*this);
	}
			
	//player->handleInput(*this);

}


void Game::update(float elapsed)
{
	if (paused) {
		return;
	}

	bigArray(elapsed);

	for (auto& entity : entities) {
		entity->update(this, elapsed);
	}

	for (auto& entity : entities) {
		if (entity == player || !entity->getColliderComponent() || !player->collidesWith(*entity)) {
			continue;
		}

		switch (entity->getEntityType()) {
		case EntityType::POTION:
			processPotionCollision(entity);
			break;
		case EntityType::LOG:
			processLogCollision(entity);
			break;
		}
	}

	entities.erase(
		std::remove_if(entities.begin(), entities.end(),
			[](const std::shared_ptr<Entity>& entity) { return entity->isDeleted(); }),
		entities.end());

	window.update();
}

void Game::processPotionCollision(std::shared_ptr<Entity>& entity) {
	std::cout << "Player health before: " << player->getHealth()->getHealth() << std::endl;
	Potion* thePotion = dynamic_cast<Potion*>(entity.get());
	player->getHealth()->changeHealth(thePotion->getHealth());
	std::cout << "Player health after: " << player->getHealth()->getHealth() << std::endl;
	thePotion->deleteEntity();
}

void Game::processLogCollision(std::shared_ptr<Entity>& entity) {
	AnimBase* curAnim = player->getSpriteSheet()->getCurrentAnim();
	if (curAnim->getName() == "Attack" && curAnim->isInAction() &&
		(curAnim->getCurrentFrame() == 4 || curAnim->getCurrentFrame() == 5)) {
		std::cout << "Player wood before: " << player->getPlayerStateComponent()->getWood() << std::endl;
		Log* theLog = dynamic_cast<Log*>(entity.get());
		player->getPlayerStateComponent()->addWood(theLog->getWood());
		std::cout << "Player wood after: " << player->getPlayerStateComponent()->getWood() << std::endl;
		theLog->deleteEntity();
	}
}


void Game::render(float elapsed)
{
	window.beginDraw();
	board->draw(&window);

	for (const auto& entity : entities) {
		if (entity) {
			entity->draw(&window);
		}
	}

	window.drawGUI(*this);

	window.endDraw();
}


sf::Time Game::getElapsed() const { return gameClock.getElapsedTime(); }


void Game::setFPS(int FPS)
{
	std::string text("FPS: " + std::to_string(FPS));
	window.getFPSText().setString(text);
}

EntityID Game::getIDCounter()
{
	return entityCounter;
}

std::shared_ptr<Entity> Game::getEntity(unsigned int idx)
{
	if (idx < entities.size()) {
		return entities[idx];
	}


	return nullptr;
}


void Game::bigArray(float elapsedTime) {
	for (auto& system : systems) {
		for (auto& entity : entities) {
			if (!entity->isDeleted() && system->validate(entity.get())) {
				system->update(this, entity.get(), elapsedTime);
			}
		}
	}
}
 