/*
 * @author: Jordi Jaspers
 * @date 25/04/2020
 * @title: Excercise_5 C program for Stack and Heap Overflow 
**/

#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h> 
#include <string.h> 
#include <errno.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 

/*
 * Heap is a region of process’s memory which is used to store dynamic variables. 
 * These variables can be accessed globally and once we allocate memory on heap it is our responsibility to free that memory space after use.
 * There are two situations which can result in heap overflow:
 * 
 * 1. If we continuously allocate memory and we do not free that memory space after use it may result in memory leakage
 * 2. If we dynamically allocate large number of variables.
**/
void createHeapOverflow1(){
  //Allocating memory without freeing it 
  for (int i=0; i<100000000000; i++) {
      int *p = (int *)malloc(sizeof(int));
   }
}

void createHeapOverflow2(){
  //Allocating large memory
  float *ptr = (int *) malloc(sizeof(float)*1000000.0); 
}

/*
 * Stack is a special region of our process’s memory which is used to store local variables used inside the function, 
 * parameters passed through a function and their return addresses. In our computer’s memory, stack size is limited. 
 * If a program uses more memory space than the stack size then stack overflow will occur and can result in a program crash. 
 * There are two cases in which stack overflow can occur:
 * 
 * 1. If we declare large number of local variables or declare an array or matrix or any higher dimensional array of large size can result in overflow of stack.
 * 2. If function recursively call itself infinite times then the stack is unable to store large number of local variables used by every function call and will result in overflow of stack.
 * 
**/
void createStackOverflow1(){
  // Creating a matrix of size 10^5 x 10^5 , which may result in stack overflow. 
  int mat[100000][100000]; 
}

void createStackOverflow2(int x){
  //Creating a non-terminating recursive function. 
  if (x == 1){
    return;
  }
  
  x = 6;
  createStackOverflow2(x); 
}

void setHeapLimit(){
    printf("Setting New Memory limits..... \n");
    struct rlimit old_lim, lim, new_lim; 
  
    // Get old limits 
    if( getrlimit(RLIMIT_NOFILE, &old_lim) == 0) 
        printf("Old limits -> soft limit= %ld \t"
           " hard limit= %ld \n", old_lim.rlim_cur,  
                                 old_lim.rlim_max); 
    else
        fprintf(stderr, "%s\n", strerror(errno)); 
      
    // Set new value 
    lim.rlim_cur = 3; 
    lim.rlim_max = 1024; 
  
    // Set limits 
    if(setrlimit(RLIMIT_NOFILE, &lim) == -1) 
        fprintf(stderr, "%s\n", strerror(errno)); 
      
    // Get new limits 
    if( getrlimit(RLIMIT_NOFILE, &new_lim) == 0) 
        printf("New limits -> soft limit= %ld "
         "\t hard limit= %ld \n", new_lim.rlim_cur,  
                                  new_lim.rlim_max); 
    else
        fprintf(stderr, "%s\n", strerror(errno));

    printf("\n"); 
    printf("\n");    
}

/*
 *  Main function to choose wich overflow we are going to catch.
 */  
int main(void) {
  int input;
  
  setHeapLimit();

  printf("Hello. What kind of overflow are trying to create? \n");
  printf("  1. Heap Overflow via allocating memory without freeing it. \n");
  printf("  2. Heap Overflow via allocating to large memory. \n");
  printf("  3. Stack Overflow via to big local variable. \n");
  printf("  4. Stack Overflow via a non-terminating recursive function. \n");

  while (1){
    scanf("%d",&input);

    // process with your input then use break to end the while loop
    if (input>=1 && input<=4){
        printf("Processing overflow: \n");

        if(input == 1){
          createHeapOverflow1();
        };
        if(input == 2){
          createHeapOverflow2();
        };
        if(input == 3){
          createStackOverflow1();
        };
        if(input == 4){
          int x = 6;
          createStackOverflow2(x);
        };

        break;
    }
    else{
        printf("Wrong input! try Again. \n");
        continue;
    }
  }

  return 0;
}



