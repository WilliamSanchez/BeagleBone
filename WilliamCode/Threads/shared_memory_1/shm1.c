#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/shm.h>

#include "shm_com.h"

int main(){
 
  int running = 1;
  void *shared_memory = (void*)0;
  struct shared_use_st *shared_stuff;
  int shmid;

  srand((unsigned int)getpid());
  shmid = shmget((key_t)1234,sizeof(struct shared_used_st),0666 | IPC_CREAT);
  if(shmid == -1){
    fprintf(stderr,"shmget failed\n");
    exit(EXIT_FAILURE);
  }

  shared_memory = shmat(shmid,(void *)0,0);
  if(shared_memory == (void*)-1){
    fprintf(stderr,"shmat failed\n");
    exit(EXIT_FAILURE);
  }

  printf("Memory attached at %X\n",(int)shared_memory);



  return 0;
}
