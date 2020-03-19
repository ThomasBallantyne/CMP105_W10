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
	onGround = false;
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

	if (input->isKeyDown(sf::Keyboard::Space) && (onGround == true))
	{
		
		velocity.y = -100;
		onGround = false;
		
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
	BcenterPos = (collider.getPosition() + (collider.getSize() / 2.f));
	PcenterPos = (getPosition() + (getSize() / 2.f));

	if (fabs(BcenterPos.y - PcenterPos.y) < fabs(BcenterPos.x - PcenterPos.x)) //y axis collision
	{
		if ((BcenterPos.y - PcenterPos.y) < (BcenterPos.x - PcenterPos.x))
		{
			std::cout << "top" << "\n";
			velocity.y = 0;
			setPosition(getPosition().x, (collider.getPosition().y - getSize().y));
		}
		else if ((PcenterPos.y - BcenterPos.y) < (PcenterPos.x - BcenterPos.x))
		{
			std::cout << "bot" << "\n";
			velocity.y = 0;
			setPosition(getPosition().x, collider.getPosition().y);
		}
	}
	//else //x axis collision
	//{
	//	if ((BcenterPos.y - PcenterPos.y) > (BcenterPos.x - PcenterPos.x))
	//	{
	//		std::cout << "left" << "\n";
	//		velocity.x = 0;
	//		setPosition((getPosition().x + getSize().x), collider.getPosition().y);
	//	}
	//	else if ((PcenterPos.y - BcenterPos.y) > (PcenterPos.x - BcenterPos.x))
	//	{
	//		std::cout << "right" << "\n";
	//		velocity.x = 0;
	//		setPosition(getPosition().x, collider.getPosition().y - getSize().y);
	//	}
	//}
}

void Player::isOnGround(bool ground)
{
	onGround = ground;
}