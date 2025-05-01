#include "AI.h"


int scoreDirection(uint8_t board[boardColumns][boardRows], int i, int j, int dir_i, int dir_j){
    int count = 0;
    int empty = 0;
    int dirScore =0;
    // score winability of the direction
    for (int k = 0; k < 4; k++) {
        if (!((i+dir_i*k)>=boardColumns || (i+dir_i*k)<0||(j+dir_j*k)>=boardRows || (j+dir_j*k)<0)){
            if(board[i+dir_i*k][j+dir_j*k] == board[i][j]){
                count++;
            }
            else if (board[i+dir_i*k][j+dir_j*k] == 0){
                empty++;
            }
        }
    }
    if (count == 3 && empty == 1) dirScore += 50;
    else if (count == 2 && empty == 2) dirScore += 10;
    return dirScore;
}
int scorePosition(uint8_t board[boardColumns][boardRows], int i, int j){
    int posScore = 0;
    //score winability of the position
    posScore += scoreDirection(board, i, j, 1,0);
    posScore += scoreDirection(board, i, j, 0,1);
    posScore += scoreDirection(board, i, j, 1,1);
    posScore += scoreDirection(board, i, j, 1,-1);
    return posScore;
}

int scoreMove(uint8_t board[boardColumns][boardRows]) {
    int score = 0;
    // prefers the center columns
    int center_col = boardColumns / 2;
    for (int row = 0; row < boardRows; row++) {
        if (board[center_col][row] == AI)
            score += 6; 
    }
    //score winability of the temp board
    for (int r = 0; r < boardRows; r++) {
        for (int c = 0; c < boardColumns; c++) {
            score += scorePosition(board, c, r);
        }
    }

    return score;
}

int moveAI(uint8_t gameBoard[boardColumns][boardRows]) {
    int best_col = -1;
    int best_score = -1;

    for (int col = 0; col < boardColumns; col++) {
        if (gameBoard[col][0] == 0) {
            int row = 0;
            while (row < boardRows && gameBoard[col][row] == 0) {
                row++;
            }
            if (row == 0) continue; 
            row--;  // simulated row drop
        
            //check win
            uint8_t tempBoard[boardColumns][boardRows];
            for (int i = 0; i < boardColumns; i++) {
                for (int j = 0; j < boardRows; j++) {
                    tempBoard[i][j] = gameBoard[i][j];
                }
            }
            tempBoard[col][row] = 2;
            if (checkState(tempBoard) == 2) return col;
        
            //check block
            tempBoard[col][row] = 1;
            if (checkState(tempBoard) == 1) return col;
        
            //otherwise score move
            tempBoard[col][row] = 2;
            int score = scoreMove(tempBoard);
            if (score > best_score) {
                best_score = score;
                best_col = col;
            }
        }
    }

    return best_col;
}

uint8_t checkState(uint8_t checkBoard[boardColumns][boardRows]){
    for (int i = 0; i< boardColumns; i++){
        for (int j = 0; j < boardRows; j++){
            if (checkBoard[i][j] != 0){
                if (checkDirection(checkBoard, i, j, 1, 0)|| //checking horizontal
                    checkDirection(checkBoard, i, j, 0, 1)|| //checking vertical 
                    checkDirection(checkBoard, i, j, 1, 1)|| //checking / diagonal
                    checkDirection(checkBoard, i, j, 1, -1)){ //checking \ diagonal
                        return checkBoard[i][j];
                }
            }
        }
    }
	return 0;
}
bool checkDirection(uint8_t checkBoard[boardColumns][boardRows], int i, int j, int dir_i, int dir_j){
    for (int k = 1; k < 4; k++){
        if ((i+dir_i*k)>=boardColumns || (i+dir_i*k)<0){
            return false;
        } 
        if ((j+dir_j*k)>=boardRows || (j+dir_j*k)<0){
            return false;
        } 
        if (checkBoard[i][j] != checkBoard[i+dir_i*k][j+dir_j*k]){
            return false;
        }

    }
    return true;

}
