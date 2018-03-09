#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t count_mutex     = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  condition_var   = PTHREAD_COND_INITIALIZER;
pthread_t thread1, thread2;

void *functionEven();
void *functionOdd();
int  count = 0;
#define COUNT_DONE  10

int main()
{

   pthread_create( &thread1, NULL, &functionEven, NULL);
   pthread_create( &thread2, NULL, &functionOdd, NULL);

   pthread_join( thread1, NULL);
   pthread_join( thread2, NULL);

   printf("Final count: %d\n",count-1);

   exit(0);
}

// Incrementing and Outputting Count when even.
// Parity check is not needed due to the check in functionCount2.

void *functionEven()
{
   for(;;)
   {
      // Lock mutex and then wait for signal to relase mutex
      pthread_mutex_lock( &count_mutex );

      // Wait while functionOdd() operates on count
      // mutex unlocked when functionEven() signals.
      pthread_cond_wait( &condition_var, &count_mutex );
      count++;
      printf("Counter value functionOdd: %d\n",count-1);
   
      pthread_mutex_unlock( &count_mutex );
      if(count >= COUNT_DONE) 
         pthread_exit(&thread1);
    }
}

//Incrementing and Outputting Count when odd
void *functionOdd()
{
    for(;;)
    {
       pthread_mutex_lock( &count_mutex );

       if(count  == 0) //Initiate Count increment
            count++;
       
       if (count & 1){
            printf("Counter value functionEven: %d\n",count);
            count++;
            pthread_cond_signal( &condition_var ); //Signaling functionEven
      }
       
       pthread_mutex_unlock( &count_mutex );

       if(count >= COUNT_DONE) 
                 pthread_exit(&thread2);
    }
}

