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
    - The program polls for a keypress to reposition, so the user has two optioons 
        1. press any character and hit enter
        2. hit the enter key twice
    - Both the above methods work, once this is done, all other threads and processes are blocked so the user can reposition the hare or the turtle using 
      the prompts given. Once done the race starts from the state where the god process left.