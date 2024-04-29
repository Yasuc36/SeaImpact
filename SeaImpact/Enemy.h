#pragma once
#include "BaseObject.h"
#include "Shot.h"

/**
* Class that takes care about enemy ships and their behaviour.
*/

class Enemy : public BaseObject
{
private:
	bool Up;	// If ship is moving upwards
	int MaxH;	// Maximum Y position
	int MinH;	// Minimum Y position
	int MaxMoveDelay;	// Delay between moves of enemy
	int MoveDelay;	// Current move delay
	int MaxShootDelay;	// Delay between enemy shots
	int ShootDelay;	// Current shooting delay
	int Score;	// How much score does enemy rewards.
public:
	int Hp;	// Health points of enemy
	std::vector<Shot> * Shots;
	Enemy(const Coordinates& pos, const std::vector<std::string>& shape, int maxH, int minH, bool up, int movedelay, int shootdelay, std::vector<Shot> * shots, int score, int hp);	// Constructor
	void move();
	virtual void shoot();
	void remShot();
	int getScore();
};