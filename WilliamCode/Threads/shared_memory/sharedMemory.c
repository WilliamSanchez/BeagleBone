#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>
#include <semaphore.h>

#define SHM_SEGMENT_SIZE	65536
#define SHM_SEGMENT_NAME 	"/demo-shm"
#define SEMA_NAME 		"/demo-sem"

static sem_t *demo_sem;

static void *get_shared_memory(){
  
  int shm_fd;
  struct shared_data *shm_p;  
  shm_fd = shm_open(SHM_SEGMENT_NAME, O_CREAT | O_EXCL | O_RDWR, 0666);
 
  if(shm_fd > 0){
    
     printf("Creating shared memory and stting size=%d\n",SHM_SEGMENT_SIZE);
     if(ftruncate(shm_fd,SHM_SEGMENT_SIZE) < 0){
       perror("ftruncate");
      exit(1);
     }

    demo_sem = sem_open(SEMA_NAME, O_RDWR | O_CREAT, 0666, 1);
    if (demo_sem == SEM_FAILED)
	perror("sem_open failed\n");
  }else if(shm_fd == -1 && errno == EEXIST){
 
     shm_fd = shm_open(SHM_SEGMENT_NAME, O_RDWR, 0);
     demo_sem = sem_open(SEMA_NAME, O_RDWR);
    
    if(demo_sem == SEM_FAILED)
        perror("sem_open failed\n");
  }
 
   if(shm_fd == -1){
      perror("shm_open"SHM_SEGMENT_NAME);
      exit(1);
    } 
  
  shm_p = mmap(NULL, SHM_SEGMENT_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

  if(shm_p == NULL){
    perror("mmap");
    exit(1);
  }
  return shm_p;
}


int main(int argc, char *argv[]){

  char *shm_p;
  printf("%s PID=%d\n",argv[0],getpid());
  shm_p = get_shared_memory();

  while(1){

    printf("press enter to see the current contens of shm \n");
    getchar();
    sem_wait(demo_sem);
    printf("%s\n",shm_p);
    sem_post(demo_sem);  
  }
 return 0;
}






