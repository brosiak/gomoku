#ifndef GAME_H
#define GAME_H
#include "gui.h"

class Game
{
public:
    Game();
    Gui *gui;
private:
    int whoseTurn;
    int score;
    void changeTurn();
};

#endif // GAME_H
