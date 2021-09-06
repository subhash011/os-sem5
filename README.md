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
    5. sysproc.c - add the new method sys_v2paddr which takes the input and calls v2paddr in proc.c.
    6. proc.c - add the method v2paddr which takes a virtual address gives the below mentioned return values.
       Return values:
         1. -1 if the required page entry not found or if the address is does not lie in the user space.
         2. If the above case fails, it returns 0 and puts the physical address in the first argument.
    7. defs.h - add the new system call v2paddr declared in proc.c to the definations file. 
    8. test_v2paddr.c - test file for testing the system call.
#### The system call v2paddr
    1. Input arguments:
       addr_t pa - this is where the physical address is stored.
       addr_t* va - the virtual address
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

## Lab-6
#### Aim - trace how the state of a process changes over its lifetime.
#### Files changed
    1. Makefile - add the syscall test file so that it can be used as a shell command.
    2. proc.h   - add syscallcount to store the number of times each system call was called by the process.
    3. syscall.h - add SYS_getcount (used for getcount) and SYS_numcalls (used to keep track of total number of syscalls)
    4. syscall.c - maded changes to increment curproc -> syscallcount[i] when the ith syscall is made by the process.
    5. user.h - add the system call to the existing system calls
    6. user.S - bind the system call to the SYSCALL
    7. sysproc.c - add the new method getcount which does all the required operations
    8. getcount.c - test file for testing the system call count getter.

## Lab-7
#### Aim - simulate the race from the very popular fable where a Hare and a Turtle enters a contest to see who is faster.
#### Work done under the folder lab7/
#### Instructions to run:
    - There are two versions of the simulator
        i. Processes version: Where all the four roles are processes.
        ii. Threads version: Where all the four roles are threads.
    
    - Run the make command in the lab7/ directory to produce the binaries.
        i. To run the processes version, in the same directory run ./bin/processes_main
        ii. To run the threads version, in the same directory run ./bin/threads_main
                  
#### How to reposition during the race
    - The god process polls for input and repositions accordingly.
    - The steps to reposition are same in the processes as well as the threads version
    - The user can press any key once to interrupt the program.
    - Once the program is interrupted, all other threads and processes are blocked so the user can reposition the hare or the turtle using 
      the prompts given. Once done the race starts from the state where the god process left.
