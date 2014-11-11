#include "huvud.h"

//En debugger som skriver ut alla notvärdena i 2darrayen

void debugg(long int noter[][5], long int storlek){
long int n;

n=1;

   while(n<storlek)
   {
   printf("noter[%d]:   ", n);
   printf("T:%ld",noter[n][track]);
   printf(" ST:%ld",noter[n][start_time]);
   printf(" P:%ld",noter[n][pitch]);
   printf(" D:%ld",noter[n][duration]);
   printf(" DY:%ld\n",noter[n][dynamic]);
   n++;
   }

}
