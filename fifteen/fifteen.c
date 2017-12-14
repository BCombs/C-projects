/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// Location of the 0 (underscore) tile
int zeroRow = 0;
int zeroColumn = 0;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void swap(int i, int j);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{

    // Set the highest value
    int num = d*d - 1;
    
    // Fill the board
    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            board[i][j] = num;
            num--;
        }
    }
    
    // Set the initial position of the zero tile
    zeroRow = d - 1;
    zeroColumn = d - 1;
    
    // If the board has an uneven amount of playable numbers, swap values 1 and 2
    if(d % 2 == 0)
    {
        int tmp = board[d-1][d-2];
        board[d-1][d-2] = board[d-1][d-3];
        board[d-1][d-3] = tmp;
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // Draw the board to the screen
    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            // Print the value 0 as an underscore
            if(board[i][j] == 0)
            {
                printf("%2c  ", '_');
            }
            else
            {
                printf("%2i  ", board[i][j]);
            }
        }
        
        // Next row
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // Iterate through the board looking for the tile selected
    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            // If we found the tile the user selected
            if(board[i][j] == tile)
            {
                // If we are on the top row
                if(i == 0)
                {
                    // Check if the next tile down is the zero tile
                    if(board[i+1][j] == board[zeroRow][zeroColumn])
                    {
                        swap(i, j);
                        return true;
                    }
                }
                // If we are on the last row
                else if( i == d - 1)
                {
                    // Check if the tile above is the zero tile
                    if(board[i - 1][j] == board[zeroRow][zeroColumn])
                    {
                        swap(i, j);
                        return true;
                    }
                }
                // we are somewhere in the middle rows, check the tile above and below
                else if(board[i-1][j] == board[zeroRow][zeroColumn] || board[i+1][j] == board[zeroRow][zeroColumn])
                {
                    swap(i, j);
                    return true;
                }
                
                // Check the left and right of the selected tile
                // If we are on the far left
                if(j == 0)
                {
                    // Check the tile to the right
                    if(board[i][j+1] == board[zeroRow][zeroColumn])
                    {
                        swap(i, j);
                        return true;
                    }
                }
                // If we are on the far right of the board
                else if(j == d-1)
                {
                    // Check the tile to the left
                    if(board[i][j-1] == board[zeroRow][zeroColumn])
                    {
                        swap(i, j);
                        return true;
                    }
                }
                // We are somewhere in the middle, check left and right tiles
                else if(board[i][j-1] == board[zeroRow][zeroColumn] || board[i][j+1] == board[zeroRow][zeroColumn])
                {
                    swap(i, j);
                    return true;
                }
            }
        }
    }
    // An illegal tile was selected or the tile wasn't found
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // Hold the last value we looked at
    int last = 0;
    
    // Check if the current value is 1 more than the last value. If we reach the end, the user has won
    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            // Check if we have are on the very last tile and it is the zero tile
            if(i == d - 1 && j == d - 1)
            {
                if(board[i][j] == board[zeroRow][zeroColumn])
                {
                    // User has won
                    return true;
                }
            }
            
            // If the current tile isn't 1 more than the last tile
            if(board[i][j] - 1 != last)
            {
                // They are still out of order
                return false;
            }
        
            // Set the current tile to last and continue on
            last = board[i][j];
        }
    }
    
    // Something went wrong
    return false;
}

// Swap the values
void swap(int i, int j)
{
    int temp = board[i][j];
    board[i][j] = board[zeroRow][zeroColumn];
    board[zeroRow][zeroColumn] = temp;
    zeroRow = i;
    zeroColumn = j;
}
