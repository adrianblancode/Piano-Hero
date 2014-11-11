#include "huvud.h"

//Denna funktion förbereder lite data som noterna måste ha
void initnotes(long int noter[][5], long int storlek, long int songtime, float *normal)
{

long int n=1, storst=0;

   while(n<storlek)
   {
   if((noter[n][start_time]+noter[n][duration])>storst){storst=(noter[n][start_time]+noter[n][duration]);}
   n++;
   }

//Tidsdatan i noterna i textfilen är bara relativ de andra noterna i samma fil
//Jag dividerar ljudfilens speltid med tiden av den största noten, 
//för att beräkna hur pass i otakt den är. Tyvärr hamnar allting i osynk ändå, 
//då jag inte kan räkna med tystnad i slutet av ljudfilen

*normal=(float)songtime/((float)storst-noter[1][start_time]);
printf("Tempo: %.2fx", *normal);
}
