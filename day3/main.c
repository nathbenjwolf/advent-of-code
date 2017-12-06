#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main( int argc, char * argv[] ) {
    int input = atoi( argv[1] );
    int squareSize = (int) sqrt( input );

    // Squares can only be of odd size
    if( ( squareSize % 2 ) == 0 ) {
        squareSize--;
    }

    int removedNums = pow( squareSize, 2 );

    int remainingNums = input - removedNums;
    // 2 more entries per side on the next layer of spiral
    int sideSize = squareSize+2;

    int indexDiff;
    int manhatDist;

    if( remainingNums == 0 ) {
        // Bottom corner of perfect square
        manhatDist = squareSize-1;
    }


    int midDist = sideSize/2;
    while( remainingNums > 0 ) {
        if( remainingNums < sideSize ) {
            indexDiff = abs( remainingNums - midDist );
            manhatDist = indexDiff + midDist;
        }
        remainingNums -= ( sideSize - 1 );
    }

    printf( "manhattan distance is: %d\n", manhatDist );
}
