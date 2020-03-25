/*
 * @author: Jordi Jaspers
 * @date 17/04/2020
 * @title: Excercise_3 C program for implementation of FCFS 
**/

//include libraries
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>

#define NUMOF_CHILDREN 5
#define MAX_COUNT  50

int const PRIORITY_LIST[5] = {-20, -10, 0, 10, 19};

//struct for process
struct node {
  int duration;
  int localID;
  int pid;
  int priority;
};

/*
 *  Calculate average time of every process
 */	
void getavgTime(struct node *processes) 
{   
    int pid;
    int priority;
	float waitTime;
    float duration;
    float waitDuration;
    float total_waitTime = 0.0;
    float total_duration = 0.0; 
	
	//Display processes along with all details 
	printf("ProcessID: | Priority: | Duration: |    WaitTime:   | Duration+Wait: \n"); 
	for (int i=0; i < NUMOF_CHILDREN; i++) 
	{   
        pid = (int) processes[i].pid; 
        priority = (int) processes[i].priority;

        waitTime = ((int) processes[0].duration) - ((int) processes[i].duration);
        duration = (int) processes[i].duration;
        waitDuration = waitTime + duration;

		total_waitTime = total_waitTime + waitTime; 
		total_duration = total_duration + duration; 

		printf("    %d  ",              pid);                //ProcessID:
        printf("          %d  ",        priority);           //Priority:
		printf("     %f  ",             duration );          //Duration:
		printf("     %f  ",             waitTime );          //Wait:
		printf("      %f\n",            waitDuration);       //Duration+Wait:
	} 

	int s=(float)total_waitTime / (float) NUMOF_CHILDREN; 
	int t=(float)total_duration / (float) NUMOF_CHILDREN; 

	printf("Average Job Waiting Time (AJWT)= %d \n",s); 
	printf("Average Job Completion Time (AJCT)= %d \n",t); 
}

/*
 *  Calculate the prime numbers of a certain range.
 */	
void prime(void){
    int i, j, isPrime, counter=0;
    pid_t pid = getpid();

    sleep(1);
    printf("[CHILD %d]Prime numbers between 0 and %d are: \n", pid, MAX_COUNT);

    for (i = 2; i <= MAX_COUNT; i++) {
        isPrime = 1;

        for (j = 2; (j <= i/2)&&(isPrime==1); j++) {
        if (i % j==0) {
            isPrime = 0;
        }
        }

        if(isPrime == 1) {
        printf("[CHILD %d] announces that %d is prime.\n", pid, i);
        counter += 1;
        // sleep(1);
        }
    }
}

/*
 *  Storing all the information of the process.
 */	
void store_process(struct node *process, float duration, int localID, int pid, int priority) {
    // storing the data in the object
    process[localID].localID = localID;
    process[localID].duration = duration;
    process[localID].pid = pid;
    process[localID].priority = priority;

    // printing passed variables
    printf("duration: %d",      process[localID].duration );         
    printf("localID: %d  ",     process[localID].localID );          
    printf("pid: %d\n",         process[localID].pid );           
    printf("priority: %d\n",    process[localID].priority);
}

/*
 *  Main function
 */     
int main() {  
    //local variables
    struct node process[NUMOF_CHILDREN];
    pid_t pids[NUMOF_CHILDREN], pid;
    int retval;
    int priority;
    int n = NUMOF_CHILDREN;
    
    float duration;

    //Creating 5 child-processes (i = 5)
    printf("Creating 5 child-processes (i = 5) \n");
    for(int i=0; i < NUMOF_CHILDREN; i++)  { 
        if((pids[i] = fork()) < 0) {
            perror("Error: exit(1) -- Fork \n");
            exit(1);
        }
        else if(pids[i] == 0) { 
            sleep(1);     
            printf("Creating child-process! \n");

            //Start counter;  
            clock_t beginChild = clock();

            //changing priority or nice(PRIORITY_LIST[i-1]);
            setpriority(PRIO_PROCESS, getpid(), PRIORITY_LIST[i]);
            printf("Changed priority to %d! \n", getpriority(PRIO_PROCESS, getpid())); 

            //getting Proces ID (PID)
            pid = getpid();
            printf("[CHILD(%d) PID] %d \n", i+1, getpid()); 

            //start child program
            prime();

            //End counter
            clock_t endChild = clock();  
            duration = (float)(endChild - beginChild) / CLOCKS_PER_SEC;

            //storing data
            store_process(&process[i], duration, i, pid, PRIORITY_LIST[i]);

            //ending child program
            printf("Child Program with priority (%d) has succesfully been executed! \n", getpriority(PRIO_PROCESS, getpid())); 

            exit(0);
        }
    }
    while (n > 0) {
        //waiting for all the child processes 
        pid = wait(&retval);
        printf("Parent: child with PID %ld exited with status 0x%x.\n", (long)pid, retval);
        printf("---------------------------------------------------\n");
        --n;
    }

    //end of the program 
    getavgTime(&process);
    printf("Finishing main program \n");
    return 0;
}