/*==============================================================================
 | Filename: battleship.h                                                    
 | Programmer: Gabriel V. de a Cruz Jr.                                  
 | Class: CptS 121, Fall 2012 ; Lab Section 7                            
 | Programming Assignment 4: Basic Game of Battleship                    
 | Date: October 6, 2012                                                 
 +------------------------------------------------------------------------------                                                                       
 | Description:                              
 ==============================================================================*/

#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 10
#define COLS 10

#define LOG_FILE_NAME "battleship.log"

#define NUM_OF_SHIPS 5

#define HORIZONTAL 0
#define VERTICAL   1

#define WATER '~'

typedef enum {
	FALSE, TRUE
} Boolean;

typedef enum {
	CARRIER = 5, BATTLESHIP = 4,
	CRUISER = 3, SUBMARINE = 3,
	DESTROYER = 2
} ShipType;

typedef struct stats {
	int numHits;
	int numMisses;
	int totalShots;
	double hitMissRatio;
} Stats;

typedef struct coordinate {
	int row;
	int column;
} Coordinate;

typedef struct cell {
	char symbol;
	Coordinate position;
} Cell;

typedef struct watercraft {
	char symbol;
	ShipType type;
} WaterCraft;

void welcomeScreen (void);
void initializeGameBoard (Cell gameBoard[][COLS], int rows, int cols);
void printGameBoard (Cell gameBoard [][COLS], int rows, int cols);

Coordinate generatePosition (int direction, int length);
Boolean isValidLocation (Cell gameBoard[][COLS], 
	                     Coordinate position, 
				         int direction, int length);
void putShipOnGameBoard (Cell gameBoard[][COLS], WaterCraft ship, 
	                     Coordinate position, int direction);

int getRandomNumber (int lowest, int highest);

#endif