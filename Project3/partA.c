#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

#define LINES 5 //How many lines of A or B will be printed.
#define TIMES 10 //How many times the group of lines will be printed.

//Defines the thread functions that will be used in main.
void* threadA();
void* threadB();

int main()
{

  pthread_t tid;
  pthread_setconcurrency(2);
  
  //Loop to create a thread that calls the function A or B. Passes in where in the loop the 
  //the thread is (i).
  int i;
  for(i = 0; i < TIMES; ++i)
  {
    pthread_create(&tid, NULL, (void *(*) (void *))threadA, (void *) &i); //creates the threadA thread.
    pthread_create(&tid, NULL, (void *(*) (void *))threadB, (void *) &i); //creates the threadB thread.
  }

  pthread_exit(0);
}

//Function that prints the current iteration that the thread is in as well as A printed 9 times.
//Accepts a void variable that will be typecast into an integer and printed before the As.
void* threadA(void* input)
{
  int i;
  for(i = 0; i < LINES; ++i)
  {
    printf("%d: AAAAAAAAA\n", *((int *) input));
  }
}

//Identical to threadA function but is the threadB function.
void* threadB(void* input)
{
  int i;
  for(i = 0; i < LINES; ++i)
  {
    printf("%d: BBBBBBBBBB\n", *((int *) input));
  }
}
