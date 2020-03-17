/*
 * @author: Jordi Jaspers
 * @date 10/03/2020
 * @title: Excercise_3 Linked lists
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// typedef of "book"
typedef struct node {
    char * title;
    char * author;
    struct node * next;
} book;

//static declarations
char* STATIC_TITLE[4] = {
    "Cleaning the streets Beyond the Gate",
    "Beyond the depths of the Underdark",
    "Ancient Aberrations and how to prevent them",
    "Killing people with cows: the ins and outs of Wild Magic"
};
char* STATIC_AUTHOR[4] = {
    "Ulder Ravengard",
    "Drizzt Do’Urden",
    "Elminster Aumar",
    "Neera"
};

// forward declarations
book* create_books(char* title, char* author);
void print_books(book* library);
void sort_books_by_author(book* library);
void sort_books_by_title(book* library);

//Implementing excercise 3.1
int main() {
    book *library, *tail;

    // initialise the object
    library = NULL;
    
    for(int i=0; i<4; i++) {
        // append the object to the list
        if (library == NULL) {
            library = create_books(STATIC_TITLE[i], STATIC_AUTHOR[i]);
            tail = library;
        } 
        else {
            tail -> next = create_books(STATIC_TITLE[i], STATIC_AUTHOR[i]);
            tail = tail -> next;
        };
    };

    print_books(library);

    //Implementing excercise 3.3
    printf("------------------------------------------- \n");
    printf("Sort_book() by author Troubleshooter: \n");
    void (*sort_books)(book*) = sort_books_by_author;
    sort_books(library);
    printf("------------------------------------------- \n");
    print_books(library);

    printf("------------------------------------------- \n");
    printf("Sort_book() by title Troubleshooter: \n");
    sort_books = sort_books_by_title;
    sort_books(library);
    printf("------------------------------------------- \n");
    print_books(library);
    
    return 0;
}

book* create_books(char* title, char* author) {

    // make an object
    book *newelement;
    newelement = malloc(sizeof(book));

    // initialise the object
    newelement->title = title;
    newelement->author = author;
    newelement->next = NULL;
    
    if (newelement == NULL) {
        printf("ERROR: memory could not be allocated\n");
        exit (1);
    }

    return newelement;
}

void print_books(book* library) {
    if( library == NULL ) {
        printf("the library is empty \n");
    } else {
        printf("printing the library:\n");
        while( library != NULL ) {
            printf("book: %s, by %s \n", library->title, library->author);
            library = library->next;
        }
        printf("end of the list\n");
  }
}

//Implementing excercise 3.2
void sort_books_by_author(book* library) {
    //defining local variables
    int flag = 1;
    char *x, *y;
    book temp;
    book* library_next;
    book* library_first = library;
   
    printf("Sorting library: \n");
    while( flag == 1 ){
        printf("resetting values \n");
        flag = 0;
        library = library_first;
        library_next = library -> next;
        if( library == NULL ) {
            printf("the library is empty \n");
        } 
        else {
            while( library_next != NULL ) {
                printf("x author = %s \n", library->author);
                printf("y author = %s \n", library_next->author);
                x = library->author;
                y = library_next->author;

                printf("entering sorting algorithm \n");
                if(strcmp(x, y) > 0){
                    flag = 1;
                    printf("Swapping objects \n");
                    temp = *library;
                    *library = *library_next;
                    *library_next = temp;

                    printf("correcting pointers \n");
                    library_next -> next = library -> next;
                    library -> next = library_next;
                } 

                printf("Next books \n");  
                library = library->next;
                library_next = library->next;
            }
        }
    }
    printf("Sorted by Author\n");
    library = library_first;
}

//Implementing excercise 3.3
void sort_books_by_title(book* library) {
    //defining local variables
    int flag = 1;
    char *x, *y;
    book temp;
    book* library_next;
    book* library_first = library;
   
    printf("Sorting library: \n");
    while( flag == 1 ){
        printf("resetting values \n");
        flag = 0;
        library = library_first;
        library_next = library -> next;
        if( library == NULL ) {
            printf("the library is empty \n");
        } 
        else {
            while( library_next != NULL ) {
                printf("x Title = %s \n", library->title);
                printf("y Title = %s \n", library_next->title);
                x = library->title;
                y = library_next->title;

                printf("entering sorting algorithm \n");
                if(strcmp(x, y) > 0){
                    flag = 1;
                    printf("Swapping objects \n");
                    temp = *library;
                    *library = *library_next;
                    *library_next = temp;

                    printf("correcting pointers \n");
                    library_next -> next = library -> next;
                    library -> next = library_next;
                } 

                printf("Next books \n");  
                library = library->next;
                library_next = library->next;
            }
        }
    }
    printf("Sorted by Title\n");
    library = library_first;
}