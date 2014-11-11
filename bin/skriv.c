#include "huvud.h"

//Denna funktionen skriver den sorterade textfilen "filnamn"sort.txt

void skriv(long int noter[][5], long int storlek, char filnamn[])
{

FONT* myfont = load_font("resources/bitten.pcx", NULL, NULL);
char convsort[54];
int slenght;
long int n=1;

FILE *skriv;

//Tar filnamnet och lägger till sort.txt i slutet
//Är till för att spara filerna så att man slipper sortera dem hela tiden

strcpy(convsort, filnamn);
slenght=strlen(convsort);

   while(n<=slenght)
   {
   convsort[slenght-n+5]=convsort[slenght-n];
   n++;
   }

convsort[0]='s';
convsort[1]='o';
convsort[2]='r';
convsort[3]='t';
convsort[4]='/';

convsort[slenght+5]='s';
convsort[slenght+1+5]='o';
convsort[slenght+2+5]='r';
convsort[slenght+3+5]='t';
convsort[slenght+4+5]='.';
convsort[slenght+5+5]='t';
convsort[slenght+6+5]='x';
convsort[slenght+7+5]='t';
convsort[slenght+8+5]='\0';

n=1;

skriv = fopen(convsort, "w");
textprintf_ex(screen,myfont, 330, 360, WHITE,1,"Writing to %ssort.txt",filnamn);

fprintf(skriv, "Track\tStart_Time\tPitch\tDuration\tDynamic\n");

   while(n<storlek)
   {
   fprintf(skriv, "%d.0\t%d.%d\t%d\t%d.%d\t%d\n", noter[n][track], noter[n][start_time]/1000, noter[n][start_time]%1000, noter[n][pitch], noter[n][duration]/1000, noter[n][duration]%1000, noter[n][dynamic]);
   n++;
   }

//textprintf(screen,myfont, 330, 400, WHITE,"DONE",filnamn);
fclose(skriv);

las(noter, storlek, filnamn);
}
