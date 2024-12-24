#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>
#include <cstdlib>

using namespace std;

/* ==========================  Structure ========================== */

// Board Structure

struct board3 {
    string chart[3][3] = {
        {" ", " ", " "},
        {" ", " ", " "},
        {" ", " ", " "},
    };
};

struct board4 {
    string chart[4][4] = {
        {" ", " ", " ", " "},
        {" ", " ", " ", " "},
        {" ", " ", " ", " "},
        {" ", " ", " ", " "},
    };
};

struct board5 {
    string chart[5][5] = {
        {" ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " "},
    };
};

struct selectedBoard {
    int boardSize;
    board3 boardSize3;
    board4 boardSize4;
    board5 boardSize5;
};

// User Structure

struct user {
    string stringValue; // can be X or O
};

// Player Structure

struct player {
    user nowpPlay; // current Player
};

// Main Screen

/* ========================== Screen ========================== */ 

int mainScreen() {
    cout << "======================================" << endl;
    cout << "          APLIKASI TIC TAC TOE        " << endl;
    cout << "  TUGAS BESAR KOMPLEKSITAS ALGORITMA  " << endl;
    cout << "======================================" << endl;
    cout << "Pilih menu bermain : " << endl;
    cout << "1. Bermain dengan Bot Iteratif " << endl;
    cout << "2. Bermain denghan Bot Rekursif " << endl;
    cout << "3. Bermain sesama manusia " << endl;
    cout << "4. Uji coba eksekusi waktu algoritma" << endl;
    cout << "5. Uji coba eksekusi waktu rekursif" << endl;
    cout << "0. Exit " << endl;

    return 0;
}

/* ==========================  Game Fucntion ========================== */ 

// Checkking if the board is filled or not

bool isFilled(selectedBoard b, int locationX, int locationY) {
    if (b.boardSize == 3) {
        return b.boardSize3.chart[locationX][locationY] != " ";
    } else if (b.boardSize == 4) {
        return b.boardSize4.chart[locationX][locationY] != " ";
    } else if (b.boardSize == 5) {
        return b.boardSize5.chart[locationX][locationY] != " ";
    }
    return false;
}

// Checking if there's a winner

bool isWinner(selectedBoard b, string player) {
    if (b.boardSize == 3) {
        for (int i = 0; i < 3; i++) {
            // Horizontal Check
            if (b.boardSize3.chart[i][0] == player && b.boardSize3.chart[i][1] == player && b.boardSize3.chart[i][2] == player) {
                return true;
            }
            // Vertical Check
            if (b.boardSize3.chart[0][i] == player && b.boardSize3.chart[1][i] == player && b.boardSize3.chart[2][i] == player) {
                return true;
            }
        }
        // Diagonal Check
        if ((b.boardSize3.chart[0][0] == player && b.boardSize3.chart[1][1] == player && b.boardSize3.chart[2][2] == player) || (b.boardSize3.chart[0][2] == player && b.boardSize3.chart[1][1] == player && b.boardSize3.chart[2][0] == player)) {
            return true;
        }
    } else if (b.boardSize == 4) {
        for (int i = 0; i < 4; i++) {
            // Horizontal Check
            if (b.boardSize4.chart[i][0] == player && b.boardSize4.chart[i][1] == player && b.boardSize4.chart[i][2] == player && b.boardSize4.chart[i][3] == player) {
                return true;
            }
            // Vertical Check
            if (b.boardSize4.chart[0][i] == player && b.boardSize4.chart[1][i] == player && b.boardSize4.chart[2][i] == player && b.boardSize4.chart[3][i] == player) {
                return true;
            }
        }
        // Diagonal Check
        if ((b.boardSize4.chart[0][0] == player && b.boardSize4.chart[1][1] == player && b.boardSize4.chart[2][2] == player && b.boardSize4.chart[3][3] == player) || (b.boardSize4.chart[0][3] == player && b.boardSize4.chart[1][2] == player && b.boardSize4.chart[2][1] == player && b.boardSize4.chart[3][0] == player)) {
            return true;
        }
    } else if (b.boardSize == 5) {
        for (int i = 0; i < 5; i++) {
            // Horizontal Check
            if (b.boardSize5.chart[i][0] == player && b.boardSize5.chart[i][1] == player && b.boardSize5.chart[i][2] == player && b.boardSize5.chart[i][3] == player && b.boardSize5.chart[i][4] == player) {
                return true;
            }
            // Vertical Check
            if (b.boardSize5.chart[0][i] == player && b.boardSize5.chart[1][i] == player && b.boardSize5.chart[2][i] == player && b.boardSize5.chart[3][i] == player && b.boardSize5.chart[4][i] == player) {
                return true;
            }
        }
        // Diagonal Check
        if ((b.boardSize5.chart[0][0] == player && b.boardSize5.chart[1][1] == player && b.boardSize5.chart[2][2] == player && b.boardSize5.chart[3][3] == player && b.boardSize5.chart[4][4] == player) || (b.boardSize5.chart[0][4] == player && b.boardSize5.chart[1][3] == player && b.boardSize5.chart[2][2] == player && b.boardSize5.chart[3][1] == player && b.boardSize5.chart[4][0] == player)) {
            return true;
        }
    }
    return false; 
}

// Checking if the board is full or not

bool isFull(selectedBoard b) {
    if (b.boardSize == 3) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (b.boardSize3.chart[i][j] == " ") {
                    return false;
                }
            }
        }
    } else if (b.boardSize == 4) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (b.boardSize4.chart[i][j] == " ") {
                    return false;
                }
            }
        }
    } else if (b.boardSize == 5) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (b.boardSize5.chart[i][j] == " ") {
                    return false; 
                }
            }
        }
    }
    return true; 
}

// Printing the board

void printBoard(selectedBoard b) {
    if (b.boardSize == 3) {
        for (int i = 0; i < 3; i++) {  // loop through each row
            for (int j = 0; j < 3; j++) {  // loop through each column
                if (j == 0) {
                    cout << " "; 
                }
                cout << b.boardSize3.chart[i][j];
                if (j < 2) {
                    cout << " | "; // line devider for each column
                } 
            }
            cout << "\n"; // New line
            if (i < 2) {
                cout << "---+---+---\n";  // line devider for each row
            }
        }
        cout << "\n";
    } else if (b.boardSize == 4) {
        for (int i = 0; i < 4; i++) {  // loop through each row
            for (int j = 0; j < 4; j++) {  // loop through each column
                if (j == 0) {
                    cout << " "; 
                }
                cout << b.boardSize4.chart[i][j];
                if (j < 3) {
                    cout << " | "; // line devider for each column
                } 
            }
            cout << "\n"; // New line
            if (i < 3) {
                cout << "---+---+---+---\n";  // line devider for each row
            }
        }
        cout << "\n";
    } else if (b.boardSize == 5) {
        for (int i = 0; i < 5; i++) {  // loop through each row
            for (int j = 0; j < 5; j++) {  // loop through each column
                if (j == 0) {
                    cout << " "; 
                }
                cout << b.boardSize5.chart[i][j];
                if (j < 4) {
                    cout << " | "; // line devider for each column
                } 
            }
            cout << "\n"; // New line
            if (i < 4) {
                cout << "---+---+---+---+---\n";  // line devider for each row
            }
        }
        cout << "\n";
    }
}

// Clearing the board

void clearBoard(selectedBoard &b) {
    if (b.boardSize == 3) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                b.boardSize3.chart[i][j] = " "; // just clear the board
            }
        }
    } else if (b.boardSize == 4) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                b.boardSize4.chart[i][j] = " "; // just clear the board
            }
        }
    } else if (b.boardSize == 5) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                b.boardSize5.chart[i][j] = " "; // just clear the board
            }
        }
    }
}

// Decising the player

void playDesicionMaker(string userInput, string &player1, string &player2) {
    if (userInput == "X") { // if the user choose X, bot will be O
        player1 = "X";
        player2 = "O";
    } else if (userInput == "O") { // if the user choose O, bot will be X
        player1 = "O";
        player2 = "X";
    }
}

/* ========================== Iterative Section ========================== */ 

// Iterative Engine

void iterativeEngine(selectedBoard &b, string stringValue) {
    int chunkEmptyLocationArray[25][2];
    int arrayCounter = 0;

    if (b.boardSize == 3) {
        for (int chunkLocationX = 0; chunkLocationX < 3 ; chunkLocationX++) {
            for (int chunkLocationY = 0; chunkLocationY < 3 ; chunkLocationY++) {
                if (b.boardSize3.chart[chunkLocationX][chunkLocationY] == " ") {
                    chunkEmptyLocationArray[arrayCounter][0] = chunkLocationX;
                    chunkEmptyLocationArray[arrayCounter][1] = chunkLocationY;
                    arrayCounter++;
                }
            }
        }
    } else if (b.boardSize == 4) {
        for (int chunkLocationX = 0; chunkLocationX < 4 ; chunkLocationX++) {
            for (int chunkLocationY = 0; chunkLocationY < 4 ; chunkLocationY++) {
                if (b.boardSize3.chart[chunkLocationX][chunkLocationY] == " ") {
                    chunkEmptyLocationArray[arrayCounter][0] = chunkLocationX;
                    chunkEmptyLocationArray[arrayCounter][1] = chunkLocationY;
                    arrayCounter++;
                }
            }
        }
    } else if (b.boardSize == 5) {
        for (int chunkLocationX = 0; chunkLocationX < 5 ; chunkLocationX++) {
            for (int chunkLocationY = 0; chunkLocationY < 5 ; chunkLocationY++) {
                if (b.boardSize3.chart[chunkLocationX][chunkLocationY] == " ") {
                    chunkEmptyLocationArray[arrayCounter][0] = chunkLocationX;
                    chunkEmptyLocationArray[arrayCounter][1] = chunkLocationY;
                    arrayCounter++;
                }
            }
        }
    }
    if (arrayCounter > 0) {
        int randomIndex = rand() % arrayCounter;
        int x = chunkEmptyLocationArray[randomIndex][0];
        int y = chunkEmptyLocationArray[randomIndex][1];

        if (b.boardSize == 3) {
            b.boardSize3.chart[x][y] = stringValue;
        } else if (b.boardSize == 4) {
            b.boardSize4.chart[x][y] = stringValue;
        } else if (b.boardSize == 5) {
            b.boardSize5.chart[x][y] = stringValue;
        }
    }
}

/* ========================== Recursive Section ========================== */ 

// Evaluation Function for Minimax Algorithm

int evaluateBoardScoring(selectedBoard &b, string botValue, string humanValue) {
    if (isWinner(b, botValue)) { // if the bot is the winner
        return 10;
    } else if (isWinner(b, humanValue)) { // if the human is the winner
        return -10;
    } else { // if the board is full
        return 0;
    }
}

// Minimax Algorithm

int minimax(selectedBoard &b, int depth, bool isMaximizing, string botValue, string humanValue) {
    // Evaluate Score for evaluation function
    int currentScore = evaluateBoardScoring(b, botValue, humanValue);

    // Base Case : if there's a winner or the board is full
    if (isWinner(b, botValue)) {
        return 10 - depth;
    }
    if (isWinner(b, humanValue)) {
        return depth - 10;
    }
    if (isFull(b)) {
        return 0;
    }

    // Recursive Case
    if (b.boardSize == 3) {
        if (isMaximizing) {  // if the bot is maximizing
            int bestScore = -1000;

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (b.boardSize3.chart[i][j] == " ") { 
                        b.boardSize3.chart[i][j] = botValue; 
                        int score = minimax(b, depth + 1, false, botValue, humanValue);
                        b.boardSize3.chart[i][j] = " ";
                        bestScore = max(bestScore, score);
                    }
                }
            }
            return bestScore;
        } else {  // if the bot is minimizing
            int bestScore = 1000;

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (b.boardSize3.chart[i][j] == " ") { 
                        b.boardSize3.chart[i][j] = humanValue; 
                        int score = minimax(b, depth + 1, true, botValue, humanValue);
                        b.boardSize3.chart[i][j] = " ";
                        bestScore = min(bestScore, score);
                    }
                }
            }
            return bestScore;
        }
    } else if (b.boardSize == 4) {
        if (isMaximizing) {  // if the bot is maximizing
            int bestScore = -1000;

            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (b.boardSize4.chart[i][j] == " ") { 
                        b.boardSize4.chart[i][j] = botValue; 
                        int score = minimax(b, depth + 1, false, botValue, humanValue);
                        b.boardSize4.chart[i][j] = " ";
                        bestScore = max(bestScore, score);
                    }
                }
            }
            return bestScore;
        } else {  // if the bot is minimizing
            int bestScore = 1000;

            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (b.boardSize4.chart[i][j] == " ") { 
                        b.boardSize4.chart[i][j] = humanValue; 
                        int score = minimax(b, depth + 1, true, botValue, humanValue);
                        b.boardSize4.chart[i][j] = " ";
                        bestScore = min(bestScore, score);
                    }
                }
            }
            return bestScore;
        }
    } else if (b.boardSize == 5) {
        cout << "Masuk 5";
        if (isMaximizing) {  // if the bot is maximizing
            int bestScore = -1000;

            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 5; j++) {
                    if (b.boardSize5.chart[i][j] == " ") { 
                        b.boardSize5.chart[i][j] = botValue; 
                        int score = minimax(b, depth + 1, false, botValue, humanValue);
                        b.boardSize5.chart[i][j] = " ";
                        bestScore = max(bestScore, score);
                    }
                }
            }
            return bestScore;
        } else {  // if the bot is minimizing
            int bestScore = 1000;

            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 5; j++) {
                    if (b.boardSize5.chart[i][j] == " ") { 
                        b.boardSize5.chart[i][j] = humanValue; 
                        int score = minimax(b, depth + 1, true, botValue, humanValue);
                        b.boardSize5.chart[i][j] = " ";
                        bestScore = min(bestScore, score);
                    }
                }
            }
            return bestScore;
        }
    }
    return 0;
}

// Recursive Engine

void recursiveEngine(selectedBoard &b, string botValue, string humanValue) {
    int bestScore = -1000; // initial best score
    int bestMoveX = -1, bestMoveY = -1; // initial best move

    if (b.boardSize == 3) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (b.boardSize3.chart[i][j] == " ") { 
                    b.boardSize3.chart[i][j] = botValue; 
                    int moveScore = minimax(b, 0, false, botValue, humanValue);
                    b.boardSize3.chart[i][j] = " "; 

                    if (moveScore > bestScore) { 
                        bestScore = moveScore;
                        bestMoveX = i;
                        bestMoveY = j;
                    }
                }
            }
        }

        if (bestMoveX != -1 && bestMoveY != -1) {
            b.boardSize3.chart[bestMoveX][bestMoveY] = botValue;
        }
    } else if (b.boardSize == 4) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (b.boardSize4.chart[i][j] == " ") { 
                    b.boardSize4.chart[i][j] = botValue; 
                    int moveScore = minimax(b, 0, false, botValue, humanValue);
                    b.boardSize4.chart[i][j] = " "; 

                    if (moveScore > bestScore) { 
                        bestScore = moveScore;
                        bestMoveX = i;
                        bestMoveY = j;
                    }
                }
            }
        }

        if (bestMoveX != -1 && bestMoveY != -1) {
            b.boardSize4.chart[bestMoveX][bestMoveY] = botValue;
        }
    } else if (b.boardSize == 5) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (b.boardSize5.chart[i][j] == " ") { 
                    b.boardSize5.chart[i][j] = botValue; 
                    int moveScore = minimax(b, 0, false, botValue, humanValue);
                    b.boardSize5.chart[i][j] = " "; 

                    if (moveScore > bestScore) { 
                        bestScore = moveScore;
                        bestMoveX = i;
                        bestMoveY = j;
                    }
                }
            }
        }
    }
}

/* ========================== Play Section ========================== */

// Iterative Play

void playIterative(selectedBoard &b) {
    string chunkChoose;
    user playerHuman, playerBot;
    player whoIs, tempPlay;
    int counter = 0, chunkBoard;
    bool isPlayerWin = false, isBotWin = false, isLocationFilled;
    int chunkLocationX, chunkLocationY;
    
    cout << "Masukkan ukuran board yang diinginkan (3/4/5) : ";
    cin >> chunkBoard;

    while (chunkBoard != 3 && chunkBoard != 4 && chunkBoard != 5) {
        cout << "Ukuran board tidak valid! Masukkan ulang (3/4/5) : ";
        cin >> chunkBoard;
    }
    
    b.boardSize = chunkBoard;

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
            
            if (chunkBoard == 3) {
                while (chunkLocationX < 1 || chunkLocationX > 3 || chunkLocationY < 1 || chunkLocationY > 3 || isFilled(b, chunkLocationX - 1, chunkLocationY - 1)) {
                    cout << "Input tidak valid atau lokasi sudah terisi. Masukkan ulang (X,Y) (1-3): ";
                    cin >> chunkLocationX >> chunkLocationY;
                }
                b.boardSize3.chart[chunkLocationX - 1][chunkLocationY - 1] = whoIs.nowpPlay.stringValue;
            } else if (chunkBoard == 4) {
                while (chunkLocationX < 1 || chunkLocationX > 4 || chunkLocationY < 1 || chunkLocationY > 4 || isFilled(b, chunkLocationX - 1, chunkLocationY - 1)) {
                    cout << "Input tidak valid atau lokasi sudah terisi. Masukkan ulang (X,Y) (1-4): ";
                    cin >> chunkLocationX >> chunkLocationY;
                }
                b.boardSize4.chart[chunkLocationX - 1][chunkLocationY - 1] = whoIs.nowpPlay.stringValue;
            } else if (chunkBoard == 5) {
                while (chunkLocationX < 1 || chunkLocationX > 5 || chunkLocationY < 1 || chunkLocationY > 5 || isFilled(b, chunkLocationX - 1, chunkLocationY - 1)) {
                    cout << "Input tidak valid atau lokasi sudah terisi. Masukkan ulang (X,Y) (1-5): ";
                    cin >> chunkLocationX >> chunkLocationY;
                }
                b.boardSize5.chart[chunkLocationX - 1][chunkLocationY - 1] = whoIs.nowpPlay.stringValue;
            }

            isPlayerWin = isWinner(b, whoIs.nowpPlay.stringValue);

            whoIs.nowpPlay = playerBot;  
        } else {
            cout << "========== Giliran Bot ==========" << endl;

            std::this_thread::sleep_for(std::chrono::seconds(1 + rand() % 4));
            
            cout << "Bot sedang berpikir !! " << endl;
            iterativeEngine(b, whoIs.nowpPlay.stringValue);

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

    b.boardSize = 0;
}

// Recursive Play

void playRecursive(selectedBoard &b) {
    string chunkChoose;
    int chunkBoard;
    user playerHuman, playerBot;
    player whoIs;
    bool isPlayerWin = false, isBotWin = false;

    cout << "Masukkan ukuran board yang diinginkan (3/4/5) : ";
    cout << "Recursive Play didn't recommend for 4x4 or more board" << endl;
    cin >> chunkBoard;

    while (chunkBoard != 3 && chunkBoard != 4 && chunkBoard != 5) {
        cout << "Ukuran board tidak valid! Masukkan ulang (3/4/5) : ";
        cin >> chunkBoard;
    }
    
    b.boardSize = chunkBoard;

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
            
            if (chunkBoard == 3) {
                while (chunkLocationX < 1 || chunkLocationX > 3 || chunkLocationY < 1 || chunkLocationY > 3 || isFilled(b, chunkLocationX - 1, chunkLocationY - 1)) {
                    cout << "Input tidak valid atau lokasi sudah terisi. Masukkan ulang (X,Y) (1-3): ";
                    cin >> chunkLocationX >> chunkLocationY;
                }
                b.boardSize3.chart[chunkLocationX - 1][chunkLocationY - 1] = whoIs.nowpPlay.stringValue;
            } else if (chunkBoard == 4) {
                while (chunkLocationX < 1 || chunkLocationX > 4 || chunkLocationY < 1 || chunkLocationY > 4 || isFilled(b, chunkLocationX - 1, chunkLocationY - 1)) {
                    cout << "Input tidak valid atau lokasi sudah terisi. Masukkan ulang (X,Y) (1-4): ";
                    cin >> chunkLocationX >> chunkLocationY;
                }
                b.boardSize4.chart[chunkLocationX - 1][chunkLocationY - 1] = whoIs.nowpPlay.stringValue;
            } else if (chunkBoard == 5) {
                while (chunkLocationX < 1 || chunkLocationX > 5 || chunkLocationY < 1 || chunkLocationY > 5 || isFilled(b, chunkLocationX - 1, chunkLocationY - 1)) {
                    cout << "Input tidak valid atau lokasi sudah terisi. Masukkan ulang (X,Y) (1-5): ";
                    cin >> chunkLocationX >> chunkLocationY;
                }
                b.boardSize5.chart[chunkLocationX - 1][chunkLocationY - 1] = whoIs.nowpPlay.stringValue;
            }
            
            isPlayerWin = isWinner(b, whoIs.nowpPlay.stringValue);
            whoIs.nowpPlay = playerBot;
        } else {
            cout << "========== Giliran Bot ==========" << endl;
            cout << "Bot sedang berpikir !! " << endl;

            
            auto start = std::chrono::high_resolution_clock::now();
            recursiveEngine(b, playerBot.stringValue, playerHuman.stringValue);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = end - start;
            cout << "Bot berpikir selama " << duration.count() << " detik." << endl;

            static double durationArray[100]; // Assuming a maximum of 100 moves
            static int moveCount = 0;
            if (moveCount < 100) {
                durationArray[moveCount++] = duration.count();
            }

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

    b.boardSize = 0;
}

// Human Play

void playHuman(selectedBoard b) {
    string chunkPlayDesicion;
    user player1, player2;
    player whoIs;
    bool isPlayer1Win = false, isPlayer2Win = false;

    cout << "Masukkan X atau O untuk player 1 : ";
    cin >> chunkPlayDesicion;

    while (chunkPlayDesicion != "X" && chunkPlayDesicion != "O") {
        cout << "Input tidak valid! Masukkan X atau O untuk player 1 : ";
        cin >> chunkPlayDesicion;
    }
    
    if (chunkPlayDesicion == "X") {
        cout << "Player 1 adalah X dan Player 2 adalah O" << endl;
    } else {
        cout << "Player 1 adalah O dan Player 2 adalah X" << endl;
    }

    playDesicionMaker(chunkPlayDesicion, player1.stringValue, player2.stringValue);

    whoIs.nowpPlay = (rand() % 2 == 0) ? player1 : player2;

    while (!isPlayer1Win && !isPlayer2Win && !isFull(b)) {
        cout << endl;
        printBoard(b);
        if (whoIs.nowpPlay.stringValue == player1.stringValue) {
            cout << "========== Giliran Player 1 ==========" << endl;
            int chunkLocationX, chunkLocationY;

            cout << "Masukkan lokasi yang ingin diisi (X,Y) : ";
            cin >> chunkLocationX >> chunkLocationY;

            if (b.boardSize == 3) {
                while (chunkLocationX < 1 || chunkLocationX > 3 || chunkLocationY < 1 || chunkLocationY > 3 || isFilled(b, chunkLocationX - 1, chunkLocationY - 1)) {
                    cout << "Input tidak valid atau lokasi sudah terisi. Masukkan ulang (X,Y) (1-3): ";
                    cin >> chunkLocationX >> chunkLocationY;
                    b.boardSize3.chart[chunkLocationX - 1][chunkLocationY - 1] = whoIs.nowpPlay.stringValue;
                }
            } else if (b.boardSize == 4) {
                while (chunkLocationX < 1 || chunkLocationX > 4 || chunkLocationY < 1 || chunkLocationY > 4 || isFilled(b, chunkLocationX - 1, chunkLocationY - 1)) {
                    cout << "Input tidak valid atau lokasi sudah terisi. Masukkan ulang (X,Y) (1-4): ";
                    cin >> chunkLocationX >> chunkLocationY;
                    b.boardSize4.chart[chunkLocationX - 1][chunkLocationY - 1] = whoIs.nowpPlay.stringValue;
                }
            } else if (b.boardSize == 5) {
                while (chunkLocationX < 1 || chunkLocationX > 5 || chunkLocationY < 1 || chunkLocationY > 5 || isFilled(b, chunkLocationX - 1, chunkLocationY - 1)) {
                    cout << "Input tidak valid atau lokasi sudah terisi. Masukkan ulang (X,Y) (1-5): ";
                    cin >> chunkLocationX >> chunkLocationY;
                    b.boardSize5.chart[chunkLocationX - 1][chunkLocationY - 1] = whoIs.nowpPlay.stringValue;
                }
            }

            isPlayer1Win = isWinner(b, whoIs.nowpPlay.stringValue);
            whoIs.nowpPlay = player2;
        } else {
            cout << "========== Giliran Player 2 ==========" << endl;
            int chunkLocationX, chunkLocationY;

            cout << "Masukkan lokasi yang ingin diisi (X,Y) : ";
            cin >> chunkLocationX >> chunkLocationY;

            if (b.boardSize == 3) {
                while (chunkLocationX < 1 || chunkLocationX > 3 || chunkLocationY < 1 || chunkLocationY > 3 || isFilled(b, chunkLocationX - 1, chunkLocationY - 1)) {
                    cout << "Input tidak valid atau lokasi sudah terisi. Masukkan ulang (X,Y) (1-3): ";
                    cin >> chunkLocationX >> chunkLocationY;
                    b.boardSize3.chart[chunkLocationX - 1][chunkLocationY - 1] = whoIs.nowpPlay.stringValue;
                }
            } else if (b.boardSize == 4) {
                while (chunkLocationX < 1 || chunkLocationX > 4 || chunkLocationY < 1 || chunkLocationY > 4 || isFilled(b, chunkLocationX - 1, chunkLocationY - 1)) {
                    cout << "Input tidak valid atau lokasi sudah terisi. Masukkan ulang (X,Y) (1-4): ";
                    cin >> chunkLocationX >> chunkLocationY;
                    b.boardSize4.chart[chunkLocationX - 1][chunkLocationY - 1] = whoIs.nowpPlay.stringValue;
                }
            } else if (b.boardSize == 5) {
                while (chunkLocationX < 1 || chunkLocationX > 5 || chunkLocationY < 1 || chunkLocationY > 5 || isFilled(b, chunkLocationX - 1, chunkLocationY - 1)) {
                    cout << "Input tidak valid atau lokasi sudah terisi. Masukkan ulang (X,Y) (1-5): ";
                    cin >> chunkLocationX >> chunkLocationY;
                    b.boardSize5.chart[chunkLocationX - 1][chunkLocationY - 1] = whoIs.nowpPlay.stringValue;
                }
            }

            isPlayer2Win = isWinner(b, whoIs.nowpPlay.stringValue);
            whoIs.nowpPlay = player1;
        }
    }

    printBoard(b);
    if (isPlayer1Win) {
        cout << "Player 1 menang!\n";
    } else if (isPlayer2Win) {
        cout << "Player 2 menang!\n";
    } else {
        cout << "Permainan seri!\n";
    }

    clearBoard(b);

    b.boardSize = 0;
}

#include <fstream>

void testRunningtimeIterative(selectedBoard b) {
    user playerBot1, playerBot2;
    player whoIs;
    bool isBot1Win = false, isBot2Win = false;

    b.boardSize = 3; // Set board size to 3x3

    playerBot1.stringValue = "X";
    playerBot2.stringValue = "O";

    srand(time(0));
    whoIs.nowpPlay = (rand() % 2 == 0) ? playerBot1 : playerBot2;

    while (!isBot1Win && !isBot2Win && !isFull(b)) {
        cout << endl;
        printBoard(b);
        cout << "========== Giliran " << (whoIs.nowpPlay.stringValue == playerBot1.stringValue ? "Bot 1" : "Bot 2") << " ==========" << endl;
        cout << "Bot sedang berpikir !! " << endl;

        auto start = std::chrono::high_resolution_clock::now();
        iterativeEngine(b, whoIs.nowpPlay.stringValue);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        cout << "Bot berpikir selama " << duration.count() << " detik." << endl;

        if (whoIs.nowpPlay.stringValue == playerBot1.stringValue) {
            isBot1Win = isWinner(b, whoIs.nowpPlay.stringValue);
            whoIs.nowpPlay = playerBot2;
        } else {
            isBot2Win = isWinner(b, whoIs.nowpPlay.stringValue);
            whoIs.nowpPlay = playerBot1;
        }
    }

    printBoard(b);
    if (isBot1Win) {
        cout << "Bot 1 menang!\n";
    } else if (isBot2Win) {
        cout << "Bot 2 menang!\n";
    } else {
        cout << "Permainan seri!\n";
    }

    clearBoard(b);
    b.boardSize = 0;
}


void testRunningtimeRecursive(selectedBoard b) {
    user playerBot1, playerBot2;
    player whoIs;
    bool isBot1Win = false, isBot2Win = false;

    b.boardSize = 3; // Set board size to 3x3

    playerBot1.stringValue = "X";
    playerBot2.stringValue = "O";

    srand(time(0));
    whoIs.nowpPlay = (rand() % 2 == 0) ? playerBot1 : playerBot2;


    while (!isBot1Win && !isBot2Win && !isFull(b)) {
        cout << endl;
        printBoard(b);
        cout << "========== Giliran " << (whoIs.nowpPlay.stringValue == playerBot1.stringValue ? "Bot 1" : "Bot 2") << " ==========" << endl;
        cout << "Bot sedang berpikir !! " << endl;

        auto start = std::chrono::high_resolution_clock::now();
        recursiveEngine(b, whoIs.nowpPlay.stringValue, (whoIs.nowpPlay.stringValue == playerBot1.stringValue ? playerBot2.stringValue : playerBot1.stringValue));
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        cout << "Bot berpikir selama " << duration.count() << " detik." << endl;

        if (whoIs.nowpPlay.stringValue == playerBot1.stringValue) {
            isBot1Win = isWinner(b, whoIs.nowpPlay.stringValue);
            whoIs.nowpPlay = playerBot2;
        } else {
            isBot2Win = isWinner(b, whoIs.nowpPlay.stringValue);
            whoIs.nowpPlay = playerBot1;
        }
    }

    printBoard(b);
    if (isBot1Win) {
        cout << "Bot 1 menang!\n";
    } else if (isBot2Win) {
        cout << "Bot 2 menang!\n";
    } else {
        cout << "Permainan seri!\n";
    }

    clearBoard(b);
    b.boardSize = 0;
}

/* ========================== Main Program ========================== */

int main() {
    selectedBoard boardDatabase;
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
            playHuman(boardDatabase);
        } else if (serviceCode == 4) {
            testRunningtimeIterative(boardDatabase);
        } else if (serviceCode == 5) {
            testRunningtimeRecursive(boardDatabase);
        } else if (serviceCode == 0) {
            cout << "Terima kasih telah menggunakan aplikasi ini!" << endl;
        } else {
            cout << "Input tidak valid! Masukkan menu aplikasi yang benar." << endl;
        }
    }
    
    return 0;
}