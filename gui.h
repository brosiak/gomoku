#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <QPainter>
#include "board.h"
#include <iostream>



class Gui : public QMainWindow
{
    Q_OBJECT

public:
    Gui(QWidget *parent = nullptr);
    ~Gui();
    virtual void paintEvent(QPaintEvent *event)override;
    void print_board();
    void init_board(QPainter *painter);
    void draw_balls(QPainter *painter);
    int get_cell_value(int x, int y);
    int get_cell_value(std::pair<int, int> coords);
    std::pair<int, int> get_coords(QPoint point);
    bool is_clicked;
    Board *board;

private:
    static constexpr int border = 6;
    static constexpr int dimension = 15;
    static constexpr int cell_size_px = 64;
    static constexpr int board_size_px = dimension * cell_size_px;
    QPoint last_point;
    void mousePressEvent(QMouseEvent *event)override;


};
#endif // GUI_H
