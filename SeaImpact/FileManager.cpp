#include "FileManager.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <regex> 

bool FileManager::compare(const std::string& big, const std::string& low)
{
    if (big == low) return false;
    else if (big.length() > low.length()) return true;
    else if (big.length() < low.length()) return false;
    else if (big > low) return true;
    return false;
}

int FileManager::saveHS(int score)
{
    int retVal = 0;
    unsigned int capacity = 3;
    std::string file = "Highscore.sav";
    std::vector<std::string> scoreList = loadHS();
    std::stringstream ss;
    ss << score;
    std::vector<std::string>::iterator it;
    if (scoreList.size() > 0)
    {
        it = std::lower_bound(scoreList.begin(), scoreList.end(), ss.str(), FileManager::compare);
        retVal = (it - scoreList.begin());
        scoreList.insert(it, ss.str());
    }
    else scoreList.push_back(ss.str());
    if (scoreList.size() > capacity) scoreList.resize(capacity);
    if (retVal >= (int)capacity) retVal = -1;
    std::ofstream os;
    os.open(file, std::ofstream::out | std::ofstream::trunc);
    int size = scoreList.size();
    for (int i = 0; i < size; ++i) os << scoreList[i] + "\n";
    os.close();
    return retVal;
}

std::vector<std::string> FileManager::loadHS()
{
    std::string file = "Highscore.sav";
    std::string temp;
    std::vector<std::string> scoreList;
    std::ifstream is;
    is.open(file);
    while (std::getline(is, temp)) scoreList.push_back(temp); 
    is.close();
    return scoreList;
}

std::vector<int> FileManager::loadDensity(std::string fileName)
{
    std::ifstream is(fileName);
    std::ofstream os;
    std::vector<int> fileContet = { -1, -1, -1, -1, -1, -1};
    if (is.fail())  // If cannot open file (doesn't exist etc.), create new with default values.
    {
        os.open(fileName, std::ofstream::out | std::ofstream::trunc);
        os << "Name\tValue(0-9)\n";
        os << "spawn\t6\n";
        os << "boss\t2\n";
        os << "narrow\t7\n";
        os << "toucher\t6\n";
        os << "wiggler\t5\n";
        os << "bonus\t3\n";
        os.close();
        is.open(fileName);
    }
    std::vector<std::string> tempVector;
    std::string temp;
    while (std::getline(is, temp)) tempVector.push_back(temp);
    int size = tempVector.size();
    for (int i = 0; i < size; ++i)  // Checks each line for presence of wanted lines using regular expressions.
    {
        if (std::regex_match(tempVector[i], std::regex("^(spawn)\\s*[0-9]$"))) fileContet[0] = tempVector[i][tempVector[i].length() - 1] - 48; 
        else if (std::regex_match(tempVector[i], std::regex("^(boss)\\s*[0-9]$"))) fileContet[1] = tempVector[i][tempVector[i].length() - 1] - 48;
        else if (std::regex_match(tempVector[i], std::regex("^(narrow)\\s*[0-9]$"))) fileContet[2] = tempVector[i][tempVector[i].length() - 1] - 48;
        else if (std::regex_match(tempVector[i], std::regex("^(toucher)\\s*[0-9]$"))) fileContet[3] = tempVector[i][tempVector[i].length() - 1] - 48;
        else if (std::regex_match(tempVector[i], std::regex("^(wiggler)\\s*[0-9]$"))) fileContet[4] = tempVector[i][tempVector[i].length() - 1] - 48;
        else if (std::regex_match(tempVector[i], std::regex("^(bonus)\\s*[0-9]$"))) fileContet[5] = tempVector[i][tempVector[i].length() - 1] - 48;
    }
    size = fileContet.size();
    if (fileContet[0] == -1) fileContet[0] = 6; // If some values were not found, set their values as default.
    if (fileContet[1] == -1) fileContet[1] = 2;
    if (fileContet[2] == -1) fileContet[2] = 7;
    if (fileContet[3] == -1) fileContet[3] = 6;
    if (fileContet[4] == -1) fileContet[4] = 5;
    if (fileContet[5] == -1) fileContet[5] = 3;
    return fileContet;
}

std::vector<std::string> FileManager::loadBackground(std::string fileName, int width, int height)
{
    std::ifstream is(fileName);
    std::ofstream os;
    if (is.fail())  // If cannot open file (doesn't exist etc.), create new with default values.
    {
        is.close();
        os.open(fileName, std::ofstream::out | std::ofstream::trunc);  
        os << "                                                                                                                        \n"; // Default background            
        os << "                                                                                                                        \n";
        os << "                                                                                                                        \n";
        os << "                                                                                                                        \n";
        os << "                                                                                                                        \n";
        os << "                                                                                                                        \n";
        os << "                                                                                                                        \n";
        os << "                                                                                                                        \n";
        os << "                                                                x                                                       \n";
        os << "                                                                xx                                                      \n";
        os << "                                                               xx                                                       \n";
        os << "                                                              xxxx                                                      \n";
        os << "                                                               xxxx                                                     \n";
        os << "                                                               xxxxx                                                    \n";
        os << "                                                              xxxxxxx                                                   \n";
        os << "                                                           xxxxxxxxxxxx                                                 \n";
        os << "xxxxxxx                                                  xxxxxxxxxxxxxxx                                                \n";
        os << "xxxxxxxxxxx                                           xxxxxxxxxxxxxxxxxxxxx                                        xxxxx\n";
        os << "xxxxxxxxxxxxxx                                    xxxxxxxxxxxxxxxxxxxxxxxxxxxx                                xxxxxxxxxx\n";
        os << "xxxxxxxxxxxxxxxxxx                             xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx                        xxxxxxxxxxxxxx\n";
        os << "xxxxxxxxxxxxxxxxxxxxxx                       xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx                   xxxxxxxxxxxxxxxxx\n";
        os << "xxxxxxxxxxxxxxxxxxxxxxxxxxx            xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        os << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        os << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        os << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        os << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        os.close();
        is.open(fileName);
    }
    std::vector<std::string> retVect;
    std::string temp;
    while (std::getline(is, temp)) retVect.push_back(temp);
    int size = retVect.size();
    if (size > height) retVect.resize(height);  // Resizes vector to fit on game screen.
    else if (size < height)
    {
        for (int i = size; i < height; ++i)
        {
            retVect.push_back("");
            retVect[i].resize(width, ' ');
        }
    }
    for (int i = 0; i < size; ++i)
    {
        if ((int)retVect[i].length() != width) retVect[i].resize(width, ' ');
    }
    return retVect;
}