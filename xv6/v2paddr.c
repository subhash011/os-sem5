#include "types.h"
#include "user.h"
#include "memlayout.h"

void test(void);

int
main(int argc, char *argv[])
{
    int i = 0;
    int invalid = 0x1;
    int a[] = {1, 2};
    printf(1, "variable: virtual: %x, physical: %x\n", &i, v2paddr((int) &i));
    for (i = 0; i < 2; i++) {
        printf(1, "array[%d]: virtual: %x, physical: %x\n", i, &a[i], v2paddr((int) &a[i]));
    }
    printf(1, "variable: virtual: %x, physical: %x\n", invalid, v2paddr(invalid));
    printf(1, "KERNBASE: virtual: %x, physical: %x\n", KERNBASE + 0x1, v2paddr(KERNBASE + 0x1));
    exit();
}