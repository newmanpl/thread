#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <stdio.h>
using namespace std;

#define NUM_THREADS     1

typedef void (*event_callback)(void* data);
typedef struct {
   int  thread_id;
   char *message;
   event_callback callback;
}thread_data;

void *PrintHello(void *threadarg)
{
   thread_data *my_data;

   my_data = (thread_data *) threadarg;

   cout << "Thread ID : " << my_data->thread_id ;
   my_data->message = "new message";
   (*my_data->callback)(my_data);
   pthread_exit(NULL);
}

void callback_impl(void* data) {
  thread_data *d = (thread_data*)data;
  printf("\033[22;34m %s %d %s %s \033[0m\n", __FILE__,__LINE__,__FUNCTION__,d->message);
}

int main ()
{
   pthread_t thread;
   thread_data td;
   int rc;

   td.thread_id = 100;
   td.message = "This is org message";
   td.callback = callback_impl;
   cout <<"main() : creating thread, " << td.thread_id << endl;
   rc = pthread_create(&thread, NULL,PrintHello, (void *)&td);
   if (rc){
      cout << "Error:unable to create thread," << rc << endl;
      exit(-1);
   }
   pthread_exit(NULL);
}
