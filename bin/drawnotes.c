#include "huvud.h"

//Denna funktion �r ansvarig f�r att rita ut alla noterna

void drawnotes(long int noter[][5], BITMAP *buffer, float normal, long int nowtime, long int storlek)
{
     
//FONT* myfont = load_font("resources/bitten.pcx", NULL, NULL);
long int n, x1=0, y1=0, x2=0, y2=0;
n=1;

//Ger varje not v�rden i y-led, 505 �r y-v�rdet f�r b�rjan av pianot, 
//allts� d�r vi vill se noterna synka. Vi m�ste multiplicera tidsdatan med normalen 
//f�r att f� tiden i ms, och dividera med 10 f�r att f�
//1 sekund = 100 pixlar = ca. en femtedel av sk�rmen. 

//Noterna ritas sedan upp med nowtime/10 p� y
//eftersom noterna ska r�ra sig ner�t med en hastighet av 100pixlar/sek

   while(n<storlek)
   {

   y1 = (505-(normal*(noter[n][start_time]+noter[n][duration])/10)); 
   y2 = (505-(normal*noter[n][start_time]/10));

//Avg�r ifall noten hamnar p� en svart eller vit tangent. 
//Notationen startar med C som har pitchv�rdet 0.
//C=0, C#=1, D=2, D#=3, E=4, F=5 F#=6, G=7 G#=8, A=9, A#=10, B=11  
//Eftersom en oktav = 12 noter s� kan man skriva det som tex C#=1 +12*n
//(nottyp+n*12)%12 = (n+nottyp)%12, d�rf�r f�r varje not ett 
//s�rskilt decimalv�rde p� pitch/12 oavsett vilken oktav

//Att ta bort alla svarta noter g�r 21-108 limit till 21-73, konverterar f�r korrekt output
//Pianot ritas upp fr�n x=35, inom paranteserna r�knar den ut vilken oktav det �r, 
//och ber�knar min-max. D� har vi ett v�rde mellan 0-52, som sedan multipliceras med l�ngden 
//av pianot (730 pixlar) och divideras med 52 f�r noterna

      if(noter[n][pitch]%12 == 0%12 || noter[n][pitch]%12 == 2%12 || noter[n][pitch]%12 == 4%12 || noter[n][pitch]%12 == 5%12 || noter[n][pitch]%12 == 7%12|| noter[n][pitch]%12 == 9%12|| noter[n][pitch]%12 == 11%12)
      {
         //C
         if(noter[n][pitch]%12==0)
         {
         x1 = 35+(((7*floor((noter[n][pitch]-21)/12))+2)*730/52);
         x2 = 35+(((7*floor((noter[n][pitch]-21)/12))+3)*730/52);
         }

         //D
         else if(noter[n][pitch]%12==2%12)
         {
         x1 = 35+(((7*floor((noter[n][pitch]-21)/12))+3)*730/52);
         x2 = 35+(((7*floor((noter[n][pitch]-21)/12))+4)*730/52);
         }

         //E
         else if(noter[n][pitch]%12==4%12)
         {
         x1 = 35+(((7*floor((noter[n][pitch]-21)/12))+4)*730/52);
         x2 = 35+(((7*floor((noter[n][pitch]-21)/12))+5)*730/52);
         }

         //F
         else if(noter[n][pitch]%12==5%12)
         {
         x1 = 35+(((7*floor((noter[n][pitch]-21)/12))+5)*730/52);
         x2 = 35+(((7*floor((noter[n][pitch]-21)/12))+6)*730/52);
         }

         //G
         else if(noter[n][pitch]%12==7%12)
         {
         x1 = 35+(((7*floor((noter[n][pitch]-21)/12))+6)*730/52);
         x2 = 35+(((7*floor((noter[n][pitch]-21)/12))+7)*730/52);
         }

         //A
         else if(noter[n][pitch]%12==9%12)
         {
         x1 = 35+(((7*floor((noter[n][pitch]-21)/12))+0)*730/52);
         x2 = 35+(((7*floor((noter[n][pitch]-21)/12))+1)*730/52);
         }

         //B
         else if(noter[n][pitch]%12==11%12)
         {
         x1 = 35+(((7*floor((noter[n][pitch]-21)/12))+1)*730/52);
         x2 = 35+(((7*floor((noter[n][pitch]-21)/12))+2)*730/52);
         }
         
         //Ger noterna f�rg efter deras track
         if(noter[n][track]==1)
         {
         rectfill(buffer, x1, y1+(nowtime-5000)/10, x2, y2+(nowtime-5000)/10, makecol(0,0,150));
         rectfill(buffer, x1+2, y1+2+(nowtime-5000)/10, x2-2, y2-2+(nowtime-5000)/10, WHITE);
         }
         
         else if(noter[n][track]==2)
         {
         rectfill(buffer, x1, y1+(nowtime-5000)/10, x2, y2+(nowtime-5000)/10, makecol(0,100,0));
         rectfill(buffer, x1+2, y1+2+(nowtime-5000)/10, x2-2, y2-2+(nowtime-5000)/10, WHITE);
         }
         
         else if(noter[n][track]==3)
         {
         rectfill(buffer, x1, y1+(nowtime-5000)/10, x2, y2+(nowtime-5000)/10, makecol(100,0,0));
         rectfill(buffer, x1+2, y1+2+(nowtime-5000)/10, x2-2, y2-2+(nowtime-5000)/10, WHITE);
         }
         
         else
         {
         rectfill(buffer, x1, y1+(nowtime-5000)/10, x2, y2+(nowtime-5000)/10, makecol(0,0,0));
         rectfill(buffer, x1+2, y1+2+(nowtime-5000)/10, x2-2, y2-2+(nowtime-5000)/10, WHITE);
         }
      }

//Ritar upp alla svarta noter. Pianot b�rjar vid 35 pixlar
//det f�rsta v�rdet �r avst�ndet fr�n 35 pixlar till f�rsta noten av det slaget
//Avst�ndet f�r en oktav �r 98 pixlar, det inom parantes best�mmer oktaven

      else
      {
         //C#
         if(noter[n][pitch]%12==1%12)
         {
         x1 = 38 +35+98*floor((noter[n][pitch]-21)/12);
         x2 = 38 +6 +35+98*floor((noter[n][pitch]-21)/12);
         }

         //D#
         else if(noter[n][pitch]%12==3%12)
         {
         x1 = 52 +35+98*floor((noter[n][pitch]-21)/12);
         x2 = 52 +6 +35+98*floor((noter[n][pitch]-21)/12);
         }

         //F#
         else if(noter[n][pitch]%12==6%12)
         {
         x1 = 80 +35+98*floor((noter[n][pitch]-21)/12);
         x2 = 80 +6 +35+98*floor((noter[n][pitch]-21)/12);
         }

         //G#
         if(noter[n][pitch]%12==8%12)
         {
         x1 = 94 +35+98*floor((noter[n][pitch]-21)/12);
         x2 = 94 +6 +35+98*floor((noter[n][pitch]-21)/12);
         }

         //A#
         else if(noter[n][pitch]%12==10%12)
         {
         x1 = 10 +35+98*floor((noter[n][pitch]-21)/12);
         x2 = 10 +6 +35+98*floor((noter[n][pitch]-21)/12);
         }
         
         //Ger noterna f�rg efter deras track
         if(noter[n][track]==1)
         {
         rect(buffer, x1, y1+(nowtime-5000)/10, x2, y2+(nowtime-5000)/10, makecol(0,0,150));
         rectfill(buffer, x1+1, y1+1+(nowtime-5000)/10, x2-1, y2-1+(nowtime-5000)/10, makecol(0,0,0));
         }
         
         else if(noter[n][track]==2)
         {
         rect(buffer, x1, y1+(nowtime-5000)/10, x2, y2+(nowtime-5000)/10, makecol(0,100,0));
         rectfill(buffer, x1+1, y1+1+(nowtime-5000)/10, x2-1, y2-1+(nowtime-5000)/10, makecol(0,0,0));
         }
         
         else if(noter[n][track]==3)
         {
         rect(buffer, x1, y1+(nowtime-5000)/10, x2, y2+(nowtime-5000)/10, makecol(100,0,0));
         rectfill(buffer, x1+1, y1+1+(nowtime-5000)/10, x2-1, y2-1+(nowtime-5000)/10, makecol(0,0,0));
         }
         
         else
         {
         rect(buffer, x1, y1+(nowtime-5000)/10, x2, y2+(nowtime-5000)/10, WHITE);
         rectfill(buffer, x1+1, y1+1+(nowtime-5000)/10, x2-1, y2-1+(nowtime-5000)/10, makecol(0,0,0));
         }
      }


   n++;
   }
   
}
