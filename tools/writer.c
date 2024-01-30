
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEM_SIZE ( 0x10000)

int main( void)
{
    char *data = malloc( MEM_SIZE * sizeof(char));
    memset( data, 0xea, MEM_SIZE);

    // program start location
    data[0x7FFC] = 0x00;
    data[0x7FFD] = 0x80;

    // the assembly byte code
    data[0x8000] = 0xea;

    FILE *output = fopen( "../romfile", "wb+");

    fwrite( data, sizeof(char), MEM_SIZE, output);

    fclose( output);
    output = NULL;

    free( data);
    data = NULL;
    return 0;
}
