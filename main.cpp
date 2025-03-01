#include <iostream>
#include "handler.h"

int main(void)
{
    
    Handler* program = new Handler();

    program->Loop();

    delete program;

    return 0;
}