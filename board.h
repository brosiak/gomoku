#ifndef BOARD_H
#define BOARD_H
#include <QVector>
#include <iostream>
#include <QPoint>
class Board
{
public:
    Board(int dimension);
    void printBoard();
    void resetBoard();
    int getCellValue(int x, int y);
    int getCellValue(std::pair<int, int> coords);
    void setCellValue(int x, int y, const int PLAYER);
    void setCellValue(std::pair<int, int> coords, const int PLAYER);
    bool checkVertical(const int x);
    bool checkHorizontal(const int y);
    bool checkDiagonalBR();
    bool checkDiagonalBL();
    bool checkWin(std::pair<int, int> coords);

    bool checkWinScore(int first, int second, int &score);
    static constexpr int WIN_SCORE = 5;
    static constexpr int START_SCORE = 1;
    static constexpr int INDEXING = 1;
private:
    QVector<QVector<int>> board_matrix;
    bool isWinSeq;
};

#endif // BOARD_H
