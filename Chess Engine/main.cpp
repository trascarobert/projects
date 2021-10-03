#include <deque>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <list>
#include <algorithm>
#include "Piece.h"
#include "Move.h"
#include "King.h"
#include "Pawn.h"
#include "Rook.h"
#include "Queen.h"
#include "Bishop.h"
#include "Knight.h"
#include "Board.h"
#include <ctime>
#include <cstdlib>

#define loop while(1)

void DEBUG_printBoard(Piece*** board) {
    if (false) {
        for (int j = 0; j < 8; j++) {
            for (int i = 0; i < 8; i++) {
                if (board[i][j] != nullptr) {
                    if (board[i][j]->color == Color::white)
                    std::cout << board[i][j]->name << "a";
                    else
                    std::cout << board[i][j]->name << "n";
                }
                else {
                    std::cout << "   NULL";
                }
            }
            std::cout << std::endl;
        }
    }
}

void DEBUG_printMoves(std::list<std::string> movesWhite, std::list<std::string> movesBlack) {
    if (false) {
    	std::ofstream out("mutari.out");
    	int i = 1;
    	while (!movesWhite.empty() && !movesBlack.empty()) {
            out << i++ << ". " << movesWhite.front() << " " << movesBlack.front() << std::endl;
            movesWhite.pop_front();
            movesBlack.pop_front();
        }
    	out.close();
    }
}

int main() {
    srand(time(NULL));

    bool playingWhite = 0;

    bool shouldPlay = 1; 
    std::cout.setf(std::ios::unitbuf);

    std::string command;
    std::cin >> command;
    std::getline(std::cin, command);
    std::cout << "feature sigint=0 san=0 name=VlogSquad" << std::endl;

    Piece*** board = newBoard();
    std::string move;

    std::list<std::string> movesWhite;
    std::list<std::string> movesBlack;

    loop {
        DEBUG_printMoves(movesWhite, movesBlack);	
        std::regex regexSan0Move("[a-h][0-8][a-h][0-8].?");
        std::getline(std::cin, move);

        if (move.find("new") != std::string::npos) {
            freeBoard(board);
            board = newBoard();
            playingWhite = 0;
            shouldPlay = 1;
            movesWhite.clear();
            movesBlack.clear();
        }

        else if (move.find("force") != std::string::npos) {
            shouldPlay = 0;
        }

        else if (move.find("go") != std::string::npos) {
            shouldPlay = 1;
            std::pair<bool,std::pair<int,int>> en_passant;
            en_passant = std::make_pair(false, std::make_pair(-1, -1));

            if (!movesWhite.empty() && !movesBlack.empty()) {
                int x_initial, y_initial, x_final, y_final;
                DEBUG_printMoves(movesWhite, movesBlack);
                if (playingWhite) {
                    x_initial = static_cast<int>(movesBlack.back()[0] - 97);
                    y_initial = static_cast<int>(movesBlack.back()[1] - 49);
                    x_final = static_cast<int>(movesBlack.back()[2] - 97);
                    y_final = static_cast<int>(movesBlack.back()[3] - 49);
                    
                }
                else {
                    x_initial = static_cast<int>(movesWhite.back()[0] - 97);
                    y_initial = static_cast<int>(movesWhite.back()[1] - 49);
                    x_final = static_cast<int>(movesWhite.back()[2] - 97);
                    y_final = static_cast<int>(movesWhite.back()[3] - 49);
                    
                }

                if (board[x_final][y_final] != nullptr) {
    	            if(board[x_final][y_final]->name.find("Pawn")  != std::string::npos){
    	            	if (playingWhite) {
    		                if (y_initial == 6 && y_final == 4 && x_initial == x_final) {
    		                    
    		                    en_passant = std::make_pair(true,std::make_pair(x_final,y_final));
    		                }
    	            	}
    	            	else {
    	            		if (y_initial == 1 && y_final == 3 && x_initial == x_final) {
    		                    
    		                    en_passant = std::make_pair(true,std::make_pair(x_final,y_final));
    		                }
    	            	}
    	            }
    	        }
            }
            auto fakeMoves = getMoves(board, playingWhite, en_passant);

                if (inCheck(board, getKingPosition(board, playingWhite), playingWhite) && false) {
                    std::cout << "resign\n";
                }
                else {
                    if (!fakeMoves.empty()) {
                        size_t index = std::rand() % fakeMoves.size();
                        if (castle(board, fakeMoves.back(), playingWhite)) {
                            index = fakeMoves.size() - 1;
                        }
                        std::cout << index << " " << fakeMoves.size() << std::endl;
                        while (badMove(board, fakeMoves[index], playingWhite) && !fakeMoves.empty()) {
                            fakeMoves.erase (fakeMoves.begin() + index);
                            if (fakeMoves.size() > 0) {
                                index = std::rand() % fakeMoves.size();
                               
                            }
                        }

                        if (fakeMoves.empty()) {
                            std::cout << "resign\n";
                            continue;
                        }

                        auto castleCheck = moveToString(fakeMoves[index].first, fakeMoves[index].second);
                        bool castled = false;
                        if (!playingWhite) {
                            if (castleCheck.find("e8g8") != std::string::npos &&
                                board[fakeMoves[index].first.x][fakeMoves[index].first.y]->name.find("King") != std::string::npos) {
                                stringToMove(board, "e8g8"); 
                                stringToMove(board, "h8f8"); 
                                castled = true;
                            }
                            if (castleCheck.find("e8c8") != std::string::npos &&
                                board[fakeMoves[index].first.x][fakeMoves[index].first.y]->name.find("King") != std::string::npos) {
                                stringToMove(board, "e8c8"); 
                                stringToMove(board, "a8d8"); 
                                castled = true;
                            }
                        }
                        else {
                            if (castleCheck.find("e1g1") != std::string::npos &&
                                board[fakeMoves[index].first.x][fakeMoves[index].first.y]->name.find("King") != std::string::npos) {
                                stringToMove(board, "e1g1"); 
                                stringToMove(board, "h1f1");
                                castled = true;
                            }
                            if (castleCheck.find("e1c1") != std::string::npos &&
                                board[fakeMoves[index].first.x][fakeMoves[index].first.y]->name.find("King") != std::string::npos) {
                                stringToMove(board, "e1c1"); /
                                stringToMove(board, "a1d1"); 
                                castled = true;
                            }
                        }
                        if (!castled) {
                            if (board[fakeMoves[index].first.x]
                                        [fakeMoves[index].first.y]
                                            ->name.find("Pawn") != std::string::npos) {
                                
                                if (fakeMoves[index].first.x != fakeMoves[index].second.x &&
                                    fakeMoves[index].first.y != fakeMoves[index].second.y) {
                                    
                                    if (board[fakeMoves[index].second.x]
                                                [fakeMoves[index].second.y] == nullptr) {
                                        
                                        board[fakeMoves[index].second.x]
                                                [fakeMoves[index].first.y] = nullptr;
                                    }
                                }
                            }
                        }

                        std::cout 
                            << moveToString(fakeMoves[index].first,
                                                    fakeMoves[index].second)
                            << std::endl;
                            
                        if (!castled) {
                            movePiece(board, fakeMoves[index].first,
                                                    fakeMoves[index].second);
                        }
                        DEBUG_printBoard(board);
                        if (playingWhite) {
                            movesWhite.push_back(moveToString(fakeMoves[index].first,
                                                                fakeMoves[index].second).substr(5));
                            movesBlack.push_back(move);
                        }
                        else {
                            movesBlack.push_back(moveToString(fakeMoves[index].first,
                                                                fakeMoves[index].second).substr(5));
                            movesWhite.push_back(move);
                        }
                        fakeMoves.clear();
                    }
                    else {
                        std::cout << "resign\n";
                    }
                }
            
        }

        else if (move.find("white")!= std::string::npos) {
            playingWhite = 1;
        }

        else if (move.find("black")!= std::string::npos) {
            playingWhite = 0;
        }

        else if (std::regex_match(move, regexSan0Move)){
            bool opponentCastled = false;
            if (playingWhite) {
                if (board[4][7] != nullptr && board[4][7]->name.find("King") != std::string::npos &&
                    board[4][7]->color == Color::black) {
                    if (move.find("e8g8") != std::string::npos) {
                        stringToMove(board, "e8g8"); 
                        stringToMove(board, "h8f8"); 
                        opponentCastled = true;
                    }
                    if (move.find("e8c8") != std::string::npos) {
                        stringToMove(board, "e8c8"); 
                        stringToMove(board, "a8d8"); 
                        opponentCastled = true;
                    }
                }
            }
            else {
                if (board[4][0] != nullptr && board[4][0]->name.find("King") != std::string::npos &&
                    board[4][0]->color == Color::white) {
                    if (move.find("e1g1") != std::string::npos) {
                        stringToMove(board, "e1g1"); 
                        stringToMove(board, "h1f1"); 
                        opponentCastled = true;
                    }
                    
                    if (move.find("e1c1") != std::string::npos) {
                        stringToMove(board, "e1c1");
                        stringToMove(board, "a1d1"); 
                        opponentCastled = true;
                    }
                }
            }

            bool promotion = false;
            char promotionPiece = 'z';
            if (move.size() == 5) {
                promotionPiece = move[4];
                move = move.substr(0, 4);
                promotion = true;
            }

            int x_initial = static_cast<int>(move[0] - 97);
            int y_initial = static_cast<int>(move[1] - 49);
            int x_final = static_cast<int>(move[2] - 97);
            int y_final = static_cast<int>(move[3] - 49);


            std::pair<bool,std::pair<int,int>> en_passant;
            en_passant = std::make_pair(false, std::make_pair(-1, -1));

            if (!opponentCastled) {
                if(board[x_initial][y_initial]->name.find("Pawn")  != std::string::npos){
                	if (playingWhite) {
    	                if (y_initial == 6 && y_final == 4 && x_initial == x_final) {
    	                   
    	                    en_passant = std::make_pair(true,std::make_pair(x_final,y_final));
    	                }
    	                else {
    	                    en_passant = std::make_pair(false,std::make_pair(-1,-1));
    	                }
                	}
                	else {
                		if (y_initial == 1 && y_final == 3 && x_initial == x_final) {
    	                   
    	                    en_passant = std::make_pair(true,std::make_pair(x_final,y_final));
    	                }
    	                else {
    	                    en_passant = std::make_pair(false,std::make_pair(-1,-1));
    	                }
                	}
                }
            
                if(board[x_initial][y_initial]->name.find("Pawn")  != std::string::npos){
                	if (x_initial != x_final && y_initial != y_final) {
            			if (board[x_final][y_final] == nullptr) {
            				stringToMove(board, move);
            				board[x_final][y_initial] = nullptr;
            			}
            		}
                }
            }
            stringToMove(board, move);

            if(promotion) {
                if(!playingWhite) {
                    if (promotionPiece == 'q') {
                        board[static_cast<int>(move[2] - 97)][7] = new Queen(Color::white, move[2]-97, 7);
                    }
                    else if (promotionPiece == 'r') {
                        board[static_cast<int>(move[2] - 97)][7] = new Rook(Color::white, move[2]-97, 7);
                    }
                    else if (promotionPiece == 'n') {
                        board[static_cast<int>(move[2] - 97)][7] = new Knight(Color::white, move[2]-97, 7);
                    }
                    else if (promotionPiece == 'b') {
                        board[static_cast<int>(move[2] - 97)][7] = new Bishop(Color::white, move[2]-97, 7);
                    }
                }
                else {
                    if (promotionPiece == 'q') {
                        board[static_cast<int>(move[2] - 97)][0] = new Queen(Color::black, move[2]-97, 0);
                    }
                    else if (promotionPiece == 'r') {
                        board[static_cast<int>(move[2] - 97)][0] = new Rook(Color::black, move[2]-97, 0);
                    }
                    else if (promotionPiece == 'n') {
                        board[static_cast<int>(move[2] - 97)][0] = new Knight(Color::black, move[2]-97, 0);
                    }
                    else if (promotionPiece == 'b') {
                        board[static_cast<int>(move[2] - 97)][0] = new Bishop(Color::black, move[2]-97, 0);
                    }
                    
                }
            }

            if (shouldPlay) {
                auto fakeMoves = getMoves(board, playingWhite, en_passant);

                if (inCheck(board, getKingPosition(board, playingWhite), playingWhite) && false) {
                    std::cout << "resign\n";
                }
                else {
                    if (!fakeMoves.empty()) {
                        size_t index = std::rand() % fakeMoves.size();
                        if (castle(board, fakeMoves.back(), playingWhite)) {
                            index = fakeMoves.size() - 1;
                        }
                        while (badMove(board, fakeMoves[index], playingWhite) && !fakeMoves.empty()) {
                            fakeMoves.erase (fakeMoves.begin() + index);
                            if (fakeMoves.size() > 0) {
                                index = std::rand() % fakeMoves.size();
                            }
                        }

                        if (fakeMoves.empty()) {
                            std::cout << "resign\n";
                            continue;
                        }

                        auto castleCheck = moveToString(fakeMoves[index].first, fakeMoves[index].second);
                        bool castled = false;
                        if (!playingWhite) {
                            if (castleCheck.find("e8g8") != std::string::npos &&
                                board[fakeMoves[index].first.x][fakeMoves[index].first.y]->name.find("King") != std::string::npos) {
                                stringToMove(board, "e8g8"); 
                                stringToMove(board, "h8f8"); 
                                castled = true;
                            }
                            if (castleCheck.find("e8c8") != std::string::npos &&
                                board[fakeMoves[index].first.x][fakeMoves[index].first.y]->name.find("King") != std::string::npos) {
                                stringToMove(board, "e8c8");
                                stringToMove(board, "a8d8"); 
                                castled = true;
                            }
                        }
                        else {
                           
                            if (castleCheck.find("e1g1") != std::string::npos &&
                                board[fakeMoves[index].first.x][fakeMoves[index].first.y]->name.find("King") != std::string::npos) {
                                stringToMove(board, "e1g1"); 
                                stringToMove(board, "h1f1"); 
                                castled = true;
                            }
                            if (castleCheck.find("e1c1") != std::string::npos &&
                                board[fakeMoves[index].first.x][fakeMoves[index].first.y]->name.find("King") != std::string::npos) {
                                stringToMove(board, "e1c1"); 
                                stringToMove(board, "a1d1"); 
                                castled = true;
                            }
                        }
                        if (!castled) {
    	                    if (board[fakeMoves[index].first.x]
    	                    			[fakeMoves[index].first.y]
    	                    				->name.find("Pawn")	!= std::string::npos) {
    	                    	
    	                    	if (fakeMoves[index].first.x != fakeMoves[index].second.x &&
    	                    		fakeMoves[index].first.y != fakeMoves[index].second.y) {
    	                    		
    	                    		if (board[fakeMoves[index].second.x]
    	                    					[fakeMoves[index].second.y] == nullptr) {
    	                    			
    	                    			board[fakeMoves[index].second.x]
    	                    					[fakeMoves[index].first.y] = nullptr;
    	                    		}
    	                    	}
    	                    }
    	                }

                        std::cout 
                            << moveToString(fakeMoves[index].first,
                                                    fakeMoves[index].second)
                            << std::endl;
                            
                        if (!castled) {
                            movePiece(board, fakeMoves[index].first,
                                                    fakeMoves[index].second);
                            auto final = fakeMoves[index].second;
                            if (board[final.x][final.y]->name.find("Pawn") != std::string::npos) {
                                if (final.y == 7) {
                                    board[final.x][final.y] = nullptr;
                                    board[final.x][final.y] = new Queen(Color::white, final.x, final.y);
                                }
                                else if (final.y == 0) {
                                    board[final.x][final.y] = nullptr;
                                    board[final.x][final.y] = new Queen(Color::black, final.x, final.y);
                                }
                            }
                        }
                        DEBUG_printBoard(board);
                        if (playingWhite) {
                            movesWhite.push_back(moveToString(fakeMoves[index].first,
                                                                fakeMoves[index].second).substr(5));
                            movesBlack.push_back(move);
                        }
                        else {
                            movesBlack.push_back(moveToString(fakeMoves[index].first,
                                                                fakeMoves[index].second).substr(5));
                            movesWhite.push_back(move);
                        }
                        fakeMoves.clear();
                    }
                    else {
                        std::cout << "resign\n";
                    }
                }
            }
            else {
                playingWhite = !playingWhite;
                if (playingWhite) {
                    movesWhite.push_back(move);
                }
                else {
                    movesBlack.push_back(move);
                }
            }
        }
        else if (move.find("quit") != std::string::npos) {
            exit(0);
        }
    }
}
