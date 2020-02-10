#include "board.h"
#include "draw.h"

Board::Board(int dimension)
{
     QVector<QVector<int>> board_matrix(dimension, QVector<int>(dimension, 0));
     this->board_matrix = board_matrix;
     std::cout<<"Vector initialized"<<std::endl;
     this->print_board();
}

void Board::print_board()
{
    for(int i=0; i<this->board_matrix.size();i++)
    {
        for(int j=0; j<board_matrix[i].size(); j++)
        {
            std::cout << board_matrix[i][j];
        }
        std::cout<<std::endl;
    }
}
int const &Board::get_cell_value(int x, int y)
{
    return this->board_matrix[x][y];
}

int const &Board::get_cell_value(std::pair<int, int> coords)
{
    std::cout<<this->board_matrix[coords.first][coords.second]<<std::endl;
    return this->board_matrix[coords.first][coords.second];
}
void Board:: set_cell_value(int x, int y, QVector<QVector<int>> &board_matrix)
{
    board_matrix[x][y] = rand()%2 +1;
}

void Board::set_cell_value(std::pair<int, int> coords)
{
    this->board_matrix[coords.first][coords.second] = rand()%2 +1;
}

QVector<QVector<int> > &Board::get_board_matrix()
{
    return this->board_matrix;
}
void Board::set_board_matrix(QVector<QVector<int>> &board_matrix)
{
    this->board_matrix = board_matrix;
}
