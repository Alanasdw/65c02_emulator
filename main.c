
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MEM_SIZE 65535

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

void init_mem( SMem mem)
{
    mem.data = malloc( MEM_SIZE * sizeof(char));
    return;
}

void destroy_mem( SMem mem)
{
    free( mem.data);
    mem.data = NULL;
    return;
}

void reset_cpu( S65c02 cpu, SMem mem)
{

    return;
}

int main( void)
{
    S65c02 CPU;
    SMem mem;
    init_mem( mem);

    destroy_mem( mem);

    return 0;
}
