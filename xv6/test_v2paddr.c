#include "types.h"
#include "user.h"
#include "memlayout.h"

void printmsg(int status, uint v2p, void* vaddr) {
    switch (status) {
        case -1:
            printf(1, "Page not found or not enough permissions to access address 0x%x.\n", vaddr);
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
    // virtual addresses
    void *random, *kernaddr, *devmem;
    // physical addresses
    uint v2p_num, v2p_globalnum, v2p_random,
         v2p_kernaddr, v2p_devmem, v2p_temp;
    // status codes
    int s_num, s_globalnum, s_random, s_kernaddr,
        s_devmem, s_temp;
    random  = (void *) 0x345;
    kernaddr = (void *) (KERNBASE + 0x1);
    devmem = (void *) (DEVSPACE + 0x1);

    // local variable va to pa.
    s_num = v2paddr(&v2p_num, &num);
    printmsg(s_num, v2p_num, &num);

    // global variable va to pa.
    s_globalnum = v2paddr(&v2p_globalnum, &globalnum);
    printmsg(s_globalnum, v2p_globalnum, &globalnum);

    // just a random integer va to pa.
    s_random = v2paddr(&v2p_random, random);
    printmsg(s_random, v2p_random, random);

    // kernel space va to pa.
    s_kernaddr = v2paddr(&v2p_kernaddr, kernaddr);
    printmsg(s_kernaddr, v2p_kernaddr, kernaddr);

    // device memory space va to pa.
    s_devmem = v2paddr(&v2p_devmem, devmem);
    printmsg(s_devmem, v2p_devmem, devmem);

    // array va to pa.
    printf(1, "===== Array elements start =====\n");
    int a[] = {1, 2, 3, 4};
    for (int i = 0; i < sizeof(a)/sizeof(a[0]); i++) {
        s_temp = v2paddr(&v2p_temp, &a[i]);
        printmsg(s_temp, v2p_temp, &a[i]);
    }
    exit();
}