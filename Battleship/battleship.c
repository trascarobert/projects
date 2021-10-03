#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void readPlayerMatrix(char (*matricePlayer)[10], char *argv);
int meniu(char list[][100], char *argv);
void start_game(char *argv);
bool isValid(char computerMatrix[][10], int row, int col);
void generateComputerMatrix(char (*computerMatrix)[10]);
bool isWin(char matrix[][10]);
bool validPosition(char playerMatrix[][10], int row, int col);
void message(WINDOW * w);

int main(int argc, char *argv[])
{
    if (argc < 2) {
	printf("[Eroare]: Nu s-au dat argumente de comanda.\n");
	return 1;
    }
    char **fileContent;
    int i;
    fileContent = (char **) malloc(argc * sizeof(char *));
    for (i = 0; i < argc; i++) {
	fileContent[i] = (char *) malloc(120 * sizeof(char *));
    }
    for (i = 1; i < argc; i++) {
	FILE *fp = fopen(argv[i], "r");
	if (fp == NULL) {
	    printf("[Eroare]: Fisierul %s nu poate fi deschis.\n",
		   argv[i]);
	    return 1;
	}
	fseek(fp, 0L, SEEK_END);
	long sz = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	char *buffer = (char *) malloc((sz + 1) * sizeof(char));
	if (buffer) {
	    fread(buffer, sizeof(char), sz, fp);
	}
	strcpy(fileContent[i], buffer);
	free(buffer);
	fclose(fp);
    }
    int lower = 1;
    int upper = argc - 1;
    int mapNumber = (rand() % (upper - lower + 1)) + lower;
    char list[3][100] = { "New Game", "Resume Game", "Quit" };
    meniu(list, argv[mapNumber]);
    free(fileContent);
    return 0;
}


void readPlayerMatrix(char (*matricePlayer)[10], char *argv)
{
    int i, j;
    FILE *fp;
    fp = fopen(argv, "r");
    for (i = 0; i < 10; ++i) {
	char read;
	for (j = 0; j < 10; ++j) {
	    fscanf(fp, "%c", matricePlayer[i] + j);

	}
	fscanf(fp, "%c", &read);
    }
    fclose(fp);
}

int meniu(char list[][100], char *argv)
{
    WINDOW *w;			
    int i, ch = 0;
    initscr();			
    w = newwin(0, 0, 0, 0);
    start_color();		
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    wbkgd(w, COLOR_PAIR(1));
    message(w);
    for (i = 0; i < 3; i++) {
	if (i == 0) {
	    wattron(w, A_REVERSE);
	    wattron(w, COLOR_PAIR(2));
	} else {
	    wattroff(w, A_REVERSE);
	    wattroff(w, COLOR_PAIR(2));
	}
	mvwprintw(w, i + 10, 33, "%s", list[i]);
    }
    wrefresh(w);		
    i = 0;
    noecho();			
    keypad(w, TRUE);		
    curs_set(0);		
    while ((ch = wgetch(w))) {
	mvwprintw(w, i + 10, 33, "%s", list[i]);
	switch (ch) {
	case KEY_UP:
	    i--;
	    if (i < 0)
		i = 2;
	    break;
	case KEY_DOWN:
	    i++;
	    if (i > 2)
		i = 0;
	    break;
	case 10:		
	    switch (i) {
	    case 2:
		endwin();
		exit(1);=
	    case 0:
		start_game(argv);
		clear();	
		message(w);
		for (i = 0; i < 3; i++) {
		    mvwprintw(w, i + 10, 33, "%s", list[i]);
		}
		i = 0;
		noecho();
		refresh();
	    }

	}
	wattron(w, A_REVERSE);
	wattron(w, COLOR_PAIR(2));
	mvwprintw(w, i + 10, 33, "%s", list[i]);
	wattroff(w, COLOR_PAIR(2));
	wattroff(w, A_REVERSE);
    }
    delwin(w);			
    endwin();			
    return 0;
}

void start_game(char *argv)
{
    WINDOW *start_game;		
    int ch;
    int x = 0, y = 0;
    int i, j;
    initscr();			
    start_game = newwin(0, 0, 0, 1);
    start_color();
    keypad(start_game, TRUE);	
    curs_set(0);		
    char computerMatrix[10][10];
    generateComputerMatrix(computerMatrix);
    char playerMatrix[10][10];
    readPlayerMatrix(playerMatrix, argv);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_WHITE, COLOR_BLACK);
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);
    wbkgd(start_game, COLOR_PAIR(3));
    char gameMatrix[10][10];
    for (x = 0; x < 10; x++) {
	for (y = 0; y < 10; y++) {
	    gameMatrix[x][y] = (char) 39;
	}
    }
    x = 0;
    int attack_computer = 0;
    int attack_player = 0;
    y = 0;
    int modified = 1;
    int computerTurn = 0;
    int score_computer = 0;
    int score_player = 0;
    int score = 0;
    int ship_player = 0;
    int ship_computer = 0;
    FILE *player;
    player = fopen("save_player.txt", "r");
    fscanf(player, "%d", &score_player);
    fclose(player);
    FILE *computer;
    computer = fopen("save_computer.txt", "r");
    fscanf(computer, "%d", &score_computer);
    fclose(computer);
    FILE *egal;
    egal = fopen("save_egal.txt", "r");
    fscanf(egal, "%d", &score);
    fclose(egal);
    while ((modified == 1) || (computerTurn == 1)
	   || (ch = wgetch(start_game))) {
	if (ch == 'q') {
	    break;
	}
	int upper = 9;
	int lower = 0;
	while (computerTurn == 1) {
	    int row = (rand() % (upper - lower + 1)) + lower;
	    int col = (rand() % (upper - lower + 1)) + lower;
	    if (playerMatrix[row][col] == 'X'
		&& validPosition(playerMatrix, row, col)) {
		playerMatrix[row][col] = 'K';
		ship_computer++;
		wattron(start_game, COLOR_PAIR(2));
		mvwprintw(start_game, row + 11, col, "%c",
			  playerMatrix[row][col]);
		wattroff(start_game, COLOR_PAIR(2));
		if (isWin(playerMatrix)) {
		    wattron(start_game, COLOR_PAIR(5));
		    mvwprintw(start_game, 5, 50, "%s", "Computer WON!");
		    mvwprintw(start_game, 2, 68, "%s", "!!");
		    score_computer++;
		    wattroff(start_game, COLOR_PAIR(5));
		    sleep(5);
		}
	    } else if (validPosition(playerMatrix, row, col)) {
		playerMatrix[row][col] = '?';
		wattron(start_game, COLOR_PAIR(1));
		mvwprintw(start_game, row + 11, col, "%c",
			  playerMatrix[row][col]);
		wattroff(start_game, COLOR_PAIR(1));
		computerTurn = 0;
	    }
	    //sleep(3);


	}
	if (modified == 1) {
	    for (i = 0; i < 10; ++i) {
		for (j = 0; j < 10; ++j) {
		    waddch(start_game, gameMatrix[i][j]);

		}
		waddch(start_game, '\n');
	    }
	    waddch(start_game, '\n');
	    for (i = 0; i < 10; ++i) {
		for (j = 0; j < 10; ++j) {
		    waddch(start_game, playerMatrix[i][j]);
		}
		waddch(start_game, '\n');
	    }
	    modified = 0;
	}
	mvwprintw(start_game, x, y, "%c", gameMatrix[x][y]);
	switch (ch) {
	case KEY_UP:
	    x--;
	    if (x < 0)
		x = 9;
	    break;
	case KEY_DOWN:
	    x++;
	    if (x > 9)
		x = 0;
	    break;
	case KEY_RIGHT:
	    y++;
	    if (y > 9)
		y = 0;
	    break;
	case KEY_LEFT:
	    y--;
	    if (y < 9)
		y = 0;
	    break;
	case 10:{
		if (computerTurn == 0 && gameMatrix[x][y] == (char) 39) {
		    if (computerMatrix[x][y] == (char) 39) {
			gameMatrix[x][y] = '?';
			computerTurn = 1;
		    } else {
			gameMatrix[x][y] = 'K';
			ship_player++;
			if (isWin(gameMatrix)) {
			    wattron(start_game, COLOR_PAIR(5));
			    mvwprintw(start_game, 5, 50, "%s",
				      "Player WON!");
			    mvwprintw(start_game, 1, 68, "%s", "!!");
			    score_player++;
			    wattroff(start_game, COLOR_PAIR(5));
			    sleep(5);
			}
		    }
		}
	    }
	}
	switch (ch) {
	case 100:{
		while (attack_computer < 100) {
		    x = (rand() % (upper - lower + 1)) + lower;
		    y = (rand() % (upper - lower + 1)) + lower;
		    if (gameMatrix[x][y] == (char) 39) {
			if (computerMatrix[x][y] == (char) 39) {
			    gameMatrix[x][y] = '?';
			    attack_computer++;
			    wattron(start_game, COLOR_PAIR(1));
			    mvwprintw(start_game, x, y, "%c",
				      gameMatrix[x][y]);
			    wattroff(start_game, COLOR_PAIR(1));
			} else {
			    gameMatrix[x][y] = 'K';
			    attack_computer++;
			    ship_player++;
			    wattron(start_game, COLOR_PAIR(2));
			    mvwprintw(start_game, x, y, "%c",
				      gameMatrix[x][y]);
			    wattroff(start_game, COLOR_PAIR(2));
			}
		    }
		}
		while (attack_player < 100) {
		    int row = (rand() % (upper - lower + 1)) + lower;
		    int col = (rand() % (upper - lower + 1)) + lower;
		    if (playerMatrix[row][col] == 'X'
			&& validPosition(playerMatrix, row, col)) {
			playerMatrix[row][col] = 'K';
			attack_player++;
			ship_computer++;
			wattron(start_game, COLOR_PAIR(2));
			mvwprintw(start_game, row + 11, col, "%c",
				  playerMatrix[row][col]);
			wattroff(start_game, COLOR_PAIR(2));
		    } else if (validPosition(playerMatrix, row, col)) {
			playerMatrix[row][col] = '?';
			attack_player++;
			wattron(start_game, COLOR_PAIR(1));
			mvwprintw(start_game, row + 11, col, "%c",
				  playerMatrix[row][col]);
			wattroff(start_game, COLOR_PAIR(1));
			wrefresh(start_game);
		    }
		}
		if (isWin(gameMatrix) && ship_computer != 20) {
		    wattron(start_game, COLOR_PAIR(5));
		    mvwprintw(start_game, 5, 50, "%s", "Player WON!");
		    mvwprintw(start_game, 1, 68, "%s", "!!");
		    score_player++;
		    wattroff(start_game, COLOR_PAIR(5));
		    sleep(5);
		}
		if (isWin(playerMatrix) && ship_player != 20) {
		    wattron(start_game, COLOR_PAIR(5));
		    mvwprintw(start_game, 5, 50, "%s", "Computer WON!");
		    mvwprintw(start_game, 2, 68, "%s", "!!");
		    score_computer++;
		    wattroff(start_game, COLOR_PAIR(5));
		    sleep(5);
		}
	    }
	    if (ship_computer == 20 && ship_player == 20) {
		wattron(start_game, COLOR_PAIR(5));
		mvwprintw(start_game, 5, 50, "%s", "NOBODY WON!");
		mvwprintw(start_game, 3, 63, "%s", "!!");
		score++;
		wattroff(start_game, COLOR_PAIR(5));
		sleep(5);
	    }
	}

	wattron(start_game, COLOR_PAIR(4));
	mvwprintw(start_game, 0, 12, "%s", "Computer Map");
	mvwprintw(start_game, 11, 12, "%s", "Player Map");
	mvwprintw(start_game, 21, 0, "%s",
		  "In caz ca doriti sa ajungeti la meniul jocului apasati tasta 'q'");
	mvwprintw(start_game, 22, 0, "%s",
		  "In caz ca doriti sa folositi abilitatea 'Destroy in Advance' apasati tasta 'd'");
	mvwprintw(start_game, 0, 50, "%s", "Tabela de scor :\n");
	mvwprintw(start_game, 1, 50, "Scor player : %d", score_player);
	mvwprintw(start_game, 2, 50, "Scor computer : %d", score_computer);
	mvwprintw(start_game, 3, 50, "Egalitate: %d", score);
	mvwprintw(start_game, 10, 35, "Componente distruse de PLAYER : %d",
		  ship_player);
	mvwprintw(start_game, 11, 35,
		  "Componente distruse de COMPUTER : %d", ship_computer);
	wattroff(start_game, COLOR_PAIR(4));
	wattron(start_game, A_REVERSE);
	wattron(start_game, COLOR_PAIR(5));
	mvwprintw(start_game, x, y, "%c", gameMatrix[x][y]);
	wattroff(start_game, COLOR_PAIR(5));
	wattroff(start_game, A_REVERSE);
	if (gameMatrix[x][y] == '?') {
	    wattron(start_game, COLOR_PAIR(1));
	} else if (gameMatrix[x][y] == 'K') {
	    wattron(start_game, COLOR_PAIR(2));
	}
	FILE *fp;
	fp = fopen("save_player.txt", "w+");
	fprintf(fp, "%d", score_player);
	fclose(fp);
	FILE *fp2;
	fp2 = fopen("save_computer.txt", "w+");
	fprintf(fp2, "%d", score_computer);
	fclose(fp2);
	FILE *fp3;
	fp3 = fopen("save_egal.txt", "w+");
	fprintf(fp3, "%d", score);
	fclose(fp3);
	wrefresh(start_game);
    }
    clear();
    wrefresh(start_game);
    noecho();
    delwin(start_game);
    endwin();
}

bool isValid(char computerMatrix[][10], int row, int col)
{
    if (row < 0 || row > 9 || col < 0 || col > 9) {
	return false;
    }

    if (computerMatrix[row][col] == 'X'
	|| computerMatrix[row - 1][col] == 'X'
	|| computerMatrix[row][col - 1] == 'X'
	|| computerMatrix[row - 1][col - 1] == 'X'
	|| computerMatrix[row + 1][col] == 'X'
	|| computerMatrix[row][col + 1] == 'X'
	|| computerMatrix[row + 1][col + 1] == 'X'
	|| computerMatrix[row - 1][col + 1] == 'X'
	|| computerMatrix[row + 1][col - 1] == 'X') {
	return false;
    }
    return true;
}

bool validPosition(char playerMatrix[][10], int x, int y)
{
    if (x < 0 || y > 9 || x < 0 || y > 9) {
	return false;
    }
    if (playerMatrix[x][y] == 'K' || playerMatrix[x][y] == '?') {
	return false;
    }
    return true;
}

void generateComputerMatrix(char (*computerMatrix)[10])
{
    int i, j;
    for (i = 0; i < 10; i++) {
	for (j = 0; j < 10; j++) {
	    computerMatrix[i][j] = (char) 39;
	}
    }
    int nave1 = 4, nave2 = 3, nave3 = 2, nave4 = 1;
    int lower = 0;
    int upper = 9;
    while (nave1 != 0) {
	int row = (rand() % (upper - lower + 1)) + lower;
	int col = (rand() % (upper - lower + 1)) + lower;
	if (isValid(computerMatrix, row, col)) {
	    computerMatrix[row][col] = 'X';
	    nave1--;
	}
    }
    while (nave2 != 0) {
	int row = (rand() % (upper - lower + 1)) + lower;
	int col = (rand() % (upper - lower + 1)) + lower;
	int upperSize = 3;
	int lowerSize = 0;
	if (isValid(computerMatrix, row, col)) {
	    int direction = (rand() %
			     (upperSize - lowerSize + 1)) + lowerSize;
	    if (direction == 0) {
		if (isValid(computerMatrix, row + 1, col)) {
		    computerMatrix[row][col] = 'X';
		    computerMatrix[row + 1][col] = 'X';
		    nave2--;
		}
	    }
	    if (direction == 1) {
		if (isValid(computerMatrix, row, col + 1)) {
		    computerMatrix[row][col] = 'X';
		    computerMatrix[row][col + 1] = 'X';
		    nave2--;
		}
	    }
	    if (direction == 2) {
		if (isValid(computerMatrix, row - 1, col)) {
		    computerMatrix[row][col] = 'X';
		    computerMatrix[row - 1][col] = 'X';
		    nave2--;
		}
	    }
	    if (direction == 3) {
		if (isValid(computerMatrix, row, col - 1)) {
		    computerMatrix[row][col] = 'X';
		    computerMatrix[row][col - 1] = 'X';
		    nave2--;
		}
	    }
	}
    }
    while (nave3 != 0) {
	int row = (rand() % (upper - lower + 1)) + lower;
	int col = (rand() % (upper - lower + 1)) + lower;
	int upperSize = 3;
	int lowerSize = 0;
	if (isValid(computerMatrix, row, col)) {
	    int direction = (rand() %
			     (upperSize - lowerSize + 1)) + lowerSize;
	    if (direction == 0) {
		if (isValid(computerMatrix, row + 1, col)
		    && isValid(computerMatrix, row + 2, col)) {
		    computerMatrix[row][col] = 'X';
		    computerMatrix[row + 1][col] = 'X';
		    computerMatrix[row + 2][col] = 'X';
		    nave3--;
		}
	    }
	    if (direction == 1) {
		if (isValid(computerMatrix, row, col + 1)
		    && isValid(computerMatrix, row, col + 2)) {
		    computerMatrix[row][col] = 'X';
		    computerMatrix[row][col + 1] = 'X';
		    computerMatrix[row][col + 2] = 'X';
		    nave3--;
		}
	    }
	    if (direction == 2) {
		if (isValid(computerMatrix, row - 1, col)
		    && isValid(computerMatrix, row - 2, col)) {
		    computerMatrix[row][col] = 'X';
		    computerMatrix[row - 1][col] = 'X';
		    computerMatrix[row - 2][col] = 'X';
		    nave3--;
		}
	    }
	    if (direction == 3) {
		if (isValid(computerMatrix, row, col - 1)
		    && isValid(computerMatrix, row, col - 2)) {
		    computerMatrix[row][col] = 'X';
		    computerMatrix[row][col - 1] = 'X';
		    computerMatrix[row][col - 2] = 'X';
		    nave3--;
		}
	    }
	}
    }
    while (nave4 != 0) {
	int row = (rand() % (upper - lower + 1)) + lower;
	int col = (rand() % (upper - lower + 1)) + lower;
	int upperSize = 3;
	int lowerSize = 0;
	if (isValid(computerMatrix, row, col)) {
	    int direction = (rand() %
			     (upperSize - lowerSize + 1)) + lowerSize;
	    if (direction == 0) {
		if (isValid(computerMatrix, row + 1, col)
		    && isValid(computerMatrix, row + 3, col)) {
		    computerMatrix[row][col] = 'X';
		    computerMatrix[row + 1][col] = 'X';
		    computerMatrix[row + 2][col] = 'X';
		    computerMatrix[row + 3][col] = 'X';
		    nave4--;
		}
	    }
	    if (direction == 1) {
		if (isValid(computerMatrix, row, col + 1)
		    && isValid(computerMatrix, row, col + 3)) {
		    computerMatrix[row][col] = 'X';
		    computerMatrix[row][col + 1] = 'X';
		    computerMatrix[row][col + 2] = 'X';
		    computerMatrix[row][col + 3] = 'X';
		    nave4--;
		}
	    }
	    if (direction == 2) {
		if (isValid(computerMatrix, row - 1, col)
		    && isValid(computerMatrix, row - 3, col)) {
		    computerMatrix[row][col] = 'X';
		    computerMatrix[row - 1][col] = 'X';
		    computerMatrix[row - 2][col] = 'X';
		    computerMatrix[row - 3][col] = 'X';
		    nave4--;
		}
	    }
	    if (direction == 3) {
		if (isValid(computerMatrix, row, col - 1)
		    && isValid(computerMatrix, row, col - 3)) {
		    computerMatrix[row][col] = 'X';
		    computerMatrix[row][col - 1] = 'X';
		    computerMatrix[row][col - 2] = 'X';
		    computerMatrix[row][col - 3] = 'X';
		    nave4--;
		}
	    }
	}
    }
}

bool isWin(char matrix[][10])
{
    int noOfB = 0;
    for (int i = 0; i < 10; i++) {
	for (int j = 0; j < 10; j++) {
	    if (matrix[i][j] == 'K') {
		noOfB++;
	    }
	}
    }
    if (noOfB == 20) {
	return true;
    }
    return false;
}

void message(WINDOW * w)
{
    mvwprintw(w, 0, 10,
	      "XXXXX   XXXX  XXXXXX XXXXXX XX     XXXXXX  XXXXX XX  XX XX XXXX\n");
    mvwprintw(w, 1, 10,
	      "XX  XX XX  XX   XX     XX   XX     XX     XX     XX  XX XX XX XX\n");
    mvwprintw(w, 2, 10,
	      "XXXXX  XX  XX   XX     XX   XX     XXXX    XXXX  XXXXXX XX XXXX\n");
    mvwprintw(w, 3, 10,
	      "XX  XX XXXXXX   XX     XX   XX     XX         XX XX  XX XX XX\n");
    mvwprintw(w, 4, 10,
	      "XXXXX  XX  XX   XX     XX   XXXXXX XXXXXX XXXXX  XX  XX XX XX\n");
}
