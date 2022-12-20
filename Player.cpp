#include"Player.h"

Player::Player()
{
	isDead = false;
	player_dp = 0;
	player_ddp = 0;
	//heiPlayer:: ght = width = 0;
	player_pX = 0;
	player_pY = -45;
	entity.clear();
	player_half_X = 3;
	player_half_Y = 5;
}
float Player:: getHalfX()
{
	return player_half_X;
}
float Player:: getHalfY()
{
	return player_half_Y;
}
void Player::up(float speed, float dt)
{
	player_pY += 14;
}
void Player::down(float speed, float dt) {
	player_pY -= 14;
}
void Player::left(float speed, float dt) {
	player_pX -= 5;
}
void Player::right(float speed, float dt) {
	player_pX += 5;
}
float Player:: getX()
{
	return player_pX;
}
float Player::getY()
{
	return player_pY;
}
float Player:: getDP()
{
	return player_dp;
}
void Player:: setX(float src)
{
	player_pX = src;
}
void Player:: setY(float src)
{
	player_pY = src;
}
void Player:: setDP(float src)
{
	player_dp = src;
}
void Player:: setDDP(float src)
{
	player_ddp = src;
}
float Player:: getDDP()
{
	return player_ddp;
}
void Player:: setIsDead(bool type)
{
	Player:: isDead = type;
}
bool Player:: getIsDead()
{
	return isDead;
}
bool Player::isImpact(vector<Threat*>threat)
{
	for (auto x : threat)
	{
		for (auto y : x->getThreat())
		{
			if (player_pX + player_half_X > y->getX() - y->getHalfX()
				&& player_pY + player_half_Y > y->getY() - y->getHalfY()
				&& player_pX - player_half_X < y->getX() + y->getHalfX()
				&& player_pY - player_half_Y < y->getY() + y->getHalfY())
			{
				setIsDead(true);
				return true;
			}
		}
	}
	return false;
}
void Player::move(Input* input, float dt, float speed)
{
	{
		if (released(BUTTON_W)||released(BUTTON_UP))
		{
			is_down(BUTTON_W) = is_down(BUTTON_UP) = true;
			up(speed, dt);
		}
		if (released(BUTTON_S)||released(BUTTON_DOWN))
		{
			is_down(BUTTON_S) = is_down(BUTTON_DOWN) = true;
			down(speed, dt);
		}
		if (released(BUTTON_A) || released(BUTTON_LEFT))
		{
			is_down(BUTTON_A) = is_down(BUTTON_LEFT) = true;
			left(speed, dt);
		}
		if (released(BUTTON_D) || released(BUTTON_RIGHT))
		{
			is_down(BUTTON_D) = is_down(BUTTON_RIGHT) = true;
			right(speed, dt);
		}
		render_state = getRender();
		Renderer::draw_titan(getX(), getY(), getHalfX(), getHalfY());
		return;
	}
}
void Player::checkWall(float x, float y, float half_x, float half_y)
{
	if (player_pX + player_half_X > 50)
	{
		setX(50);
		setDP(0);
	}
	if (player_pY + player_half_Y > half_y + y)
	{
		setY(40);
		setDP(0);
	}
	if (player_pX - player_half_X < -90)
	{
		setX(-half_x - x + player_half_X);
		setDP(-90);
	}
	if (player_pY - player_half_Y < -half_y - y)
	{
		setY(-half_y - y + player_half_Y);
		setDP(-40);
	}
}
