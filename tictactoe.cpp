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

            if (!takePlayerTurn()) {
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
     bool takePlayerTurn(int &row, int &col) {
        while (true) {
            int key = _getch(); // دریافت ورودی کلید
            if (key == 224) { // کلیدهای جهت‌دار
                key = _getch(); // دریافت کد جهت‌دار
                switch (key) {
                    case 72: // کلید بالا
                        row = (row > 0) ? row - 1 : 2; // حرکت مکان‌نما به بالا
                        break;
                    case 80: // کلید پایین
                        row = (row < 2) ? row + 1 : 0; // حرکت مکان‌نما به پایین
                        break;
                    case 75: // کلید چپ
                        col = (col > 0) ? col - 1 : 2; // حرکت مکان‌نما به چپ
                        break;
                    case 77: // کلید راست
                        col = (col < 2) ? col + 1 : 0; // حرکت مکان‌نما به راست
                        break;
                }
            } else if (key == 13) { // کلید Enter
                if (isValidMove(row, col)) {
                    board[row][col] = currentPlayer; // گذاشتن علامت در خانه انتخاب شده
                    return true;
                } else {
                    cout << "Invalid move, please try again." << endl;
                    return false;
                }
            }
        }
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




