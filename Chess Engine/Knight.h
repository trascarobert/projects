#pragma once

class Knight: public Piece {
public:
    std::list<Move> getMoves(Piece*** board, int x, int y) override;
    ~Knight(){}
    Knight(Color c, int x, int y) {
        name = " Knight";
        color = c;
        lives = 1;
        this->x = x;
        this->y = y;
    }
};

std::list<Move> Knight::getMoves(Piece*** board, int x, int y) {
    std::list <Move> moves;
    Move move;
    if(y + 2 < 8) {
        if(x + 1 < 8 && (board[x+1][y+2] == nullptr || board[x][y]->color != board[x+1][y+2]->color)) {
            move.x = x + 1;
            move.y = y + 2;
            moves.push_front(move);
        }
        if(x - 1 >= 0 && (board[x-1][y+2] == nullptr || board[x][y]->color != board[x-1][y+2]->color)) {
            move.x = x - 1;
            move.y = y + 2;
            moves.push_front(move);
        }
    }
    if(y + 1 < 8) {
        if(x - 2 >= 0 && (board[x-2][y+1] == nullptr || board[x][y]->color != board[x-2][y+1]->color)) {
            move.x = x - 2;
            move.y = y + 1;
            moves.push_front(move);
        }
        if(x + 2 < 8 && (board[x+2][y+1] == nullptr || board[x][y]->color != board[x+2][y+1]->color)) {
            move.x = x + 2;
            move.y = y + 1;
            moves.push_front(move);
        }
    }
    if(y - 1 >= 0) {
        if(x + 2 < 8 && (board[x+2][y-1] == nullptr || board[x][y]->color != board[x+2][y-1]->color)) {
            move.x = x + 2;
            move.y = y - 1;
            moves.push_front(move);
        }
        if(x - 2 >= 0 && (board[x-2][y-1] == nullptr || board[x][y]->color != board[x-2][y-1]->color)) {
            move.x = x - 2;
            move.y = y - 1;
            moves.push_front(move);
        }
    }
    if(y - 2 >= 0) {
        if(x + 1 < 8 && (board[x+1][y-2] == nullptr || board[x][y]->color != board[x+1][y-2]->color)) {
            move.x = x + 1;
            move.y = y - 2;
            moves.push_front(move);
        }
        if(x - 1 >= 0 && (board[x-1][y-2] == nullptr || board[x][y]->color != board[x-1][y-2]->color)) {
            move.x = x - 1;
            move.y = y - 2;
            moves.push_front(move);
        }
    }
    return moves;
}