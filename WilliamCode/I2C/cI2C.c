#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>


#define DEVID 		0x0F
#define SIZE_BUFFER	40

int main(){
 
  int file;
  printf("Starting the acelerometer and gyrometer \n\r");
 
  if((file=open("/dev/i2c-2",O_RDWR)) < 0){
     perror("El dispositivo no pudo abrirse \n\r");
     return 1;
  }

  if(ioctl(file,I2C_SLAVE,0x6B) < 0){
    perror("NO se pudo conectar al sensor \n\r");
    return 1;
  }

  char writeBuffer[1]= {0x0F};
  if(write(file,writeBuffer,1) != 1){
    perror("Fallo al resetear la direccion \n\r");
    return 1;
  }

  char readBuffer[SIZE_BUFFER];
  if(read(file,readBuffer,SIZE_BUFFER) != SIZE_BUFFER){
    perror("Fallo al leer el buffer \n\r");
    return 1;
  }

  printf("La ID del dispositivo es: 0x%02x \n\r",readBuffer[0x00]);
  close(file); 
  return 0;
}

