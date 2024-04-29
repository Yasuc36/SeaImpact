#pragma once
#include "curses.h"
#include "Coordinates.h"
#include <string>
#include <vector>

/**
* Class that takes care about visual output.
*/

class GameRender
{
private:
	class Player* PlayerPtr;
	bool Legend;
	bool Colors;	// Keep information, if colored background should be used.
	WINDOW* UItop;	// Top 2 lines
	WINDOW* GameScreen;	// Height - 2 top and 2 bottom line (-4)
	WINDOW* UIbot;	// Last but one line
	WINDOW* UIcontrols;	// Last line
	std::vector<std::string> Background;
	void outputText(WINDOW* win, std::vector<std::string> text);	// Outputs text to middle of the screen.
	void pressToEnd(WINDOW* win, int miliseconds);	// Types 'exit text' at the bottom and waits for any input.
	std::vector<std::string> returnScoreText(const int highScorePosition, std::vector<std::string> scoreList);	// Return formated high scores.
public:
	static const int Width = 120;	// Width of the whole game
	static const int Height = 30;	// Height of the whole game
	WINDOW* Functionality;	// Bottom-Right windown (1x1 size) for inputs etc.
	GameRender(Player* playerPtr, std::vector<std::string> background);	// Constructor
	void clear_window();	// Clears game screen.
	void draw_background();	// Draws colored background.
	void draw_shape(std::vector<std::string> shape, Coordinates position);	// Draws shape at their location (e.g. ship, bonuses...).
	void draw_ui(int score, int magazine, int rockets, int hp);	// Draws user interface at the top.
	void init_screen();	// initialize screen before running the game.
	void draw_legend();	// Draws legend of bonuses at the bottom.
	void refresh();	// Refreshes all windows.
	bool homeScreen(std::vector<std::string> scoreList); // Manages main menu (false for exiting the game).
	void endScreen(int score, int highScorePosition, std::vector<std::string> scoreList);	// Draws end screen after death.
};