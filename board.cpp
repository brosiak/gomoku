#include "board.h"

Board::Board(int dimension) :
    board_matrix(dimension, QVector<int>(dimension, 0)),
    isWinSeq(false)
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
void Board:: setCellValue(int x, int y, const int PLAYER)
{
    board_matrix[x][y] = PLAYER;//rand()%2 +1;
}

void Board::setCellValue(std::pair<int, int> coords, const int PLAYER)
{
    board_matrix[coords.first][coords.second] = PLAYER;//rand()%2 +1;
}

bool Board::checkWinScore(int first, int second, int &score)
{
    if(first == second && first != 0 && second != 0)
    {
        score++;
        if(score == WIN_SCORE)
        {
            isWinSeq = true;
            return true;
        }
        else if(score>WIN_SCORE)
        {
            score = START_SCORE;
            isWinSeq = false;
            return false;
        }
    }
    else if(isWinSeq==true)
    {
            return true;
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
                // if this col not last -> check if not more than 5 in line
                if(col+1 != row->end())
                {
                    if(checkWinScore(*col, *(col+1), count_score))
                    {
                        return true;
                    }
                    else
                    {
                        prev++;
                        continue;
                    }
                }
                else
                {
                    return true;
                }

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
    for(int col=0; col < board_matrix.size() ;col++)
    {
        count_score = START_SCORE;
        pos=0;
        for(row = board_matrix.begin() + 1; row != board_matrix.end(); row++)
        {
            prev = (board_matrix.begin()+pos)->begin()+col;
            sec = row->begin()+col;
            if(checkWinScore(*prev, *sec, count_score))
            {
                if(row + 1 != board_matrix.end())
                {
                    if(checkWinScore(*sec, *((row+1)->begin()+col), count_score))
                    {
                            return true;
                    }
                    else
                    {
                        pos++;
                        continue;
                    }
                }
                else
                {
                    return true;
                }

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
    //int compare_value = 0;
    for(int i = board_matrix.size() - WIN_SCORE; i >= 0; i--)
    {
        count_score = 1;
        pos = 0;
        col = 0;
        /*Check left-down part of matrix */
        for(row = board_matrix.begin() + i + INDEXING; row !=board_matrix.end(); row++)
        {
            prev = (board_matrix.begin() + i + pos)->begin() + col;
            sec = row->begin() + col + INDEXING;
            if(checkWinScore(*prev, *sec, count_score))
            {
                if(row + 1 != board_matrix.end())
                {
                    if((row + 1)->begin() + col + INDEXING + 1 != (row + 1)->end())
                    {
                        if (checkWinScore(*sec, *((row + 1)->begin() + col + INDEXING + 1), count_score))
                        {
                                return true;
                        }
                        else
                        {
                            pos++;
                            col++;
                            continue;
                        }
                    }
                    else
                    {
                        return true;
                    }
                }
                else
                {
                   return true;
                }

            }
            pos++;
            col++;
        }
        count_score = 1;
        pos=0;
        col=0;
        /*Check right-upper part of matrix */
        for(row = board_matrix.begin() + INDEXING; row != board_matrix.end() - shift_col; row++)
        {
            prev = (board_matrix.begin() + pos)->begin() + col + shift_col;
            sec = row->begin() + col + shift_col + INDEXING;
            if(checkWinScore(*prev, *sec, count_score))
            {
                if(row + 1 != board_matrix.end() - shift_col)
                {
                    if((row + 1)->begin() + col + shift_col + INDEXING + 1 != (row + 1)->end())
                    {
                        if (checkWinScore(*sec, *((row + 1)->begin() + col + shift_col + INDEXING + 1), count_score))
                        {
                                return true;
                        }
                        else
                        {
                            pos++;
                            col++;
                            continue;
                        }
                    }
                    else
                    {
                        return true;
                    }
                }
                else
                {
                   return true;
                }
            }
            pos++;
            col++;
        }
        shift_col++;
    }
    return false;
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
        /*Check right-down part of matrix */
        for(row = board_matrix.begin()+i+INDEXING; row !=board_matrix.end(); row++)
        {
            prev = (board_matrix.begin()+i+pos)->rbegin() + col;
            sec = row->rbegin() + col + INDEXING;
            if(checkWinScore(*prev, *sec, count_score))
            {
                if(row + 1 != board_matrix.end())
                {
                    if((row + 1)->rbegin() + col + INDEXING + 1 != (row + 1)->rend())
                    {
                        if (checkWinScore(*sec, *((row + 1)->rbegin() + col + INDEXING + 1), count_score))
                        {
                                return true;
                        }
                        else
                        {
                            pos++;
                            col++;
                            continue;
                        }
                    }
                    else
                    {
                        return true;
                    }
                }
                else
                {
                   return true;
                }

            }
            pos++;
            col++;
        }
        count_score = 1;
        pos=0;
        col=0;
        /*Check left-upper part of matrix */
        for(row = board_matrix.begin() + INDEXING; row != board_matrix.end() - shift_col; row++)
        {
            prev = (board_matrix.begin() + pos)->rbegin() + col + shift_col;
            sec = row->rbegin() + col + shift_col + INDEXING;
            if(checkWinScore(*prev, *sec, count_score))
            {
                if(row + 1 != board_matrix.end() - shift_col)
                {
                    if((row + 1)->rbegin() + col + shift_col + INDEXING + 1 != (row + 1)->rend())
                    {
                        if (checkWinScore(*sec, *((row + 1)->rbegin() + col + shift_col + INDEXING + 1), count_score))
                        {
                                return true;
                        }
                        else
                        {
                            pos++;
                            col++;
                            continue;
                        }
                    }
                    else
                    {
                        return true;
                    }
                }
                else
                {
                   return true;
                }
            }
            pos++;
            col++;
        }
        shift_col++;
    }
    return false;
}

bool Board::checkWin()
{
    if(checkHorizontal() || checkVertical() || checkDiagonalBL() || checkDiagonalBR())
    {
        return true;
    }
    else
    {
        return false;
    }
}
