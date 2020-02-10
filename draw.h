#ifndef DRAW_H
#define DRAW_H

#include <QMainWindow>
#include <QPainter>
#include <iostream>
#include <board.h>

class Board;

class Draw : public QMainWindow
{
    Q_OBJECT

public:
    Draw(QWidget *parent = nullptr);
    ~Draw();
    virtual void paintEvent(QPaintEvent *event)override;
    int get_dimension();
    int get_cell_size();
    int get_board_size();
    void print_board();
    void init_board(QPainter *painter);
    void draw_balls(QPainter *painter);
    int get_cell_value(int x, int y);
    int get_cell_value(std::pair<int, int> coords);
    std::pair<int, int> get_coords(QPoint point);
    bool isClicked;
    Board *board;
private:
    static const int dimension = 15;
    static const int cell_size = 64;
    static const int board_size = dimension * cell_size;
    QPoint last_point;
    void mousePressEvent(QMouseEvent *event)override;


};
#endif // DRAW_H
