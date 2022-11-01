#include "Row.h"

Row::Row(int y) : y_coord(y) // DEFAULT
{
	std::uniform_int_distribution <int> randType(0, 3);
	type = randType(gen); // rand % 4
	t = 0;
	_lvl = 0;
	MAX_ENEMIES = 4;
	redLightTime = 4;
	speed = 10;
	distance = 40;
	_speed = speed;
	std::uniform_int_distribution <int> randSpeed(0, 1);
	isFromRight = randSpeed(gen); // rand % 2
	isRedLight = false;
}

Row::~Row()
{
	for (auto x : inhabitance)
		delete x;
	while (!inhabitance.empty())
		inhabitance.pop_back();
}

int Row::GetY() const
{
	return y_coord;
}

int Row::GetT() const
{
	return t;
}

int Row::GetTime() const
{
	return redLightTime;
}

bool Row::GetRight() const
{
	return isFromRight;
}

bool Row::GetRedLight() const
{
	return isRedLight;
}

int Row::getType() const
{
	return type;
}

bool Row::getIsFromRight() const
{
	return isFromRight;
}
std::vector <Entity*> Row::GetList() const
{
	return inhabitance;
}

void Row::SetY(int y)
{
	y_coord = y;
}

void Row::SetT(clock_t T)
{
	t = T;
}

void Row::SetTime(float time)
{
	redLightTime = time;
}

void Row::SetRight(bool right)
{
	isFromRight = right;
}

void Row::SetRedLight(bool tick)
{
	isRedLight = tick;
}

void Row::toggle()
{
	isRedLight = !isRedLight;

	if (isRedLight)
		t = clock();
}

void Row::AtLevel(int lvl) // Set new red light time by new level
{
	if (lvl > 0 && _lvl != lvl)
	{
		if (lvl % 20 == 0) // Lvl.20 40 60... set new values
		{
			MAX_ENEMIES = 6;
			redLightTime = 4;
			speed = 10;
			distance = 40;
		}
		else if (lvl % 3 == 0 && MAX_ENEMIES < 8) // Lvl.3 6 9 increase enemies, decrease distance
		{
			MAX_ENEMIES++;
			distance -= 10;
		}
		else if (lvl % 2 == 0 && redLightTime > 1) // Lvl.2 4 8 decrease stop time
		{
			redLightTime--;
			speed -= 2;
		}

		_lvl = lvl;
	}
}

void Row::append()
{
	std::uniform_int_distribution <int> randDistance(0, distance);
	std::uniform_int_distribution <int> _randDistance(0, 110);
	if (isFromRight)
	{
		//0: Car
		//1: Truck
		//2: Bird
		//3: Dino
		switch (type)
		{
		case 0:
			if (inhabitance.empty())
			{
				inhabitance.push_back(new Car(_randDistance(gen) - 30, y_coord));
				//inhabitance.push_back(new Car(rand() % 110 - 60, y_coord));
			}

			if (inhabitance.size() < MAX_ENEMIES)
			{
				int prevXcoord = inhabitance.back()->getX();
				inhabitance.push_back(new Car(prevXcoord + randDistance(gen) + 30, y_coord));
			}

			break;

		case 1:
			if (inhabitance.empty())
			{
				inhabitance.push_back(new Truck(_randDistance(gen) - 30, y_coord));
				//inhabitance.push_back(new Truck(rand() % 110 - 60, y_coord));
			}

			if (inhabitance.size() < MAX_ENEMIES)
			{
				int prevXcoord = inhabitance.back()->getX();
				inhabitance.push_back(new Truck(prevXcoord + randDistance(gen) + 30, y_coord));
			}

			break;

		case 2:
			if (inhabitance.empty())
			{
				inhabitance.push_back(new Bird(_randDistance(gen) - 30, y_coord));
				//inhabitance.push_back(new Bird(rand() % 110 - 60, y_coord));
			}

			if (inhabitance.size() < MAX_ENEMIES)
			{
				int prevXcoord = inhabitance.back()->getX();
				inhabitance.push_back(new Bird(prevXcoord + randDistance(gen) + 30, y_coord));
			}

			break;

		case 3:
			if (inhabitance.empty())
			{
				inhabitance.push_back(new Dinosaur(_randDistance(gen) - 30, y_coord));
				//inhabitance.push_back(new Dinosaur(rand() % 110 - 60, y_coord));
			}

			if (inhabitance.size() < MAX_ENEMIES)
			{
				int prevXcoord = inhabitance.back()->getX();
				inhabitance.push_back(new Dinosaur(prevXcoord + randDistance(gen) + 30, y_coord));
			}

			break;

		default:
			break;
		}
	}
	else // From Left
	{
		switch (type)
		{
		case 0:
			if (inhabitance.empty())
			{
				inhabitance.push_back(new Car(_randDistance(gen) + 30, y_coord));
				//inhabitance.push_back(new Car(rand() % 110 + 60, y_coord));
			}

			if (inhabitance.size() < MAX_ENEMIES)
			{
				int prevXcoord = inhabitance.back()->getX();
				inhabitance.push_back(new Car(prevXcoord - randDistance(gen) - 30, y_coord));
			}

			break;

		case 1:
			if (inhabitance.empty())
			{
				inhabitance.push_back(new Truck(_randDistance(gen) + 30, y_coord));
				//inhabitance.push_back(new Truck(rand() % 110 + 60, y_coord));
			}

			if (inhabitance.size() < MAX_ENEMIES)
			{
				int prevXcoord = inhabitance.back()->getX();
				inhabitance.push_back(new Truck(prevXcoord - randDistance(gen) - 30, y_coord));
			}

			break;

		case 2:
			if (inhabitance.empty())
			{
				inhabitance.push_back(new Bird(_randDistance(gen) + 30, y_coord));
				//inhabitance.push_back(new Bird(rand() % 110 + 60, y_coord));
			}

			if (inhabitance.size() < MAX_ENEMIES)
			{
				int prevXcoord = inhabitance.back()->getX();
				inhabitance.push_back(new Bird(prevXcoord - randDistance(gen) - 30, y_coord));
			}

			break;

		case 3:
			if (inhabitance.empty())
			{
				inhabitance.push_back(new Dinosaur(_randDistance(gen) + 30, y_coord));
				//inhabitance.push_back(new Dinosaur(rand() % 110 + 60, y_coord));
			}

			if (inhabitance.size() < MAX_ENEMIES)
			{
				int prevXcoord = inhabitance.back()->getX();
				inhabitance.push_back(new Dinosaur(prevXcoord - randDistance(gen) - 30, y_coord));
			}

			break;

		default:
			break;
		}
	}
}

void Row::move()
{
	if (!isRedLight)
	{
		if (_speed == 0)
		{
			for (auto& enemy : inhabitance)
			{
				if (isFromRight) // Enemy gets out of row will return to the start
				{
					if (enemy->getX() == -20)
						inhabitance.erase(inhabitance.begin());
					else
						enemy->move(enemy->getX() - 1, y_coord);
				}
				else
				{
					if (enemy->getX() == 130)
						inhabitance.erase(inhabitance.begin());
					else
						enemy->move(enemy->getX() + 1, y_coord);
				}
			}

			std::uniform_int_distribution <int> randToggle(0, 200);
			if (randToggle(gen) < 2 && inhabitance.size() >= 4) // Randomize when to turn red light
				toggle();

			_speed = speed; // Timing to move etity
		}
		else
			_speed--;
	}
	else
	{
		clock_t _t = clock() - t;
		if (((int)_t) / CLOCKS_PER_SEC == redLightTime) // Timer to turn green light
		{
			toggle();
			t = clock();
		}
	}
}