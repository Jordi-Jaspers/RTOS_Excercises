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

int PROCESS_AMOUNT = 5;
int PRIORITY_LIST[5] = {-20, -10, 0, 10, 19};

//struct for process
typedef struct node {
  int duration;
  int localID;
  int pid;
  int priority;
} process;

/*
 *  Calculate average time of every process
 */	
void getavgTime(process* processes[]) 
{   
    int pid;
    int priority;
	int waitTime;
    int duration;
    int waitDuration;
    int total_waitTime = 0;
    int total_duration = 0; 
	
	//Display processes along with all details 
	printf("ProcessID: | Priority: | Duration: | Wait: | Duration+Wait: \n"); 
	for (int i=0; i < PROCESS_AMOUNT; i++) 
	{   
        pid = processes[i] -> pid; 
        priority =  processes[i] -> priority;

        waitTime = (processes[0] -> duration) - (processes[i] -> duration);
        duration = processes[i] -> duration;
        waitDuration = waitTime + duration;

		total_waitTime = total_waitTime + waitTime; 
		total_duration = total_duration + duration; 

		printf("    %d  ", pid);            //ProcessID:
        printf("    %d  ", priority);       //Priority:
		printf("    %d  ", duration );      //Duration:
		printf("	%d  ", waitTime );      //Wait:
		printf("	%d\n", waitDuration);            //Duration+Wait:
	} 

	int s=(float)total_waitTime / (float) PROCESS_AMOUNT; 
	int t=(float)total_duration / (float) PROCESS_AMOUNT; 

	printf("Average Job Waiting Time (AJWT)= %d \n",s); 
	printf("\n"); 
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
process* create_process(int duration, int localID, int pid, int priority) {

    // make an object
    process *newelement;
    newelement = malloc(sizeof(process));

    // initialise the object
    newelement->duration = duration;
    newelement->localID = localID;
    newelement->pid = pid;
    newelement->priority = priority;
    
    if (newelement == NULL) {
        printf("ERROR: memory could not be allocated\n");
        exit (1);
    }

    return newelement;
}

/*
 *  Main function
 */     
int main() 
{ 
    process* processes[PROCESS_AMOUNT]; 
    int pid;
    
    double duration;
	
    printf("Creating 5 child-processes (i = 5) \n");
    //Creating 5 child-processes (i = 5)
    for(int i=0; i < PROCESS_AMOUNT; i++)  
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
            duration = (double)(endChild - beginChild) / CLOCKS_PER_SEC;

            //storing data
            processes[i] = create_process(duration, i, getpid(), getpriority(PRIO_PROCESS, getpid()));

            //ending child program
            printf("Child Program succesfully executed! \n"); 
            exit(0);
        }
        else{

            //waiting for all the child processes 
            printf("Waiting for all the child processes \n");
            wait(NULL);

            getavgTime(processes);
        }
    } 

    //end of the program 
    printf("Finishing main program \n");
    return 0;
} 
