#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>


using namespace std;

#define NUM_THREADS     1

typedef void (*event_callback)(void* data );
typedef struct {
   int  thread_id;
   char *message;
   event_callback callback;
   int timeout;
}thread_data;

void *PrintHello(void *threadarg)
{
	thread_data *my_data;
    my_data = (thread_data *) threadarg;
    int timeout = my_data->timeout;

    timeval t1, t2;
    double elapsedTime, prev_elapsedTime;
    prev_elapsedTime = 0;
        // start timer
    gettimeofday(&t1, NULL);
    do {
    	gettimeofday(&t2, NULL);

    	elapsedTime = (t2.tv_sec - t1.tv_sec);
    	if (elapsedTime != prev_elapsedTime) {
    	  std::cout<<"elapsedTime = "<<elapsedTime<<std::endl;
    	  prev_elapsedTime = elapsedTime;
    	}
    }while(elapsedTime < timeout);

   cout << "!!! Thread ID : " << my_data->thread_id <<endl;
   my_data->message = (char*)"new message";
   (*my_data->callback)(my_data);
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
   td.message = (char*)"This is org message";
   td.callback = callback_impl;
   td.timeout = 15;
   cout <<"main() : creating thread, " << td.thread_id << endl;
   rc = pthread_create(&thread, NULL,PrintHello, (void *)&td);
   if (rc){
      cout << "Error:unable to create thread," << rc << endl;
      exit(-1);
   }
   pthread_join( thread, NULL);
   cout<<"after thread"<<endl;
}
