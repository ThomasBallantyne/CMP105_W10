#include "Player.h"

Player::Player()
{
	marioTexture.loadFromFile("gfx/marioSheetT.png");
	setTexture(&marioTexture);
	walk.addFrame(sf::IntRect(0, 0, 15, 21));
	walk.addFrame(sf::IntRect(15, 0, 15, 21));
	walk.addFrame(sf::IntRect(30, 0, 15, 21));
	walk.addFrame(sf::IntRect(45, 0, 15, 21));
	walk.setFrameSpeed(0.1f);

	setPosition(25, 400);
	speed = 100;
	gravity = sf::Vector2f(0,100);
	moving = false;
	setSize(sf::Vector2f(45, 63));
	//setOrigin(sf::Vector2f(getSize() / 2.f));
	setCollisionBox(0,0,45,63);
	walk.reset();
	setTextureRect(walk.getCurrentFrame());
}

Player::~Player()
{

}

void Player::handleInput(float dt)
{
	if (input->isKeyDown(sf::Keyboard::D))
	{
		walk.setFlipped(false);
		moving = true;
		velocity.x = speed;
	}
	else if (input->isKeyDown(sf::Keyboard::A))
	{
		walk.setFlipped(true);
		moving = true;
		velocity.x = -speed;
	}
	else
	{
		velocity.x = 0;
		moving = false;
	}

	if (input->isKeyDown(sf::Keyboard::Space))
	{
		if (isOnGround == true)
		{
			velocity.y = -100;
			isOnGround = false;
		}
	}
}

void Player::update(float dt)
{
	if (moving)
	{
		walk.animate(dt);
		setTextureRect(walk.getCurrentFrame());
	}
	position = velocity * dt + 0.5f * gravity * dt * dt;
	velocity += gravity * dt;
	move(position);
}

void Player::collisionResponse(GameObject collider)
{
	centerPos = (collider.getPosition() + (collider.getSize() / 2.f));
	if ((centerPos.y - getPosition().y) < (centerPos.x - getPosition().x))
	{
		velocity.y = 0;
		setPosition(getPosition().x, (collider.getPosition().y));
	}
	else if ((getPosition().y - centerPos.y) < (getPosition().x - centerPos.x))
	{
		velocity.y = 0;
		setPosition(getPosition().x, collider.getPosition().y - getSize().y);
	}
	else if ((centerPos.y - getPosition().y) > (centerPos.x - getPosition().x))
	{
		velocity.x = 0;
		setPosition((getPosition().x+getSize().x), collider.getPosition().y);
	}
	else if ((getPosition().y - centerPos.y) > (getPosition().x - centerPos.x))
	{
		velocity.x = 0;
		setPosition(getPosition().x, collider.getPosition().y - getSize().y);
	}
}