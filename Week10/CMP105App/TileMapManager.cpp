#include "TileMapManager.h"

TileMapManager::TileMapManager()
{
	tileMap.loadTexture("gfx/marioTiles.png");

	for (int i = 0; i < 9; i++)
	{
		tile.setSize(sf::Vector2f(32, 32));
		tile.setCollisionBox(0, 0, 32, 32);
		tile.setCollider(true);
		tiles.push_back(tile);
	}

	tiles[0].setCollider(false); 
	tiles[0].setTextureRect(sf::IntRect(187, 51, 16, 16)); 
	tiles[1].setTextureRect(sf::IntRect(0, 0, 16, 16)); 
	tiles[2].setTextureRect(sf::IntRect(17, 0, 16, 16)); 
	tiles[3].setTextureRect(sf::IntRect(34, 0, 16, 16)); 
	tiles[4].setTextureRect(sf::IntRect(0, 34, 16, 16)); 
	tiles[5].setTextureRect(sf::IntRect(17, 34, 16, 16)); 
	tiles[6].setTextureRect(sf::IntRect(34, 34, 16, 16));

	tileMap.setTileSet(tiles);

	sf::Vector2u mapSize(10, 6);

	map = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 1, 2, 0, 0, 0, 0, 0,
		0, 0, 0, 4, 6, 0, 0, 0, 0, 0,
		1, 2, 3, 0, 0, 1, 2, 3, 0, 0,
		4, 5, 6, 0, 0, 4, 5, 6, 0, 0
	};

	tileMap.setTileMap(map, mapSize); 
	tileMap.setPosition(sf::Vector2f(0, 408)); 
	tileMap.buildLevel();
	world = tileMap.getLevel();

	for (int i = 0; i < (int)world->size(); i++)
	{
		if ((*world)[i].isCollider())
		{
			hitboxes.push_back(sf::RectangleShape());
			hitboxes.back().setPosition((*world)[i].getPosition());
			hitboxes.back().setSize(sf::Vector2f((*world)[i].getCollisionBox().width, (*world)[i].getCollisionBox().height));
			hitboxes.back().setFillColor(sf::Color::Transparent);
			hitboxes.back().setOutlineColor(sf::Color::Red);
			hitboxes.back().setOutlineThickness(1.f);
		}
	}
}

TileMapManager::~TileMapManager()
{
}

void TileMapManager::update(float dt)
{

	for (int i = 0; i < (int)world->size(); i++)
	{
		if ((*world)[i].isCollider())
		{
			if (Collision::checkBoundingBox(player, &(*world)[i]))
			{
				player->collisionResponse((*world)[i]);
			}
		}
	}
}

void TileMapManager::render(sf::RenderWindow* window)
{
	tileMap.render(window);
	
	for (int i = 0; i < hitboxes.size()-1; i++)
	{
		window->draw(hitboxes[i]);
	}
}