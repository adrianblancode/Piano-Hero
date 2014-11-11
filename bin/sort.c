#include "huvud.h"

//Denna funktion sorterar noterna i ordning efter start_time från lägst till högst

void sort(long int noter[][5], long int storlek)
{

long int n=1, cycle=1;
long int temparray[1][5];
FONT* myfont = load_font("resources/bitten.pcx", NULL, NULL);

rectfill(screen, 335, 345, 335+105, 355, makecol(0,0,0));

   while(n!=storlek)
   {

      while(cycle!=storlek)
      {
                      
         if(noter[n][start_time]<noter[cycle][start_time])
         {
                                                  
         temparray[0][track]=noter[cycle][track];
         temparray[0][start_time]=noter[cycle][start_time];
         temparray[0][pitch]=noter[cycle][pitch];
         temparray[0][duration]=noter[cycle][duration];
         temparray[0][dynamic]=noter[cycle][dynamic];

         noter[cycle][track]=noter[n][track];
         noter[cycle][start_time]=noter[n][start_time];
         noter[cycle][pitch]=noter[n][pitch];
         noter[cycle][duration]=noter[n][duration];
         noter[cycle][dynamic]=noter[n][dynamic];
                                                  
         noter[n][track]=temparray[0][track];
         noter[n][start_time]=temparray[0][start_time];
         noter[n][pitch]=temparray[0][pitch];
         noter[n][duration]=temparray[0][duration];
         noter[n][dynamic]=temparray[0][dynamic];

         cycle=1;
         }

      cycle++;
      }
                
   textprintf_ex(screen,myfont, 330,300,WHITE,1,"Sorting: %d",n);
   textprintf_ex(screen,myfont, 330,320,WHITE,1,"Percent: %d %%",n*100/storlek);
   rectfill(screen, 335, 345, 335+105*n/storlek, 355, WHITE);
   line(screen, 330 , 343 , 330 , 357 , WHITE );
   line(screen, 445 , 343 , 445 , 357 , WHITE );

   n++;
   cycle=1;
   }

textprintf_ex(screen,myfont, 330,320,WHITE,1,"Percent: 100 %%");
destroy_font(myfont);
}
