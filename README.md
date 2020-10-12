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
