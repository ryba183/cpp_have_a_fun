#include <iostream>
using namespace std;

char board[3][3] = {{'1','2','3'},{'4','5','6'},{'7','8','9'}};
char player = 'X';

void drawBoard() {
    cout << "Tic Tac Toe v1.0" << endl;
    cout << "-----------------" << endl << endl;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool placeMarker(int slot) {
    int row = (slot - 1) / 3;
    int col = (slot - 1) % 3;

    if (board[row][col] != 'X' && board[row][col] != 'O') {
        board[row][col] = player;
        return true;
    } else {
        return false;
    }
}

void switchPlayer() {
    if (player == 'X') {
        player = 'O';
    } else {
        player = 'X';
    }
}

char checkForWinner() {
    // Check for horizontal wins
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return board[i][0];
        }
    }

    // Check for vertical wins
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            return board[0][i];
        }
    }

    // Check for diagonal wins
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return board[0][0];
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return board[0][2];
    }

    return '/';
}

int main() {
    drawBoard();
    int choice;
    char winner;

    while (true) {
        cout << "Player " << player << " turn. Enter slot number: ";
        cin >> choice;

        if (choice < 1 || choice > 9) {
            cout << "Invalid input, try again!" << endl;
            continue;
        }

        if (!placeMarker(choice)) {
            cout << "That slot is already taken, try again!" << endl;
            continue;
        }

        drawBoard();

        winner = checkForWinner();

        if (winner == 'X' || winner == 'O') {
            cout << "Congratulations, player " << winner << " won the game!" << endl;
            break;
        } else if (winner == '/' && board[0][0] != '1' && board[0][1] != '2' && board[0][2] != '3' && board[1][0] != '4' && board[1][1] != '5' && board[1][2] != '6' && board[2][0] != '7' && board[2][1] != '8' && board[2][2] != '9') {
            cout << "The game is a tie!" << endl;
        }
    }
}