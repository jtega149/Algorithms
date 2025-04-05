#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include<unordered_set>
using namespace std;
#define MIXLENGTH 50 //Need to shorten for it to work 

class PuzzleState{
    public:
        PuzzleState(){
            for(int i = 0; i < 16; i++){
                puzzle[i] = 0;
            }
            steps = 0;
        }
        PuzzleState(int arr[]){
            for (int i = 0; i < 16; i++){
                puzzle[i] = arr[i];
            }
            steps = 0;
        }
        PuzzleState(const PuzzleState& other) {
            for (int i = 0; i < 16; i++) {
                puzzle[i] = other.puzzle[i];
            }
            steps = other.steps;
        }
        //~PuzzleState() {delete[] puzzle;}

        size_t hash() const {
            size_t h = 0;
            for (int i = 0; i < 16; i++) {
                h = h * 31 + puzzle[i];
            }
            return h;
        }
/*
        int* getCopyOfArray(){
            int* copy = new int[16];
            for (int i = 0; i < 16; i++) {
                copy[i] = puzzle[i];
            }
            return copy;
        }
*/

        bool operator==(const PuzzleState& other) const{
            for(int i = 0; i < 16; i++){
                if(other.puzzle[i] != puzzle[i]){
                    return false;
                }
            }
            return true;
        }
        bool operator!=(const PuzzleState& other) const{
            return !(*this == other);
        }
        void operator=(const PuzzleState& other){
            for(int i = 0; i < 16; i++){
                puzzle[i] = other.puzzle[i];
            }
        }
        int incorrectPieces(){
            int incorrectPieces = 0;
            for(int i = 0; i < 16; i++){
                if(puzzle[i] != i + 1){
                    incorrectPieces++;
                }
            }
            return incorrectPieces;
        }
        void incSteps(){ steps++; }
        int getSteps(){ return steps; }
        int puzzle[16];
        int steps;
};
namespace std {
    template<> struct hash<PuzzleState> {
        size_t operator()(const PuzzleState& p) const {
            return p.hash();
        }
    };
}

void printpuzzle( int * a)
{  int i,j;
   printf("\n");
   for( i=0; i<4; i++)
   {  for( j=0; j<4; j++)
         if( a[4*i+j] == 16 )
	   printf("   ");
         else
	   printf(" %2d", a[4*i+j]);
      printf("\n");
   }
}

void initpuzzle( int * a)
{  int i,j;
   for( i=0; i<4; i++)
     for( j=0; j<4; j++)
       a[4*i+j] = 4*i+j+1;
}

int left( int * a)
{  int i,j, gapx, gapy;
   for( i=0; i<4; i++)
     for( j=0; j<4; j++)
       if( a[4*i+j] == 16 )
	 { gapx = j; gapy = i;}
   /*found gap, now move it left */
   if( gapx == 0 ) /* cannot move left */
     return (0);
   else /* move left */
   { a[4*gapy + gapx] = a[4*gapy + gapx -1];
     a[4*gapy + gapx -1] = 16;
     return(1);
   }
}

int right( int * a)
{  int i,j, gapx, gapy;
   for( i=0; i<4; i++)
     for( j=0; j<4; j++)
       if( a[4*i+j] == 16 )
	 { gapx = j; gapy = i;}
   /*found gap, now move it right */
   if( gapx == 3 ) /* cannot move right */
     return (0);
   else /* move right */
   { a[4*gapy + gapx] = a[4*gapy + gapx +1];
     a[4*gapy + gapx +1] = 16;
     return(1);
   }
}

int up( int * a)
{  int i,j, gapx, gapy;
   for( i=0; i<4; i++)
     for( j=0; j<4; j++)
       if( a[4*i+j] == 16 )
	 { gapx = j; gapy = i;}
   /* found gap, now move it up */
   if( gapy == 0 ) /* cannot move up */
     return (0);
   else /* move up */
   { a[4*gapy + gapx] = a[4*gapy + gapx -4];
     a[4*gapy + gapx -4] = 16;
     return(1);
   }
}

int down( int * a)
{  int i,j, gapx, gapy;
   for( i=0; i<4; i++)
     for( j=0; j<4; j++)
       if( a[4*i+j] == 16 )
	 { gapx = j; gapy = i;}
   /* found gap, now move it down */
   if( gapy == 3 ) /* cannot move down */
     return (0);
   else /* move down */
   { a[4*gapy + gapx] = a[4*gapy + gapx +4];
     a[4*gapy + gapx +4] = 16;
     return(1);
   }
}

int main()
{ int b[16]; int i, j;
  initpuzzle( b );
  printf(" Created Puzzle\n");
  printpuzzle( b );
  printf(" Now mixing up \n");
  srand(time(NULL));

  for( i=0; i< MIXLENGTH; i++)
  {  j= rand()%8;
    switch(j)
    {  case 0 : left(b); break;
       case 1 : left(b); left(b); break;
       case 2 : right(b); break;
       case 3 : right(b); right(b); break;
       case 4 : up(b); break;
       case 5 : up(b); up(b); break;
       case 6 : down(b); break;
       case 7 : down(b); down(b); break;
       default: printf("impossible\n"); exit(0); break;
    }
  }
/*
  b[0] = 1;
  b[1] = 2;
  b[2] = 3;
  b[3] = 4;
  b[4] = 5;
  b[5] = 6;
  b[6] = 16;
  b[7] = 8;
  b[8] = 9;
  b[9] = 10;
  b[10] = 7;
  b[11] = 11;
  b[12] = 13;
  b[13] = 14;
  b[14] = 15;
  b[15] = 12; 
*/
  printpuzzle(b);
  printf("Now it is mixed up, can you untangle it ?\n");
  /* here enter your homework code; print the puzzle  in the end, and report */
  /* how many steps it took to bring it back to the sorted state */
  
    PuzzleState root(b);
    queue<PuzzleState> q;
    unordered_set<PuzzleState> visited;
    q.push(root);
    visited.insert(root);

    while (!q.empty()){
        PuzzleState current = q.front();
        q.pop();

        if (current.incorrectPieces() == 0){
            cout << "Puzzle is completed, took " << current.getSteps() << endl;
            printpuzzle(current.puzzle);
            return 0;
        }

        //LEFT MOVE STATE
        int leftMove[16];
        for(int i = 0; i < 16; i++){
            leftMove[i] = current.puzzle[i];
        }
        if( left(leftMove) == 1){
            PuzzleState leftState(leftMove);
            leftState.incSteps();
            if(visited.find(leftState) == visited.end()){
                q.push(leftState);
                visited.insert(leftState);
            }
        }

        //RIGHT MOVE STATE
        int rightMove[16];
        for(int i = 0; i < 16; i++){
            rightMove[i] = current.puzzle[i];
        }
        if ( right(rightMove) == 1){
            PuzzleState rightState(rightMove);
            rightState.incSteps();
            if(visited.find(rightState) == visited.end()){
                q.push(rightState);
                visited.insert(rightState);
            }
        }

        //UP MOVE STATE
        int upMove[16];
        for(int i = 0; i < 16; i++){
            upMove[i] = current.puzzle[i];
        }
        if ( up(upMove) == 1){
            PuzzleState upState(upMove);
            upState.incSteps();
            if(visited.find(upState) == visited.end()){
                q.push(upState);
                visited.insert(upState);
            }
        }

        //DOWN MOVE STATE
        int downMove[16];
        for(int i = 0; i < 16; i++){
            downMove[i] = current.puzzle[i];
        }
        if( down(downMove) == 1){
            PuzzleState downState(downMove);
            downState.incSteps();
            if(visited.find(downState) == visited.end()){
                q.push(downState);
                visited.insert(downState);
            }
        }
    }

    cout << "Testing end point !!!" << endl;
    return 0;
}