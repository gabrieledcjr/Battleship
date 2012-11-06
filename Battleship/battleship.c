/*==============================================================================
 | Filename: battleship.h                                                    
 | Programmer: Gabriel V. de a Cruz Jr.                                  
 | Class: CptS 121, Fall 2012 ; Lab Section 7                            
 | Programming Assignment 4: Basic Game of Battleship                    
 | Date: October 6, 2012                                                 
 +------------------------------------------------------------------------------                                                                       
 | Description:                              
 ==============================================================================*/

#include "battleship.h"

/**
 * that displays an initial program welcome message along with the rules of 
 * Battleship.
 */
void welcomeScreen (void) {
	printf ("Welcome to Battleship\n\n");
	printf ("Rules of the Game:\n");
	printf ("1. This is a two player game.\n");
	printf ("2. Player 1 is you and Player 2 is the computer.\n");
	printf ("3. ...\n");
}

void initializeGameBoard (Cell gameBoard[][COLS]) {
	int i = 0, j = 0;

	for (i = 0; i < ROWS; i++)
		for (j = 0; j < COLS; j++) {
			gameBoard[i][j].symbol          = WATER;
			gameBoard[i][j].position.row    = i;
			gameBoard[i][j].position.column = j;
		}
}

void printGameBoard (Cell gameBoard [][COLS]) {
	int i = 0, j = 0;

	printf ("  0 1 2 3 4 5 6 7 8 9\n");

	for (i = 0; i < ROWS; i++) {
		printf ("%d ", i);

		for (j = 0; j < COLS; j++) {
			printf ("%c ", gameBoard [i][j].symbol);
		}
		
		putchar ('\n');
	}
}

void putShipOnGameBoard (Cell gameBoard[][COLS], WaterCraft ship, 
	                     Coordinate position, int direction) {
	int i = ship.length - 1;

	for (i = 0; i < ship.length; i++) {
		if (direction == HORIZONTAL) 
			gameBoard [position.row][position.column + i].symbol = ship.symbol;
		else /* VERTICAL */
			gameBoard [position.row + i][position.column].symbol = ship.symbol;
	}
}

void manuallyPlaceShipsOnGameBoard (Cell gameBoard[][COLS], WaterCraft ship[]) {
	char stringPosition[11] = "";
	Coordinate position[5];
	int i = 0, j = 0;
	Boolean isValid = FALSE;

	fflush (stdin);

	for (i = 0; i < NUM_OF_SHIPS; i++) {
		while (TRUE) {
			printf ("> Please enter the %d cells to place the %s across:\n", ship[i].length, ship[i].name);
			scanf ("%s", stringPosition);

			/* convertStringtoPosition returns false if unsuccessful */
			if (convertStringtoPosition (position, stringPosition, ship[i].length)) {
				isValid = TRUE;
				for (j = 0; j < ship[i].length; j++) {
					if (gameBoard[position[j].row][position[j].column].symbol == WATER) {
						gameBoard[position[j].row][position[j].column].symbol = ship[i].symbol;
					} else {
						isValid = FALSE;
						printf ("> Invalid input!\n");

						if (j != 0)
							while (j >= 0) {
								gameBoard[position[j].row][position[j].column].symbol = WATER;
								j--;
							}
						break;
					}
				}
			} else {
				isValid = FALSE;
				printf ("> Invalid input!\n");
			}

			if (isValid == TRUE) break;
		}

	}
}

void randomlyPlaceShipsOnGameBoard (Cell gameBoard[][COLS], WaterCraft ship[]) {
	Coordinate position;
	int direction = -1;
	int i = 0;

	for (i = 0; i < NUM_OF_SHIPS; i++) {
		while (TRUE) {
			direction = getRandomNumber (0, 1); /* 0 -> horizontal, 1 -> vertical */
			position = generatePosition (direction, ship[i].length);

			if (isValidLocation (gameBoard, position, direction, ship[i].length)) break;
		}

		putShipOnGameBoard (gameBoard, ship[i], position, direction);
	}
}

/* (~) water, (*) hit, (m) miss, (c) carrier, (b) battleship, (r) cruiser, (s) submarine, (d) destroyer */
void updateGameBoard (Cell gameBoard[][COLS], Coordinate target) {
	switch (gameBoard[target.row][target.column].symbol) {
		/* miss */ 
		case WATER: 
			gameBoard[target.row][target.column].symbol = MISS;
			break;

		/* hit */
		case CARRIER: 
		case BATTLESHIP:
		case CRUISER:
		case SUBMARINE:
		case DESTROYER:
			gameBoard[target.row][target.column].symbol = HIT;
			break;

		case HIT:
		case MISS:
		default:
			break;
	}	
}

void checkSunkShip (short sunkShip[][NUM_OF_SHIPS], short player, char shipSymbol, FILE *stream) {
	switch (shipSymbol) {
		case CARRIER:    
			if (--sunkShip[player][0] == 0) {
				printf ("> Player %d's Carrier sunked!\n", player + 1);

				/* Write to battleship.log */
				fprintf (stream, "Player %d's Carrier sunked!\n", player + 1);
			}
			break;

		case BATTLESHIP: 
			if (--sunkShip[player][1] == 0) {
				printf ("> Player %d's Battleship sunked!\n", player + 1);

				/* Write to battleship.log */
				fprintf (stream, "Player %d's Battleship sunked!\n", player + 1);
			}
			break;

		case CRUISER:    
			if (--sunkShip[player][2] == 0) {
				printf ("> Player %d's Cruiser sunked!\n", player + 1);

				/* Write to battleship.log */
				fprintf (stream, "Player %d's Cruiser sunked!\n", player + 1);
			}
			break;

		case SUBMARINE:  
			if (--sunkShip[player][3] == 0) {
				printf ("> Player %d's Submarine sunked!\n", player + 1);

				/* Write to battleship.log */
				fprintf (stream, "Player %d's Submarine sunked!\n", player + 1);
			}
			break;

		case DESTROYER:  
			if (--sunkShip[player][4] == 0) {
				printf ("> Player %d's Destroyer sunked!\n", player + 1);

				/* Write to battleship.log */
				fprintf (stream, "Player %d's Destroyer sunked!\n", player + 1);
			}
			break;
	}
}

Boolean isValidLocation (Cell gameBoard[][COLS], Coordinate position, 
				         int direction, int length) {
	int i = length - 1;
	Boolean isValid = TRUE;

	for (i = 0; isValid && i < length; i++) {
		if (direction == HORIZONTAL) {
			if (gameBoard [position.row][position.column + i].symbol != WATER &&
				(position.column + i) < COLS)
				isValid = FALSE;
		} else { /* VERTICAL */
			if (gameBoard [position.row + i][position.column].symbol != WATER &&
				(position.row + i) < ROWS)
				isValid = FALSE;
		}
	}

	return isValid;
}

Boolean convertStringtoPosition (Coordinate position[], char *stringPosition, int length) {
	Boolean flag = TRUE;
	char temp = '\0';
	int i = 0, j = 0, k = 1;

	/* checks if length of input is good */
	if (strlen (stringPosition)/2 == length) {
		/* loops through the length of the ship */
		for (i = 0; i < length && flag; i++) {
			/* checks if each cell is a digit */
			if (isdigit (stringPosition[j]) && isdigit (stringPosition[k])) {
				position[i].row    = stringPosition[j] - '0';
				position[i].column = stringPosition[k] - '0'; 

				printf ("r = %d, c = %d\n", position[i].row, position[i].column);

				j += 2;
				k += 2;
			} else {
				flag = FALSE;
			}
		}
	} else {
		flag = FALSE;
	}

	return flag;
}

Boolean isWinner (Stats players[], int player) {
	Boolean isWin = FALSE;

	if (players[player].numHits == 17) 
		isWin = TRUE;

	return isWin;
}

Coordinate generatePosition (int direction, int length) {
	Coordinate position;

	if (direction == HORIZONTAL) {
		position.row    = getRandomNumber (0, ROWS);
		position.column = getRandomNumber (0, COLS - length);
	} else { /* VERTICAL */
		position.row    = getRandomNumber (0, ROWS - length);
		position.column = getRandomNumber (0, COLS);
	}

	return position;
}

Coordinate getTarget (void) {
	Coordinate target;

	fflush (stdin);

	printf ("> Enter Target: ");
	scanf ("%d %d", &target.row, &target.column);

	return target;
}

Coordinate getTargetAI (Cell gameBoard [][COLS]) {
	Coordinate target;

	/** NEEDS TO BE IMPLEMENTED **/

	return target;
}

short checkShot (Cell gameBoard[][COLS], Coordinate target) {
	int hit = -2;

	switch (gameBoard[target.row][target.column].symbol) {
		/* miss */ 
		case WATER: 
			hit = 0;
			break;

		/* hit */
		case CARRIER: 
		case BATTLESHIP:
		case CRUISER:
		case SUBMARINE:
		case DESTROYER:
			hit = 1;
			break;

		case HIT:
		case MISS:
		default:
			hit = -1;
			break;
	}	

	return hit;
}

int getRandomNumber (int lowest, int highest) {
	if (lowest == 0)
		return rand () % ++highest;
	
	if (lowest > 0)
		return rand () % ++highest + lowest;
}