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
			gameBoard[i][j].symbol = WATER;
			gameBoard[i][j].position.row = i;
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
		position.row = getRandomNumber (0, ROWS);
		position.column = getRandomNumber (0, COLS - length + 1);
	} else { // VERTICAL
		position.row = getRandomNumber (0, ROWS - length + 1);
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
			if (gameBoard [position.row][position.column + i].symbol != WATER)
				isValid = FALSE;
		} else { // VERTICAL
			if (gameBoard [position.row + i][position.column].symbol != WATER)
				isValid = FALSE;
		}
	}

	return isValid;
}

void putShipOnGameBoard (Cell gameBoard[][COLS], WaterCraft ship, 
	                     Coordinate position, int direction) {
	int i = ship.type - 1;

	for (i = 0; i < ship.type; i++) {
		if (direction == HORIZONTAL) 
			gameBoard [position.row][position.column + i].symbol = ship.symbol;
		else // VERTICAL
			gameBoard [position.row + i][position.column].symbol = ship.symbol;
	}
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