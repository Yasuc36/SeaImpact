#pragma once
#include "Shot.h"

/**
* Class that takes care of everything, that is connected directly to player.
*/

class Player : public BaseObject
{
private:
	int Score;
	int Hp;
	int Rockets;
	int Magazine;
	int WeaponCooldown;	// Between each shot player must wait for the cooldown.
	bool Shield;
	bool Invincibility;
	bool Legend;	// Display/hide legend at the bottom of the screen.
	bool Play;	// Keeps track of running game. (When Hp reaches zero -> false)
	int InvDur;	// Invincibility duration
	int MaxHeight;	// Maximum height for ship position
	bool usingRocket;	// Keeps track, if player fired the rocket.
public:
	std::vector<Shot> Shots;	// Keeps all shots fired by a player.
	Player();	// Constructor
	bool addHp(const int hp);
	bool addInvincibility();
	bool addRocket(const int rockets);
	bool addShield();
	void addScore(int value);
	void addBullet(int value);	// Adds bullets in magazine (reloads).
	void coolWeapon(int value);	// Between each shot player must wait for the cooldown. This cools a weapon by a specified value.
	bool remHp(const int hp);	// rem = remove
	bool remInvincibility();
	bool remRocket(const int hp);
	bool remShield();
	void remShot();
	bool detectKey(WINDOW* win); // Detects keyboard input.
	void setLegend(bool state);
	bool getLegend();
	int getHp();
	int getRockets();
	int getScore();
	int getMagazine();
	bool getUsedRocket();
private:
	void MoveUp();
	void MoveDown();
};