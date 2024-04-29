#include "GameRender.h"
#include "FileManager.h"
#include <cstdlib>
#include <cmath>
#include <sstream>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void GameRender::outputText(WINDOW* win, std::vector<std::string> text)
{
    wclear(win);
    unsigned int size = text.size();
    for (unsigned int i = 0; i < size; ++i)
    {
        unsigned int length = text[i].length();
        wmove(win, (Height - size) / 2 + i, Width / 2 - Width / 25 - length / 2);   // Center cursos in the middle, minus the offset.
        for (unsigned int j = 0; j < length; ++j) waddch(win, text[i][j]);
    }
    wrefresh(win);
}

void GameRender::pressToEnd(WINDOW* win, int miliseconds)
{
    std::string pressEnd = "Press any key to return to the main menu.";
    int length = pressEnd.length();
    wmove(win, GameRender::Height - 2, GameRender::Width / 2 - GameRender::Width / 25 - length / 2);
    for (int j = 0; j < length; ++j) waddch(win, pressEnd[j]);
    wrefresh(win);
#ifdef _WIN32
    Sleep(miliseconds);
#else
    usleep(miliseconds * 1000);
#endif
    flushinp(); // Flushes any unused input, so that only first press per tick is used.ss
    wgetch(win);
    wclear(win);
    wrefresh(win);
}

std::vector<std::string> GameRender::returnScoreText(const int highScorePosition, std::vector<std::string> scoreList)
{
    std::vector<std::string> retText = {"Top high scores:", ""};    
    int slsize = scoreList.size();
    std::stringstream ss;
    for (int i = 0; i < slsize; ++i)
    {
        std::string prefix = "       ";
        if (i == highScorePosition) prefix = "You -> ";
        ss.str("");
        ss << (i + 1);
        std::string postfix = "       ";
        if (i > 0)
        {
            unsigned int cycle = scoreList[0].length() - scoreList[i].length();
            for (unsigned int j = 0; j < cycle; ++j) postfix += " ";
        }
        retText.push_back(prefix + ss.str() + ".: " + scoreList[i] + postfix);
    }
    return retText;
}

GameRender::GameRender(Player* playerPtr, std::vector<std::string> background)
{
    PlayerPtr = playerPtr;
    Legend = false;
    Colors = true;
    if (has_colors() == FALSE) Colors = false;  // Checks, if terminal support colors.
    else
    {
        start_color();
        init_pair(1, COLOR_BLACK, COLOR_CYAN);
        init_pair(2, COLOR_BLACK, COLOR_GREEN);
    }
    UItop = newwin(2, Width, 0, 0);
    GameScreen = newwin(Height - 4, Width, 2, 0);
    UIbot = newwin(1, Width, Height - 2, 0);
    UIcontrols = newwin(1, Width - 1, Height - 1, 0);
    Functionality = newwin(1, 1, Height - 1, Width - 1);
    Background = background;
}

void GameRender::clear_window()
{
    werase(GameScreen);
}

void GameRender::draw_background()
{
    wmove(GameScreen, 0, 0);
    for (int i = 0; i < Height - 4; ++i)
    {
        for (int j = 0; j < Width; ++j)
        {
            if (Background[i][j] == ' ' && Colors) wattron(GameScreen, COLOR_PAIR(1));
            else if (Colors) wattron(GameScreen, COLOR_PAIR(2));
            waddch(GameScreen, ' ');
            wattroff(GameScreen, COLOR_PAIR(1));
            wattroff(GameScreen, COLOR_PAIR(2));
        }
    }
    wrefresh(GameScreen);
}

void GameRender::draw_shape(std::vector<std::string> shape, Coordinates position)
{
    int shapeW = shape[0].length();
    int shapeH = shape.size();
    if (GameRender::Width - position.X - shapeW >= 0)
    {
        for (int i = 0; i < shapeH; ++i)
        {
            wmove(GameScreen, position.Y + i, position.X);
            for (int j = 0; j < shapeW; ++j)
            {
                {
                    if(Background[position.Y + i][position.X + j] == ' ' && Colors) wattron(GameScreen, COLOR_PAIR(1));
                    else if (Colors) wattron(GameScreen, COLOR_PAIR(2));
                    waddch(GameScreen, shape[i][j]);
                    wattroff(GameScreen, COLOR_PAIR(1));
                    wattroff(GameScreen, COLOR_PAIR(2));
                }
            }
        }
        wmove(GameScreen, 0, 0);
        wrefresh(GameScreen);
    }
}

void GameRender::draw_ui(int score, int magazine, int rockets, int hp)
{
    std::stringstream ss;
    ss << score;
    wmove(UItop, 0, 8);
    waddstr(UItop, (char*)(ss.str().c_str()));
    wmove(UItop, 0, Width / 2 - 10);
    for (int i = 0; i < 20; ++i)
    {
        waddch(UItop, ' ');
        wrefresh(UItop);
    }
    wmove(UItop, 0, Width / 2 - (magazine));
    for (int i = 0; i < magazine * 2; ++i)
    {
        waddch(UItop, '|');
        wrefresh(UItop);
    }
    wmove(UItop, 0, Width - 20 - 8);
    waddstr(UItop, "         ");
    wmove(UItop, 0, Width - 20 - 8);
    for (int i = 0; i < rockets; ++i) waddstr(UItop, "=> ");
    wmove(UItop, 0, Width - 9);
    waddstr(UItop, "         ");
    wmove(UItop, 0, Width - 9);
    for (int i = 0; i < hp; ++i) waddstr(UItop, "<3 ");
    wmove(UItop, 0, 0);
    wrefresh(UItop);
}

void GameRender::init_screen()
{
    curs_set(0); // Hides cursos (Visibility range: 0-3).
    cbreak(); // Getch is not waiting for a new line.
    noecho(); // Input is not shown on screen.
    nodelay(stdscr, TRUE);  // Window doesn't wait for input
    nodelay(UItop, TRUE);
    nodelay(GameScreen, TRUE);
    nodelay(UIbot, TRUE);
    nodelay(UIcontrols, TRUE);
    nodelay(Functionality, TRUE);
    for (int i = 0; i < Width; ++i) waddch(UItop, ' ');
    wmove(UItop, 0, 1);
    waddstr(UItop, "Score: "); 
    wmove(UItop, 0, Width / 2 - 11 - 10);
    waddstr(UItop, "Magazine: [");
    wmove(UItop, 0, Width / 2 + 10);
    waddch(UItop, ']');
    wmove(UItop, 0, Width - 20 - 8 - 9);
    waddstr(UItop, "Rockets: ");
    wmove(UItop, 0, Width - 9 - 8);
    waddstr(UItop, "Health: ");
    wmove(UItop, 1, 0);
    for (int i = 0; i < Width; ++i)
    {
        waddch(UItop, '-');
        wrefresh(UItop);
    }
    for (int i = 0; i < Width * 26; ++i)waddch(GameScreen, ' ');
    for (int i = 0; i < Width; i++)
    {
        waddch(UIbot, '-');
        wrefresh(UIbot);
    }
    wmove(UIbot, 1, 0);
    waddstr(UIcontrols, " [W] Move up | [S] Move down | [J] Shoot a bullet | [K] Shoot a rocket | [M] Return to main menu | [L] Show legend         ");
    wrefresh(UItop);
    wrefresh(GameScreen);
    wrefresh(UIbot);
    wrefresh(UIcontrols);
}

void GameRender::draw_legend()
{
    Legend = !Legend;
    wmove(UIcontrols, 0, 0);
    switch (Legend)
    {
    case true:
        waddstr(UIcontrols, " H: +1 health | I: Grants short-time invincibility | R: +1 rocket | S: Adss the shield |     [L] Back to controls      ");
        break;
    case false:
        waddstr(UIcontrols, " [W] Move up | [S] Move down | [J] Shoot a bullet | [K] Shoot a rocket | [M] Return to main menu | [L] Show legend     ");
        break;
    }
    wmove(UIcontrols, 0, 0);
    wrefresh(UIcontrols);
}

void GameRender::refresh()
{
    wrefresh(UItop);
    wrefresh(GameScreen);
    wrefresh(UIbot);
    wrefresh(UIcontrols);
    wrefresh(Functionality);
}

bool GameRender::homeScreen(std::vector<std::string> scoreList)
{
    curs_set(0); // Hides cursos (Visibility range: 0-3)
    cbreak(); // getch is not waiting for a new line
    noecho(); // input is not shown on screen
    WINDOW* wholeScreen = newwin(Height, Width, 0, 0);
    bool menu = true;
    while (menu)
    {
        wclear(wholeScreen);
        wrefresh(wholeScreen);
        std::vector<std::string> text = {
    "                        ___                                                                           ",
    "                     .-'   `'.                                                                        ",
    "                    /         \\                                                                       ",
    "                    |         ;                                                                       ",
    "                    |         |           ___.--,                                                     ",
    "           _.._     |0) ~ (0) |    _.---'`__.-( (_.                                                   ",
    "    __.--'`_.. '.__.\\    '--. \\_.-' ,.--'`     `\"\"`                                                   ",
    "   ( ,.--'`   ',__ /./;   ;, '.__.'`    __                                                            ",
    "   _`) )  .---.__.' / |   |\\   \\__..--\"\"  \"\"\"--.,_                                                    ",
    "  `---' .'.''-._.-'`_./  /\\ '.  \\ _.-~~~````~~~-._`-.__.'                                             ",
    "        | |  .' _.-' |  |  \\  \\  '.         _____ `~---`       _____                            _     ",
    "         \\ \\/ .'     \\  \\   '. '-._)       / ____|            |_   _|                          | |    ",
    "          \\/ /        \\  \\    `=.__`~-.   | (___   ___  __ _    | |  _ __ ___  _ __   __ _  ___| |_   ",
    "          / /\\         `) )    / / `\"\".`\\  \\___ \\ / _ \\/ _` |   | | | '_ ` _ \\| '_ \\ / _` |/ __| __|  ",
    "    , _.-'.'\\ \\        / /    ( (     / /  ____) |  __/ (_| |  _| |_| | | | | | |_) | (_| | (__| |_   ",
    "     `--~`   ) )    .-'.'      '.'.  | (  |_____/ \\___|\\__,_| |_____|_| |_| |_| .__/ \\__,_|\\___|\\__|  ",
    "            (/`    ( (`          ) )  '-;                                     | |                     ",
    "             `      '-;         (-'                                           |_|                     ",
    "                                               [1] Play                                               ",
    "                                               [2] Show Highscore                                     ",
    "                                               [3] Import Background                                  ",
    "                                               [4] Import Enemy Density                               ",
    "                                               [5] Exit                                               " };
        unsigned int textW = text[0].length();
        unsigned int textH = text.size();
        for (unsigned int i = 0; i < textH; ++i)
        {
            wmove(wholeScreen, ((Height - textH) / 2) + i, (Width - textW) / 2);
            for (unsigned int j = 0; j < textW; ++j) waddch(wholeScreen, text[i][j]);
        }
        wrefresh(wholeScreen);
        bool repeat = true;
        while (repeat)
        {
            int ch = wgetch(wholeScreen);
            switch(ch)
            {
                case '1':   // New game
                {
                    repeat = false;
                    menu = false;
                }
                    break;
                case '2':   // Show highscore list
                {
                    repeat = false;
                    wclear(wholeScreen);
                    std::vector<std::string> textHS;
                    int sizeSL = scoreList.size();
                    if (sizeSL != 0) textHS = returnScoreText(-1, scoreList);
                    else textHS.push_back("No highscores set.");
                    outputText(wholeScreen, textHS);
                    pressToEnd(wholeScreen, 0);
                }
                    break;
                case '3':   // Import background
                {
                    std::string fileName = "background.txt";
                    repeat = false;
                    std::stringstream ss;
                    std::vector<std::string> textED = {
                        "[1] Import file             ",
                        "[2] How to change background" };
                    outputText(wholeScreen, textED);
                    ss << Width;
                    std::string w = ss.str();
                    ss.str("");
                    ss << Height;
                    std::string h = ss.str();
                    textED = {
                        "How to change the background:",
                        "",
                        "- Locate and open the file '" + fileName + "' in the game folder.",
                        "- Game will render two colors.",
                        "- Draw background in textfile using any ASCII characters.",
                        "- Spaces will be represented as one color.",
                        "- Other characters will represent second color.",
                        "- Width should be " + w + " and height " + h + ".",
                        "- Save and close the file after editing.",
                        "- Changes will be seen after restarting the game."
                    };
                    wclear(wholeScreen);
                    outputText(wholeScreen, textED);
                    pressToEnd(wholeScreen, 0);
                }
                    break;
                case '4':   // Import enemy density file
                {
                    std::string fileName = "density.txt";
                    repeat = false;
                    std::vector<std::string> textED = {
                        "[1] Import file         ",
                        "[2] How to change values"};
                    outputText(wholeScreen, textED);
                        textED = {
                            "How to change the spawning values:",
                            "",
                            "- Locate and open the file '" + fileName + "' in the game folder.",
                            "- Dont put any other text than name and number between 0-9.",
                            "- Keep names unchanged.",
                            "- Name and value can be separated by whitespaces (space, tabulator...).",
                            "- Save and close the file after editing.",
                            "- Changes will be seen when you start playing."
                            "- Keep each name and coresponding value at individual lines.",
                            "",
                            "Spawn",
                            "-----",
                            "Enemies spawn at 10-(value) second rate. [0 = 10 seconds] [9 = 1 second]",
                            "",
                            "Boss, Narrow, Toucher, Wiggler",
                            "------------------------------",
                            "Value represents how possible is, that enemy type will be chosen among the others to spawn.",
                            "All values are added together and then possibility in % for each is calculated.",
                            "For example, Boss spawn chance (in %) is calculated like this: (Boss/(Boss+Narrow+Toucher+Wiggler))*100",
                            "",
                            "Bonus",
                            "-----",
                            "Value represents percentil chance for bonus to drop from dead enemy.",
                            "Spawn chance is (Value*10)%",
                            ""
                        };
                    wclear(wholeScreen);
                    outputText(wholeScreen, textED);
                    pressToEnd(wholeScreen, 0);
                }
                    break;
                case '5':
                {
                    return false;
                }
                    break;
            }
        }
    }
    return true;
}

void GameRender::endScreen(const int score, const int highScorePosition, std::vector<std::string> scoreList)
{
    wclear(UItop);
    wclear(GameScreen);
    wclear(UIbot);
    wclear(UIcontrols);
    wclear(Functionality);
    WINDOW* wholeScreen = newwin(Height, Width, 0, 0);
    std::stringstream ss;
    ss << score;
    std::vector<std::string> text = { "You died!", "","Final Score: " + ss.str(), "", "" };
    std::vector<std::string> texths = returnScoreText(highScorePosition, scoreList);
    text.insert(text.end(), texths.begin(), texths.end());
    outputText(wholeScreen, text);
    nodelay(wholeScreen, false);
    pressToEnd(wholeScreen, 1000);
}