
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <string.h>

#define MEM_SIZE ( 0x10000)
#define REG_COUNT ( 6)
#define MEM_SHOW_RANGE ( 10)

struct s_mem
{
    void *data;
};

struct s_65c02
{
    uint8_t A;
    uint8_t Y;
    uint8_t X;

    uint16_t PC;
    uint8_t S;

    union
    {
        uint8_t P;
        struct
        {
            uint8_t C : 1;
            uint8_t Z : 1;
            uint8_t I : 1;
            uint8_t D : 1;
            uint8_t B : 1;
            uint8_t : 1;
            uint8_t V : 1;
            uint8_t N : 1;
        } flag;
    } status;
};

typedef struct s_65c02 S65c02;
typedef struct s_mem SMem;

void init_mem( SMem *mem)
{
    mem -> data = malloc( MEM_SIZE * sizeof(char));

    // load program from romfile
    FILE *rom = fopen( "romfile", "rb");
    fread( mem -> data, sizeof(char), MEM_SIZE, rom);

    fclose( rom);
    rom = NULL;

    return;
}

void destroy_mem( SMem *mem)
{
    free( mem -> data);
    mem -> data = NULL;
    return;
}

void reset_cpu( S65c02 *cpu, SMem mem)
{
    cpu -> PC = (((uint8_t *)mem.data)[0x7FFD] << 0x8) + 
                ((uint8_t *)mem.data)[0x7FFC];
    cpu -> status.P = 0xF7; // set to (**1101**) = (N,V,,B,D,I,Z,C)
    return;
}

void cmd_update( S65c02 cpu, SMem mem)
{
    // clear terminal
    printf("\e[1;1H\e[2J");

    // register
    printf("-------------------register---------------\n");
    printf("%-3s: 0x%.2hhx\n", "A", cpu.A);
    printf("%-3s: 0x%.2hhx\n", "Y", cpu.Y);
    printf("%-3s: 0x%.2hhx\n", "X", cpu.X);
    printf("%-3s: 0x%.4hx\n", "PC", cpu.PC);
    printf("%-3s: 0x%.2hhx\n", "S", cpu.S);
    printf("%-3s: 0x%.2hhx", "P", cpu.status.P);
    // add status meaning
    printf(" (");
    uint8_t reader = (uint8_t)0x01;
    char names[ 8][ 30] = { "Carry", "Zero", "IRQB disable", "Decimal mode", "BRK command", "unused", "Overflow", " Negative"};
    for ( int i = 0; i < 8; i += 1)
    {
        if ( i != 0)
        {
            printf(",");
        }// if
        
        if ( cpu.status.P & reader)
        {
            // set is read
            printf("\033[31m");
        }// if
        else
        {
            // unset is green
            printf("\033[32m");
        }// else
        printf(" %s", names[ i]);
        printf("\033[0m");
        reader = reader << 1;
    }// for i

    // reset the colors
    printf("\033[0m)\n");

    // code around PC
    printf("-------------------code---------------\n");
    for ( int i = -1 * MEM_SHOW_RANGE; i < MEM_SHOW_RANGE; i += 1)
    {
        printf("%.4hx: ", cpu.PC + i * 3);
        for ( int j = 0; j < 3; j += 1)
        {
            printf("%.2hhx ", ((char *)mem.data)[ cpu.PC + i * 3 + j]);
        }// for j
        printf("\n");
    }// for i


    return;
}

int main( void)
{
    S65c02 CPU;
    SMem mem;
    init_mem( &mem);

    reset_cpu( &CPU, mem);

    cmd_update( CPU, mem);

    destroy_mem( &mem);

    return 0;
}
