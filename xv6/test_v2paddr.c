#include "types.h"
#include "user.h"
#include "memlayout.h"

void printmsg(int status, addr_t v2p, addr_t* vaddr) {
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
    addr_t *numaddr, *globaladdr, *random,
           *kernaddr, *devmem, *tempaddr;
    // physical addresses
    addr_t v2p_num, v2p_globalnum, v2p_random,
         v2p_kernaddr, v2p_devmem, v2p_temp;
    // status codes
    int s_num, s_globalnum, s_random, s_kernaddr,
        s_devmem, s_temp;

    numaddr  = (addr_t *)&num;
    globaladdr = (addr_t *)&globalnum;
    random  = (void *) 0x2999;
    kernaddr = (void *) (KERNBASE + 0x1);
    devmem = (void *) (DEVSPACE + 0x1);

    // local variable va to pa.
    s_num = v2paddr(&v2p_num, numaddr);
    printmsg(s_num, v2p_num, numaddr);

    // global variable va to pa.
    s_globalnum = v2paddr(&v2p_globalnum, globaladdr);
    printmsg(s_globalnum, v2p_globalnum, globaladdr);

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
        tempaddr = (addr_t *)&a[i];
        s_temp = v2paddr(&v2p_temp, tempaddr);
        printmsg(s_temp, v2p_temp, tempaddr);
    }
    exit();
}