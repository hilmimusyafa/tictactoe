#include <iostream>

using namespace std;

struct board {
    string chart[3][3] = {
        {" ", " ", " "},
        {" ", " ", " "},
        {" ", " ", " "},
    };
};

struct user {
    string stringValue;
};

struct player {
    user nowpPlay;
};

int mainScreen () {
    cout << "================================" << endl;
    cout << "      APLIKASI TIC TAC TOE      " << endl;
    cout << "================================" << endl;
    cout << "Pilih menu bermain : " << endl;
    cout << "1. Bermain dengan Bot Sekuensial " << endl;
    cout << "2. Bermain denghan Bot " << endl;
    cout << "3. Bermain sesama manusia " << endl;
    cout << "0. Exit " << endl;

    return 0;
}

bool isFilled(board b, int locationX, int locationY) {
    return b.chart[locationX][locationY] != " ";
}

void printBoard(board b) {
    for (int i = 0; i < 3; i++) {  
        for (int j = 0; j < 3; j++) {  
            cout << b.chart[i][j];
            if (j < 2) cout << " | "; 
        }
        cout << "\n";
        if (i < 2) cout << "-----------\n";  
    }
    cout << "\n";
}

bool isWinner(board b, string player) {
    for (int i = 0; i < 3; i++) {
        if (b.chart[i][0] == player && b.chart[i][1] == player && b.chart[i][2] == player) {
            return true;
        }
        if (b.chart[0][i] == player && b.chart[1][i] == player && b.chart[2][i] == player) {
            return true;
        }
    }

    if ((b.chart[0][0] == player && b.chart[1][1] == player && b.chart[2][2] == player) || (b.chart[0][2] == player && b.chart[1][1] == player && b.chart[2][0] == player)) {
        return true;
    }
    return false;
}

bool isFull(board b) {
    int counterLoopX = 0, counterLoopY = 0;

    while (counterLoopX < 3) {
        while (counterLoopY) {
            if (b.chart[counterLoopX][counterLoopY] == " ") {
                return false;
            }
            counterLoopY = counterLoopY + 1;
        }
        counterLoopX = counterLoopX + 1;
    }
    return true;
}

void playDesicionMaker(string userInput, string &playerHuman, string &playerBot) {
    if (userInput == "X") {
        playerHuman = "X";
        playerBot = "O";
    } else if (userInput == "O") {
        playerHuman = "O";
        playerBot = "X";
    }
}

void sequentialEngine(board &b, string stringValue) {
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

void recursiveEngine(board &b, string stringValue) {

}

void playSequential(board &b) {
    string chunkChoose;
    user playerHuman, playerBot;
    player whoIs, tempPlay;
    int counter = 0;
    bool isPlayerWin = false, isBotWin = false, isLocationFilled;
    int chunkLocationX, chunkLocationY;

    cout << "Pilih anda ingin X atau O : " << endl;
    cin >> chunkChoose;

    while (chunkChoose != "X" || chunkChoose == "O") {
        cout << "Tidak Valid! Pastikan anda memilih antara X atau O";
        cin >> chunkChoose;
    }

    playDesicionMaker(chunkChoose, playerHuman.stringValue, playerBot.stringValue);
    srand(time(0));
    whoIs.nowpPlay = (rand() % 2 == 0) ? playerHuman : playerBot; 

    while (isPlayerWin != true || isBotWin != true || isFull(b) != true) {
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

            if (isPlayerWin == true) {
                break;
            }

            whoIs.nowpPlay = playerBot;  
        } else {
            cout << "========== Giliran Bot ==========" << endl;
            cout << "Bot sedang berpikir !! " << endl;
            sequentialEngine(b, whoIs.nowpPlay.stringValue);

            isBotWin = isWinner(b, whoIs.nowpPlay.stringValue);

            if (isBotWin == true) {
                break;
            }
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
}

void playRecursive(board b) {
    string chunkChoose;
    user playerHuman, playerBot;
    player whoIs, tempPlay;
    int counter = 0;
    bool isPlayerWin = false, isBotWin = false, isLocationFilled;
    int chunkLocationX, chunkLocationY;

    cout << "Pilih anda ingin X atau O : " << endl;
    cin >> chunkChoose;

    while (chunkChoose != "X" || chunkChoose == "O") {
        cout << "Tidak Valid! Pastikan anda memilih antara X atau O";
        cin >> chunkChoose;
    }
    playDesicionMaker(chunkChoose, playerHuman.stringValue, playerBot.stringValue);
    srand(time(0));
    whoIs.nowpPlay = (rand() % 2 == 0) ? playerHuman : playerBot; 

    while (isPlayerWin != true || isBotWin != true || isFull(b) != true) {
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

            if (isPlayerWin == true) {
                break;
            }

            whoIs.nowpPlay = playerBot;  
        } else {
            cout << "========== Giliran Bot ==========" << endl;
            cout << "Bot sedang berpikir !! " << endl;
            recursiveEngine(b, whoIs.nowpPlay.stringValue);

            isBotWin = isWinner(b, whoIs.nowpPlay.stringValue);

            if (isBotWin == true) {
                break;
            }
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
}

void playHuman(board b) {

}

int main() {
    board boardDatabase;
    int serviceCode = 1;
    string player1, player2; 

    while (serviceCode != 0) {
        mainScreen();
        cout << "Masukkan menu aplikasi : ";
        cin >> serviceCode;
        if (serviceCode == 1) {
            playSequential(boardDatabase);
        } else if (serviceCode == 2) {
            //playRecursive(boardDatabase);
        } else if (serviceCode == 3) {
            //playHuman(boardDatabase);
        }
    }

    return 0;
}