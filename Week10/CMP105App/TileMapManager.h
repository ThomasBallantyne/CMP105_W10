#pragma once
#include "Framework/TileMap.h"
#include "Framework/Collision.h"
#include "player.h"
class TileMapManager
{	
public:
	TileMapManager();
	~TileMapManager();

	void update(float dt);
	void render(sf::RenderWindow* window);
	void setPlayer(Player* p) { player = p; };

protected:
	
	TileMap tileMap;
	GameObject tile;
	Player* player;
	std::vector<GameObject> tiles;
	std::vector<int> map;
	std::vector<GameObject>* world;
};