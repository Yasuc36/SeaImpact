#pragma once
#include "Player.h"
#include "Shot.h"
#include "EnemyBoss.h"
#include "EnemyNarrow.h"
#include "EnemyToucher.h"
#include "EnemyWiggler.h"
#include "Bonus.h"
#include "Spawner.h"
#include <memory>

/**
* Class that helps to control automated object like shots etc.
*/

class Control
{
public:
	static void update(Player * obj, WINDOW * win);	// Updates checks prerequisites for actions and then does them. (Player -> check input and do action; Enemy -> check movement delay and move etc.).
	static void update(std::vector<Shot>& obj);	// Updates position of shots.
	static void update(std::vector< std::shared_ptr<Enemy>> & obj);	// Updates position of enemies.
	static void update(std::vector< std::shared_ptr<Bonus>> & bonus);	// Updates position of bonuses.
	static void collision(Player* pl, std::vector<std::shared_ptr<Bonus>> & obj);	// Checks for collisions between player and bonuses.
	static void collision(Player* pl, std::vector<Shot>* shot);	// Checks for collisions between player and enemy shots.
	static void collision(std::vector< std::shared_ptr<Enemy>> & ship, std::vector<std::shared_ptr<Bonus>> & bonuses ,std::vector<Shot>* shot, Player* pl, Spawner * sp);	// Checks for collisions between enemies and player shots.
	static void destroyAll(std::vector< std::shared_ptr<Enemy>> & enemies);	// Destroys all enemy ships.
	static void sleep(int miliseconds);	// Freeze screen for specified amount.
};