#include "huvud.h"

//Denna funktion läser textfilen och sparar sedan allt till 2darrayen

void las(long noter[][5], long storlek, char filnamn[])
{

FONT* myfont = load_font("resources/bitten.pcx", NULL, NULL);
long int temptimesek=0, temptimems, tempdurasek, tempdurams, n=0;
unsigned int temptrack, temppitch, tempdyn, conv;
int slenght, dummy;
char rad, convtxt[70], convsort[70];

//sätter element till typ-1 för att den inte ska börja räkna innan första nyradstecknet, 
//blir track vid \n
enum element typ=-1;

//Variabel för att avgöra ifall en funktion körs eller inte, används lite varstans. 
//Blir true vid första '\n' i texten
_Bool start=false, sort=false;

//Lägger terminationstecknet vid . eg thefrail.txt blir thefrail
//vilket gör så att man kan skriva in tex thefrail, thefrail.txt, thefrail.mid '
//och fortfarande få samma resultat

slenght=strlen(filnamn);

   while(n<slenght)
   {
   if(filnamn[n]=='.')filnamn[n]='\0';
   if(filnamn[n]=='\n')filnamn[n]='\0';
   n++;
   }

n=1;

slenght=strlen(filnamn);

//Lägger till .txt i slutet av filnamnet, ifall jag vill öppna .midfilen senare 
//blir det lättare att ha en sträng utan filändelse
strcpy(convtxt, filnamn);
convtxt[slenght]='.';
convtxt[slenght+1]='t';
convtxt[slenght+2]='x';
convtxt[slenght+3]='t';
convtxt[slenght+4]='\0';


//Lägger till sort.txt i slutet av filnamnet för att se ifall det finns en färdigsorterad fil
strcpy(convsort, filnamn);

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

n=0;

//Öppnar textfilen. Ifall filen inte kan öppnas korrekt skippar den hela läsfunktionen
//returnerar värdet 0 och börjar om från början
FILE *fil;

//Ifall det finns en sorterad fil redan, öppnas den
//Annars öppnas den osorterade filen
//Annars hittas inte filen och man måste börja om

if(dummy = fopen(convsort, "r") != NULL)fil = fopen(convsort, "r");
else if(dummy = fopen(convtxt, "r") != NULL)fil = fopen(convtxt, "r");

else{
textprintf_ex(screen,myfont, 415 - text_length(myfont, "ERROR: FILE NOT FOUND")/2,300, RED,1,"ERROR: FILE NOT FOUND");
sleep(1000);
return;
}


   while(rad!=EOF)
   {
   rad=fgetc(fil);

   if(rad-'0'>=0 && rad-'0'<10){conv=(rad-'0');}
   //conv konverterar rad (char) till long int

      if(rad=='\n')
      {

      start=true;
      typ=track;

      //Sparar variabler vid nyrad
      noter[n][track]=temptrack;
      noter[n][start_time]=(temptimesek*1000)+temptimems;
      noter[n][pitch]=temppitch;
      noter[n][dynamic]=tempdyn;
      
      //Förhindrar noter över 8 sekunder, det blir för rörigt annars
      if((tempdurasek*1000)+tempdurams < 8000)noter[n][duration]=(tempdurasek*1000)+tempdurams;
      else noter[n][duration]=8000;

      n++;

      textprintf_ex(screen,myfont,330,280,WHITE,1,"Reading: %d",n);
      textprintf_ex(screen,myfont, 330,320,WHITE,1,"Percent: %d %%",n*100/storlek);
      rectfill(screen, 335, 345, 335+105*n/storlek, 355, WHITE);
      line(screen, 330 , 343 , 330 , 357 , WHITE );
      line(screen, 445 , 343 , 445 , 357 , WHITE );

      //Resettar variabler vid nyrad
      temptrack=0;
      temptimesek=0;
      temptimems=0;
      temppitch=0;
      tempdurasek=0;
      tempdurams=0;
      tempdyn=0;
      }

      //Sparar värdet för track på temptrack
      if(typ==track && start==true && rad!='\t' && rad!='\n')
      {
      if(rad=='.'){start=false;}
      temptrack=conv;
      }


      //Sparar värdet för start_time i sekunder i temptimesek, och millisek i temptimems
      if(typ==start_time && rad!='\t' && rad!='\n')
      {            
         if(rad=='.'){start=false;}

         if(start==true)
         {
         if(temptimesek==0){temptimesek=conv;}
         else temptimesek=temptimesek*10+conv;

         }
             
         if(start==false && rad!='.')
         {
         if(temptimems==0){temptimems=conv*100;}
         else if(temptimems>=10){temptimems=temptimems+conv*10;}
         }
      }

      //Sparar färdet för pitch i temppitch
      if(typ==pitch && start==true && rad!= '\t')
      {
      if(temppitch==0){temppitch=conv;}
      else temppitch=temppitch*10+conv;
      }


      //Sparar värdet för duration i sekunder i tempdurasek, för millisek i tempdurams
      if(typ==duration && rad!='\t' && rad!='\n')
      {
      if(rad=='.'){start=false;}             

         if(start==true)
         {
         if(tempdurasek==0){tempdurasek=conv;}
         else tempdurasek=tempdurasek*10+conv;

         }
             
         if(start==false && rad!='.')
         {
         if(tempdurams==0){tempdurams=conv*100;}
         else if(tempdurams>=10){tempdurams=tempdurams+conv*10;}
         }
      }


      //Sparar värdet för dynamic i tempdynams
      if(typ==dynamic && start==true && rad!='\t')
      {
      if(tempdyn==0){tempdyn=conv;}
      else tempdyn=tempdyn*10+conv;
      }

   //Byter element vid \t, inträffar förrän efter första \n på grund av at typ==-1
   if(rad=='\t' && typ!=-1){
   typ++;
   start=true;}
   }

destroy_font(myfont);
fclose(fil);
}
