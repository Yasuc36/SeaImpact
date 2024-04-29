#include "Spawner.h"

Spawner::Spawner(int spawn, int boss, int narrow, int toucher, int wiggler, int bonus, std::vector<Shot>* shots)
{
    Spawn = spawn;
    Boss = boss;
    Narrow = narrow;
    Toucher = toucher;
    Wiggler = wiggler;
    BonusRate = bonus;
    Shots = shots;
}

void Spawner::spawnBonus(std::vector<std::shared_ptr<Bonus>> & bonuses, Coordinates position)
{
    int pick = rand()%10;
    if (pick < BonusRate) // Chance for spawning bonus: (Bonus*10)%
    {
        pick = rand()%4;
        switch (pick)
        {
            case 0:
                bonuses.push_back(std::make_shared<BonusHealth>(position));
                break;
            case 1:
                bonuses.push_back(std::make_shared<BonusInvincibility>(position));
                break;
            case 2:
                bonuses.push_back(std::make_shared<BonusRockets>(position));
                break;
            case 3:
                bonuses.push_back(std::make_shared<BonusShield>(position));
                break;
        }
    }
}
   
void Spawner::spawnEnemy(std::vector<std::shared_ptr<Enemy>> & enemies)
{
    int max = Boss + Narrow + Toucher + Wiggler;
    int chanEb;
    int chanEn;
    int chanEt;
    int chanEw;
    if (max != 0)
    {
        chanEb = 100 * Boss / max;
        chanEn = 100 * Narrow / max;
        chanEt = 100 * Toucher / max;
        chanEw = 100 * Wiggler / max;
    }
    else
    {
        chanEb = 1;
        chanEn = 1;
        chanEt = 1;
        chanEw = 1;
    }
    int pick = rand() % (chanEb + chanEn + chanEt + chanEw);
    if (pick < chanEb) enemies.push_back(std::make_shared < EnemyBoss>(Coordinates(GameRender::Width, rand() % GameRender::Height), Shots));
    else if (pick < chanEb + chanEn) enemies.push_back(std::make_shared < EnemyNarrow>(Coordinates(GameRender::Width, rand() % GameRender::Height), Shots));
    else if (pick < chanEb + chanEn + chanEt) enemies.push_back(std::make_shared <EnemyToucher>(Coordinates(GameRender::Width, rand() % GameRender::Height), Shots));
    else if (pick < chanEb + chanEn + chanEt + chanEw) enemies.push_back(std::make_shared <EnemyWiggler>(Coordinates(GameRender::Width, rand() % GameRender::Height), Shots));
}

int Spawner::getTimer()
{
    return (400 - (4 * 10 * Spawn)); // 400 ticks are 1 second
}