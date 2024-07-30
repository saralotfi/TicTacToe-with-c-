#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

class TicTacToe {
public:
    TicTacToe() {
        initializeBoard();
    }

    void playTurn() {
        currentPlayer = 'X';
        int row = 0, col = 0;
        while (!isBoardFull()) {
            clearScreen();
            draw(row, col); 

            if (!takePlayerTurn(row,col)) {
                continue;
            }

            if (isWin(currentPlayer)) {
                clearScreen();
                draw(row, col);
                cout << currentPlayer << " is win!" << endl;
                return; 
            }

            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X'; 
        }

        clearScreen();
        draw(row, col);
        cout << "equal" << endl;
    }

private:
    char board[3][3];
    char currentPlayer;

    void initializeBoard() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                board[i][j] = '-'; 
            }
        }
    }

 void draw(int cursorRow, int cursorCol) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (i == cursorRow && j == cursorCol) {
                    cout << '[' << board[i][j] << "] ";
                } else {
                    cout << ' ' << board[i][j] << "  "; 
                }
            }
            cout << endl;
        }
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
     bool takePlayerTurn(int &row, int &col) {
        while (true) {
            int key = _getch(); 
            if (key == 224) { 
                key = _getch(); 
                switch (key) {
                    case 72:
                        moveCursorRow(row, -1);
                        break;
                    case 80: 
                        moveCursorRow(row, 1);
                        break;
                    case 75: 
                        col = (col > 0) ? col - 1 : 2; 
                        break;
                    case 77: 
                        col = (col < 2) ? col + 1 : 0; 
                        break;
                }
            } else if (key == 13) {
                if (isValidMove(row, col)) {
                    board[row][col] = currentPlayer; 
                    return true;
                } else {
                    cout << "Invalid move, please try again." << endl;
                    return false;
                }
            }
        }
    }


    bool isValidMove(int row, int col) {
        if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == '-') {
            return true;
        } else {
            return false;
        }
    }

    void clearScreen() {
        system("cls");
    }
};
int main() {
    TicTacToe game;
    game.playTurn();
    return 0;
}




