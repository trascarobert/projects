#pragma once

class Pawn: public Piece {
public:
    std::list<Move> getMoves(Piece*** board, int x, int y) override;
    ~Pawn(){}
    Pawn(Color c, int x, int y) {
        name = "   Pawn";
        color = c;
        lives = 1;
        this->x = x;
        this->y = y;
    }
};

std::list<Move> Pawn::getMoves(Piece*** board, int x, int y) {
    std::list <Move> moves;
    Move move;
    int verify = 0;
    if(board[x][y]->color == Color::white) {
        if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
            if (y == 1) {
                if (board[x][y + 1] == nullptr) {
                    move.x = x;
                    move.y = y + 1;
                    moves.push_front(move);
                }
                if(board[x][y + 2] == nullptr && board[x][y + 1] == nullptr) {
                    move.x = x;
                    move.y = y + 2;
                    moves.push_front(move);
                }
                verify = x + 1;
                if(verify <= 7) {
                    if (board[x + 1][y + 1] != nullptr && board[x + 1][y + 1]->color != board[x][y]->color){
                        move.x = x + 1;
                        move.y = y + 1;
                        moves.push_front(move);
                    }
                }
                verify = x - 1;
                if(verify >= 0) {
                    if (board[x - 1][y + 1] != nullptr && board[x - 1][y + 1]->color != board[x][y]->color) {
                        move.x = x - 1;
                        move.y = y + 1;
                        moves.push_front(move);
                    }
                }
            }else {
                if (y + 1 <= 7) {
                    if (board[x][y + 1] == nullptr) {
                        move.x = x;
                        move.y = y + 1;
                        moves.push_front(move);
                    }
                }
                
                verify = x + 1;
                if(verify <= 7 && y + 1 <= 7) {
                    if (board[x + 1][y + 1] != nullptr && board[x + 1][y + 1]->color != board[x][y]->color) {
                        move.x = x + 1;
                        move.y = y + 1;
                        moves.push_front(move);
                    }
                }
                verify = x - 1;
                if(verify >= 0 && y + 1 <= 7) {
                    if (board[x - 1][y + 1] != nullptr && board[x - 1][y + 1]->color != board[x][y]->color) {
                        move.x = x - 1;
                        move.y = y + 1;
                        moves.push_front(move);
                    }
                }
            }
        }
    }else {
        if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
            if (y == 6) {
                if (board[x][y - 1] == nullptr) {
                    move.x = x;
                    move.y = y - 1;
                    moves.push_front(move);
                }
                if (board[x][y - 2] == nullptr && board[x][y - 1] == nullptr) {
                    move.x = x;
                    move.y = y - 2;
                    moves.push_front(move);
                }
                verify = x + 1;
                if (verify <= 7) {
                    if (board[x + 1][y - 1] != nullptr && board[x + 1][y - 1]->color != board[x][y]->color) {
                        move.x = x + 1;
                        move.y = y - 1;
                        moves.push_front(move);
                    }
                }
                verify = x - 1;
                if (verify >= 0) {
                    if (board[x - 1][y - 1] != nullptr && board[x - 1][y - 1]->color != board[x][y]->color) {
                        move.x = x - 1;
                        move.y = y - 1;
                        moves.push_front(move);
                    }
                }
            } else {
                verify = y - 1;
                if (verify >= 0) {
                    if (board[x][y - 1] == nullptr) {
                        move.x = x;
                        move.y = y - 1;
                        moves.push_front(move);
                    }
                }
                
                verify = x + 1;
                if (verify <= 7 && y - 1 >= 0) {
                    if (board[x + 1][y - 1] != nullptr && board[x + 1][y - 1]->color != board[x][y]->color) {
                        move.x = x + 1;
                        move.y = y - 1;
                        moves.push_front(move);
                    }
                }
                verify = x - 1;
                if (verify >= 0 && y - 1 >= 0) {
                    if (board[x - 1][y - 1] != nullptr  && board[x - 1][y - 1]->color != board[x][y]->color) {
                        move.x = x - 1;
                        move.y = y - 1;
                        moves.push_front(move);
                    }
                }
            }
        }
    }
    return moves;
}

