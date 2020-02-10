#include "draw.h"
#include <QMouseEvent>
#include <QDebug>
#include <stdlib.h>
Draw::Draw(QWidget *parent)
    : QMainWindow(parent), board(new Board (this->dimension))
{
}

Draw::~Draw()
{
}

void Draw::init_board(QPainter *painter)
{
    painter->setWindow(0, 0, this->get_board_size(), this->get_board_size());
    for(int i=0; i<this->dimension;i++)
    {
        for(int j=0; j<this->dimension;j++)
        {
            painter->drawRect(i*this->cell_size, j*this->cell_size, this->cell_size, this->cell_size);
        }
    }
}

void Draw::draw_balls(QPainter *painter)
{
    int border = 6;
    for(int i=0; i<this->dimension; i++){
        for(int j=0; j<this->dimension;j++){
            if (this->board->get_cell_value(i,j) == 0){
                continue;
            }
            else if(this->board->get_cell_value(i,j) == 1){
                painter->setBrush(Qt::red);
                painter->drawEllipse(i*this->cell_size + border/2, j*this->cell_size + border/2,
                                     this->get_cell_size() - border, this->get_cell_size() - border);
            }
            else if(this->board->get_cell_value(i,j) == 2){
                painter->setBrush(Qt::blue);
                painter->drawEllipse(i*this->cell_size + border/2, j*this->cell_size + border/2,
                                     this->get_cell_size() - border, this->get_cell_size() - border);
            }
        }
    }
}

std::pair<int, int> Draw::get_coords(QPoint point)
{
    int x = point.rx();
    int y = point.ry();
    if (x % this->cell_size == 0){
        x /= this->cell_size -1;
    }
    else{
        x = (x - x % this->cell_size) / this->cell_size;
    }
    if (y % this->cell_size == 0){
        y /= this->cell_size - 1;
    }
    else{
        y = (y - y % this->cell_size) / this->cell_size;
    }
    return std::make_pair(x, y);
}

void Draw::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //painter.begin(this);
    this->setMaximumWidth(this->board_size);
    this->setMaximumHeight(this->board_size);
    this->init_board(&painter);
    this->draw_balls(&painter);
}

int Draw::get_dimension()
{
    return this->dimension;
}

int Draw::get_cell_size()
{
    return this->cell_size;
}

int Draw::get_board_size()
{
    return this->board_size;
}



void Draw::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        last_point = event->pos();
        isClicked = true;
        qDebug() << last_point;
        std::pair<int, int> coords = this->get_coords(last_point);
        if(this->board->get_cell_value(coords) == 0){
            //QVector<QVector<int>> board = this->board->get_board_matrix();
            this->board->set_cell_value(coords.first, coords.second, this->board->get_board_matrix());
            //this->board->set_board_matrix(board);
            QWidget::update();
        }

        //std::cout << "coords: "<< coords.first << " "<< coords.second<<std::endl;
    }
}

