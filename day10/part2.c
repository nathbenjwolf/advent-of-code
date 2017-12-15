#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int listLen = 256;
int currIdx = 0;
int skip = 0;

//int lenInputs[] = {3,4,1,5};
//int lenInputs[] = { 212,254,178,237,2,0,1,54,167,92,117,125,255,61,159,164 };
//char lenInputsChar[] = "AoC 2017";
char lenInputsChar[] = "212,254,178,237,2,0,1,54,167,92,117,125,255,61,159,164";

void reverseListSegment( int list[], int lenInput ) {
    for( int i=0; i<(lenInput/2); i++ ) {
        // Swap the numbers
        int idx1 = currIdx + i < listLen ? currIdx + i : currIdx + i - listLen;
        int idx2 = currIdx + lenInput - 1 - i < listLen ? currIdx + lenInput - 1 - i : currIdx + lenInput - 1 - i - listLen;
        int tmp = list[idx1];
        list[idx1] = list[idx2];
        list[idx2] = tmp;
    }
}

void shiftCurrIdx( int lenInput ) {
    currIdx = ( currIdx + lenInput + skip ) % listLen;
}

void printList( int list[] ) {
    printf( "Dense Hash is: " );
    for( int i=0; i<16; i++ ) {
        printf( "%02x", list[i] );
   }
   printf( "\n" );
}

int main( void ) {
    int list[ listLen ];

    // Generate List
    for( int i=0; i<listLen; i++ ) {
        list[i] = i;
    }

    // Get size of lenInputs
    int inputSize = ( sizeof( lenInputsChar ) / sizeof( char ) ) - 1;

    // Convert char list to int list
    int lenInputs[ inputSize + 5 ];
    for( int i=0; i<inputSize; i++ ) {
        lenInputs[i] = lenInputsChar[i];
    }

    // Add tail bits
    lenInputs[ inputSize ] = 17;
    lenInputs[ inputSize + 1 ] = 31;
    lenInputs[ inputSize + 2 ] = 73;
    lenInputs[ inputSize + 3 ] = 47;
    lenInputs[ inputSize + 4 ] = 23;

    inputSize += 5;

    int numIterations = 64;

    for( int j=0; j<numIterations; j++ ) {
        for( int i=0; i<inputSize; i++ ) {
            reverseListSegment( list, lenInputs[i] );
            shiftCurrIdx( lenInputs[i] );
            skip++;
        }
    }

    // Create Dense Hash
    int denseHash[16];
    for( int i=0; i<16; i++ ) {
        int idx = (i*16);
        denseHash[ i ] = list[ idx ] ^ list[ idx+1 ];
        for( int j=2; j<16; j++ ) {
            denseHash[ i ] ^= list[ idx + j ];
        }
    }

    // print Dense hash in hex
    printList( denseHash );

    int result = list[0] * list[1];
    printf( "result is: %d\n", result );
}
