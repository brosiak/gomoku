#include "board.h"

Board::Board(int dimension)
{
     QVector<QVector<int>> board_matrix(dimension, QVector<int>(dimension, 0));
     this->board_matrix = board_matrix;
     std::cout<<"Vector initialized"<<std::endl;
     print_board();
}

void Board::print_board()
{
    for(int i=0; i<board_matrix.size();i++)
    {
        for(int j=0; j<board_matrix[i].size(); j++)
        {
            std::cout << board_matrix[i][j];
        }
        std::cout<<std::endl;
    }
}
int Board::get_cell_value(int x, int y)
{
    return board_matrix[x][y];
}

int Board::get_cell_value(std::pair<int, int> coords)
{
    return board_matrix[coords.first][coords.second];
}
void Board:: set_cell_value(int x, int y)
{
    board_matrix[x][y] = rand()%2 +1;
}

void Board::set_cell_value(std::pair<int, int> coords)
{
    board_matrix[coords.first][coords.second] = rand()%2 +1;
}


bool Board::check_horizontal()
{
    int count;
    //int prev=0;
    QVector<QVector<int>>::iterator row;
    QVector<int>::iterator col;
    QVector<int>::iterator prev;
    print_board();
    for(row = board_matrix.begin(); row !=board_matrix.end(); row++)
    {
        count=1;
        prev = row->begin();
        for(col = row->begin()+1; col!= row->end(); col++)
        {

            if(*prev == *col && *prev!=0 && *col!=0)
            {
                count++;
                if(count==5)
                {
                    std::cout<<"Finish"<<std::endl;
                    return true;
                }
            }
            else
            {
                count = 1;
            }
            prev++;
            //prev=*col;
        }
    }
}

//bool Board::check_vertical()
//{
//    int count;
//    //int prev=0;
//    QVector<QVector<int>>::iterator row;
//    QVector<int>::iterator col;
//    QVector<int>::iterator prev;
//    for(col = board_matrix.begin()->begin(); col!= board_matrix.end()->end();col++)
//    {
//        for(row = board_matrix.begin()+1; row !=board_matrix.end(); row++)
//        {
//           prev = board_matrix.begin()
//        }
//    }
//}
