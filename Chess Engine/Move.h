#include <fstream>

#pragma once
Move* newMove(int x, int y)
{
	Move* move = new Move;
	move->x = x;
	move->y = y;
	return move;
}

std::string moveToString(Move initial, Move final) {
	std::string move = "move ";
	move.push_back(static_cast<char>(initial.x + 97));
	move.push_back(static_cast<char>(initial.y + 49));
	move.push_back(static_cast<char>(final.x + 97));
	move.push_back(static_cast<char>(final.y + 49));
	return move;
}

void stringToMove(Piece*** board, std::string move) {
	Move initial, final;
	char c;
	c = move.back();
	final.y = static_cast<int>(c - 49);
	move.pop_back();
	c = move.back();
	final.x = static_cast<int>(c - 97);
	move.pop_back();
	c = move.back();
	initial.y = static_cast<int>(c - 49);
	move.pop_back();
	c = move.back();
	initial.x = static_cast<int>(c - 97);
	move.pop_back();
	movePiece(board, initial, final);
}

std::deque<std::pair<Move, Move>> getMoves(Piece*** board, bool playingWhite , std::pair<bool,std::pair<int,int>> enPassant) {
	std::deque<std::pair<Move, Move>> moves;
	Color playingColor = playingWhite ? Color::white : Color::black;

	

	bool longCastle = true;
	bool shortCastle = true;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] != nullptr && board[i][j]->color == playingColor) {
				
				
				auto aux = board[i][j]->getMoves(board, i, j);
				for (auto it : aux) {
					if (board[it.x][it.y] != nullptr) {
						moves.push_back(std::make_pair(*newMove(i, j), it));
					}
					else {
						moves.push_front(std::make_pair(*newMove(i, j), it));
					}
				}

				if (board[i][j]->name.find("King") != std::string::npos) {
					if (board[i][j]->hasMoved) {
						longCastle = false;
						shortCastle = false;
					}
				}

                if(playingColor == Color::white) {
                    if (board[i][j]->name.find("Pawn") != std::string::npos && enPassant.first && enPassant.second.second == j) {
                        if (i - 1 >= 0 && enPassant.second.first == i - 1) {
                            if (board[i - 1][j] != nullptr && board[i][j]->color != board[i - 1][j]->color) {
                                if (board[i - 1][j + 1] == nullptr) {
                                    moves.push_back(std::make_pair(*newMove(i, j), *newMove(i - 1, j + 1)));
                                }
                            }
                        }
                        if (i + 1 <= 7 && enPassant.second.first == i + 1) {
                            if (board[i + 1][j] != nullptr && board[i][j]->color != board[i + 1][j]->color) {
                                if (board[i + 1][j + 1] == nullptr) {
                                    moves.push_back(std::make_pair(*newMove(i, j), *newMove(i + 1, j + 1)));
                                }
                            }
                        }
                    }
                }
                else {
                    if (board[i][j]->name.find("Pawn") != std::string::npos && enPassant.first &&  enPassant.second.second == j) {
                        if (i - 1 >= 0 && enPassant.second.first == i - 1) {
                            if (board[i - 1][j] != nullptr && board[i-1][j]->color != board[i][j]->color) {
                                if (board[i - 1][j - 1] == nullptr) {
                                    moves.push_back(std::make_pair(*newMove(i, j), *newMove(i - 1, j - 1)));
                                }
                            }
                        }
                        if (i + 1 <= 7 && enPassant.second.first == i + 1) {
                            if (board[i + 1][j] != nullptr && board[i][j]->color != board[i + 1][j]->color) {
                                if (board[i + 1][j - 1] == nullptr) {
                                    moves.push_back(std::make_pair(*newMove(i, j), *newMove(i + 1, j - 1)));
                                }
                            }
                        }
                    }
                }
			}
		}
	}

	if (playingWhite) {
		if (board[0][0] == nullptr) {
			longCastle = false;
		}
		if (board[7][0] == nullptr) {
			shortCastle = false;
		}
	}
	else {
		if (board[0][7] == nullptr) {
			longCastle = false;
		}
		if (board[7][7] == nullptr) {
			shortCastle = false;
		}
	}

	if (longCastle) {
	
		if (playingWhite) {
			if (board[1][0] != nullptr ||
				board[2][0] != nullptr || 
				board[3][0] != nullptr) {
					longCastle = false;	
				}
		}
	
		else {
			if (board[1][7] != nullptr ||
				board[2][7] != nullptr || 
				board[3][7] != nullptr) {
					longCastle = false;	
				}
		}
	}
	if (shortCastle) {
		if (playingWhite) {
			if (board[6][0] != nullptr || 
				board[5][0] != nullptr) {
					shortCastle = false;	
				}
		}
		else {
			if (board[6][7] != nullptr || 
				board[5][7] != nullptr) {
					shortCastle = false;	
			}
		}
	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] != nullptr && board[i][j]->color != playingColor) {
				
				auto aux = board[i][j]->getMoves(board, i, j);
				for (auto it : aux) {
					if (playingWhite) {
						if (it.y == 0) {
							if (it.x == 2 || it.x == 3 || it.x == 4) {
								longCastle = false;
							}
							if (it.x == 4 || it.x == 5 || it.x == 6) {
								shortCastle = false;
							}
						}
					}
					else {
						if (it.y == 7) {
							if (it.x == 2 || it.x == 3 || it.x == 4) {
								longCastle = false;
							}
							if (it.x == 4 || it.x == 5 || it.x == 6) {
								shortCastle = false;
							}
						}
					}
				}
			}
		}
	}
	

	if (playingWhite) {
		if (longCastle) {
			if (board[0][0] != nullptr) {
				if (board[0][0]->name.find("Rook") != std::string::npos) {
					if (!board[0][0]->hasMoved) {
						moves.push_back(std::make_pair(*newMove(4, 0), *newMove(2, 0)));
					}
				}
			}
		}
		if (shortCastle) {
			if (board[7][0] != nullptr) {
				if (board[7][0]->name.find("Rook") != std::string::npos) {
					if (!board[7][0]->hasMoved) {
						moves.push_back(std::make_pair(*newMove(4, 0), *newMove(6, 0)));
					}
				}
			}
		}
	}
	else {
		if (longCastle) {
			if (board[0][7] != nullptr) {
				if (board[0][7]->name.find("Rook") != std::string::npos) {
					if (!board[0][7]->hasMoved) {
						moves.push_back(std::make_pair(*newMove(4, 7), *newMove(2, 7)));
					}
				}
			}
		}
		if (shortCastle) {
			if (board[7][7] != nullptr) {
				if (board[7][7]->name.find("Rook") != std::string::npos) {
					if (!board[7][7]->hasMoved) {
						moves.push_back(std::make_pair(*newMove(4, 7), *newMove(6, 7)));
					}
				}
			}
		}
	}

	return moves;
}

Move getKingPosition(Piece*** board, bool playingWhite) {
	Color playingColor = playingWhite ? Color::white : Color::black;
	Move kingPosition;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] != nullptr && 
				board[i][j]->color == playingColor && 
				board[i][j]->name.find("King") != std::string::npos) {
					kingPosition.x = i;
					kingPosition.y = j;
					return kingPosition;
			}
		}
	}
	kingPosition.x = -1;
	kingPosition.y = -1;
	return kingPosition;
}
