#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

void *thread_function(void *arg);

char message[] = "Hello World";

int main(){

  int res;
  pthread_t a_thread;
  void *thread_result;

  res = pthread_create(&a_thread,NULL,thread_function,(void*)message);
  if(res != 0){
     perror("Thread create falled");
     exit(EXIT_FAILURE);

   }

  printf("Waiting for thread to finish ...\n");
  res = pthread_join(a_thread,&thread_result);
  if(res != 0 ){
    perror("Thread join falled");
    exit(EXIT_FAILURE);
  }

 printf("Thread joined, it returned %s\n",(char*)thread_result);
 printf("Message is now %s\n",message);
 exit(EXIT_SUCCESS);
}

void *thread_function(void *arg){
  printf("Thread_function is running. Argument was %s\n",(char*)arg);
  sleep(3);
  strcpy(message,"bye!");
  pthread_exit("Thnak your for the cpu time");

}
