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
    board_matrix[x][y] = 1;//rand()%2 +1;
}

void Board::setCellValue(std::pair<int, int> coords)
{
    board_matrix[coords.first][coords.second] = 1;//rand()%2 +1;
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
    }
    else
    {
            score = START_SCORE;
            return false;
    }
    return false;
}

bool Board::checkHorizontal()
{
    int count_score;
    QVector<QVector<int>>::iterator row;
    QVector<int>::iterator col;
    QVector<int>::iterator prev;
    for(row = board_matrix.begin(); row !=board_matrix.end(); row++)
    {
        count_score=START_SCORE;
        prev = row->begin();
        for(col = row->begin()+1; col!= row->end(); col++)
        {
            if(checkWinScore(*prev, *col, count_score))
            {
                std::cout<<"Finish"<<std::endl;
                return true;
            }
            prev++;
        }
    }
    return false;
}

bool Board::checkVertical()
{
    int count_score;
    int pos;
    QVector<QVector<int>>::iterator row;
    QVector<int>::iterator prev;
    QVector<int>::iterator sec;
    for(int col=0; col < board_matrix.size() - 1;col++)
    {
        count_score = START_SCORE;
        pos=0;
        for(row = board_matrix.begin()+1; row !=board_matrix.end(); row++)
        {
            prev = (board_matrix.begin()+pos)->begin()+col;
            sec = row->begin()+col;
            if(checkWinScore(*prev, *sec, count_score))
            {
                return true;
            }
            pos++;
        }

    }
    return false;
}
/*Check diagonal from top left to bottom right*/
bool Board::checkDiagonalBR()
{
    int col;
    int shift_col=0;
    int pos;
    int count_score;
    QVector<QVector<int>>::iterator row;
    QVector<int>::iterator prev;
    QVector<int>::iterator sec;
    for(int i = board_matrix.size() - WIN_SCORE; i >= 0; i--)
    {
        count_score = 1;
        pos = 0;
        col = 0;
        for(row = board_matrix.begin()+i+1; row !=board_matrix.end(); row++)
        {
            prev = (board_matrix.begin()+i+pos)->begin()+col;
            sec = row->begin()+col+1;
            if(checkWinScore(*prev, *sec, count_score))
            {
                return true;
            }
            pos++;
            col++;
        }
        count_score = 1;
        pos=0;
        col=0;
        for(row = board_matrix.begin() + 1; row != board_matrix.end() - shift_col; row++)
        {
            prev = (board_matrix.begin() + pos)->begin() + col + shift_col;
            sec = row->begin() + col + shift_col + 1;
            if(checkWinScore(*prev, *sec, count_score))
            {
                return true;
            }
            pos++;
            col++;
        }
        shift_col++;
    }

}
/*Check diagonal from top right to bottom left*/
bool Board::checkDiagonalBL()
{
    int col;
    int shift_col = 0;
    int pos;
    int count_score;
    QVector<QVector<int>>::iterator row;
    QVector<int>::reverse_iterator prev;
    QVector<int>::reverse_iterator sec;
    for(int i = board_matrix.size() - WIN_SCORE; i >= 0; i--)
    {
        count_score = 1;
        pos = 0;
        col = 0;
        for(row = board_matrix.begin()+i+1; row !=board_matrix.end(); row++)
        {
            prev = (board_matrix.begin()+i+pos)->rbegin() + col;
            sec = row->rbegin() + col + 1;
            if(checkWinScore(*prev, *sec, count_score))
            {
                return true;
            }
            pos++;
            col++;
        }
        count_score = 1;
        pos=0;
        col=0;
        for(row = board_matrix.begin() + 1; row != board_matrix.end() - shift_col; row++)
        {
            prev = (board_matrix.begin() + pos)->rbegin() + col + shift_col;
            sec = row->rbegin() + col + shift_col + 1;
            if(checkWinScore(*prev, *sec, count_score))
            {
                return true;
            }
            pos++;
            col++;
        }
        shift_col++;
    }

}
