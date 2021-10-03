#pragma once


void freeBoard(Piece*** board) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if(board[i][j] != nullptr) {
                delete board[i][j];
            }
        }
        delete[] board[i];
    }
    delete[] board;
}

Piece*** newBoard() {
    Piece*** board;
    board = new Piece**[8];
    for (int i = 0; i < 8; i++) {
        board[i] = new Piece*[8];
    }

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            board[i][j] = nullptr;
        }
    }

    for(int i = 0 ; i < 8 ; i++) {
        board[i][1] = new Pawn(Color::white, i, 1);
        board[i][6] = new Pawn(Color::black, i, 6);
    }
    
    board[3][0] = new Queen(Color::white, 3, 0);
    board[3][7] = new Queen(Color::black, 3, 7);
    board[2][0] = new Bishop(Color::white, 2, 0);
    board[5][0] = new Bishop(Color::white, 5, 0);
    board[2][7] = new Bishop(Color::black, 2, 7);
    board[5][7] = new Bishop(Color::black, 5, 7);
    board[4][0] = new King(Color::white, 4, 0);
    board[4][7] = new King(Color::black, 4, 7);
    board[0][0] = new Rook(Color::white, 0, 0);
    board[7][0] = new Rook(Color::white, 7, 0);
    board[0][7] = new Rook(Color::black, 0, 7);
    board[7][7] = new Rook(Color::black, 7, 7);
    board[1][0] = new Knight(Color::white, 1, 0);
    board[6][0] = new Knight(Color::white, 6 ,0);
    board[1][7] = new Knight(Color::black, 1, 7);
    board[6][7] = new Knight(Color::black, 6, 7);

    return board;
}
