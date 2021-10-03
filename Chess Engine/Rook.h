#pragma once

class Rook: public Piece {
public:
    std::list<Move> getMoves(Piece*** board, int x, int y) override;
    ~Rook(){}
    Rook(Color c, int x, int y) {
        name = "   Rook";
        color = c;
        lives = 1;
        this->x = x;
        this->y = y;
    }
};

std::list<Move> Rook::getMoves(Piece*** board, int x, int y)
{
    std::list<Move> moves;
    Move move;
    for(int i = y + 1; i < 8; i++)
    {
        if(board[x][i] == nullptr)
        {
            move.x = x;
            move.y = i;
            moves.push_front(move);
        }
        else if(board[x][y]->color == board[x][i]->color)
        {
            break;
        }
        else
        {
            move.x = x;
            move.y = i;
            moves.push_front(move);
            break;
        }
    }
    for(int i = y - 1; i >= 0; i--)
    {
        if(board[x][i] == nullptr)
        {
            move.x = x;
            move.y = i;
            moves.push_front(move);
        }
        else if(board[x][y]->color == board[x][i]->color)
        {
            break;
        }
        else
        {
            move.x = x;
            move.y = i;
            moves.push_front(move);
            break;
        }
    }
    for(int i = x + 1; i < 8; i++)
    {
        if(board[i][y] == nullptr)
        {
            move.x = i;
            move.y = y;
            moves.push_front(move);
        }
        else if(board[x][y]->color == board[i][y]->color)
        {
            break;
        }
        else
        {
            move.x = i;
            move.y = y;
            moves.push_front(move);
            break;
        }
    }
    for(int i = x - 1; i >= 0; i--)
    {
        if(board[i][y] == nullptr)
        {
            move.x = i;
            move.y = y;
            moves.push_front(move);
        }
        else if(board[x][y]->color == board[i][y]->color)
        {
            break;
        }
        else
        {
            move.x = i;
            move.y = y;
            moves.push_front(move);
            break;
        }
    }
    return moves; 
}
