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
        while (!isBoardFull()) {
            draw(); 

            if (!takePlayerTurn()) {
                continue;
            }

            if (isWin(currentPlayer)) {
                draw();
                cout << currentPlayer << " is win!" << endl;
                return; 
            }

            clearScreen();
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X'; 
        }

        draw();
        cout << "It's a draw!" << endl;
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

    void draw() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cout << board[i][j] << ' ';
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

    bool takePlayerTurn() {
        int row, col;
        cout << currentPlayer << ", row? (0 , 2): ";
        cin >> row;
        cout << "col? (0 , 2): ";
        cin >> col;

        if (!cin) { 
            cin.clear(); 
            cout << "Enter valid numbers." << endl;
            return false;
        }

        if (isValidMove(row, col)) {
            board[row][col] = currentPlayer;
            return true;
        } else {
            cout << "Invalid input, please re-enter." << endl;
            return false; 
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




