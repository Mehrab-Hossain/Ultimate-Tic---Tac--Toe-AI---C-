#include<bits/stdc++.h>
using namespace std;

// defaults

int currentTurn = 1;
int player = 1;
int ai = -1;
int currentBoard = -1;

int gameRunning = true;

int RUNS = 0;

int MOVES = 0;

int switchAroo = 1;

int AIACTIVE = true;

char playerNames[3][10] = {"PLAYER", "AI", "X"};
int Infinity = 1e9;
int bestMove = -1;
int bestScore[10];



//BOARDS IS AN ARRAY OF ARRAYS, WHERE EACH OF THE 9 ARRAYS REPRESENTS A LOCAL BOARD
int boards[10][10] = {0};

//THIS ARRAY GETS EDITED IF YOU WIN A LOCAL BOARD
int mainBoard[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

char convert(int a){
    if (a == -1){
        return 'O';
    }
    else if (a == 1){
        return 'X';
    }
    else return '*';
}
void print_board(){
    for( int j = 0; j < 11; j++){
        cout <<"- ";
    }
    cout <<endl<<endl;

    for ( int i = 0; i < 3; i++){

            // printing 1 to 3
            for( int j = i*3; j < (i+1)*3; j++){
                cout << convert(boards[j][0]) <<" "<< convert(boards[j][1]) <<" "<< convert(boards[j][2])<<" ";

                if( j + 1 < (i+1)*3){
                    cout <<"| ";
                }
            }
            cout <<endl;

            for( int j = i*3; j < (i+1)*3; j++){
                cout << convert(boards[j][3]) <<" "<< convert(boards[j][4]) <<" "<< convert(boards[j][5])<<" ";

                if( j + 1 < (i+1)*3){
                    cout <<"| ";
                }
            }
            cout <<endl;

            for( int j = i*3; j < (i+1)*3; j++){
                cout << convert(boards[j][6]) <<" "<< convert(boards[j][7]) <<" "<< convert(boards[j][8])<<" ";

                if( j + 1 < (i+1)*3){
                    cout <<"| ";
                }
            }

            cout << endl<<endl;

            for( int j = 0; j < 11; j++){
                cout <<"- ";
            }

            cout <<endl<<endl;

    }


    cout << convert(mainBoard[0]) <<" "<< convert(mainBoard[1])<<" "<<convert(mainBoard[2])<<endl;
    cout << convert(mainBoard[3]) <<" "<< convert(mainBoard[4])<<" "<<convert(mainBoard[5])<<endl;
    cout << convert(mainBoard[6]) <<" "<< convert(mainBoard[7])<<" "<<convert(mainBoard[8])<<endl;

    cout << endl;

   for( int j = 0; j < 11; j++){
        cout <<"- ";
   }
   cout <<endl;

}

//SIMPLY CHECKS A NORMAL TIC TAC TOE BOARD, RETURNS 1 or -1 if a specific player has won, returns 0 if no one has won.
int checkWinCondition(int SG[9]) {
    int a = 1;
    if (SG[0] + SG[1] + SG[2] == a * 3 ||
        SG[3] + SG[4] + SG[5] == a * 3 ||
        SG[6] + SG[7] + SG[8] == a * 3 ||
        SG[0] + SG[3] + SG[6] == a * 3 ||
        SG[1] + SG[4] + SG[7] == a * 3 ||
        SG[2] + SG[5] + SG[8] == a * 3 ||
        SG[0] + SG[4] + SG[8] == a * 3 ||
        SG[2] + SG[4] + SG[6] == a * 3){
        return a;
    }
    a = -1;
    if (SG[0] + SG[1] + SG[2] == a * 3 ||
        SG[3] + SG[4] + SG[5] == a * 3 ||
        SG[6] + SG[7] + SG[8] == a * 3 ||
        SG[0] + SG[3] + SG[6] == a * 3 ||
        SG[1] + SG[4] + SG[7] == a * 3 ||
        SG[2] + SG[5] + SG[8] == a * 3 ||
        SG[0] + SG[4] + SG[8] == a * 3 ||
        SG[2] + SG[4] + SG[6] == a * 3){
        return a;
    }
    return 0;
}


//This function actually evaluates a board fairly
int realEvaluateSquare(int pos[10]){
    int evaluation = 0;
    int points[10] = {4,2,4,2,8,2,4,2,4};

    for(int bw = 0; bw < 9; bw++){
        evaluation -= pos[bw]*points[bw];
    }

    int a = 2;
    if(pos[0] + pos[1] + pos[2] == a ||
       pos[3] + pos[4] + pos[5] == a ||
       pos[6] + pos[7] + pos[8] == a) {
        evaluation -= 6;
    }
    if(pos[0] + pos[3] + pos[6] == a ||
       pos[1] + pos[4] + pos[7] == a ||
       pos[2] + pos[5] + pos[8] == a) {
        evaluation -= 6;
    }
    if(pos[0] + pos[4] + pos[8] == a ||
       pos[2] + pos[4] + pos[6] == a) {
        evaluation -= 7;
    }

    a = -1;
    if((pos[0] + pos[1] == 2*a && pos[2] == -a) ||
        (pos[1] + pos[2] == 2*a && pos[0] == -a) ||
        (pos[0] + pos[2] == 2*a && pos[1] == -a)
        || (pos[3] + pos[4] == 2*a && pos[5] == -a) ||
        (pos[3] + pos[5] == 2*a && pos[4] == -a) || (pos[5] + pos[4] == 2*a && pos[3] == -a)
        || (pos[6] + pos[7] == 2*a && pos[8] == -a) || (pos[6] + pos[8] == 2*a && pos[7] == -a) || (pos[7] + pos[8] == 2*a && pos[6] == -a)
        || (pos[0] + pos[3] == 2*a && pos[6] == -a) || (pos[0] + pos[6] == 2*a && pos[3] == -a) || (pos[3] + pos[6] == 2*a && pos[0] == -a)
        || (pos[1] + pos[4] == 2*a && pos[7] == -a) || (pos[1] + pos[7] == 2*a && pos[4] == -a) || (pos[4] + pos[7] == 2*a && pos[1] == -a)
        || (pos[2] + pos[5] == 2*a && pos[8] == -a) || (pos[2] + pos[8] == 2*a && pos[5] == -a) || (pos[5] + pos[8] == 2*a && pos[2] == -a)
        || (pos[0] + pos[4] == 2*a && pos[8] == -a) || (pos[0] + pos[8] == 2*a && pos[4] == -a) || (pos[4] + pos[8] == 2*a && pos[0] == -a)
        || (pos[2] + pos[4] == 2*a && pos[6] == -a) || (pos[2] + pos[6] == 2*a && pos[4] == -a) || (pos[4] + pos[6] == 2*a && pos[2] == -a)){
        evaluation-=9;
    }

    a = -2;
    if(pos[0] + pos[1] + pos[2] == a || pos[3] + pos[4] + pos[5] == a || pos[6] + pos[7] + pos[8] == a) {
        evaluation += 6;
    }
    if(pos[0] + pos[3] + pos[6] == a || pos[1] + pos[4] + pos[7] == a || pos[2] + pos[5] + pos[8] == a) {
        evaluation += 6;
    }
    if(pos[0] + pos[4] + pos[8] == a || pos[2] + pos[4] + pos[6] == a) {
        evaluation += 7;
    }

    a = 1;
    if((pos[0] + pos[1] == 2*a && pos[2] == -a) || (pos[1] + pos[2] == 2*a && pos[0] == -a) || (pos[0] + pos[2] == 2*a && pos[1] == -a)
        || (pos[3] + pos[4] == 2*a && pos[5] == -a) || (pos[3] + pos[5] == 2*a && pos[4] == -a) || (pos[5] + pos[4] == 2*a && pos[3] == -a)
        || (pos[6] + pos[7] == 2*a && pos[8] == -a) || (pos[6] + pos[8] == 2*a && pos[7] == -a) || (pos[7] + pos[8] == 2*a && pos[6] == -a)
        || (pos[0] + pos[3] == 2*a && pos[6] == -a) || (pos[0] + pos[6] == 2*a && pos[3] == -a) || (pos[3] + pos[6] == 2*a && pos[0] == -a)
        || (pos[1] + pos[4] == 2*a && pos[7] == -a) || (pos[1] + pos[7] == 2*a && pos[4] == -a) || (pos[4] + pos[7] == 2*a && pos[1] == -a)
        || (pos[2] + pos[5] == 2*a && pos[8] == -a) || (pos[2] + pos[8] == 2*a && pos[5] == -a) || (pos[5] + pos[8] == 2*a && pos[2] == -a)
        || (pos[0] + pos[4] == 2*a && pos[8] == -a) || (pos[0] + pos[8] == 2*a && pos[4] == -a) || (pos[4] + pos[8] == 2*a && pos[0] == -a)
        || (pos[2] + pos[4] == 2*a && pos[6] == -a) || (pos[2] + pos[6] == 2*a && pos[4] == -a) || (pos[4] + pos[6] == 2*a && pos[2] == -a)){
        evaluation+=9;
    }

    evaluation -= checkWinCondition(pos)*12;

    return evaluation;
}

//Low number means losing the board, big number means winning
//Tbf this is less an evaluation algorithm and more something that figures out where the AI should move to win normal Tic Tac Toe
int evaluatePos(int pos[10], int square){
    pos[square] = ai;
    int evaluation = 0;
    //Prefer center over corners over edges
    //evaluation -= (pos[0]*0.2+pos[1]*0.1+pos[2]*0.2+pos[3]*0.1+pos[4]*0.25+pos[5]*0.1+pos[6]*0.2+pos[7]*0.1+pos[8]*0.2);
    int points[10] = {4,2,4,2,8,2,4,2,4};

    int a = 2;
    evaluation+=points[square];

    //Prefer creating pairs
    a = -2;
    if(pos[0] + pos[1] + pos[2] == a || pos[3] + pos[4] + pos[5] == a ||
       pos[6] + pos[7] + pos[8] == a || pos[0] + pos[3] + pos[6] == a || pos[1] + pos[4] + pos[7] == a ||
       pos[2] + pos[5] + pos[8] == a || pos[0] + pos[4] + pos[8] == a || pos[2] + pos[4] + pos[6] == a) {
        evaluation += 1;
    }
    //Take victories
    a = -3;
    if(pos[0] + pos[1] + pos[2] == a || pos[3] + pos[4] + pos[5] == a ||
       pos[6] + pos[7] + pos[8] == a || pos[0] + pos[3] + pos[6] == a || pos[1] + pos[4] + pos[7] == a ||
       pos[2] + pos[5] + pos[8] == a || pos[0] + pos[4] + pos[8] == a || pos[2] + pos[4] + pos[6] == a) {
        evaluation += 5;
    }

    //Block a players turn if necessary
    pos[square] = player;

    a = 3;
    if(pos[0] + pos[1] + pos[2] == a || pos[3] + pos[4] + pos[5] == a ||
        pos[6] + pos[7] + pos[8] == a || pos[0] + pos[3] + pos[6] == a ||
        pos[1] + pos[4] + pos[7] == a ||
        pos[2] + pos[5] + pos[8] == a ||
        pos[0] + pos[4] + pos[8] == a ||
        pos[2] + pos[4] + pos[6] == a) {
        evaluation += 2;
    }

    pos[square] = ai;

    evaluation-= checkWinCondition(pos)*15;

    pos[square] = 0;

    return evaluation;
}



//The most important function, returns a numerical evaluation of the whole game in it's current state
int evaluateGame(int position[10][10], int currentBoard) {
    int evale = 0;
    int mainBd[10] = {0};
    int evaluatorMul[10] = {4,2,4,2,8,2,4,2,4};
    for (int eh = 0; eh < 9; eh++){
        evale += realEvaluateSquare(position[eh])*2*evaluatorMul[eh];
        if(eh == currentBoard){
            evale += realEvaluateSquare(position[eh])*evaluatorMul[eh];
        }
        int tmpEv = checkWinCondition(position[eh]);
        //evale -= tmpEv*evaluatorMul[eh];
        mainBd[eh] = tmpEv;
    }
    evale -= checkWinCondition(mainBd)*5000;
    evale += realEvaluateSquare(mainBd)*150;
    return evale;
}

bool emptySquare(int pos[10]){
    for ( int i = 0; i < 9; i++){
        if( pos[i]==0) return true;
    }

    return false;
}
pair<int,int> miniMax(int position[10][10], int boardToPlayOn,int depth,int alpha,int beta,bool maximizingPlayer){
    RUNS++;

    int tmpPlay = -1;

    int calcEval = evaluateGame(position, boardToPlayOn);
    if(depth <= 0 || abs(calcEval) > 5000) {
        //cout << calcEval <<" "<<depth<<endl;
        return {calcEval,tmpPlay};
    }
    //If the board to play on is -1, it means you can play on any board
    if(boardToPlayOn != -1 && checkWinCondition(position[boardToPlayOn]) != 0){
        boardToPlayOn = -1;
    }
    //If a board is full (doesn't include 0), it also sets the board to play on to -1
    if(boardToPlayOn != -1 && !emptySquare(position[boardToPlayOn])){
        boardToPlayOn = -1;
    }

    if(maximizingPlayer==true){

        int maxEval = -Infinity;


        for(int mm = 0; mm < 9; mm++){
            int evalut = -Infinity;
            //If you can play on any board, you have to go through all of them
            if(boardToPlayOn == -1){
                for(int trr = 0; trr < 9; trr++){
                    //Except the ones which are won
                    if(checkWinCondition(position[mm]) == 0){
                        if(position[mm][trr] == 0){
                            position[mm][trr] = ai;
                            //tmpPlay = pickBoard(position, true);
                            evalut = miniMax(position, trr, depth-1, alpha, beta, false).first;
                            //evalut+=150;
                            position[mm][trr] = 0;
                        }
                        if(evalut > maxEval){
                            maxEval = evalut;
                            tmpPlay = mm;
                        }
                        alpha = max(alpha, evalut);
                    }

                }
                if(beta <= alpha){
                    break;
                }
            //If there's a specific board to play on, you just go through it's squares
            }else{
                pair<int,int> evalut2;
                if(position[boardToPlayOn][mm] == 0){
                    position[boardToPlayOn][mm] = ai;
                    evalut2=  miniMax(position, mm, depth-1, alpha, beta, false);
                    position[boardToPlayOn][mm] = 0;
                }
                //Beautiful variable naming
                int blop = evalut2.first;
                if(blop > maxEval){
                    maxEval = blop;
                    //Saves which board you should play on, so that this can be passed on when the AI is allowed to play in any board
                    tmpPlay = evalut2.second;
                }
                alpha = max(alpha, blop);
                if(beta <= alpha){
                    break;
                }
            }
        }
        return make_pair(maxEval, tmpPlay);
    }else{
        //Same for the minimizing end
        int minEval = Infinity;
        for(int mm = 0; mm < 9; mm++){
            int evalua = Infinity;
            if(boardToPlayOn == -1){
                for(int trr = 0; trr < 9; trr++){
                    if(checkWinCondition(position[mm]) == 0){
                        if(position[mm][trr] == 0){
                            position[mm][trr] = player;
                            //tmpPlay = pickBoard(position, true);
                            evalua = miniMax(position, trr, depth-1, alpha, beta, true).first;
                            //evalua -= 150;
                            position[mm][trr] = 0;
                        }
                        if(evalua < minEval){
                            minEval = evalua;
                            tmpPlay = mm;
                        }
                        beta = min(beta, evalua);
                    }

                }
                if(beta <= alpha){
                    break;
                }
            }else{

                pair<int,int> evalua;
                if(position[boardToPlayOn][mm] == 0){
                    position[boardToPlayOn][mm] = player;
                    evalua = miniMax(position, mm, depth-1, alpha, beta, true);
                    position[boardToPlayOn][mm] = 0;
                }
                int blep = evalua.first;
                if(blep < minEval){
                    minEval = blep;
                    tmpPlay = evalua.second;
                }
                beta = min(beta, blep);
                if(beta <= alpha){
                    break;
                }
            }
        }
        return make_pair(minEval,tmpPlay);
    }
}
void game(){

     if(currentTurn == -1){

        bestMove = -1;

        for ( int i = 0; i < 10; i++) bestScore[i] = -1e9;

        RUNS = 0; //Just a variable where I store how many times minimax has run

        //Calculates the remaining amount of empty squares
        int count1 = 0;
        for(int bt = 0; bt < 9; bt++){
            if(checkWinCondition(boards[bt]) == 0){
                for ( int j = 0; j < 9; j++){
                    if( boards[bt][j] == 0) count1++;
                }
            }
        }

        if(currentBoard == -1 || checkWinCondition(boards[currentBoard]) != 0){
            pair<int,int> savedMm;

            //This minimax doesn't actually play a move, it simply figures out which board you should play on
            if(MOVES < 10) {
                savedMm = miniMax(boards, -1, min(4, count1), -Infinity, Infinity, true); //Putting min makes sure that minimax doesn't run when the board is full
            }else if(MOVES < 18){
                savedMm = miniMax(boards, -1, min(5, count1), -Infinity, Infinity, true);
            }else{
                savedMm = miniMax(boards, -1, min(6, count1), -Infinity, Infinity, true);

            }
            currentBoard = savedMm.second;

        }

        //Just makes a quick default move for if all else fails
        for (int i = 0; i < 9; i++) {
            if (boards[currentBoard][i] == 0) {
                bestMove = i;
                break;
            }
        }


        if(bestMove != -1) { //This condition should only be false if the board is full, but it's here in case

            //Best score is an array which contains individual scores for each square, here we're just changing them based on how good the move is on that one local board
            for (int a = 0; a < 9; a++) {
                if (boards[currentBoard][a] == 0) {
                    int score = evaluatePos(boards[currentBoard], a)*45;
                    bestScore[a] = score;
                }
            }

            //And here we actually run minimax and add those values to the array
            for(int b = 0; b < 9; b++){
                if(checkWinCondition(boards[currentBoard]) == 0){
                    if (boards[currentBoard][b] == 0) {
                        boards[currentBoard][b] = ai;
                        pair<int,int> savedMm;
                        //Notice the stacking, at the beginning of the game, the depth is much lower than at the end
                        if(MOVES < 20){
                            savedMm = miniMax(boards, b, min(5, count1), -Infinity, Infinity, false);
                        }else if(MOVES < 32){

                            savedMm = miniMax(boards, b, min(6, count1), -Infinity, Infinity, false);
                        }else{
                            savedMm = miniMax(boards, b, min(7, count1), -Infinity, Infinity, false);
                        }

                        int score2 = savedMm.first;
                        boards[currentBoard][b] = 0;
                        bestScore[b] += score2;
                    }
                }
            }

            //Choses to play on the square with the highest evaluation in the bestScore array
            for(int i = 0; i < 9; i++){
                if(bestScore[i] > bestScore[bestMove]){
                    bestMove = i;
                }
            }

            //Actually places the cross/nought
            if(boards[currentBoard][bestMove] == 0){
                boards[currentBoard][bestMove] = ai;
                cout <<"AI "<< currentBoard <<" "<<bestMove<<endl;
                currentBoard = bestMove;

                mainBoard[currentBoard] = checkWinCondition(boards[currentBoard]);
            }
        }

        currentTurn = -currentTurn;

        for ( int i = 0; i < 10; i++){
            int f = checkWinCondition(boards[i]);
            mainBoard[i] = f;

        }

        print_board();

     }else{
         int subgrid, square;

         cout <<"Enter Sub Grid Number and square: ";
         cin >> subgrid >> square;

         if(checkWinCondition(boards[subgrid]) != 0){
            cout <<"Not Valid Sub grid."<<endl;
            game();
         }

         if (boards[subgrid][square]!=0){
            cout << "Please Enter Empty Space: ";
            cin >> subgrid >> square;
         }else{
             boards[subgrid][square] = 1;

             mainBoard[subgrid] = checkWinCondition(boards[subgrid]);
         }

         currentBoard = square;
         currentTurn = -currentTurn;
     }

     MOVES +=2;

     int f =checkWinCondition(mainBoard);

     if(f == -1){
        cout <<"AI Wins"<<endl;
        return;
     }else if( f == 1){
         cout <<"Player Wins"<<endl;
         return;
     }

     game();
}

int main(){
    print_board();
    int coun = 0;
    for ( int i = 0; i < 9; i++){
        bestScore[i] = -1e9;
    }

    game();



}
