#pragma once
#include <vector>
#include <string>

/**
* Class for managing files. (Loading and saving)
*/

class FileManager
{
private:
	static bool compare(const std::string& big, const std::string& low);	// Comparator for lower_bound
public:
	static int saveHS(int score);	// Saves highscore in the file.
	static std::vector<std::string> loadHS();	// Loads highscore from the file.
	static std::vector<int> loadDensity(std::string fileName);	// Loads density values from file.
	static std::vector<std::string> loadBackground(std::string fileName, int width, int height);	// Loads background from file.
};