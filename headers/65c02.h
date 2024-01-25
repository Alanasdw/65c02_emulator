
#include <stdint.h>

enum e_reg
{
    A,
    Y,
    X,
    PCH,
    PCL,
    REG_COUNT
};

int8_t read_reg( int reg_num);
