#include "huvud.h"

//Avgör ifall noterna är i ordning, skippar sortering i sådana fall

bool verify(long int noter[][5], long int storlek)
{
   
FONT* myfont = load_font("resources/bitten.pcx", NULL, NULL);
long int n=1;     

   while(n!=storlek)
   {

      if(noter[n][start_time]>noter[n+1][start_time])
      {
      return(true);
      }

   n++;
                   
      if(n+1==storlek)
      {
      n=storlek;
      textprintf_ex(screen,myfont, 330,300,WHITE,1,"Sorting not needed",n);
      return(false);
      }
   }
}
