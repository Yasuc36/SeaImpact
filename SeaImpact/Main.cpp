#include "curses.h"
#include "GameRender.h"
#include "FileManager.h"
#include "Control.h"
#include "EnemyBoss.h"
#include "EnemyNarrow.h"
#include "EnemyToucher.h"
#include "EnemyWiggler.h"
#include "BonusHealth.h"
#include "BonusInvincibility.h"
#include "BonusRockets.h"
#include "BonusShield.h"
#include "Spawner.h"
#include "FileManager.h"
#include <iostream>
#include <ctime>
#include <memory>

using namespace std;

int main(void)
{
    //Initialization
    srand((unsigned int)time(NULL));
    initscr();
    Player pl;
    GameRender gra(&pl, FileManager::loadBackground("background.txt", GameRender::Width, GameRender::Height));
    // Main menu
    while(gra.homeScreen(FileManager::loadHS()))
    {
        pl = Player();
        int counter = 0;    // Counts frames.
        vector<Shot> Shots;
        vector<shared_ptr<Enemy>> enemies;
        vector<shared_ptr<Bonus>> bonuses;
        vector<int> density = FileManager::loadDensity("density.txt");
        Spawner spawner = Spawner(density[0], density[1], density[2], density[3], density[4], density[5], &Shots);
        gra.init_screen();
        gra.draw_ui(pl.getScore(), pl.getMagazine(), pl.getRockets(), pl.getHp());
        gra.draw_shape(pl.getShape(), pl.getPosition());
        while (pl.detectKey(gra.Functionality)) // Each loop is 1 tick
        {
            // Cleanup
            flushinp(); // Flushes any unused input, so that only first press per tick is used.
            if (pl.getUsedRocket()) // Checks if player shot a rocket.
            {
                Control::destroyAll(enemies);
            }
            if (counter % spawner.getTimer() == 0) spawner.spawnEnemy(enemies);    // Spawns enemy after delay passed.
            gra.clear_window(); // Cleans game area.

            // Rendering part
            gra.draw_background();
            gra.draw_shape(pl.getShape(), pl.getPosition()); // Draw player.        
            int max = pl.Shots.size();
            for (int i = 0; i < max; ++i) gra.draw_shape(pl.Shots[i].getShape(), pl.Shots[i].getPosition());    // Draw player shots.
            max = enemies.size();
            for (int i = 0; i < max; ++i) gra.draw_shape(enemies[i]->getShape(), enemies[i]->getPosition());    // Draw enemies.
            max = (int)Shots.size();
            for (int i = 0; i < max; ++i) gra.draw_shape(Shots[i].getShape(), Shots[i].getPosition());  // Draw enemy shots.
            max = bonuses.size();
            for (int i = 0; i < max; ++i) gra.draw_shape(bonuses[i]->getShape(), bonuses[i]->getPosition());    // Draw bonuses.
            gra.draw_ui(pl.getScore(), pl.getMagazine(), pl.getRockets(), pl.getHp()); // Draws score.

            // Update part
            counter++;
            Control::update(pl.Shots); // Updates player shots.
            Control::collision(enemies, bonuses, &pl.Shots, &pl, &spawner);   // Controls collisions for enemies.
            Control::update(Shots); // Update enemy shots.
            Control::update(enemies);  // Updates enemy position.
            if (counter % 3 == 0) Control::update(bonuses);  // Updates bonuses every 3rd frame.
            Control::collision(&pl, &Shots);   // Controls collisions of player and enemy shots.
            Control::collision(&pl, bonuses);  // Controls collisions for bonuses.
            Control::collision(enemies, bonuses, &pl.Shots, &pl, &spawner);   // Controls collisions for enemies.
            if (counter % 40 == 0)  // Add score, ammo and update Invincibility every 40th frame.
            {
                pl.addScore(10);
                pl.addBullet(2);
                pl.remInvincibility();
            }
            if (counter % 10 == 0) pl.coolWeapon(1);    // Resets cooldown for shooting every 10th frame.
            if (pl.getLegend() == true) // Draws legend at the bottom.
            {
                pl.setLegend(false);
                gra.draw_legend();
            }
            Control::sleep(25); // Freezes frame for a bit.
        }
        int hsPos = FileManager::saveHS(pl.getScore());
        gra.endScreen(pl.getScore(), hsPos, FileManager::loadHS());
    }
    endwin();
    return 0;
}