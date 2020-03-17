# RTOS_Excercises

## Biography  
**Authors:**
Jordi Jaspers [[Github](https://github.com/Jordi-Jaspers "Github Page"), [Linkedin](https://www.linkedin.com/in/jordi-jaspers/ "Linkedin Page")] 
  
**Date of initial commit:** 
25/02/2020  

**Description:**
All the different excercises are saved in this repository. Thess excercises are part of the RTOS-course of the KULeuven/UHasselt University. Course Information can be found on the following [Link](https://uhintra03.uhasselt.be/studiegidswww/opleidingsonderdeel.aspx?a=2019&i=4082&n=4&t=01 "ECTS Page"). 

## Documentation  
Excercise_1: A C-program that creates 4 child-processes to calculate and prints all the different prime numbers (>=10k).
  
Excercise_2: Solve the problem of the original C-code. So, the code doesn't give any errors. Prevent the chance that multiple consumers handle the same number.
  
Excercise_3:...  
  
## What We Learned
 * Basic C-programming
 * Basic CL usage
 * Usage of MAKE-files
 * Basic use of System calls & Interrupts
 * Creating threads and processes
 * basic muli-threaded programming
 * linked lists in C
 * ...
  
## TODO-List:
**Excercise_1:**
-   Create MAKE-File -> done!
-   Create 4 child processes using fork() -> done!
-   Calculate Prime numbers (>10k) -> done!
-   Print all the numbers -> done!
-   Connect child processes with the c-program -> done!  
  
**Excercise_2:**
-   Copy original C-code -> done!
-   Modify the code that the error is prevented. -> done!
-   Create Report about the code -> done!

**Report**
Analyse exercise 6_4_3.c (shown below) and write a report (< 3 pages):
* describe what the program does
* make a chart that plots ‘the elapsed real time’ the program consumes in function of the number of ‘the number of threads that are contributing’
* the scale on the X-axis goes from 2 to 300 with at least 8 data points should be present in the chart
* TIP: the command time
* interpret the chart

**Excercise_3:**
**Excercise 3.1:**
* The structure you provided can be expanded with a third property: book* next, pointing to the next element in the row. That way, when looping through all books, we simply need to follow the ‘next’ pointer, until a NULL is reached, indicating the end of the library. This technique makes it possible to loop through things without knowing it’s size! Write the required struct and complete the function bodies of create_books() and print_books().
  
**Tips: You may hardcode the four books mentioned above in the create_books() function. Pay attention that you keep the order of the entries !**
  
**Excercise 3.2**
* Create the function book* sort_books(book* library). Display the original library and then print it again, after applying the sort_books() function.

**Tips:**
1. Use the strcmp() function from <string.h> to compare two strings.
2. The sorting algorithm that you use is not important. You can simply use bubble sort. However, if you want to use a fancy approach, feel welcome to do so.
3. Sorting should be done by moving the objects, not the content of the objects.
4. For the sake of simplicity, you may assume that the length of the library is fixed to 4.

**Excercise 3.3**
* Changes the function pointer of sort_books() from sort_books_by_author() to sort_books_by_title().

**Excercise_4:**
* Write a program in C-language that forks 5 processes. These processes edit their own priority divided over the following values (-20, -10, 0, 10, 19). The content of these processes is a double nested "for-loop"  of the previous prime-number excercise. After the task has been executed it has to report a message on the screen with the PID and priority of the process. 

**Tip: Assure that the parent-process waits untill all the child-processes are finished.**

## Troubleshooting:   
-   Nothing yet...  

## References:  
 * Troubleshooting: <https://stackoverflow.com/>
 * using Fork(): <https://www.geeksforgeeks.org/fork-system-call/>