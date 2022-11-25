#include"Player.h"

bool Player::isImpact(vector<Threat*>threat)
{
	for (auto x : threat)
	{
		for (auto y : x->getThreat())
		{
			//cout << y->getY() << endl << y->getHalfY() << endl;
			/*if (player.getX() + player.getHalfX() > y->getX() - y->getHalfX())
				running = false;
			if (player.getX() - player.getHalfX() > y->getX() - y->getHalfX())
				running = false;*/

			if (player_pX + player_half_X > y->getX() - y->getHalfX()
				&& player_pY + player_half_Y > y->getY() - y->getHalfY()
				&& player_pX - player_half_X < y->getX() + y->getHalfX()
				&& player_pY - player_half_Y < y->getY() + y->getHalfY())

				setIsDead(true);
				return true;
		}
	}
	return false;
}

//}
////void Player::setHeight(int height)
////{
////	this->height = height;
////}
////void Player::setWidth(int width)
////{
////	this->width = width;
////}