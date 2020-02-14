#include "board.h"

Board::Board(int dimension) :  board_matrix(dimension, QVector<int>(dimension, 0))
{
     std::cout<<"board initialized"<<std::endl;
     printBoard();
}

void Board::printBoard()
{
    for(auto row : board_matrix)
    {
        for(auto col : row)
        {
            std::cout << col;
        }
        std::cout<<std::endl;
    }
}
int Board::getCellValue(int x, int y)
{
    return board_matrix[x][y];
}

int Board::getCellValue(std::pair<int, int> coords)
{
    return board_matrix[coords.first][coords.second];
}
void Board:: setCellValue(int x, int y)
{
    board_matrix[x][y] = rand()%2 +1;
}

void Board::setCellValue(std::pair<int, int> coords)
{
    board_matrix[coords.first][coords.second] = rand()%2 +1;
}

bool Board::checkWinScore(int first, int second, int &score)
{
    if(first == second && first != 0 && second != 0)
    {
        score++;
        if(score == WIN_SCORE)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

bool Board::checkHorizontal()
{
    int count_score;
    QVector<QVector<int>>::iterator row;
    QVector<int>::iterator col;
    QVector<int>::iterator prev;
    //print_board();
    for(row = board_matrix.begin(); row !=board_matrix.end(); row++)
    {
        count_score=START_SCORE;
        prev = row->begin();
        for(col = row->begin()+1; col!= row->end(); col++)
        {

            if(*prev == *col && *prev!=0 && *col!=0)
            {
                count_score++;
                if(count_score==WIN_SCORE)
                {
                    std::cout<<"Finish"<<std::endl;
                    return true;
                }
            }
            else
            {
                count_score = START_SCORE;
            }
            prev++;
        }
    }
    return false;
}

bool Board::checkVertical()
{
//    int count;
//    int col=0;
//    int prev=0;
//    for(int i=0; i<board_matrix.size();i++)
//    {
//        count = 1;
//        for(auto row : board_matrix)
//        {

//        }
//    }
    int count_score;
    int pos;
    QVector<QVector<int>>::iterator row;
    QVector<int>::iterator prev;
    QVector<int>::iterator sec;
    for(int col=0; col<board_matrix.size()-1;col++)
    {
        count_score = START_SCORE;
        pos=0;
        for(row = board_matrix.begin()+1; row !=board_matrix.end(); row++)
        {
            prev = (board_matrix.begin()+pos)->begin()+col;
            sec = row->begin()+col;
            if(*prev == *sec && *prev!=0 && *sec!=0)
            {
                count_score++;
                std::cout<<count_score<<std::endl;
                if(count_score==WIN_SCORE)
                {
                    std::cout<<"finish 2"<<std::endl;
                    return true;
                }
            }
            else
            {
                count_score=START_SCORE;
            }
            pos++;
        }

    }
    return false;
}
/*Check diagonal from top left to bottom right*/
bool Board::checkDiagonalBR()
{
    int col = 0;
    int pos;
    int count_score;
    QVector<QVector<int>>::iterator row;
    QVector<int>::iterator prev;
    QVector<int>::iterator sec;
    for(int i = board_matrix.size() - WIN_SCORE; i > 0; i--)
    {
        count_score = 1;
        pos=0;
        col=0;
        for(row = board_matrix.begin()+i+1; row !=board_matrix.end(); row++)
        {
            prev = (board_matrix.begin()+i+pos)->begin()+col;
            sec = row->begin()+col+1;
            if(*prev == *sec && *prev!=0 && *sec!=0)
            {
                count_score++;
                std::cout<<count_score<<std::endl;
                if(count_score==WIN_SCORE)
                {
                    std::cout<<"finish 3"<<std::endl;
                    return true;
                }
            }
            else
            {
                count_score=START_SCORE;
            }
            pos++;
            col++;
        }
        pos=0;
        col=0;
        for(row = board_matrix.begin(); row != board_matrix.end()-i; row++)
        {
            prev = (board_matrix.begin()+pos)->begin()+col;
            sec = row->begin()+col+1;
        }
    }

}
/*Check diagonal from top right to bottom left*/
bool Board::checkDiagonalBL()
{
    return true;
}
