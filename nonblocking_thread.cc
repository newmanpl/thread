#include <iostream>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h> 
using namespace std;
typedef void (*callback)(void * args);
typedef struct {
   int  thread_id;
   char *message;
}thread_data;
thread_data data;
void* OnCallback(void* args) {
  std::cout<<"callback is called "<<std::endl;
  int timeout = 5;
  timeval t1, t2;
  double elapsedTime, prev_elapsedTime;
  prev_elapsedTime = 0;
        // start timer
  gettimeofday(&t1, NULL);
  do {
    gettimeofday(&t2, NULL);
    sleep(1);
    elapsedTime = (t2.tv_sec - t1.tv_sec);
    if (elapsedTime != prev_elapsedTime) {
      std::cout<<"elapsedTime = "<<elapsedTime<<std::endl;
      prev_elapsedTime = elapsedTime;
    }
  }while(elapsedTime < timeout);
  std::cout <<"out of loop"<<std::endl;
}

int create()
{
  pthread_attr_t thread_attr;
  pthread_t pt = 0;
  const void* context = NULL;

  if (0 != pthread_attr_init(&thread_attr)) {
    return -1;
  }

  if (0 != pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED)) {
    pthread_attr_destroy(&thread_attr);
    return -1;
  }

  if (0 != pthread_create(&pt, &thread_attr, OnCallback, (void*)&data)) {
    pthread_attr_destroy(&thread_attr);
    return -1;
  }

  pthread_attr_destroy(&thread_attr);
}

int main () {
  create();
  std::string input("");
  std::cout<<"enter quit to quit the program :";
  std::cin>>input;
  while (input != "quit") {
  }
//  pthread_exit(NULL);
  return 0;
}
