#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(int argc, char **argv) 
{
    int intial = memsize();
    printf("Initial memory usage: %d bytes\n", intial); // Task 2.5.a

    void *mem = malloc(20000); // Task 2.5.b
    printf("# Bytes of memory after malloc 20k bytes: %d bytes\n", memsize()); // Task 2.5.c

    free(mem); // Task 2.5.d
    printf("# Bytes of memory after free: %d\n", memsize()); // Task 2.5.e
    return 0;
}

