#ifndef BOARD_H
#define BOARD_H
#include <draw.h>

class Board
{
public:
    Board(int dimension);
    void print_board();
    int const &get_cell_value(int x, int y);
    int const &get_cell_value(std::pair<int, int> coords);
    void set_cell_value(int x, int y, QVector<QVector<int>> &board_matrix);
    void set_cell_value(std::pair<int, int> coords);
    QVector<QVector<int>> &get_board_matrix();
    void set_board_matrix(QVector<QVector<int>> &board_matrix);
private:
    QVector<QVector<int>> board_matrix;
};

#endif // BOARD_H
