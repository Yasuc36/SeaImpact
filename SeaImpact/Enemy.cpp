#include "Enemy.h"
#include "Coordinates.h"
#include "GameRender.h"

Enemy::Enemy(const Coordinates& pos, const std::vector<std::string>& shape, int maxH, int minH, bool up, int movedelay, int shootdelay, std::vector<Shot>* shots, int score, int hp) : BaseObject(pos, shape)
{
	Up = up;
	if (GameRender::Height - 4 >= maxH) MaxH = maxH;
	else MaxH = GameRender::Height - 4;
	if (0 <= minH) MinH = minH;
	else MinH = 0;
	MaxMoveDelay = movedelay;
	MaxShootDelay = shootdelay;
	MoveDelay = movedelay;
	ShootDelay = shootdelay;
	Shots = shots;
	Score = score;
	Hp = hp;
}

void Enemy::move()
{
	if (Position.Y > GameRender::Height - 4 - (int)Shape.size()) Position.Y = GameRender::Height - 4 - Shape.size();
	if (MoveDelay <= 0)
	{
		if (MaxH != MinH)
		{
			if (Position.Y + (int)Shape.size() >= MaxH || Position.Y <= MinH) Up = !Up;	//	Swaps movement direction (Up || Down).
			switch (Up)
			{
			case true:
				Position.Y--;
				break;
			case false:
				Position.Y++;
				break;
			}
		}
		if (Position.X > 20) Position.X--;
		MoveDelay = MaxMoveDelay;
	}
	else --MoveDelay;
}

void Enemy::shoot()
{
	if (ShootDelay <= 0)
	{
		Shots->push_back(Shot(Coordinates((Position.X - 1), (Position.Y + Shape.size() / 2)), { "<" }, -1));
		ShootDelay = MaxShootDelay;
	}
	else --ShootDelay;
}

void Enemy::remShot()
{
	for (std::vector<Shot>::iterator it = Shots->begin(); it != Shots->end(); ++it)
	{
		if (Shots->at(it - Shots->begin()).outOfBounds()) Shots->erase(it);
	}
}

int Enemy::getScore()
{
	return Score;
}