## Lab-1
#### Aim - Write shell script to get student mark for all the courses

## Lab-2
#### Aim - Write a basic image processing library to perform two operations on an image

## Lab-3
#### Aim - Understand the binary and crack the three passwords stored in the binary file. 

## Lab-4
#### Aim - add a system call getcount which gives the number of times a system call was called by the calling process.
#### Files changed
    1. Makefile - add the syscall test file so that it can be used as a shell command.
    2. proc.h   - add syscallcount to store the number of times each system call was called by the process.
    3. syscall.h - add SYS_getcount (used for getcount) and SYS_numcalls (used to keep track of total number of syscalls)
    4. syscall.c - maded changes to increment curproc -> syscallcount[i] when the ith syscall is made by the process.
    5. user.h - add the system call to the existing system calls
    6. user.S - bind the system call to the SYSCALL
    7. sysproc.c - add the new method getcount which does all the required operations
    8. getcount.c - test file for testing the system call count getter.

## Lab-5
#### Aim - add a system call v2paddr which takes the virtual address in the address space of the calling process and returns the corresponding physical address
#### Files changed
    1. Makefile - add the syscall test file so that it can be used as a shell command.
    2. syscall.h - add SYS_v2paddr to map to v2paddr syscall.
    3. user.h - add the system call to the existing system calls
    4. user.S - bind the system call to the SYSCALL
    5. sysproc.c - add the new method sys_v2paddr which converts va to pa.
       Return values:
         1. -2 if the required page directory is absent.
         2. -1 if the page table entry is absent.
         3. 0 if the address does not lie in the user space.
         4. If all the above cases fail, it returns the physical address of the given virtual address.  
    6. test_v2paddr.c - test file for testing the system call.