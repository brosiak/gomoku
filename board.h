#ifndef BOARD_H
#define BOARD_H
#include <QVector>
#include <iostream>
class Board
{
public:
    Board(int dimension);
    void printBoard();
    int getCellValue(int x, int y);
    int getCellValue(std::pair<int, int> coords);
    void setCellValue(int x, int y);
    void setCellValue(std::pair<int, int> coords);
    bool checkVertical();
    bool checkHorizontal();
    bool checkDiagonalBR();
    bool checkDiagonalBL();
    bool checkWinScore(int first, int second, int &score);
    static constexpr int WIN_SCORE = 5;
    static constexpr int START_SCORE = 1;
private:
    QVector<QVector<int>> board_matrix;
};

#endif // BOARD_H
