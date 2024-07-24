#include <iostream>
#include <windows.h> 
using namespace std;

class TicTacToe {
public:
    TicTacToe() {
        initializeBoard();
    }

    void play() {
        char currentPlayer = 'X';
        int row, col;

        while (!isFull()) {
            draw();
            cout << "Player " << currentPlayer << ", enter row (0-2): ";
            cin >> row;
            cout << "Enter col (0-2): ";
            cin >> col;

            if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != '-') {
                cout << "Invalid input, please re-enter." << endl;
                continue;
            }

            board[row][col] = currentPlayer;
            if (isWin(currentPlayer)) {
                draw();
                cout << "Player " << currentPlayer << " wins!" << endl;
                return;
            }

            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';

            system("cls"); 
        }

        draw();
        cout << "It's a draw!" << endl;
    }

private:
    char board[3][3]; 

    void initializeBoard() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[i][j] = '-';
            }
        }
    }

    void draw() {
        cout << "Current board:" << endl;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << board[i][j] << ' ';
            }
            cout << endl;
        }
    }

    bool isFull() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '-')
                    return false;
            }
        }
        return true;
    }

    bool isWin(char player) {
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
                return true;
        }

        for (int j = 0; j < 3; j++) {
            if (board[0][j] == player && board[1][j] == player && board[2][j] == player)
                return true;
        }
        if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
            return true;
        if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
            return true;

        return false;
    }
};

int main() {
    TicTacToe game;
    game.play();
    return 0;
}
