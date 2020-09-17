#include<stdio.h>

/*
* This method will loop through all the pids and print out a process status for each process
*/
void printStatus(int *pid, int stateInformationFlag, int userTimeFlag, int systemTimeFlag, int virtualMemoryFlag, int commandLineFlag) {
  for (int i = 0; i < sizeof(pid); ++i) {
	char pidString[20];
	itoa(pid[i], pidString, 10);
	char processStatus[];
	char state;
	long size;
	unsigned long userTime;
	unsigned long systemTime;
	char commandLine[1024];

	if(stateInformationFlag) {
	    //char stateInfoChar = find way to get the single-character state information about the process. This information is found in the stat file in
	    //process's directory, looking at the third ("state") field. Note that the information that you read from the stat file is a charcter string.
	    //This option defaults to false aka 0
		FILE *fp = fopen(strcat(strcat("/proc/", pidString),"/stat"), "r");
		fscanf(fp, "%c", &state);
		fclose(fp); 
	}
	if(userTimeFlag) {
	    //userTime = find way to display the amount of user time consumed by this process. This information is found in the stat file in process's directory,
        //looking at the "utime" field. This option defaults to true aka 1
		FILE *fp = fopen(strcat(strcat("/proc/", pidString),"/stat"), "r");
		fscanf(fp, "%lu", &userTime);
		fclose(fp);	
	}
	if(systemTimeFlag) {
	    //systemTime = find way to get the amount of system time consumed so far by this process.
	    //this information is found in the stat file in process's directory, looking at the "stime" field.
        //this option defaults to false aka 0
		FILE *fp = fopen(strcat(strcat("/proc/", pidString),"/stat"), "r");
		fscanf(fp, "%lu", &systemTime);
		fclose(fp);
	}
	if(virtualMemoryFlag) {
	    //virtualMemory = find way to get the amount of virtual memory currently being used (in pages) by this program. This information is 
	    //found in the statm file in process's directory, looking at first ("size") field. This option defaults to false aka 0
		FILE *fp = fopen(strcat(strcat("/proc/", pidString), "/statm"), "r");
		fscanf(fp, "%ld", &size);
		fclose(fp); 	
	}
	if(commandLineFlag) {
	    //commandLine = find way to get the command-line that started this program. This information is found in the cmdline file in process's directory.
	    //Be careful on this one, because this file contains a list of null (zero byte) terminated strings.
		FILE *fp = fopen(strcat(strcat("/proc/", pidString), "/cmdline"), "r");
		fgets(commandLine, sizeof commandLine, fp);
		fclose(fp);
	}
	char[] stateString;
	char[] userTimeString;
	char[] systemTimeString;
	char[] sizeString;
	char[] commandLineString;
	// when making the strings, need to remember to add a space to the end of each one
	printf("%s: %s\n", pid[i], + state + userTime + systemTime + size + commandLine);
  }
}

/*
* Main method of program, first processes the command line args, then prints out process info
*
*/
int main(int argc, char **argv) {
    int pid[];
    int stateInformationFlag = 0;
    int userTimeFlag = 1;
    int systemTimeFlag = 0;
    int virtualMemoryFlag = 0;
    int commandLineFlag = 1;
    char commandLine[];
    //the arguments are processed in order from left to right
    for (int i = 0; i < argc; ++i) {
	if(i = 1) {
	    if(argv[1] == "-p") {
		pid[1] = argv[2];
		++i; //use this to skip over the next argv, which would be a number, so we don't have to deal with that case
	    } else {
	  		//pid[] = get all current user process's pids and put in array

			//get the current user id from the passwd file
	    	struct passwd *p = getpwuid(getuid());
			char userId[];
			if(p) {
				userId = p->pw_name;
			}
		}
	}
	else if(argv[i] == "-s") {
            //enables displaying the single char state information
	    stateInformationFlag = 1;   
	}
	else if(argv[i] == "-s-") {
            //disables displaying the single char state information
	    stateInformationFlag = 0;   
	}
	else if(argv[i] == "-U-") {
	    //disables displaying of the user time
	    userTimeFlag = 0;
	}
	else if(argv[i] == "-U") {
	    //enables displaying of the user time
	    userTimeFlag = 1;
	}
	else if(argv[i] == "-S") {
            //enables displaying the amount of system time consumed so far by process
	    systemTimeFlag = 1;	
	}
	else if(argv[i] == "-S-") {
            //disables displaying the amount of system time consumed so far by process
	    systemTimeFlag = 0;	
	}
	else if(argv[i] == "-v") {
	    //enables displaying the amount of virtual memory a process is using
	    virtualMemoryFlag = 1;
	}
	else if(argv[i] == "-v-") {
	    //disables displaying the amount of virtual memory a process is using
	    virtualMemoryFlag = 0;
	}
	else if(argv[i] == "-c-") {
	    //disables displaying of the command line of the process
	    commandLineFlag = 0;	
	}
	else if(argv[i] == "-c") {
	    //enables displaying of the command line of the process
	    commandLineFlag = 1;	
	}
	else {
		//exit program when invalid command is entered e.g. "-f"
		printf("Error: invalid command was entered");
		exit();
	}
    }
    printStatus(pid, stateInformationFlag, userTimeFlag, systemTimeFlag, virtualMemoryFlag, commandLineFlag);
}