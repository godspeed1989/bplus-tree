#include "bpt.h"

int main()
{
    u32 i;
    initial_bpt();

    for(i = 0; i < M*100; ++i)
        insert_in_bpt(i, NULL);


    return 0;
}

