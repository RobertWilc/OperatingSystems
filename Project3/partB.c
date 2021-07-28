#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <unistd.h>

#define LINES 5 //How many times a character line will be printed.
#define TIMES 10 //How many times the group of characters will be printed.

//Declares the threadX functions that are being called in pthread_create.
void* threadA();
void* threadB();

//Declars the mutex global variable
pthread_mutex_t mutex;

int main()
{

  pthread_t tid;
  pthread_setconcurrency(2);

  //Iterates up to TIMES. Creates a thread for both threadA and threadB and passes in
  //the count to each fuction.
  int it;
  for(it = 1; it <= TIMES; it++)
  {
    //An alternative way to pass an integer to the functions. Tried something different
    //from part A for the sake of learning. Not 100% sure which is better. I am not cleaning
    //up my pointers, so I am assuming part A handles this more gracefully.
    int *i = malloc(sizeof(*i));
    *i = it;
    pthread_create(&tid, NULL, (void *(*) (void *))threadA, (void *) i); //Creates a thread and runs the threadA function.
    pthread_create(&tid, NULL, (void *(*) (void *))threadB, (void *) i); //Creates a thread and runs the threadB function.

    pthread_join(tid, NULL);
    printf("\n");
  }

  pthread_exit(0);
}

void* threadA(void *input)
{
  int i;
  int a = *((int *) input);
  //uses the mutex variable and locks it so that only this function will run.
  pthread_mutex_lock(&mutex);

  for(i = 0; i < LINES; ++i)
  {
    printf("%d: AAAAAAAAA\n", a);
  }

  //unlocks the mutex so that other threads can start running.
  pthread_mutex_unlock(&mutex);
  sleep(1);
}

void* threadB(void *input)
{
  int i;
  int a = *((int *) input);
  //Identical to threadA. This is so that they are not "stepping" on one another.
  pthread_mutex_lock(&mutex);

  for(i = 0; i < LINES; ++i)
  {
    printf("%d: BBBBBBBBBB\n", a);
  }
  //unlocks the mutex.
  pthread_mutex_unlock(&mutex);
  sleep(1);
}
