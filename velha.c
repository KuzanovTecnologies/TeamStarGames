// tictactoe.c
// Simple Tic-Tac-Toe game (console), English messages.
// Compile: gcc -std=c11 -Wall -Wextra -pedantic -o tictactoe tictactoe.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#ifdef _WIN32
  #include <windows.h>
#endif

/* Clear the console screen in a cross-platform way.
   On Unix-like systems we emit ANSI escape codes.
   On Windows we call system("cls") (works in standard cmd).
*/
static void clear_screen(void) {
#ifdef _WIN32
    /* Use system("cls") for Windows console; it's the simplest portable option. */
    system("cls");
#else
    /* ANSI escape to clear screen and move cursor to top-left. Works in most terminals. */
    printf("\x1b[2J\x1b[H");
    fflush(stdout);
#endif
}

/* Draw the board */
void drawBoard(char board[3][3]) {
    putchar('\n');
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            printf(" %c ", board[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("---+---+---\n");
    }
    putchar('\n');
}

/* Try to make a move:
   pos is 1..9, player is 'X' or 'O'.
   Returns 1 if move succeeded, 0 otherwise.
*/
int makeMove(char board[3][3], int pos, char player) {
    if (pos < 1 || pos > 9) return 0;
    int row = (pos - 1) / 3;
    int col = (pos - 1) % 3;
    if (board[row][col] == 'X' || board[row][col] == 'O') return 0;
    board[row][col] = player;
    return 1;
}

/* Check for a win. Returns 1 if someone has won, 0 otherwise. */
int checkWin(char board[3][3]) {
    /* Rows */
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) return 1;
    }
    /* Columns */
    for (int i = 0; i < 3; ++i) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) return 1;
    }
    /* Diagonals */
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) return 1;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) return 1;

    return 0;
}

/* Return 1 if board is full, 0 otherwise */
int boardFull(char board[3][3]) {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return 0;
    return 1;
}

/* Read an integer from stdin safely. Returns 1 on success and stores value in *out.
   Returns 0 on parse error.
*/
int readInt(const char *prompt, int *out) {
    char buf[128];
    char *endptr;
    long val;

    if (prompt) {
        printf("%s", prompt);
        fflush(stdout);
    }

    if (!fgets(buf, sizeof(buf), stdin)) return 0;

    /* Remove trailing newline */
    size_t len = strlen(buf);
    if (len > 0 && buf[len-1] == '\n') buf[len-1] = '\0';

    errno = 0;
    val = strtol(buf, &endptr, 10);

    /* Basic validation: some digits present, entire string consumed, within int range. */
    if (endptr == buf) return 0; /* no conversion */
    while (isspace((unsigned char)*endptr)) endptr++;
    if (*endptr != '\0') return 0; /* extra characters */
    if (errno == ERANGE) return 0;

    *out = (int)val;
    return 1;
}

int main(void) {
    /* Initialize board with numbers 1..9 so player sees positions */
    char board[3][3] = {
        {'1','2','3'},
        {'4','5','6'},
        {'7','8','9'}
    };

    int gameOver = 0;
    char currentPlayer = 'X';

    while (!gameOver) {
        clear_screen();
        drawBoard(board);

        /* Prompt loop: keep asking until a valid move is made */
        int pos;
        int ok;
        while (1) {
            char prompt[64];
            snprintf(prompt, sizeof(prompt), "Player %c, choose a position (1-9): ", currentPlayer);
            if (!readInt(prompt, &pos)) {
                printf("Invalid input. Please enter a number between 1 and 9.\n");
                continue;
            }
            ok = makeMove(board, pos, currentPlayer);
            if (!ok) {
                printf("That position is invalid or already taken. Try again.\n");
                continue;
            }
            break; /* valid move made */
        }

        /* After a valid move, check for win or draw */
        if (checkWin(board)) {
            clear_screen();
            drawBoard(board);
            printf("Player %c wins! Congratulations!\n", currentPlayer);
            gameOver = 1;
        } else if (boardFull(board)) {
            clear_screen();
            drawBoard(board);
            printf("It's a draw!\n");
            gameOver = 1;
        } else {
            /* switch player and continue */
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }

    /* Wait for the user to press Enter before exiting */
    printf("Press Enter to exit...");
    fflush(stdout);
    /* consume leftover input until newline if any, then wait */
    char buf[4];
    fgets(buf, sizeof(buf), stdin);

    return 0;
}
