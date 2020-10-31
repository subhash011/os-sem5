## Lab-6
#### Aim - trace how the state of a process changes over its lifetime.
#### Files changed
    1. proc.c - this is where all the print statements were added for tracing
    2. console.c - to print in the wakeup function the console lock has to be released and acquire between call to wakeup which is done here.
    3. benchmark_arith.c - arith benchmark ported onto xv6
    4. benchmark_pipe.c - pipe benchmark ported onto xv6
    5. benchmark_spawn.c - spawn benchmark ported onto xv6 
    6. benchmark_syscall.c - syscall benchmark ported onto xv6
             