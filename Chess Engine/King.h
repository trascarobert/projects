#pragma once



class King: public Piece {
public:
    std::list<Move> getMoves(Piece*** board, int x, int y) override;
    ~King(){}
    King(Color c, int x, int y) {
        name = "   King";
        color = c;
        lives = 3;
        this->x = x;
        this->y = y;
    }
};

std::list<Move> King::getMoves(Piece*** board, int x, int y) {
    std::list<Move> moves;
    Move move;
    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            if (i >= 0 && j >= 0 && i <= 7 && j <= 7) {
                if (board[i][j] == nullptr || (board[i][j]->color != board[x][y]->color &&
                								board[i][j]->name.find("King") == std::string::npos)) {
                    move.x = i;
                    move.y = j;
                    moves.push_front(move);
                }
            }
        }
    }
    return moves; 
}

bool inCheck(Piece*** board, Move kingPosition, bool playingWhite) {
	if (false) {
		std::ofstream out("tablaFake.out");
		for (int j = 0; j < 8; j++) {
	        for (int i = 0; i < 8; i++) {
	            if (board[i][j] != nullptr) {
	                if (board[i][j]->color == Color::white)
	                out << board[i][j]->name << "a";
	                else
	                out << board[i][j]->name << "n";
	            }
	            else {
	                out << "   NULL";
	            }
	        }
	        out << std::endl;
	    }
		out.close();
	}

	Color playingColor = playingWhite ? Color::white : Color::black;
	int i;
	int j;

	for (i = kingPosition.x - 1, j = kingPosition.y;
		 i >= 0;
		 i--) {
		if (board[i][j] != nullptr) {
			if (board[i][j]->color != playingColor) { 
				if (board[i][j]->name.find("Queen") != std::string::npos ||
					board[i][j]->name.find("Rook") != std::string::npos) {
					return true;
				}
				else { 
					break;
				}
			}
			else { 
				break;
			}
		}
	}

	for (i = kingPosition.x + 1, j = kingPosition.y;
		 i < 8;
		 i++) {
		if (board[i][j] != nullptr) {
			if (board[i][j]->color != playingColor) {
				if (board[i][j]->name.find("Queen") != std::string::npos ||
					board[i][j]->name.find("Rook") != std::string::npos) {
					return true;
				}
				else { 
					break;
				}
			}
			else { 
				break;
			}
		}
	}

	for (i = kingPosition.x, j = kingPosition.y + 1;
		 j < 8;
		 j++) {
		if (board[i][j] != nullptr) {
			if (board[i][j]->color != playingColor) { 
				if (board[i][j]->name.find("Queen") != std::string::npos ||
					board[i][j]->name.find("Rook") != std::string::npos) {
					return true;
				}
				else {
					break;
				}
			}
			else { 
				break;
			}
		}
	}

	
	for (i = kingPosition.x, j = kingPosition.y - 1;
		 j >= 0;
		 j--) {
		if (board[i][j] != nullptr) {
			if (board[i][j]->color != playingColor) { 
				if (board[i][j]->name.find("Queen") != std::string::npos ||
					board[i][j]->name.find("Rook") != std::string::npos) {
					return true;
				}
				else { 
					break;
				}
			}
			else { 
				break;
			}
		}
	}

	for (i = kingPosition.x - 1, j = kingPosition.y + 1;
		 i >= 0 && j < 8;
		 i--, j++) {
			if (board[i][j] != nullptr) {
				if (board[i][j]->color != playingColor) { 
					if (board[i][j]->name.find("Queen") != std::string::npos ||
						board[i][j]->name.find("Bishop") != std::string::npos) {
						return true;
					}
					else { 
						break;
					}
				}
				else { 
					break;
				}
			}
	}

	for (i = kingPosition.x - 1, j = kingPosition.y - 1;
		 i >= 0 && j >= 0;
		 i--, j--) {
			if (board[i][j] != nullptr) {
				if (board[i][j]->color != playingColor) { 
					if (board[i][j]->name.find("Queen") != std::string::npos ||
						board[i][j]->name.find("Bishop") != std::string::npos) {
						return true;
					}
					else { 
						break;
					}
				}
				else { 
					break;
				}
		}
	}
	
	for (i = kingPosition.x + 1, j = kingPosition.y - 1;
		 i < 8 && j >= 0;
		 i++, j--) {
			if (board[i][j] != nullptr) {
				if (board[i][j]->color != playingColor) {
					if (board[i][j]->name.find("Queen") != std::string::npos ||
						board[i][j]->name.find("Bishop") != std::string::npos) {
						return true;
					}
					else { 
						break;
					}
				}
				else { 
					break;
				}
		}
	}

	for (i = kingPosition.x + 1, j = kingPosition.y + 1;
		 i < 8 && j < 8;
		 i++, j++) {
			if (board[i][j] != nullptr) {
				if (board[i][j]->color != playingColor) { 
					if (board[i][j]->name.find("Queen") != std::string::npos ||
						board[i][j]->name.find("Bishop") != std::string::npos) {
						return true;
					}
					else { 
						break;
					}
				}
				else { 
					break;
				}
		}
	}

	if (playingColor == Color::black) { 
		i = kingPosition.x - 1;
		j = kingPosition.y - 1;
		if (i >= 0 && j >= 0) {
			if (board[i][j] != nullptr) {
				if (board[i][j]->name.find("Pawn") != std::string::npos) {
					if (board[i][j]->color != playingColor) {
						return true;
					}
				}
			}
		}
		i = kingPosition.x + 1;
		j = kingPosition.y - 1;
		if (i < 8 && j >= 0) {
			if (board[i][j] != nullptr) {
				if (board[i][j]->name.find("Pawn") != std::string::npos) {
					if (board[i][j]->color != playingColor) {
						return true;
					}
				}
			}
		}
	}
	else { 
		i = kingPosition.x - 1;
		j = kingPosition.y + 1;
		if (i >= 0 && j < 8) {
			if (board[i][j] != nullptr) {
				if (board[i][j]->name.find("Pawn") != std::string::npos) {
					if (board[i][j]->color != playingColor) {
						return true;
					}
				}
			}
		}
		i = kingPosition.x + 1;
		j = kingPosition.y + 1;
		if (i < 8 && j < 8) {
			if (board[i][j] != nullptr) {
				if (board[i][j]->name.find("Pawn") != std::string::npos) {
					if (board[i][j]->color != playingColor) {
						return true;
					}
				}
			}
		}
	}

	i = kingPosition.x - 1;
	j = kingPosition.y - 2;
	if (i >= 0 && j >= 0) {
		if (board[i][j] != nullptr) {
			if (board[i][j]->name.find("Knight") != std::string::npos) {
				if (board[i][j]->color != playingColor) {
					return true;
				}
			}
		}
	}

	i = kingPosition.x - 2;
	j = kingPosition.y - 1;
	if (i >= 0 && j >= 0) {
		if (board[i][j] != nullptr) {
			if (board[i][j]->name.find("Knight") != std::string::npos) {
				if (board[i][j]->color != playingColor) {
					return true;
				}
			}
		}
	}

	i = kingPosition.x + 1;
	j = kingPosition.y - 2;
	if (i < 8 && j >= 0) {
		if (board[i][j] != nullptr) {
			if (board[i][j]->name.find("Knight") != std::string::npos) {
				if (board[i][j]->color != playingColor) {
					return true;
				}
			}
		}
	}
	i = kingPosition.x + 2;
	j = kingPosition.y - 1;
	if (i < 8 && j >= 0) {
		if (board[i][j] != nullptr) {
			if (board[i][j]->name.find("Knight") != std::string::npos) {
				if (board[i][j]->color != playingColor) {
					return true;
				}
			}
		}
	}

	i = kingPosition.x + 2;
	j = kingPosition.y + 1;
	if (i < 8 && j < 8) {
		if (board[i][j] != nullptr) {
			if (board[i][j]->name.find("Knight") != std::string::npos) {
				if (board[i][j]->color != playingColor) {
					return true;
				}
			}
		}
	}

	i = kingPosition.x + 1;
	j = kingPosition.y + 2;
	if (i < 8 && j < 8) {
		if (board[i][j] != nullptr) {
			if (board[i][j]->name.find("Knight") != std::string::npos) {
				if (board[i][j]->color != playingColor) {
					return true;
				}
			}
		}
	}

	i = kingPosition.x - 1;
	j = kingPosition.y + 2;
	if (i >= 0 && j < 8) {
		if (board[i][j] != nullptr) {
			if (board[i][j]->name.find("Knight") != std::string::npos) {
				if (board[i][j]->color != playingColor) {
					return true;
				}
			}
		}
	}

	i = kingPosition.x - 2;
	j = kingPosition.y + 1;
	if (i >= 0 && j < 8) {
		if (board[i][j] != nullptr) {
			if (board[i][j]->name.find("Knight") != std::string::npos) {
				if (board[i][j]->color != playingColor) {
					return true;
				}
			}
		}
	}

	for (i = kingPosition.x - 1, j = kingPosition.y-1;
		 i <= kingPosition.x + 1;
		 i++) {
		if (i >= 0 && i < 8 && j >= 0) {
			if (board[i][j] != nullptr) {
				if (board[i][j]->name.find("King") != std::string::npos) {
					if (board[i][j]->color != playingColor) {
						return true;
					}
				}
			}
		}
	}
	for (i = kingPosition.x - 1, j = kingPosition.y;
		 i <= kingPosition.x + 1;
		 i++) {
		if (i >= 0 && i < 8) {
			if (board[i][j] != nullptr) {
				if (board[i][j]->name.find("King") != std::string::npos) {
					if (board[i][j]->color != playingColor) {
						return true;
					}
				}
			}
		}
	}
	for (i = kingPosition.x - 1, j = kingPosition.y+1;
		 i <= kingPosition.x + 1;
		 i++) {
		if (i >= 0 && i < 8 && j < 8) {
			if (board[i][j] != nullptr) {
				if (board[i][j]->name.find("King") != std::string::npos) {
					if (board[i][j]->color != playingColor) {
						return true;
					}
				}
			}
		}
	}

	return false;
}

bool castle(Piece*** board, std::pair<Move, Move> move, bool playingWhite) {
	std::string aux = moveToString(move.first, move.second);
	if (playingWhite) {
		if (aux.find("e1g1") != std::string::npos ||
			aux.find("e1c1") != std::string::npos)
			if (board[move.first.x][move.first.y]->name.find("King") != std::string::npos)
				return true;
	}
	else {
		if (aux.find("e8g8") != std::string::npos ||
			aux.find("e8c8") != std::string::npos)
			if (board[move.first.x][move.first.y]->name.find("King") != std::string::npos)
				return true;
	}
	return false;
}

bool enPassant(Piece*** board, std::pair<Move, Move> move) {
	return 
		(board[move.first.x][move.first.y]->name.find("Pawn") != std::string::npos) &&
        (move.first.x != move.second.x && move.first.y != move.second.y) &&
        (board[move.second.x][move.second.y] == nullptr);
}

bool badMove(Piece*** board, std::pair<Move, Move> move, bool playingWhite) {
	if (castle(board, move, playingWhite)) {
		return false;
	}

	Piece*** fakeBoard;
    fakeBoard = new Piece**[8];
    for (int i = 0; i < 8; i++) {
        fakeBoard[i] = new Piece*[8];
    }

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            fakeBoard[i][j] = nullptr;
        }
    }

    for (int i = 0; i < 8; i++) {
    	for (int j = 0; j < 8; j++) {
    		if (board[i][j] != nullptr) {
    			fakeBoard[i][j] = board[i][j];
    		}
    	}
    }
    if (!enPassant(fakeBoard, move)) {
	    if (fakeBoard[move.first.x][move.first.y] != nullptr) {
		    fakeBoard[move.first.x][move.first.y]->hasMoved = true;
		    fakeBoard[move.second.x][move.second.y] = fakeBoard[move.first.x][move.first.y];
		    fakeBoard[move.first.x][move.first.y] = nullptr;
		}
	}
	else {
	    if (fakeBoard[move.first.x][move.first.y] != nullptr) {
		    fakeBoard[move.first.x][move.first.y]->hasMoved = true;
		    fakeBoard[move.second.x][move.second.y] = fakeBoard[move.first.x][move.first.y];
		    fakeBoard[move.first.x][move.first.y] = nullptr;
		    fakeBoard[move.second.x][move.first.y] = nullptr;
		}
	}
	if((inCheck(fakeBoard, getKingPosition(fakeBoard, playingWhite), playingWhite))) {
	    	
	    	return true;
    }
    else {
    	return false;
    }
}
