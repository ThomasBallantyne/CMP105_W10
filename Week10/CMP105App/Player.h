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
	void isOnGround(bool ground);
	void render(sf::RenderWindow* window);

protected:
	sf::Texture marioTexture;
	Animation walk;
	sf::RectangleShape hitBox;
	bool moving;
	bool onGround;
	float speed;
	float distance;
	sf::Vector2f coord;
	sf::Vector2f gravity;
	sf::Vector2f position;
	sf::Vector2f BcenterPos;
	sf::Vector2f PcenterPos;
	float diffX;
	float diffY;
};

