#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <QPainter>
#include "board.h"
#include <iostream>
#include <QPushButton>


class Gui : public QMainWindow
{
    Q_OBJECT

public:
    Gui(QWidget *parent = nullptr);
    ~Gui();
    void initWindow();

private:
    virtual void paintEvent(QPaintEvent *event)override;

    void drawBoard();
    void drawInterface();
    void drawBall(const int x, const int y);
    void drawBalls();
    int getCellValue(int x, int y);
    int getCellValue(std::pair<int, int> coords);
    bool checkIfExceeds(QPoint point);
    void changePlayer();
    std::pair<int, int> getCoords(QPoint point);
    bool isClicked;
    bool gameStarted;
    Board board;
    int actualPlayer;
    static constexpr int border = 6;
    static constexpr int dimension = 15;
    int cellSizePx;
    int menuPx;
    int boardSizePx;
    int penWidth;
    static constexpr int middlePos = (dimension - (dimension%2)) / 2;
    static constexpr int firstPlayer = 1;
    static constexpr int secondPlayer = 2;
    static constexpr int emptyCell = 0;
    const QString backgroundColor ="#a1887f";
    const QString borderColor = "#725b53";
    const QString itemColor = "#d3b8ae";
    const QString buttonSheet =   "color: %1;"
                            "background-color: %2;"
                            "border-style: %3;"
                            "border-width: %4;"
                            "border-color: %5;"
                            "border-radius: %6";
    QPoint last_point;
    void mousePressEvent(QMouseEvent *event)override;
    QPushButton *newGameButton;
    QPushButton *exitGameButton;
    QPushButton *reDoButton;
    QPushButton *unDoButton;
    QVector<std::pair<int,int>> visited;
    QVector<std::pair<int,int>> popped;
    QFont uiFont;
    void setButtonTimeSheet(QPushButton *button);
    void calcGamePixels();
    void freeButtons();
    void drawButton(QPushButton *button, const float x, const float y, const int xSize, const int ySize);
    void drawButtons();
    void connectButtons();
private slots:
    void newGame();
    void resetGame();
    void exitGame();
    void unDo();
    void reDo();


};
#endif // GUI_H
