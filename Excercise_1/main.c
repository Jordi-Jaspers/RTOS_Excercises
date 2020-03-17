/*
 * @author: Jordi Jaspers
 * @date 28/03/2020
 * @title: Excercise_1 using Fork()
*/

//include libraries
#include <stdio.h>

//Cross platform includes
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

int main()
{
    fork();
    fork();
    prime();

    return 0;
}

void prime(){
    int i, flag;
    int LOW = 0;
    int HIGH = 50;

    printf("Prime numbers between %d and %d are: \n", LOW, HIGH);

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
            // sleep(1);
        }
        ++LOW;
    }
}