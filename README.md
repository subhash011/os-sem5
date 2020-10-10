## This branch contains the work done in lab4
#### Aim - add a system call getcount which gives the number of times a system call was called by the calling process.
#### Files changed
    1. Makefile - add the syscall
    2. proc.h   - add syscallcount as another field in the struct proc
    3. syscall.h - add SYS_getcount (used for getcount) and SYS_numcalls (used to keep track of total number of syscalls)
    4. syscall.c - maded changes to update curproc -> syscallcount when a syscall is made
    5. user.h - add the system call to the existing system calls
    6. user.S - bind the system call to the SYSCALL
    7. sysproc.c - add the new method getcount which does all the required operations
    8. getcount.c - test file for testing the system call count getter.
