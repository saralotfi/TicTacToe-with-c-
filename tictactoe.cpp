#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

const int UP_ARROW = 72;
const int DOWN_ARROW = 80;
const int LEFT_ARROW = 75;
const int RIGHT_ARROW = 77;

class TicTacToe {
public:
    TicTacToe() {
        initializeBoard();
    }

    void playGame() {
        currentPlayer = 'X';
        int row = 0, col = 0;
        bool gameWon = false;
        while (!isBoardFull& !gameWon()) {
            clearScreen();
            draw(row, col,gameWon); 

            if (!PlayerTurn(row,col)) {
                continue;
            }

            if (isWin(currentPlayer)) {
                gameWon = true;
                clearScreen();
                draw(row, col);
                cout << currentPlayer << " is win!" << endl;
                
                return; 
            }

            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X'; 
        }

        clearScreen();
        draw(row, col,gameWon);
        cout << "equal" << endl;
    }

    if (!gameWon) {
        clearScreen();
        drawBoard(row, col, gameWon);
        cout << "equal" << endl;
        }
}

private:
    char board[3][3];
    char currentPlayer;

    void initializeBoard() {
        for (int i = 0; i < 3;i++) {
            for (int j = 0; j < 3;j++) {
                board[i][j] = '-'; 
            }
        }
    }

     void drawCell(int i, int j) {
        cout << ' ' << board[i][j] << ' ';
    }

    void drawBoard(int cursorRow, int cursorCol, bool gameWon) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                setColorForCell(i, j, cursorRow, cursorCol, gameWon);
                drawCell(i, j);
            }
            cout << endl;
        }

        resetColor();
        cout << endl;
    }
    bool isBoardFull() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == '-') {
                    return false; 
                }
            }
        }
        return true; 
    }

    bool allEqual(const char arr[], char player) {
        for (int i = 0; i < 3; ++i) {
            if (arr[i] != player) {
                return false;
            }
        }
        return true;
    }

    void getColumn(int col, char arr[]) {
        for (int i = 0; i < 3; ++i) {
            arr[i] = board[i][col];
        }
    }

    bool checkRows(char player) {
        for (int i = 0; i < 3; ++i) {
            if (allEqual(board[i], player)) {
                return true;
            }
        }
        return false;
    }

    bool checkColumns(char player) {
        for (int col = 0; col < 3; ++col) {
            char column[3];
            getColumn(col, column);
            if (allEqual(column, player)) {
                return true;
            }
        }
        return false;
    }

    bool checkDiagonals(char player) {
        char mainDiagonal[3];
        char antiDiagonal[3];

        for (int i = 0; i < 3; ++i) {
            mainDiagonal[i] = board[i][i];
            antiDiagonal[i] = board[i][2 - i];
        }

        return allEqual(mainDiagonal, player) || allEqual(antiDiagonal, player);
    }

    bool isWin(char player) {
        return checkRows(player) || checkColumns(player) || checkDiagonals(player);
    }
    void moveCursorRow(int &row, int direction) {
        if (direction == -1) {
            row = (row > 0) ? row - 1 : 2; 
        } else {
            row = (row < 2) ? row + 1 : 0; 
        }
    }
     void moveCursorCol(int &col, int direction) {
        if (direction == -1) {
            col = (col > 0) ? col - 1 : 2; 
        } else {
            col = (col < 2) ? col + 1 : 0;
        }
    }
    bool PlayerTurn(int& row, int& col) {
    while (true) {
        if (_kbhit()) { 
            int key = _getch();
            cout << "Key pressed: " << key << endl;
            if (key == 224) {
                key = _getch();
                cout << "Arrow key detected: " << key << endl;
                switch (key) {
                    case UP_ARROW:
                        moveCursorRow(row, -1);
                        break;
                    case DOWN_ARROW:
                        moveCursorRow(row, 1);
                        break;
                    case LEFT_ARROW:
                        moveCursorCol(col, -1);
                        break;
                    case RIGHT_ARROW:
                        moveCursorCol(col, 1);
                        break;
                }
            } else if (key == 13) { 
                cout << "Enter key pressed. Checking move validity..." << endl;
                if (isValidMove(row, col)) {
                    board[row][col] = currentPlayer;
                    cout << "Move made at (" << row << ", " << col << ") by " << currentPlayer << endl;
                    return true;
                } else {
                    cout << "Invalid move at (" << row << ", " << col << "). Please try again." << endl;
                    return false;
                }
            }
            clearScreen();
            draw(row, col);
        }
    }
}

     bool isInSideTable(int row, int col) {
        return (row >= 0 && row < 3 && col >= 0 && col < 3);
    }
     bool isCellEmpty(int row, int col) {
        return (board[row][col] == '-');
     }
    
     bool isValidMove(int row, int col) {
        return isInSideTable(row, col) && isCellEmpty(row, col);
    }

    void clearScreen() {
        system("cls");
    }
 };
int main() {
    TicTacToe game;
    game.playGame();
    return 0;
}



