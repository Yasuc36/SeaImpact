#include "EnemyBoss.h"

EnemyBoss::EnemyBoss(const Coordinates& pos, std::vector<Shot>* shots) : Enemy(pos, { (" ,---. "), ("( @ @ )"), (" ).-.( "), (" /|||` "), ("  '|`  ") }, GameRender::Height - 4, 0, true, 5, 50, shots, 2500, 5)
{
	MaxShootDelay = 50;
	ShootDelay = MaxShootDelay;
}

void EnemyBoss::shoot()
{	
	if (ShootDelay <= 0)
	{
		Shots->push_back(Shot(Coordinates((Position.X - 1), (Position.Y + Shape.size() / 2-2)), { "<" }, -1));
		Shots->push_back(Shot(Coordinates((Position.X - 1), (Position.Y + Shape.size() / 2)), { "<" }, -1));
		ShootDelay = MaxShootDelay;
	}
	else --ShootDelay;
}