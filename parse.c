#include <stdio.h>
#include "runt.h"

static runt_int loader(runt_vm *vm)
{
    runt_load_stdlib(vm);
    return runt_is_alive(vm);
}

int main(int argc, char *argv[])
{
    return irunt_begin(argc, argv, loader);
}
