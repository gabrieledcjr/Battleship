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
	/**
	 * Two boards exist within the game. Hint: each board should be 
	 * implemented as a 2-dimensional array. Each 2-dimensional array 
	 * should be 10 X 10. One represents Player1's board and one represents 
	 * Player2's board.
	 */
	Stats players[2] = {{0, 0, 0, 0.0}, {0, 0, 0, 0.0}};

	Cell playerOneGameBoard[ROWS][COLS];
	Cell playerTwoGameBoard[ROWS][COLS];

	Coordinate target;

	WaterCraft ship[NUM_OF_SHIPS] = {{'c', 5, "Carrier"}, 
	                                 {'b', 4, "Battleship"}, 
	                                 {'r', 3, "Cruiser"}, 
	                                 {'s', 3, "Submarine"}, 
	                                 {'d', 2, "Destroyer"}};

	char shipSymbol = '\0';
	short sunkShip[2][NUM_OF_SHIPS] = {{5, 4, 3, 3, 2}, 
	                                   {5, 4, 3, 3, 2}};
	short player = 0; // 0 -> player1, 1 -> player2
	short shot = 0;
	int option = 0;
	
	FILE *outStream = NULL;

	outStream = fopen (LOG_FILE_NAME, "w");

	srand ((unsigned int) time (NULL));

	/**
	 * Print welcome screen
	 */
	welcomeScreen ();
	printf ("> Hit <ENTER> to start the game!");
	getch ();
	system ("cls");

	/**
	 * Each Player's game board should be initialized to all '~' indicating
	 * no ships have been placed on either board.
	 */
	initializeGameBoard (playerOneGameBoard);
	initializeGameBoard (playerTwoGameBoard);

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
	printf ("> Please select from the following menu:\n");
	printf ("> 1: Manually\n");
	printf ("> 2: Randomly\n");
	printf ("> Enter Option: ");
	scanf ("%d", &option);
	
	switch (option) {
		case 1: manuallyPlaceShipsOnGameBoard (playerOneGameBoard, ship);
	            break;
		case 2: randomlyPlaceShipsOnGameBoard (playerOneGameBoard, ship);
				break;
	}

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
	randomlyPlaceShipsOnGameBoard (playerTwoGameBoard, ship);
	printf ("> Player 2 (Computer's) board has been generated.\n");

	/**
	 * The program should randomly select Player1 or Player2 to go first.
	 */
	player = getRandomNumber (0, 1);
	player = 0;
	printf ("> Player %d has been randomly selected to go first.\n", player + 1);

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
	 * happens to sink, then note this in the log file. 
	 */

	while (TRUE) {

		/* Write to battleship.log */
		fprintf (outStream, "Player %d's turn.\n", player + 1);

		switch (player) {
			case PLAYER_ONE: 
				/* Prompts user to enter target */
				printf ("> Player 2's Board:\n");
				printGameBoard (playerTwoGameBoard);

				do {
					target = getTarget (); 
					shot = checkShot (playerTwoGameBoard, target);
					
					if (shot == -1) 
						printf ("> Try inputting another target!\n");

				} while (shot == -1);

				shipSymbol = playerTwoGameBoard[target.row][target.column].symbol;
				break;

			case PLAYER_TWO: 
				printf ("> Player 1's Board:\n");
				printGameBoard (playerOneGameBoard);

				target = getTargetAI (playerOneGameBoard); 
				shot = checkShot (playerTwoGameBoard, target);
				shipSymbol = playerTwoGameBoard[target.row][target.column].symbol;
				break;
		}

		/* Prompts player if it's a hit or miss */
		if (shot == 1) { /* HIT */
			printf ("> %d, %d is a hit!\n", target.row, target.column);

			/* Write to battleship.log */
			fprintf (outStream, "%d, %d is a hit!\n", target.row, target.column);

			players[player].numHits++;
			checkSunkShip (sunkShip, !player, shipSymbol, outStream);
		} else {        /* MISS */
			printf ("> %d, %d is a miss!\n", target.row, target.column);

			/* Write to battleship.log */
			fprintf (outStream, "%d, %d is a miss!\n", target.row, target.column);

			players[player].numMisses++;
		}
		
		if (player) /* If Player 1 then update player 2's gameboard */
			updateGameBoard (playerTwoGameBoard, target);
		else        /* If Player 2 then update player 1's gameboard */   
			updateGameBoard (playerOneGameBoard, target);

		if (isWinner (players, player)) {
			printf ("\n> Player %d wins!\n", player + 1);

			/* Write to battleship.log */
			fprintf (outStream, "\n>>>>> Player %d wins! <<<<<\n", player + 1);
			break;
		}

		printf ("> Hit <ENTER> to continue!");
		getch();

		/* switches from player 1 to player 2 */
		player = !player;	

		system ("cls");
	}

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
	fprintf (outStream, "+===================================================\n");
	fprintf (outStream, "|                    PLAYER STATS                   \n");
	fprintf (outStream, "+---------------------------------------------------\n");
	fprintf (outStream, "| PLAYER 1 : %d hits                                \n", players[0].numHits);
	fprintf (outStream, "|            %d misses                              \n", players[0].numMisses);
	fprintf (outStream, "|            %d total shots                         \n", players[0].totalShots);
	fprintf (outStream, "|            %.2lf%% hit/miss ratio                 \n", (players[0].numHits/players[0].numMisses) * 100);
	fprintf (outStream, "| PLAYER 1 : %d hits                                \n", players[1].numHits);
	fprintf (outStream, "|            %d misses                              \n", players[1].numMisses);
	fprintf (outStream, "|            %d total shots                         \n", players[1].totalShots);
	fprintf (outStream, "|            %.2lf%% hit/miss ratio                 \n", (players[1].numHits/players[1].numMisses) * 100);
	fprintf (outStream, "+===================================================");

	fclose (outStream);
	return 0;
}