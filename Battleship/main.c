/*==============================================================================
 | Filename: main.c                                                      
 | Programmer: Gabriel V. de a Cruz Jr.                                  
 | Class: CptS 121, Fall 2012 ; Lab Section 7                            
 | Programming Assignment 4: Basic Game of Battleship                    
 | Date: October 6, 2012                                                 
 +------------------------------------------------------------------------------                                                                       
 | Description: This program simulates the game of Battleship. The game will be 
 |              completely text-based. Battleship is a two player Navy game. 
 |              The objective of the game is to sink all ships in your enemy's 
 |              fleet. The Player to sink his/her enemy's fleet first wins. Both 
 |              players' fleets consist of 5 ships that are hidden from the 
 |              enemy. Each ship may be differentiated by its "size" (besides 
 |              the Cruiser and Submarine) or number of cells it expands on the 
 |              game board. The Carrier has 5 cells, Battleship has 4 cells, 
 |              Cruiser has 3 cells, Submarine has 3 cells, and the Destroyer 
 |              has 2 cells.                               
 ==============================================================================*/

#include "battleship.h"

int main (void)
{
	int i = 0;   // counters

	/**
	 * Two boards exist within the game. Hint: each board should be 
	 * implemented as a 2-dimensional array. Each 2-dimensional array 
	 * should be 10 X 10. One represents Player1's board and one represents 
	 * Player2's board.
	 */
	Cell playerOneGameBoard[ROWS][COLS];
	Cell playerTwoGameBoard[ROWS][COLS];

	WaterCraft ship[NUM_OF_SHIPS] = {{'c', CARRIER, "carrier"}, {'b', BATTLESHIP, "battleship"}, 
	                                 {'r', CRUISER, "cruiser"}, {'s', SUBMARINE, "submarine"}, 
	                                 {'d', DESTROYER, "destroyer"}};

	short player = 0; // 0 -> player1, 1 -> player2
	int option = 0;
	
	FILE *outStream = NULL;

	outStream = fopen (LOG_FILE_NAME, "w");

	srand ((unsigned int) time (NULL));

	/**
	 * Each Player's game board should be initialized to all '~' indicating
	 * no ships have been placed on either board.
	 */
	initializeGameBoard (playerOneGameBoard, ROWS, COLS);
	initializeGameBoard (playerTwoGameBoard, ROWS, COLS);

	printGameBoard (playerOneGameBoard, ROWS, COLS);
	getch ();

	/**
	 * Both players' fleets consist of 5 ships that are hidden from the enemy. 
	 * Each ship may be differentiated by its "size" (besides the Cruiser and 
	 * Submarine) or number of cells it expands on the game board. 
	 *      The Carrier has 5 cells, 
	 *      Battleship has 4 cells, 
	 *      Cruiser has 3 cells, 
	 *      Submarine has 3 cells, and 
	 *      the Destroyer has 2 cells. 
	 */

	/**
	 * The program should be built such that the user is Player1 and the 
	 * computer is Player2. 
	 */



	/**
	 * Before the game starts, Player1 should have the option to either 
	 * manually place each of the 5 ships in his/her fleet or to have them 
	 * randomly placed on the board. If Player1 decides to place the ships 
	 * manually, then he/she should be prompted to place the Carrier first, 
	 * Battleship second, Cruiser third, Submarine fourth, and the Destroyer 
	 * last. 
	 */
	printf ("PLAYER 1\n");
	printf ("1: Manually\n");
	printf ("2: Randomly\n");
	printf ("Enter Option: ");
	scanf ("%d", &option);
	
	switch (option) {
		case 1: manuallyPlaceShipsOnGameBoard (playerOneGameBoard, ship);
	            break;
		case 2: randomlyPlaceShipsOnGameBoard (playerOneGameBoard, ship);
				break;
	}

	printGameBoard (playerOneGameBoard, ROWS, COLS);

	/**
	 * Note that ships cannot be placed diagonally on the board, they can 
	 * only be placed vertically or horizontally. You program must check to 
	 * see if the user tries to place a ship outside the boundaries of the 
	 * board or on top of a ship that has already been placed. Each cell on 
	 * the board that contains part of the ship must be indicated by 'c' for 
	 * Carrier, 'b' for Battleship, 'r' for Cruiser, 's' for Submarine, or 
	 * 'd' for Destroyer.
	 */

	/**
	 * Player2's ships must be randomly placed. Note that the placement of 
	 * Player2's ships must be unknown. Thus, Player2's board will only 
	 * display '~' in each cell after the placement of each ship.
	 */
	printf ("PLAYER 2\n");
	randomlyPlaceShipsOnGameBoard (playerTwoGameBoard, ship);
	printGameBoard (playerTwoGameBoard, ROWS, COLS);

	/**
	 * The program should randomly select Player1 or Player2 to go first.
	 */
	player = getRandomNumber (0, 1);

	/**
	 * Once it has been decided on which player goes first, the game starts. 
	 * Whenever it's Player1's turn, a prompt should be displayed asking for 
	 * a position to target (specifying where to "shoot") on the enemy's 
	 * (Player2's) board (2-dimensional array). The position should be 
	 * specified in terms of a row and a column on the board. The row and 
	 * column should always be displayed along with the board. If the 
	 * position specified happens to hit a ship, then a '*' should replace 
	 * the '-' on Player2's board. If the positioned specified misses any 
	 * one of the ships in the fleet, then a 'm' should replace the '-' on 
	 * Player2's board. Note that from turn-to-turn each player should NOT 
	 * be allowed to enter the same position. Also, between turns clear the 
	 * screen (system("cls")). In one turn, a player can only take one shot 
	 * at the enemy's (other player's) fleet. When Player2 takes a shot at 
	 * Player1's board, each hit should be specified with a '*' and each 
	 * miss with a 'm' on Player1's board. The game is over win Player1 or 
	 * Player2 has sunk all of the ships in the fleet of the enemy. 
	 */

	/**
	 * For each move made by Player1 and Player2, the results should be 
	 * echoed to a file called "battleship.log". In this file, you should 
	 * log the targeted position by each player on each move and whether it 
	 * was a hit on one of the ships in the fleet. Also, if one of the ships 
	 * happens to sink, then note this in the log file. For more information 
	 * about the rules of Battleship visit: Rules of Battleship. 
	 */

	/**
	 * At the end of the game, Player1's and Player2's statistics should be 
	 * written to "battleship.log". The stats include total number of hits, 
	 * total number of misses, total number of shots, hits to misses ratio 
	 * (as a percentage), and won or lost the game. Note that the statistics 
	 * should be placed into a structure called Stats. You need two variables 
	 * of type Stats, one for Player1 and one for Player2. Once the game has 
	 * ended you should write the contents of each struct variable to the 
	 * "battleship.log" file.
	 */

	welcomeScreen ();


	fclose (outStream);
	return 0;
}