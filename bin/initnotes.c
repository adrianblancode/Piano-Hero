#include "huvud.h"

//Denna funktion f�rbereder lite data som noterna m�ste ha
void initnotes(long int noter[][5], long int storlek, long int songtime, float *normal)
{

long int n=1, storst=0;

   while(n<storlek)
   {
   if((noter[n][start_time]+noter[n][duration])>storst){storst=(noter[n][start_time]+noter[n][duration]);}
   n++;
   }

//Tidsdatan i noterna i textfilen �r bara relativ de andra noterna i samma fil
//Jag dividerar ljudfilens speltid med tiden av den st�rsta noten, 
//f�r att ber�kna hur pass i otakt den �r. Tyv�rr hamnar allting i osynk �nd�, 
//d� jag inte kan r�kna med tystnad i slutet av ljudfilen

*normal=(float)songtime/((float)storst-noter[1][start_time]);
printf("Tempo: %.2fx", *normal);
}
