#include <openssl/rand.h>
#include <stdlib.h>             /* Standard Lib    ISOC  */
#include <stdio.h>              /* I/O lib         ISOC  */

int main(int argc, char *argv[]) {
  int totalSize = 1024*1024*1024;
  int buffSize = 100;

 unsigned char buffer[buffSize];
 do{

   if( !(RAND_pseudo_bytes((unsigned char *)buffer, sizeof(buffer)))) {
     printf("ERROR: call to RAND_pseudo_bytes() failed\n");
     exit(1);
   }

   int index=0;
   for(index = 0;index<buffSize;index++){
     printf("%c", buffer[index]);
   }
   totalSize -= buffSize;
 } 
 while (totalSize > 0) ;

 return 0;
}

