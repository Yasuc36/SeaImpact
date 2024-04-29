#include "Control.h"
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void Control::update(Player * obj, WINDOW * win)
{
	obj->detectKey(win);
}

void Control::update(std::vector<Shot>& obj)
{
    int size = (int)obj.size();
    for (int i = 0; i < size ; ++i)
    {
        obj[i].move();
        if (obj[i].outOfBounds())
        {
            obj.erase(obj.begin() + i);
            --i;
            --size;
        }
    }
}

void Control::update(std::vector< std::shared_ptr<Enemy>> & obj)
{
    int size = (int)obj.size();
    for (int i = 0; i < size; ++i)
    {
        obj[i]->move();
        obj[i]->shoot();
    }
}

void Control::update(std::vector< std::shared_ptr<Bonus>> & obj)
{
    int size = (int)obj.size();
    for (int i = 0; i < size; ++i)
    {
        obj[i]->move();
        if (obj[i]->outOfBounds())
        {
            obj.erase(obj.begin() + i);
            --i;
            --size;
        }
    }
}

void Control::collision(Player * pl, std::vector< std::shared_ptr<Bonus>> & obj)
{
    std::vector<Coordinates> coords;
    std::vector<std::string> shape = pl->getShape();
    Coordinates pos = pl->getPosition();
    int size = (int)shape.size();
    for (int i = 0; i < size; ++i)  // Checks position of every part of the object.
    {
        int length = (int)shape[i].length();
        for (int j = 0; j < length; ++j)
        {
            if (shape[i][j] != ' ') coords.push_back(Coordinates(pos.X+j, pos.Y + i));
        }
    }
    size = (int)coords.size();
    for (int i = 0; i < size; ++i)  // Checks for collision between objects.
    {
        int objSize = (int)obj.size();
        for (int j = 0; j < objSize; ++j)
        {
            if (coords[i] == obj.at(j)->getPosition())  // Collision
            {
                obj[j]->use(pl);
                obj.erase(obj.begin() + j);
                --j;
                --objSize;
            }
        }
    }
}

void Control::collision(Player* pl, std::vector<Shot>* shot)
{
        std::vector<Coordinates> coords;
        std::vector<std::string> shape = pl->getShape();
        Coordinates pos = pl->getPosition();
        int size = (int)shape.size();
        for (int i = 0; i < size; ++i)
        {
            int length = (int)shape[i].length();
            for (int j = 0; j < length; ++j)
            {
                if (shape[i][j] != ' ') coords.push_back(Coordinates(pos.X + j, pos.Y + i));
            }
        }
        size = (int)coords.size();
        for (int i = 0; i < size; ++i)
        {
            int shotSize = (int)shot->size();
            for (int j = 0; j < shotSize; ++j)
            {
                if (coords[i] == shot->at(j).getPosition())
                {
                    shot->erase(shot->begin() + j);
                    --j;
                    --shotSize;
                    pl->remHp(1);
                }
            }
        }
}

void Control::collision(std::vector<std::shared_ptr<Enemy>> & ship, std::vector<std::shared_ptr<Bonus>>& bonuses, std::vector<Shot>* shot, Player* pl, Spawner* sp)
{
    int max = (int)ship.size();
    for (int k = 0; k < max; ++k)
    {
        std::vector<Coordinates> coords;
        std::vector<std::string> shape = ship[k]->getShape();
        Coordinates pos = ship[k]->getPosition();
        int size = (int)shape.size();
        for (int i = 0; i < size; ++i)
        {
            int length = (int)shape[i].length();
            for (int j = 0; j < length; ++j)
            {
                if (shape[i][j] != ' ') coords.push_back(Coordinates(pos.X + j, pos.Y + i));
            }
        }
        size = (int)coords.size();
        for (int i = 0; i < size; ++i)
        {
            int shotSize = (int)shot->size();
            for (int j = 0; j < shotSize; ++j)
            {
                if (coords[i] == shot->at(j).getPosition())
                {
                    shot->erase(shot->begin() + j);
                    --j;
                    --shotSize;
                    ship[k]->Hp--;
                    if (ship[k]->Hp <= 0)
                    {
                        pl->addScore(ship[k]->getScore());
                        sp->spawnBonus(bonuses, ship[k]->getPosition());
                        ship.erase(ship.begin() + k);
                        --k;
                        --max;
                    }
                }
            }
        }
    }
}

void Control::destroyAll(std::vector< std::shared_ptr<Enemy>> & enemies)
{
    enemies.clear();
}

void Control::sleep(int miliseconds)
{
#ifdef _WIN32
    Sleep(miliseconds);
#else
    usleep(miliseconds * 1000);
#endif
}