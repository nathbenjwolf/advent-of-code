#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int listLen = 256;
int currIdx = 0;
int skip = 0;

//int lenInputs[] = {3,4,1,5};
int lenInputs[] = { 212,254,178,237,2,0,1,54,167,92,117,125,255,61,159,164 };

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
    printf( "List is: " );
    for( int i=0; i<listLen; i++ ) {
        printf( "%d, ", list[i] );
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
    int inputSize = sizeof( lenInputs ) / sizeof( int );

    for( int i=0; i<inputSize; i++ ) {
        reverseListSegment( list, lenInputs[i] );
        shiftCurrIdx( lenInputs[i] );
        skip++;
    }

    printList( list );

    int result = list[0] * list[1];
    printf( "result is: %d\n", result );
}
