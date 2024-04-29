#include "Player.h"
#include "curses.h"
#include "GameRender.h"

Player::Player() : BaseObject(Coordinates(5, (GameRender::Height)/2-5), {"# ", "##", "# "})
{
	Score = 0;
	Hp = 3;
	Rockets = 0;
	Magazine = 10;
	WeaponCooldown = 0;
	Shield = false;
	Invincibility = false;
	Legend = false;
	Play = true;
	InvDur = 0;
	MaxHeight = GameRender::Height - 7;
	usingRocket = false;
}

bool Player::addHp(const int hp)
{
	if (Hp + hp > 3) Hp = 3;
	else Hp += hp;
	return true;
}

bool Player::addInvincibility()
{
	InvDur = 10;
	Invincibility = true;
	Shape[1][0] = 'I';
	return true;
}

bool Player::addRocket(const int rockets)
{
	if (Rockets + rockets > 3) Rockets = 3;
	else Rockets += rockets;
	return true;
}

bool Player::addShield()
{
	Shield = true;
	Shape[0][1] = ']';
	Shape[2][1] = ']';
	return true;
}

void Player::addScore(int value)
{
	Score += value;
}

void Player::addBullet(int value)
{
	if (Magazine + value > 10) Magazine = 10;
	else Magazine += value;
}

void Player::coolWeapon(int value)
{
	if (WeaponCooldown - value < 0) WeaponCooldown = 0;
	else WeaponCooldown -= value;
}

bool Player::remHp(const int hp)
{
	if (Invincibility == false)
	{
		if (Shield != true)
		{
			if (Hp - hp <= 0)
			{
				Hp = 0;
				Play = false;
			}
			else Hp -= hp;
		}
		else remShield();
	}
	return true;
}

bool Player::remInvincibility()
{
	if (InvDur > 0) --InvDur;
	if (InvDur <= 0)
	{
		Invincibility = false;
		Shape[1][0] = '#';
	}
	return true;
}

bool Player::remRocket(const int rockets)
{
	if (Rockets + rockets < 0) Rockets = 0;
	else Rockets -= rockets;
	return true;
}

bool Player::remShield()
{
	Shield = false;
	Shape[0][1] = ' ';
	Shape[2][1] = ' ';
	return true;
}

bool Player::detectKey(WINDOW* win)
{
	if (Play == true)
	{
		int ch = wgetch(win);
		switch (ch)
		{
		case 'w':
			MoveUp();	// Move up.
			break;
		case 's': // Move down.
			MoveDown();
			break;
		case 'j': // Shoot.
			if (Magazine > 0 && WeaponCooldown == 0)
			{
				Shots.push_back(Shot(Coordinates((Position.X + Shape[0].length()), (Position.Y + Shape.size() / 2)), { ">" }, 1));
				WeaponCooldown++;
				Magazine--;
			}
			break;
		case 'k': // Shoot Rocket.
			if (Rockets > 0)
			{
				usingRocket = true;
				--Rockets;
			}
			break;
		case 'l': // Show legend.
			Legend = true;
			break;
		case 'm': // Quit.
			return false;
			break;
		}		
		return true;
	}
	else return false;
}

void Player::remShot()
{
	for (std::vector<Shot>::iterator it = Shots.begin(); it != Shots.end(); ++it)
	{
		if (Shots[it - Shots.begin()].outOfBounds()) Shots.erase(it);
	}	
}

void Player::setLegend(bool state)
{
	Legend = state;
}

bool Player::getLegend()
{
	return Legend;
}

int Player::getHp()
{
	return Hp;
}

int Player::getRockets()
{
	return Rockets;
}

int Player::getScore()
{
	return Score;
}

int Player::getMagazine()
{
	return Magazine;
}

bool Player::getUsedRocket()
{
	bool retVal = usingRocket;
	usingRocket = false;
	return retVal;
}

void Player::MoveUp()
{
	if (Position.Y > 0) --Position.Y;
}

void Player::MoveDown()
{
	if (Position.Y < MaxHeight) ++Position.Y;
}