#include "huvud.h"

//Denna funktion l�ser antalet rader i filen, s� att vi f�r en storlek s� att man kan 
//dynamiskt allokera minne f�r 2d-arrrayen i main

int filelenght(char filnamn[])
{

FONT* myfont = load_font("resources/bitten.pcx", NULL, NULL);

//L�gger terminationstecknet vid . eg thefrail.txt blir thefrail
//vilket g�r s� att man kan skriva in tex thefrail, thefrail.txt, thefrail.mid 
//och fortfarande f� samma resultat

long storlek=0;
char rad, convtxt[70];
int slenght, n=0, dummy;

slenght=strlen(filnamn);

   while(n<slenght)
   {
   if(filnamn[n]=='.')filnamn[n]='\0';
   if(filnamn[n]=='\n')filnamn[n]='\0';
   n++;
   }

n=1;

slenght=strlen(filnamn);

//L�gger till .txt i slutet av filnamnet
strcpy(convtxt, filnamn);
convtxt[slenght]='.';
convtxt[slenght+1]='t';
convtxt[slenght+2]='x';
convtxt[slenght+3]='t';
convtxt[slenght+4]='\0';

//�ppnar textfilen. Ifall filen inte kan �ppnas korrekt skippar den hela l�sfunktionen
//returnerar v�rdet 0 och b�rjar om fr�n b�rjan
FILE *fil;

//Ifall det finns en sorterad fil redan, �ppnas den
//Annars �ppnas den osorterade filen
//Annars hittas inte filen och man m�ste b�rja om

if(dummy = fopen(convtxt, "r") != NULL)fil = fopen(convtxt, "r");
else{textprintf_ex(screen,myfont, 415 - text_length(myfont, "ERROR: FILE NOT FOUND")/2,300, RED,1,"ERROR: FILE NOT FOUND");
sleep(1000);
return (0);}
    
   while(rad!=EOF)
   {
   rad=fgetc(fil);
   if(rad=='\n')storlek++;
   }
    
return(storlek);
}
