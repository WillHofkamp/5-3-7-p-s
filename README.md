537 ps

The goal of this project was to execute a version of the ps command such that it displayed information about running programs upon being called.

In order to accomplish this task, we wrote functions that parsed the command line arguments to find flags that indicated exact information was being asked to dispaly using the command.

Based on that command we extracted, information regarding amount of user time consumed, amount of system time consumed, single-character state information, amount of virtual memory, and information from the cmdline, stat and statm files.

We then display all this information to the user as requested. 
