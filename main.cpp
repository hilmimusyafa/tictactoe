#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

/* ==========================  Structure ========================== */

// Board Structure

struct board {
    string chart[3][3] = {
        {" ", " ", " "},
        {" ", " ", " "},
        {" ", " ", " "},
    };
};

// User Structure

struct user {
    string stringValue; // Can be X or O
};

// Player Structure

struct player {
    user nowpPlay; // Current Player
};

// Main Screen

/* ========================== Screen ========================== */ 

int mainScreen() {
    cout << "======================================" << endl;
    cout << "          APLIKASI TIC TAC TOE        " << endl;
    cout << "  TUGAS BESAR KOMPLEKSITAS ALGORITMA  " << endl;
    cout << "======================================" << endl;
    cout << "Pilih menu bermain : " << endl;
    cout << "1. Bermain dengan Bot Sekuensial " << endl;
    cout << "2. Bermain denghan Bot " << endl;
    cout << "3. Bermain sesama manusia " << endl;
    cout << "0. Exit " << endl;

    return 0;
}

/* ==========================  Game Fucntion ========================== */ 

// Checkking if the board is filled or not

bool isFilled(board b, int locationX, int locationY) {
    return b.chart[locationX][locationY] != " ";
}

// Printing the board

void printBoard(board b) {
    for (int i = 0; i < 3; i++) {  // Loop through each row
        for (int j = 0; j < 3; j++) {  // Loop through each column
            if (j == 0) {
                cout << " "; 
            }
            cout << b.chart[i][j];
            if (j < 2) {
                cout << " | "; // Line devider for each column
            } 
        }
        cout << "\n"; // New line
        if (i < 2) {
            cout << "---+---+---\n";  // Line devider for each row
        }
    }
    cout << "\n";
}

// Checking if there's a winner

bool isWinner(board b, string player) {
    for (int i = 0; i < 3; i++) {
        // Horizontal Check
        if (b.chart[i][0] == player && b.chart[i][1] == player && b.chart[i][2] == player) {
            return true;
        }
        // Vertical Check
        if (b.chart[0][i] == player && b.chart[1][i] == player && b.chart[2][i] == player) {
            return true;
        }
    }
    // Diagonal Check
    if ((b.chart[0][0] == player && b.chart[1][1] == player && b.chart[2][2] == player) || (b.chart[0][2] == player && b.chart[1][1] == player && b.chart[2][0] == player)) {
        return true;
    }
    return false;
}

// Checking if the board is full or not

bool isFull(board b) {
    for (int i = 0; i < 3; i++) { 
        for (int j = 0; j < 3; j++) { 
            if (b.chart[i][j] == " ") { // Check if some cell is empty
                return false; 
            }
        }
    }
    return true; 
}

// Clearing the board

void clearBoard(board &b) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            b.chart[i][j] = " "; // Just clear the board
        }
    }
}

// Decising the player

void playDesicionMaker(string userInput, string &player1, string &player2) {
    if (userInput == "X") {
        player1 = "X";
        player2 = "O";
    } else if (userInput == "O") {
        player1 = "O";
        player2 = "X";
    }
}

/* ========================== Iterative Section ========================== */ 

// Iterative Engine
void IterativeEngine(board &b, string stringValue) {
    bool isDone = false;

    for (int chunkLocationX = 0; chunkLocationX < 3 && !isDone; chunkLocationX++) {
        for (int chunkLocationY = 0; chunkLocationY < 3 && !isDone; chunkLocationY++) {
            if (b.chart[chunkLocationX][chunkLocationY] == " ") {
                b.chart[chunkLocationX][chunkLocationY] = stringValue;
                isDone = true;
            }
        }
    }
}

/* ========================== Recursive Section ========================== */ 

// Evaluation Function for Minimax Algorithm

int evaluateBoardScoring(board &b, string botValue, string humanValue) {
    if (isWinner(b, botValue)) {
        return 10;
    } else if (isWinner(b, humanValue)) {
        return -10;
    } else {
        return 0;
    }
}

// Minimax Algorithm

int minimax(board &b, int depth, bool isMaximizing, string botValue, string humanValue) {
    // Evaluate Score for evaluation function
    int currentScore = evaluateBoardScoring(b, botValue, humanValue);

    // Base Case : if there's a winner or the board is full
    if (currentScore == 10 || currentScore == -10) {
        return currentScore - depth; 
    }
    if (isFull(b)) {
        return 0;
    }

    if (isMaximizing == true) {
        int bestScore = -1000;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (b.chart[i][j] == " ") { 
                    b.chart[i][j] = botValue; 
                    int score = minimax(b, depth + 1, false, botValue, humanValue);
                    b.chart[i][j] = " "; 
                    bestScore = max(bestScore, score);
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = 1000;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (b.chart[i][j] == " ") { 
                    b.chart[i][j] = humanValue; 
                    int score = minimax(b, depth + 1, true, botValue, humanValue);
                    b.chart[i][j] = " "; 
                    bestScore = min(bestScore, score);
                }
            }
        }
        return bestScore;
    }
}

// Recursive Engine

void recursiveEngine(board &b, string botValue, string humanValue) {
    int bestScore = -1000;
    int bestMoveX = -1, bestMoveY = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (b.chart[i][j] == " ") { 
                b.chart[i][j] = botValue; 
                int moveScore = minimax(b, 0, false, botValue, humanValue);
                b.chart[i][j] = " "; 

                if (moveScore > bestScore) { 
                    bestScore = moveScore;
                    bestMoveX = i;
                    bestMoveY = j;
                }
            }
        }
    }

    if (bestMoveX != -1 && bestMoveY != -1) {
        b.chart[bestMoveX][bestMoveY] = botValue;
    }
}

/* ========================== Play Section ========================== */

// Iterative Play

void playIterative(board &b) {
    string chunkChoose;
    user playerHuman, playerBot;
    player whoIs, tempPlay;
    int counter = 0;
    bool isPlayerWin = false, isBotWin = false, isLocationFilled;
    int chunkLocationX, chunkLocationY;

    cout << "Pilih anda ingin X atau O : ";
    cin >> chunkChoose;

    while (chunkChoose != "X" && chunkChoose != "O") {
        cout << "Tidak Valid! Pastikan anda memilih antara X atau O : ";
        cin >> chunkChoose;
    }

    playDesicionMaker(chunkChoose, playerHuman.stringValue, playerBot.stringValue);
    srand(time(0));
    whoIs.nowpPlay = (rand() % 2 == 0) ? playerHuman : playerBot; 

    while (!isPlayerWin && !isBotWin && !isFull(b)) {
        cout << endl;
        printBoard(b);
        if (whoIs.nowpPlay.stringValue == playerHuman.stringValue) {
            cout << "========== Giliran kamu ==========" << endl;

            cout << "Masukkan lokasi yang ingin diisi (X,Y) : ";
            cin >> chunkLocationX >> chunkLocationY;

            while (chunkLocationX < 1 || chunkLocationX > 3 || chunkLocationY < 1 || chunkLocationY > 3 || isFilled(b, chunkLocationX - 1, chunkLocationY - 1)) {
                cout << "Input tidak valid atau lokasi sudah terisi. Masukkan ulang (X,Y) (-3): ";
                cin >> chunkLocationX >> chunkLocationY;
            }

            b.chart[chunkLocationX - 1][chunkLocationY - 1] = whoIs.nowpPlay.stringValue;
            
            isPlayerWin = isWinner(b, whoIs.nowpPlay.stringValue);

            whoIs.nowpPlay = playerBot;  
        } else {
            cout << "========== Giliran Bot ==========" << endl;

            std::this_thread::sleep_for(std::chrono::seconds(1 + rand() % 4));
            
            cout << "Bot sedang berpikir !! " << endl;
            IterativeEngine(b, whoIs.nowpPlay.stringValue);

            isBotWin = isWinner(b, whoIs.nowpPlay.stringValue);

            whoIs.nowpPlay = playerHuman;
        }
    }

    printBoard(b);
    if (isPlayerWin){
        cout << "Selamat! Anda menang!\n";
    } else if (isBotWin) {
        cout << "Bot menang! Coba lagi.\n";
    } else {
        cout << "Permainan seri!\n";
    }

    clearBoard(b);
}

// Recursive Play

void playRecursive(board &b) {
    string chunkChoose;
    user playerHuman, playerBot;
    player whoIs;
    bool isPlayerWin = false, isBotWin = false;

    cout << "Pilih anda ingin X atau O : ";
    cin >> chunkChoose;

    while (chunkChoose != "X" && chunkChoose != "O") {
        cout << "Tidak Valid! Pastikan anda memilih antara X atau O : ";
        cin >> chunkChoose;
    }

    playDesicionMaker(chunkChoose, playerHuman.stringValue, playerBot.stringValue);
    srand(time(0));
    whoIs.nowpPlay = (rand() % 2 == 0) ? playerHuman : playerBot;

    while (!isPlayerWin && !isBotWin && !isFull(b)) {
        cout << endl;
        printBoard(b);
        if (whoIs.nowpPlay.stringValue == playerHuman.stringValue) {
            cout << "========== Giliran kamu ==========" << endl;
            int chunkLocationX, chunkLocationY;

            cout << "Masukkan lokasi yang ingin diisi (X,Y) : ";
            cin >> chunkLocationX >> chunkLocationY;

            while (chunkLocationX < 1 || chunkLocationX > 3 || chunkLocationY < 1 || chunkLocationY > 3 || isFilled(b, chunkLocationX - 1, chunkLocationY - 1)) {
                cout << "Input tidak valid atau lokasi sudah terisi. Masukkan ulang (X,Y) (1-3): ";
                cin >> chunkLocationX >> chunkLocationY;
            }

            b.chart[chunkLocationX - 1][chunkLocationY - 1] = whoIs.nowpPlay.stringValue;
            isPlayerWin = isWinner(b, whoIs.nowpPlay.stringValue);
            whoIs.nowpPlay = playerBot;
        } else {
            cout << "========== Giliran Bot ==========" << endl;
            cout << "Bot sedang berpikir !! " << endl;

            std::this_thread::sleep_for(std::chrono::seconds(1 + rand() % 4));

            recursiveEngine(b, playerBot.stringValue, playerHuman.stringValue);

            isBotWin = isWinner(b, whoIs.nowpPlay.stringValue);
            whoIs.nowpPlay = playerHuman;
        }
    }

    printBoard(b);
    if (isPlayerWin) {
        cout << "Selamat! Anda menang!\n";
    } else if (isBotWin) {
        cout << "Bot menang! Coba lagi.\n";
    } else {
        cout << "Permainan seri!\n";
    }

    clearBoard(b);
}

// Human Play

// void playHuman(board b) {
//     string chunkPlayDesicion;
//     user player1, player2;

//     cout << "Masukkan X atau O untuk player 1 : ";
//     cin >> chunkPlayDesicion;

//     while (chunkPlayDesicion != "X" && chunkPlayDesicion != "O") {
//         cout << "Input tidak valid! Masukkan X atau O untuk player 1 : ";
//         cin >> chunkPlayDesicion;
//     }
    
//     if (chunkPlayDesicion == "X") {
//         cout << "Player 1 adalah X dan Player 2 adalah O" << endl;
//     } else {
//         cout << "Player 1 adalah O dan Player 2 adalah X" << endl;
//     }

//     playDesicionMaker(chunkPlayDesicion, player1.stringValue, player2.stringValue);
// }

/* ========================== Main Program ========================== */

int main() {
    board boardDatabase;
    int serviceCode = 1;
    string player1, player2; 

    while (serviceCode != 0) {
        mainScreen();
        cout << "Masukkan menu aplikasi : ";
        cin >> serviceCode;
        if (serviceCode == 1) {
            playIterative(boardDatabase);
        } else if (serviceCode == 2) {
            playRecursive(boardDatabase);
        } else if (serviceCode == 3) {
            //playHuman(boardDatabase);
        }
    }

    return 0;
}