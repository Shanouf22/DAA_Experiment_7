//header files
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>

//structure for storing queen info
struct Queen{
    int id;
    int xCor, yCor;
};

//global variables
int boardSize, numOfSoln;
int solnCounter=0;
struct Queen* queens;
int* tempSoln;
int** solutions;

//function to move a queen ahead
void moveQueen(struct Queen* q){
    if(q->yCor+1<boardSize){
        q->yCor+=1;
    }
}

//functions to check if a queen is under attack
bool isAttackable(struct Queen q1, struct Queen q2){
    if(q1.xCor==q2.xCor||q1.yCor==q2.yCor)
        return true;
    int tempX=abs(q1.xCor-q2.xCor);
    int tempY=abs(q1.yCor-q2.yCor);
    return tempX==tempY;
}

bool isUnderAttack(struct Queen q){
    for(int i=0; i<q.id; i++){
        if(isAttackable(queens[i],q))
            return true;
    }
    return false;
}

//function for transfering the solutions to a permanent array
void transfarSoln(int index){
    for(int i=0; i<boardSize; i++)
        solutions[index][i]=tempSoln[i];
}

//writing the logic for solving n-queen problem
void solveNQueen(int queenId){
    if(queenId==boardSize||solnCounter==numOfSoln)
        return;
    for(int i=0; i<boardSize; i++){
        moveQueen(&queens[queenId]);
        if(isUnderAttack(queens[queenId]))
            continue;
        else{
            tempSoln[queenId]=queens[queenId].yCor;
            solveNQueen(queenId+1);
            if(queenId==boardSize-1){
                transfarSoln(solnCounter);
                solnCounter++;
            }
        }
    }
    queens[queenId].yCor=-1;
}

//function for printing the solution
void printSoln(int solnArr[]){
    for(int i=0; i<boardSize; i++){
        for(int j=0; j<boardSize; j++){
            if(j==solnArr[i])
                printf("Q  ");
            else
                printf(".  ");
        }
        printf("\n");
    }
}

//main function
void main(){
    //taking user input regarding the dimension of the chessboard and number of solutions required
    printf("\nEnter the dimension of the chess-board -----> ");
    scanf("%d",&boardSize);
    printf("Enter the maximum number of solutions to be printed -----> ");
    scanf("%d",&numOfSoln);

    //allocating all the required locations
    queens=(struct Queen*)calloc(boardSize,sizeof(struct Queen));
    tempSoln=(int*)calloc(boardSize,sizeof(int));
    solutions=(int**)calloc(numOfSoln,sizeof(int*));
    for(int i=0; i<numOfSoln; i++)
        solutions[i]=(int*)calloc(boardSize,sizeof(int));

    //initializing the position for each queen
    for(int i=0; i<boardSize; i++){
        queens[i].id=i;
        queens[i].xCor=i;
        queens[i].yCor=-1;
    }

    //solving the N-Queen problem
    solveNQueen(0);
    printf("\n\n");
    for(int i=0; i<solnCounter; i++){
        printf("Solution-%d:\n\n",i+1);
        printSoln(solutions[i]);
        printf("\n\n");
    }

    //deallocating the used locations
    free(queens);
    free(tempSoln);
    for(int i=0; i<numOfSoln; i++){
        free(solutions[i]);
    }
    free(solutions);

}