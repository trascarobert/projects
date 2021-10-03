#pragma once

class Bishop: public Piece {
public:
    std::list<Move> getMoves(Piece*** board, int x, int y) override;
    ~Bishop(){}
    Bishop(Color c, int x, int y) 
    {
        name = "Bishop";
        color = c;
        lives = 1;
        this->x = x;
        this->y = y;
    }
};

std::list<Move> Bishop::getMoves(Piece*** board, int x, int y) {
    std::list<Move> moves;
    Move move;
    int i, j;
    for(i = x + 1; i < 8; i++) {
        j = y + i - x;
        if(j > 7) {
            break;
        }
        if(board[i][j] == nullptr) {
            move.x = i;
            move.y = j;
            moves.push_front(move);
        }
        else if(board[x][y]->color == board[i][j]->color) {
            break;
        }
        else {
            move.x = i;
            move.y = j;
            moves.push_front(move);
            break;
        }
    }
    for(i = x - 1; i >= 0; i--) {
        j = y + i - x;
        if(j < 0) {
            break;
        }
        if(board[i][j] == nullptr) {
            move.x = i;
            move.y = j;
            moves.push_front(move);
        }
        else if(board[x][y]->color == board[i][j]->color) {
            break;
        }
        else {
            move.x = i;
            move.y = j;
            moves.push_front(move);
            break;
        }
    }
    for(i = x + 1; i < 8; i++) {
        j = y + x - i;
        if(j < 0) {
            break;
        }
        if(board[i][j] == nullptr) {
            move.x = i;
            move.y = j;
            moves.push_front(move);
        }
        else if(board[x][y]->color == board[i][j]->color) {
            break;
        }
        else {
            move.x = i;
            move.y = j;
            moves.push_front(move);
            break;
        }
    }
    for(i = x - 1; i >= 0; i--) {
        j = y + x - i;
        if(j > 7) {
            break;
        }
        if(board[i][j] == nullptr) {
            move.x = i;
            move.y = j;
            moves.push_front(move);
        }
        else if(board[x][y]->color == board[i][j]->color) {
            break;
        }
        else {
            move.x = i;
            move.y = j;
            moves.push_front(move);
            break;
        }
    }
    return moves; 
}
