#ifndef GAME_H
#define GAME_H
#include "gui.h"

class Game
{
public:
    Game();

private:
    Gui *gui;
    int whoseTurn;
    int score;
    void changeTurn();
};

#endif // GAME_H
