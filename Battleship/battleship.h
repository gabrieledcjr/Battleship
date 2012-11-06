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
#include <string.h>
#include <ctype.h>

/**
 * CONSTANT MACROS
 */

#define ROWS 10
#define COLS 10

#define LOG_FILE_NAME "battleship.log"

#define NUM_OF_SHIPS  5

#define HORIZONTAL    0
#define VERTICAL      1
#define PLAYER_ONE    0
#define PLAYER_TWO    2


#define WATER         '~'
#define HIT           '*'
#define MISS          'm'

#define CARRIER       'c'
#define BATTLESHIP    'b'
#define CRUISER       'r'
#define SUBMARINE     's'
#define DESTROYER     'd'

/**
 * ENUMERATED TYPES
 */

typedef enum {
	FALSE, TRUE
} Boolean;

typedef enum {
	CARRIER_L    = 5, 
	BATTLESHIP_L = 4,
	CRUISER_L    = 3, 
	SUBMARINE_L  = 3,
	DESTROYER_L  = 2
} ShipType;

/**
 * STRUCT TYPES
 */

typedef struct watercraft {
	char   symbol;
	short  length;
	char   *name;
} WaterCraft;

typedef struct stats {
	int        numHits;
	int        numMisses;
	int        totalShots;
	double     hitMissRatio;
} Stats;

typedef struct coordinate {
	int        row;
	int        column;
} Coordinate;

typedef struct cell {
	char       symbol; /* (~) water, (*) hit, (m) miss, (c) carrier, (b) battleship, (r) cruiser, (s) submarine, (d) destroyer */
	Coordinate position;
} Cell;

/**
 * FUNCTION PROTOTYPES
 */

void         welcomeScreen                  (void);
void         initializeGameBoard            (Cell gameBoard[][COLS]);
void         printGameBoard                 (Cell gameBoard [][COLS]);

void         putShipOnGameBoard             (Cell gameBoard[][COLS], WaterCraft ship, Coordinate position, int direction);
void         manuallyPlaceShipsOnGameBoard  (Cell gameBoard[][COLS], WaterCraft ship[]);
void         randomlyPlaceShipsOnGameBoard  (Cell gameBoard[][COLS], WaterCraft ship[]);
void         updateGameBoard                (Cell gameBoard[][COLS], Coordinate target);
void         checkSunkShip                  (short sunkShip[][NUM_OF_SHIPS], short player, char shipSymbol, FILE *stream);
Boolean      isValidLocation                (Cell gameBoard[][COLS], Coordinate position, int direction, int length);
Boolean      convertStringtoPosition        (Coordinate position[], char *stringPosition, int length);
Boolean      isWinner                       (Stats players[], int player);
Coordinate   generatePosition               (int direction, int length);
Coordinate   getTarget                      (void);
Coordinate   getTargetAI                    (Cell gameBoard [][COLS]);

short        checkShot                      (Cell gameBoard[][COLS], Coordinate target);
int          getRandomNumber                (int lowest, int highest);

#endif