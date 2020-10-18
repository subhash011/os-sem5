#include "types.h"
#include "user.h"
#include "memlayout.h"

void printmsg(int v2p, int vaddr) {
    switch (v2p) {
        case -2:
            printf(1, "The page directory is absent\n");
            break;
        case -1:
            printf(1, "The page table in the directory is absent\n");
            break;
        case 0:
            printf(1, "The virtual address 0x%x cannot be accessed in the user mode.\n", vaddr);
            break;
        default:
            printf(1, "Virtual address: 0x%x -> Physical address: 0x%x\n", vaddr, v2p);
    }
}

int globalnum = 1;

int
main(int argc, char *argv[])
{
    int num = 0;
    int v2p_num = v2paddr((int) &num);
    int v2p_globalnum = v2paddr((int) &globalnum);
    int invalid = 0x0;
    int v2p_invalid = v2paddr(invalid);
    int a[] = {1, 2, 3, 4, 5, 6, 7};
    int kernaddr = KERNBASE + 0x1;
    int v2p_kernaddr = v2paddr(kernaddr);
    int devmem = DEVSPACE + 0x1;
    int v2p_devmem = v2paddr(devmem);
    printmsg(v2p_num, (int) &num);
    printmsg(v2p_globalnum, (int) &globalnum);
    for (int i = 0; i < sizeof(a)/sizeof(a[0]); i++) {
        int v2p_temp = v2paddr((int) &a[i]);
        printmsg(v2p_temp, (int) &a[i]);
    }
    printmsg(v2p_invalid, invalid);
    printmsg(v2p_kernaddr, kernaddr);
    printmsg(v2p_devmem, devmem);
    exit();
}