#include"Player.h"

Player::Player()
{
	isDead = false;
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
void Player::up()
{
	player_pY += 14;
}
void Player::down() {
	player_pY -= 14;
}
void Player::left() {
	player_pX -= 5;
}
void Player::right() {
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
void Player:: setX(float src)
{
	player_pX = src;
}
void Player:: setY(float src)
{
	player_pY = src;
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
		if (pressed(BUTTON_W))
		{
			up(speed, dt);
	}
		if (pressed(BUTTON_S))
		{
			down(speed, dt);
		}
		if (pressed(BUTTON_A))
		{
			left(speed, dt);
		}
		if (pressed(BUTTON_D))
		{
			right(speed, dt);
		}
		//checkWall()
	render_state = getRender();
	Renderer::draw_titan(getX(), getY(), getHalfX(), getHalfY());
	return;
}
void Player::checkWall(float x, float y, float half_x, float half_y)
{
	if (player_pX + player_half_X > 50)
	{
		setX(50);
	}
	if (player_pY + player_half_Y > half_y + y)
	{
		setY(40);
	}
	if (player_pX - player_half_X < -90)
	{
		setX(-half_x - x + player_half_X);
	}
	if (player_pY - player_half_Y < -half_y - y)
	{
		setY(-half_y - y + player_half_Y);
	}
}

