#include <stdlib.h>
#include <stdio.h>

int input2[] = { 0, 2, 7, 0 };
int input[] = { 4, 10, 4, 1, 8, 4, 9, 14, 5, 1, 14, 15, 0, 15, 3, 5 };
int **variations;
int numVariations=0;
int numMemBanks;

int foundInfiniteLoop( const int input[] ) {
    for( int i=0; i<numVariations; i++ ) {
        int allBanksMatch = 1;
        for( int j=0; j<numMemBanks; j++ ) {
            if( variations[i][j] != input[j] ) {
                allBanksMatch = 0;
                break;
            }
        }

        if( allBanksMatch ) {
            return i;
        }
    }

    return 0;
}

int largestBank( const int input[] ) {
    int largestBankSize = 0;
    int largestBankIndex = 0;
    for( int i=0; i<numMemBanks; i++ ) {
        if( input[i] > largestBankSize ) {
            largestBankIndex = i;
            largestBankSize = input[i];
        }
    }

    return largestBankIndex;
}

void redistributeBlocks( void ) {
    int bank = largestBank( input );
    int numBlocks = input[ bank ];

    printf( "Redistributing bank: %d\n", bank );

    // Clear blocks
    input[ bank++ ] = 0;

    // Distribute blocks
    while( numBlocks > 0 ) {
        if( bank >= numMemBanks ) {
            bank = 0;
        }
        ++input[ bank++ ];
        numBlocks--;
    }
}

void copyVariation( const int input[], int index ) {
    variations[index] = malloc( numMemBanks * sizeof( int ) );
    for( int i=0; i<numMemBanks; i++ ) {
        variations[index][i] = input[i];
    }

}

void addVariation( const int input[] ) {
    int **tmpVariations = variations;
    variations = malloc( (numVariations+1) * sizeof(int*) );

    // Copy old Variations
    for( int i=0; i<numVariations; i++ ) {
        copyVariation( tmpVariations[i], i );
        free( tmpVariations[i] );
    }

    free(tmpVariations);

    // Copy new input
    copyVariation( input, numVariations++ );
}

void printInput( const int input[] ) {
    printf( "Current Bank Dist: " );
    for( int i=0; i<numMemBanks; i++ ) {
        printf( "%d", input[i] );
    }
    printf("\n");
}

int main( void ) {

    numMemBanks = sizeof( input ) / sizeof( int );
    printInput( input );

    while( !foundInfiniteLoop( input ) ) {
        addVariation(input);
        redistributeBlocks();
        printInput( input );
    }

    int lengthOfLoop = numVariations - foundInfiniteLoop( input );

    printf( "length of the loop is: %d\n", lengthOfLoop );
}
