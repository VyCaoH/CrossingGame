#include "Player.h"

Sprite* Player::playerSprt = new Sprite("Sprites\\Player.txt");

// Maybe change this the default location
Player::Player()
{
	coord.X = 39;
	coord.Y = 27;
	isDead = false;
	recalBound();
}

Player::~Player()
{
	delete playerSprt;
}

void Player::move(int x, int y)
{
	coord.X = x;
	coord.Y = y;
}

void Player::setState(bool state)
{
	isDead = state;
}

int Player::getX() const
{
	return coord.X;
}
int Player::getY() const
{
	return coord.Y;
}

void Player::Up()
{
	if (coord.Y >= 0)
	{
		if (coord.Y == 27)
			coord.Y -= 4;
		else
			coord.Y -= 5;
	}
}
void Player::Left()
{
	if (coord.X > 3)
	{
		coord.X--;
	}
}
void Player::Down()
{
	if (coord.Y < 28)
	{
		if (coord.Y == 23)
			coord.Y += 4;
		else if (coord.Y != 27)
			coord.Y += 5;
	}
}
void Player::Right()
{
	if (coord.X < 106)
	{
		coord.X++;
	}
}

int Player::isImpact(std::vector<Row*>& listRow) const
{
	auto playerCoordY = this->getY();
	unsigned int inRow = 0;

	if (playerCoordY == 3 || playerCoordY == 27)
	{
		return 0;
	}
	else
	{
		inRow = (playerCoordY - 3) / 5 - 1;
	}


	Row* row = listRow[inRow];

	unsigned int typeOfEnemy = row->getType();
	std::vector<Entity*> listEnemy = row->GetList();

	for (auto& mem : listEnemy)
	{
		auto coordXEnemy = mem->getX();

		// Enemy -> Player
		if (coordXEnemy < this->getX())
		{
			// Right | Left
			if (coordXEnemy + mem->getBound(1) >= this->getX() - this->getBound(3))
				return typeOfEnemy + 1;
			else
				continue;
		}

		if (coordXEnemy == this->getX())
			return typeOfEnemy + 1;

		// Player -> Enemy
		if (coordXEnemy > this->getX())
		{
			if (this->getX() + this->getBound(1) >= coordXEnemy - mem->getBound(3))
				return typeOfEnemy + 1;
			else
				continue;
		}
	}

	return 0;
}

bool Player::isAtFinishLine() const
{
	return (coord.Y <= 5) ? true : false;
}

bool Player::isPlayerDead() const
{
	return !isDead;
}