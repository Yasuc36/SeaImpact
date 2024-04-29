#pragma once
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <memory>
#include "EnemyBoss.h"
#include "EnemyNarrow.h"
#include "EnemyToucher.h"
#include "EnemyWiggler.h"
#include "BonusHealth.h"
#include "BonusInvincibility.h"
#include "BonusRockets.h"
#include "BonusShield.h"
#include "GameRender.h"
#include "Shot.h"

/**
* Class that takes cares about spawning enemies and bonuses.
*/

class Spawner
{
private:
	int Spawn;
	int Boss;
    int Narrow;
    int Toucher;
    int Wiggler;
    int BonusRate;
    std::vector<Shot> * Shots;
public:
    Spawner(int spawn, int boss, int narrow, int toucher, int wiggler, int bonus, std::vector<Shot> * shots);  // Constructor 2
    void spawnBonus(std::vector<std::shared_ptr<Bonus>> & bonuses, Coordinates position);  // Chance to drop bonus out of dying enemy
    void spawnEnemy(std::vector<std::shared_ptr<Enemy>> & enemies);  // Spawn one enemy out of 4 enemy types
    int getTimer(); // Return time (in ticks) 
};