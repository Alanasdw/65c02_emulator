
#include "../headers/65c02.h"

static int8_t regs[ REG_COUNT];

int8_t read_reg( int reg_num)
{
    return regs[ reg_num];
}
