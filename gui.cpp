#include "gui.h"
#include <QMouseEvent>
#include <QDebug>
#include <utility>
Gui::Gui(QWidget *parent)
    : QMainWindow(parent), board(new Board (dimension))
{
}

Gui::~Gui()
{
}

void Gui::init_board(QPainter *painter)
{
    painter->setWindow(0, 0, board_size_px, board_size_px);
    for(int i=0; i<dimension;i++)
    {
        for(int j=0; j<dimension;j++)
        {
            painter->drawRect(i*cell_size_px, j*cell_size_px, cell_size_px, cell_size_px);
        }
    }
}

void Gui::draw_balls(QPainter *painter)
{
    for(int i=0; i<dimension; i++)
    {
        for(int j=0; j<dimension;j++)
        {
            if (board->get_cell_value(i,j) == 0)
            {
                continue;
            }
            else if(board->get_cell_value(i,j) == 1)
            {
                painter->setBrush(Qt::red);
                painter->drawEllipse(j*cell_size_px + border/2, i*cell_size_px + border/2,
                                     cell_size_px - border, cell_size_px - border);
            }
            else if(board->get_cell_value(i,j) == 2)
            {
                painter->setBrush(Qt::blue);
                painter->drawEllipse(j*cell_size_px + border/2, i*cell_size_px + border/2,
                                     cell_size_px - border, cell_size_px - border);
            }
        }
    }
}

std::pair<int, int> Gui::get_coords(QPoint point)
{
    int x = point.rx();
    int y = point.ry();
    if (x % cell_size_px == 0)
    {
        x /= cell_size_px -1;
    }
    else
    {
        x = (x - x % cell_size_px) / cell_size_px;
    }
    if (y % cell_size_px == 0)
    {
        y /= cell_size_px - 1;
    }
    else
    {
        y = (y - y % cell_size_px) / cell_size_px;
    }
    std::cout<<x<<" "<<y<<std::endl;
    return std::make_pair(y, x);
}

void Gui::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    setMaximumWidth(board_size_px);
    setMaximumHeight(board_size_px);
    init_board(&painter);
    draw_balls(&painter);
}


void Gui::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        last_point = event->pos();
        is_clicked = true;
        //qDebug() << last_point;
        std::pair<int, int> coords = get_coords(last_point);
        if(board->get_cell_value(coords) == 0)
        {
            board->set_cell_value(coords);
            QWidget::update();
            board->check_vertical();
        }

        //std::cout << "coords: "<< coords.first << " "<< coords.second<<std::endl;
    }
}

