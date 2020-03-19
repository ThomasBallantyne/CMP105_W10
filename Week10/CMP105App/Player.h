#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
#include <iostream>
class Player: public GameObject
{
public:
	Player();
	~Player();

	void handleInput(float dt);
	void update(float dt) override;
	void collisionResponse(GameObject collider);
	void jump();

protected:
	sf::Texture marioTexture;
	Animation walk;
	bool moving;
	bool isOnGround;
	float speed;
	float distance;
	sf::Vector2f coord;
	sf::Vector2f gravity;
	sf::Vector2f position;
	sf::Vector2f centerPos;
	sf::Vector2f diffX;
	sf::Vector2f diffY;
};

