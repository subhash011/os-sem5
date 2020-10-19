#include "types.h"
#include "user.h"
#include "memlayout.h"

void printmsg(int status, void* v2p, void* vaddr) {
    switch (status) {
        case -1:
            printf(1, "Page not found or address 0x%x not accessible from user space.\n", vaddr);
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
    void *v2p_num, *v2p_globalnum, *v2p_invalid, *v2p_kernaddr, *v2p_devmem, *v2p_temp;
    int s_num = v2paddr(&v2p_num, &num);
    int s_globalnum = v2paddr(&v2p_globalnum, &globalnum);
    void* invalid = 0x0;
    int s_invalid = v2paddr(&v2p_invalid, invalid);
    int a[] = {1, 2, 3, 4};
    void* kernaddr = (void *) (KERNBASE + 0x1);
    int s_kernaddr = v2paddr(&v2p_kernaddr, kernaddr);
    void* devmem = (void *) (DEVSPACE + 0x1);
    int s_devmem = v2paddr(&v2p_devmem, devmem);
    printmsg(s_num, v2p_num, &num);
    printmsg(s_globalnum, v2p_globalnum, &globalnum);
    printmsg(s_invalid, v2p_invalid, invalid);
    printmsg(s_kernaddr, v2p_kernaddr, kernaddr);
    printmsg(s_devmem, v2p_devmem, devmem);
    printf(1, "===== Array elements start =====\n");
    for (int i = 0; i < sizeof(a)/sizeof(a[0]); i++) {
        int s_temp = v2paddr(&v2p_temp, &a[i]);
        printmsg(s_temp, v2p_temp, &a[i]);
    }
    exit();
}