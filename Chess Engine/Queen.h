#pragma once

class Queen: public Piece {
public:
    std::list<Move> getMoves(Piece*** board, int x, int y) override;
    ~Queen(){}
    Queen(Color c, int x, int y) {
        name = "  Queen";
        color = c;
        lives = 1;
        this->x = x;
        this->y = y;
    }
};

std::list<Move> Queen::getMoves(Piece*** board, int x, int y) {
    std::list<Move> moves;
    Move move;
    int i, j;
    for(int j = y + 1; j < 8; j++) {
        if(board[x][j] == nullptr) {
            move.x = x;
            move.y = j;
            moves.push_front(move);
        }
        else if(board[x][y]->color == board[x][j]->color) {
            break;
        }
        else {
            move.x = x;
            move.y = j;
            moves.push_front(move);
            break;
        }
    }
    for(int j = y - 1; j >= 0; j--) {
        if(board[x][j] == nullptr) {
            move.x = x;
            move.y = j;
            moves.push_front(move);
        }
        else if(board[x][y]->color == board[x][j]->color) {
            break;
        }
        else {
            move.x = x;
            move.y = j;
            moves.push_front(move);
            break;
        }
    }
    for(i = x + 1; i < 8; i++) {
        if(board[i][y] == nullptr) {
            move.x = i;
            move.y = y;
            moves.push_front(move);
        }
        else if(board[x][y]->color == board[i][y]->color) {
            break;
        }
        else {
            move.x = i;
            move.y = y;
            moves.push_front(move);
            break;
        }
    }
    for(i = x - 1; i >= 0; i--) {
        if(board[i][y] == nullptr) {
            move.x = i;
            move.y = y;
            moves.push_front(move);
        }
        else if(board[x][y]->color == board[i][y]->color) {
            break;
        }
        else {
            move.x = i;
            move.y = y;
            moves.push_front(move);
            break;
        }
    }
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
