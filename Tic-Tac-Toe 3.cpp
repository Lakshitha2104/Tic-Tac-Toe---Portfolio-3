#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class TicTacToe {
private:
    vector<vector<char>> board;
    int gamesPlayed;
    int playerOneWins;
    int playerTwoWins;
    int ties;

public:
    TicTacToe() {
        board = vector<vector<char>>(3, vector<char>(3, ' '));
        gamesPlayed = 0;
        playerOneWins = 0;
        playerTwoWins = 0;
        ties = 0;
    }

    void printBoard() {
        cout << "\n";
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << " " << board[i][j] << " ";
                if (j < 2) cout << "|";
            }
            cout << "\n";
            if (i < 2) cout << "---+---+---\n";
        }
        cout << "\n";
    }

    bool isBoardFull() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') return false;
            }
        }
        return true;
    }

    bool checkWin(char player) {
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
                return true;
            if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
                return true;
        }
        if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
            return true;
        if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
            return true;
        return false;
    }

    void resetBoard() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[i][j] = ' ';
            }
        }
    }

    void playGame() {
        char currentPlayer = 'X';
        int move;
        bool gameWon = false;

        while (!gameWon && !isBoardFull()) {
            printBoard();  
            cout << "Player " << currentPlayer << "'s turn.\n";
            cout << "Enter a number (1-9) to place your mark: ";
            cin >> move;

            if (move >= 1 && move <= 9) {
                int row = (move - 1) / 3;
                int col = (move - 1) % 3;

                if (board[row][col] == ' ') {
                    board[row][col] = currentPlayer;

                    if (checkWin(currentPlayer)) {
                        gameWon = true;
                        if (currentPlayer == 'X') playerOneWins++;
                        else playerTwoWins++;
                    } else {
                        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
                    }
                } else {
                    cout << "That spot is already taken! Try again.\n";
                }
            } else {
                cout << "Invalid input! Please enter a number between 1 and 9.\n";
            }
        }

        if (!gameWon) {
            ties++;
        }

        gamesPlayed++;
        printBoard();  
    }

    void generateReport() {
        ofstream report("game_report.txt");
        if (report.is_open()) {
            report << "Game Session Report\n";
            report << "--------------------\n";
            report << "Total games played: " << gamesPlayed << "\n";
            report << "Player 1 (X) wins: " << playerOneWins << "\n";
            report << "Player 2 (O) wins: " << playerTwoWins << "\n";
            report << "Ties: " << ties << "\n";
            report.close();
            cout << "Game report saved to 'game_report.txt'.\n";
        } else {
            cout << "Error opening file for report.\n";
        }
    }
};

int main() {
    TicTacToe game;
    char playAgain;

    cout << "Welcome to Tic-Tac-Toe!\n";
    cout << "Player 1: X\nPlayer 2: O\n";
    cout << "Use the numbers 1-9 to select your move as shown below:\n";
    cout << "1 | 2 | 3\n";
    cout << "4 | 5 | 6\n";
    cout << "7 | 8 | 9\n";

    do {
        game.playGame(); 
        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;
        if (playAgain == 'y' || playAgain == 'Y') {
            game.resetBoard();  
        } else if (playAgain == 'n' || playAgain == 'N') {
            game.generateReport();  
        } else {
            cout << "Invalid input, exiting game.\n";
            game.generateReport();  
        }
    } while (playAgain == 'y' || playAgain == 'Y');  

    return 0;
}
