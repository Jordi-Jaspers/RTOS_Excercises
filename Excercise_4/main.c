/*
 * @author: Jordi Jaspers
 * @date 17/04/2020
 * @title: Excercise_3 C program for implementation of FCFS 
**/

//include libraries
#include <stdio.h> 
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


#define NUMOF_CHILDREN 5

int const PRIORITY_LIST[5] = {-20, -10, 0, 10, 19};

//struct for process
struct node {
  float duration;
  int localID;
  int pid;
  int priority;
}process[NUMOF_CHILDREN];

/*
 *  Calculate average time of every process
 */	
void getavgTime(struct node processes[]) 
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

        waitTime = ((float) processes[0].duration) - ((float) processes[i].duration);
        duration = (float) processes[i].duration;
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
void prime(int pid){
    int i, flag;
    int LOW = 0;
    int HIGH = 50;

    printf("[CHILD %d]Prime numbers between %d and %d are: \n", pid, LOW, HIGH);

    while (LOW < HIGH) {
        flag = 0;

        // if low is a non-prime number, flag will be 1
        for (i = 2; i <= LOW / 2; ++i) {
            if (LOW % i == 0) {
                flag = 1;
                break;
            }
        }

        if (flag == 0){
            printf("%d \n", LOW);
            //sleep(1);
        }
        ++LOW;
    }
}

/*
 *  Storing all the information of the process.
 */	
void store_process(struct node processptr[], float duration, int localID, int pid, int priority) {
    // storing the data in the object
    processptr[localID].localID = localID;
    processptr[localID].duration = duration;
    processptr[localID].pid = pid;
    processptr[localID].priority = priority;
}

/*
 *  Main function
 */     
int main() 
{  
    //local variables
    int pid;
    int retval;
    
    float duration;

    //------------------------ testing
    //setting up shared memory, don't know how yet...
    

    //------------------------ testing
	
    //Creating 5 child-processes (i = 5)
    printf("Creating 5 child-processes (i = 5) \n");
    for(int i=0; i <= NUMOF_CHILDREN; i++)  
    { 
        pid = fork();
        if(pid < 0) {
            printf("Error: exit(1) \n");
            exit(1);
        }
        else if(pid == 0) 
        {   
            //Start counter;  
            clock_t beginChild = clock();

            //changing priority or nice(PRIORITY_LIST[i]);
            setpriority(PRIO_PROCESS, getpid(), PRIORITY_LIST[i]);

            //getting Proces ID (PID)
            printf("[CHILD(%d) PID] %d \n", i+1, getpid()); 

            //start child program
            prime(getpid());

            //End counter
            clock_t endChild = clock();  
            duration = (float)(endChild - beginChild) / CLOCKS_PER_SEC;

            //storing data
            store_process(process, duration, i, getpid(), getpriority(PRIO_PROCESS, getpid()));
            
            //ending child program
            printf("Child Program succesfully executed! \n"); 
            exit(0);
        }
        else{

            //waiting for all the child processes 
            pid = wait(&retval);
            printf("Parent: child with PID %ld exited with status 0x%x.\n", (long)pid, retval);
        }
    } 

    //end of the program 
    getavgTime(process);
    printf("Finishing main program \n");
    return 0;
} 
