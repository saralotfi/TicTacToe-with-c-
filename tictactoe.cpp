#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

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
        auto startTime = high_resolution_clock::now(); // ثبت زمان شروع بازی
        currentPlayer = 'X';
        int row = 0, col = 0;
        bool gameWon = false;

        while (!isBoardFull() && !gameWon) {
            clearScreen();
            drawBoard(row, col, gameWon);
            displayMenuHint();

            if (!PlayerTurn(row, col)) {
                continue;
            }

            if (isWin(currentPlayer)) {
                gameWon = true;
                clearScreen();
                drawBoard(row, col, gameWon);
                cout << currentPlayer << " wins!" << endl;
                saveGameHistory(std::string(1, currentPlayer) + " wins", startTime);
                return;
            }

            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }

        if (!gameWon) {
            clearScreen();
            drawBoard(row, col, gameWon);
            cout << "It's a draw!" << endl;
            saveGameHistory("Draw", startTime);
        }
    }

private:
    char board[3][3];
    char currentPlayer;
    int winCells[3][2];

    void initializeBoard() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[i][j] = '-';
            }
        }
    }

    void drawBoard(int cursorRow, int cursorCol, bool gameWon) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                setColorForCell(i, j, cursorRow, cursorCol, gameWon);
                if (i == cursorRow && j == cursorCol) {
                    cout << '[' << currentPlayer << "] ";
                } else {
                    drawCell(i, j);
                }
            }
            cout << endl;
        }

        resetColor();
        cout << endl;
    }

    void setColorForCell(int i, int j, int cursorRow, int cursorCol, bool gameWon) {
        if (gameWon && isWinCell(i, j)) {
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        } else if (gameWon && board[i][j] != '-' && !isWinCell(i, j)) {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        } else if (i == cursorRow && j == cursorCol) {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        } else {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
    }

    void drawCell(int i, int j) {
        cout << ' ' << board[i][j] << ' ';
    }

    void resetColor() {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
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
                for (int j = 0; j < 3; ++j) {
                    winCells[j][0] = i;
                    winCells[j][1] = j;
                }
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
                for (int i = 0; i < 3; ++i) {
                    winCells[i][0] = i;
                    winCells[i][1] = col;
                }
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

        if (allEqual(mainDiagonal, player)) {
            for (int i = 0; i < 3; ++i) {
                winCells[i][0] = i;
                winCells[i][1] = i;
            }
            return true;
        }

        if (allEqual(antiDiagonal, player)) {
            for (int i = 0; i < 3; ++i) {
                winCells[i][0] = i;
                winCells[i][1] = 2 - i;
            }
            return true;
        }

        return false;
    }

    bool isWin(char player) {
        return checkRows(player) || checkColumns(player) || checkDiagonals(player);
    }
    
    bool isWinCell(int row, int col) {
        for (int i = 0; i < 3; ++i) {
            if (winCells[i][0] == row && winCells[i][1] == col) {
                return true;
            }
        }
        return false;
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

                if (key == 'm') {
                    cout << "Menu key 'm' pressed" << endl;
                    showMenu();
                    clearScreen();
                    drawBoard(row, col, false);
                    displayMenuHint();
                    continue;
                } else if (key == 224) {
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
                drawBoard(row, col, false);
                displayMenuHint();
            }
        }
    }

    void showMenu() {
        int selectedOption = 0;
        const char* menuItems[3] = {"Exit", "Continue", "History"};
        int lastSelectedOption = -1;

        while (true) {
            if (selectedOption != lastSelectedOption) {
                clearScreen();
                lastSelectedOption = selectedOption;
                cout << "Menu:" << endl;

                for (int i = 0; i < 3; ++i) {
                    if (i == selectedOption) {
                        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                        cout << "> " << menuItems[i] << endl;
                        resetColor();
                    } else {
                        cout << "  " << menuItems[i] << endl;
                    }
                }
            }

            if (_kbhit()) {
                int key = _getch();
                if (key == 224) {
                    key = _getch();
                    if (key == UP_ARROW) {
                        selectedOption = (selectedOption > 0) ? selectedOption - 1 : 2;
                    } else if (key == DOWN_ARROW) {
                        selectedOption = (selectedOption < 2) ? selectedOption + 1 : 0;
                    }
                } else if (key == 13) {
                    if (selectedOption == 0) {
                        exit(0);
                    } else if (selectedOption == 1) {
                        return;
                    } else if (selectedOption == 2) {
                        showHistory();
                    }
                }
            }
        }
    }

    void displayMenuHint() {
        cout << "Press 'm' for menu." << endl;
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

    void saveGameHistory(const string& result, high_resolution_clock::time_point startTime) {
        ofstream historyFile("game_history.txt", ios::app);
        if (historyFile.is_open()) {
            auto endTime = high_resolution_clock::now();
            auto duration = duration_cast<seconds>(endTime - startTime).count();
            time_t now = time(0);
            char* dt = ctime(&now);
            historyFile << "Game Result: " << result << ", Duration: " << duration << " seconds at " << dt;
            historyFile.close();
        }
    }

    void showHistory() {
        ifstream historyFile("game_history.txt");
        if (historyFile.is_open()) {
            string line;
            clearScreen();
            cout << "Game History:" << endl;
            while (getline(historyFile, line)) {
                cout << line << endl;
            }
            historyFile.close();
            cout << endl << "Use the arrow keys to go to the menu";
            _getch(); 
            clearScreen();
        } 
        else {
            cout << "No history available." << endl;
            cout << "";
            _getch(); 
            clearScreen();
        }
    }
};

int main() {
    TicTacToe game;
    game.playGame();
    return 0;
}







