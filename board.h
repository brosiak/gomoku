#ifndef BOARD_H
#define BOARD_H
#include <QPainter>
#include <iostream>
class Board
{
public:
    Board(int dimension);
    void print_board();
    int get_cell_value(int x, int y);
    int get_cell_value(std::pair<int, int> coords);
    void set_cell_value(int x, int y);
    void set_cell_value(std::pair<int, int> coords);
    bool check_vertical();
    bool check_horizontal();
    const static int win_score = 5;
private:
    QVector<QVector<int>> board_matrix;
};

#endif // BOARD_H
