#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

int in, out, cont, buffer[10];

pthread_cond_t lleno, vacio;
pthread_mutex_t semaf;


void Escribe(int Dato){
   pthread_mutex_lock(&semaf);
   while(cont == 10)
     pthread_cond_wait(&vacio, &semaf);
  cont++; buffer[in]=Dato;
  in = (in+1)%10;
  pthread_cond_broadcast(&lleno);
  pthread_mutex_unlock(&semaf);
} 

int Lee(){
  int dato;
  pthread_mutex_lock(&semaf);
  while (cont == 0)
    pthread_cond_wait(&lleno,&semaf);
  cont--; dato=buffer[out];
  out = (out+1)%10;
  pthread_cond_broadcast(&vacio);
  pthread_mutex_unlock(&semaf);
  return dato;
}

void *productor(void *arg){
  int i=0;
  printf("Hijo\n");
  for(i=0; i<100; i++)
     Escribe(i);
  pthread_exit(0);
}

int main(){
  
  int i;
  pthread_t hijo;
  in = out = cont = 0;
  
  pthread_mutex_init(&semaf,NULL);
  pthread_cond_init(&lleno,NULL);
  pthread_cond_init(&vacio,NULL);

  pthread_create(&hijo,NULL,productor,NULL);
  printf("Padre\n");
  for(i=0; i<100;i++)
    printf("Lee %d\n",Lee());
  return 0;
}
