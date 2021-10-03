#pragma once

struct Move {
	int x;
	int y;
};

enum Color { black, white };

class Piece {
public:
	std::string name;
	Color color;
	int lives;
	virtual ~Piece(){};
	virtual std::list<Move> getMoves(Piece*** board, int x, int y){std::list<Move> moves; return moves;};
	int x;
	int y;
	bool hasMoved = false;
};

void movePiece(Piece*** board, Move initial, Move final) {
	if (board[initial.x][initial.y] != nullptr) {
		board[initial.x][initial.y]->hasMoved = true;
		board[final.x][final.y] = board[initial.x][initial.y];
		board[initial.x][initial.y] = nullptr;
	}
}