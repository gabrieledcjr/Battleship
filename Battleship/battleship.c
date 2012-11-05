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
	printf ("Welcome Screen...\n");
}

void initializeGameBoard (Cell gameBoard[][COLS], int rows, int cols) {
	int i = 0, j = 0;

	for (i = 0; i < ROWS; i++)
		for (j = 0; j < COLS; j++) {
			gameBoard[i][j].symbol          = WATER;
			gameBoard[i][j].position.row    = i;
			gameBoard[i][j].position.column = j;
		}
}

void printGameBoard (Cell gameBoard [][COLS], int rows, int cols) {
	int i = 0, j = 0;

	printf ("  0 1 2 3 4 5 6 7 8 9\n");

	for (i = 0; i < rows; i++) {
		printf ("%d ", i);

		for (j = 0; j < cols; j++) {
			printf ("%c ", gameBoard [i][j].symbol);
		}
		
		putchar ('\n');
	}
}

Coordinate generatePosition (int direction, int length) {
	Coordinate position;

	if (direction == HORIZONTAL) {
		position.row    = getRandomNumber (0, ROWS);
		position.column = getRandomNumber (0, COLS - length);
	} else { // VERTICAL
		position.row    = getRandomNumber (0, ROWS - length);
		position.column = getRandomNumber (0, COLS);
	}

	return position;
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
		} else { // VERTICAL
			if (gameBoard [position.row + i][position.column].symbol != WATER &&
				(position.row + i) < ROWS)
				isValid = FALSE;
		}
	}

	return isValid;
}

void putShipOnGameBoard (Cell gameBoard[][COLS], WaterCraft ship, 
	                     Coordinate position, int direction) {
	int i = ship.length - 1;

	for (i = 0; i < ship.length; i++) {
		if (direction == HORIZONTAL) 
			gameBoard [position.row][position.column + i].symbol = ship.symbol;
		else // VERTICAL
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
			printf ("Enter the %d cells to place the %s across:\n", ship[i].length, ship[i].name);
			scanf ("%s", stringPosition);

			// convertStringtoPosition returns false if unsuccessful
			if (convertStringtoPosition (position, stringPosition, ship[i].length)) {
				isValid = TRUE;
				for (j = 0; j < ship[i].length; j++) {
					if (gameBoard[position[j].row][position[j].column].symbol == WATER) {
						gameBoard[position[j].row][position[j].column].symbol = ship[i].symbol;
					} else {
						isValid = FALSE;
						printf ("INVALID\n");
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
				printf ("INVALID!\n");
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
			// 0 -> horizontal, 1 -> vertical
			direction = getRandomNumber (0, 1);
			position = generatePosition (direction, ship[i].length);

			if (isValidLocation (gameBoard, position, direction, ship[i].length)) break;
		}

		putShipOnGameBoard (gameBoard, ship[i], position, direction);
	}
}

Boolean convertStringtoPosition (Coordinate position[], char *stringPosition, int length) {
	Boolean flag = TRUE;
	char temp = '\0';
	int i = 0, j = 0, k = 1;

	// checks if length of input is good
	if (strlen (stringPosition)/2 == length) {
		// loops through the length of the ship
		for (i = 0; i < length && flag; i++) {
			// checks if each cell is a digit
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

/**
 * UTILITY FUNCTIONS
 */
int getRandomNumber (int lowest, int highest) {
	if (lowest == 0)
		return rand () % ++highest;
	
	if (lowest > 0)
		return rand () % ++highest + lowest;
}