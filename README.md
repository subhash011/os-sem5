## Lab-5
#### Aim - add a system call v2paddr which takes the virtual address in the address space of the calling process and returns the corresponding physical address
#### Files changed
    1. Makefile - add the syscall test file so that it can be used as a shell command.
    2. syscall.h - add SYS_v2paddr to map to v2paddr syscall.
    3. user.h - add the system call to the existing system calls
    4. user.S - bind the system call to the SYSCALL
    5. sysproc.c - add the new method sys_v2paddr which takes the input and calls v2paddr in proc.c.
    6. proc.c - add the method v2paddr which takes a virtual address gives the below mentioned return values.
       Return values:
         1. -1 if the required page entry not found or if the address is does not lie in the user space.
         2. If the above case fails, it returns 0 and puts the physical address in the first argument.
    7. defs.h - add the new system call v2paddr declared in proc.c to the definations file. 
    8. test_v2paddr.c - test file for testing the system call.
#### The system call v2paddr
    1. Input arguments:
       uint* pa - this is where the physical address is stored.
       void* va - the virtual address
       Example:
       code:
           addr_t pa;
           int i = 0;
           addr_t* va = (addr_t*)&i;
           int status = v2paddr(&pa, va);
           printf(1, "virtual address is 0x%x, physical address is 0x%x\n", va, pa);
       After the call to v2paddr, the status is 0 if a mapping exists, it returns -1 if there are any other errors or
       the pages are absent or the address cannot be accessed in the user mode.
       The physical address is put into the variable pa, the virtual address is the variable va which remains unchanged.
             