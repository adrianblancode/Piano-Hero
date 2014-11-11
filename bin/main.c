#include "huvud.h"

/* Piano Hero, kodat av Adrian i NV3B

Frågor? Läs readme

För att kunna kompilera denna kod måste biblioteken allegro och fmod finnas installerade
dessutom måste projektet länkas till liballeg.a (midi) libfmod.a (ljud) samt libwinmm.a (midi) 

Kod vars kommentarer är skrivna i engelska är kod jag inte har skrivit
*/

//#undef main behövs eftersom annars vill midicallback inte fungera med winalleg.h
//winalleg används istället för windows.h pga kompabilitetsproblem med allegro.h

#undef main
int main(int argc,char* argv[])
{

//Förbereder allegro
allegro_init();
install_keyboard();
set_color_depth(16);
set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);    
   
//GFX_AUTODETECT = helskärm (får programmet att crasha vid midi input)
//GFX_AUTODETECT_WINDOWED = windowed mode

//Förbereder FSOUND
FSOUND_Init (44100, 32, 0);
FSOUND_STREAM* handle;

//Här hit kommer all notdata sparas
long *noter;

long int storlek=0, caret=0, slenght, songtime=0, n=1;
char filnamn[50]=" ", convmid[50]=" ";
float normal;

//Dessa boolar bestämmer programflödet
_Bool ver=true, process=true, songstart=true;

//Dessa variabler används för att mäta delta tid
clock_t starttime, nowtime;

//Grafik till allegro
FONT* myfont = load_font("resources/bitten.pcx", NULL, NULL);
FONT* bigfont = load_font("resources/bittenbig.pcx", NULL, NULL);
BITMAP* buffer = create_bitmap(800, 600);
BITMAP* runonce = create_bitmap(800, 95);
BITMAP *background = load_bitmap( "resources/background.bmp", NULL);
BITMAP *piano = load_bitmap( "resources/piano.bmp", NULL);

//Startar midi
initmidi();

   //Här börjar huvudloopen, programmet loopar om hela tiden
   while(!key[KEY_ESC])
   { 
   clear(buffer);
   clear_keybuf();


      //Denna del loopar om då en låt inte hittats
      while(storlek==0)
      {
      
      caret=0;
      clear_keybuf();

         while(!key[KEY_ENTER])
         {
         //Avslutar programmet ifall esc trycks
         if(key[KEY_ESC]) return(0);
         
         //Funktion som ritar introskärmen och hanterar lite input
         intro(&filnamn, &caret, buffer, myfont, bigfont);
         }

      //Då enter trycks letar funktionen efter filnamnet
      //skickar tillbaka storleken vid success
      storlek=filelenght(filnamn);
      }
      
      //Denna har en bool som spärr eftersom den bara ska köras en gång för varje ny låt
      if(process==true)
      {
      
      printf("\n\n%s\n", filnamn);
      printf("Storlek: %d noter\n", storlek);                 
      
      //Allokerar minne för en 2d array med samma antal rader som filen
      //med plats för 5 element
      //Det är i denna 2d array all information om noterna sparas
      noter=(long*)malloc(5*storlek*sizeof(long));
   
      //Öppnar filen och sparar all information om noterna i 2d arrayen
      las(noter, storlek, filnamn);
      
      //Sedan verifierar ifall de är i ordning eller inte
      //Ifall de inte är de så sorteras de och skrivs ner i en textfil för senare användning  
      ver=verify(noter, storlek);
      
         if(ver==true)
         {
         sort(noter, storlek);
         skriv(noter, storlek, filnamn);
         }
         
      //Lägger till mid till filnamnet
      slenght=strlen(filnamn);
      strcpy(convmid, filnamn);
      convmid[slenght]='.';
      convmid[slenght+1]='m';
      convmid[slenght+2]='i';
      convmid[slenght+3]='d';
      convmid[slenght+4]='\0';
      
      //Förbereder ljudfilen
      handle=FSOUND_Stream_Open(convmid,0, 0, 0);

      //Hämtar längden på ljudfilen
      songtime=FSOUND_Stream_GetLengthMs(handle);
      printf("Songtime: %d.%ds\n", songtime/1000, songtime%1000);
      
      //Ritar upp pianot i bakgrunden
      //ifall man har ett keyboard ikopplat ritas det upp automatiskt
      //Så detta gör att man har det ritat även utan ett keyboard 
      draw_sprite(runonce, piano, 35, 0);
      rectfill(runonce, 0, 0, 35, 95, makecol(0, 0, 0));
      rectfill(runonce, 765, 0, 800, 95, makecol(0, 0, 0));
      blit(runonce, screen, 0, 0, 0, 505, 800, 95);
      
      //Förbereder lite värden, samt hämtar normal-variabeln
      //som används för att synka textfilen med låten
      initnotes(noter, storlek, songtime, &normal);
      starttime = clock();
      process=false;
      }

   //Tid i ms sedan start
   nowtime = clock()-starttime;    
   clear_bitmap(buffer);

      //Spelar ljudfilen med 400sek delay
      if(nowtime>=5000-400 && songstart==true)
      {
      FSOUND_Stream_Play (0,handle);
      songstart=false;
      }


   //Ritar noterna
   draw_sprite(buffer, background, 35, 0);
   drawnotes(noter, buffer, normal, nowtime, storlek);

   //Ritar bakgrundstext
   if(nowtime<songtime+5000 && nowtime>=5000)
   {
   textprintf_ex(buffer, myfont, 765 - text_length(myfont, "TIME:---/---"), 0, WHITE,-1,"TIME: %d/%d",(nowtime/1000)-5,songtime/1000);
   textprintf_ex(buffer, myfont, 765 - text_length(myfont,"--%"), 20, WHITE,-1,"%d%%", 100*((nowtime/1000)-5)/(songtime/1000));
   }

   if(nowtime<5000)textprintf_ex(buffer, myfont, 400 - text_length(myfont, "Now playing: ---------")/2, 140, WHITE,-1,"Now playing: %s",filnamn);
   if(nowtime<=5000){textprintf_ex(buffer, bigfont, 400 - text_length(bigfont, "-")/2, 200, WHITE,-1,"%d", 5-nowtime/1000);}
   if(nowtime>songtime+5000){textout_ex(buffer, bigfont, "You rock!", 400 - text_length(bigfont, "You rock")/2, 30, WHITE,-1);}

   //Blit ritar upp allt som finns i bufferten till skärmen
   blit(buffer, screen, 0, 0, 0, 0, 800, 505);

      //Upptäcker ifall låten är slut och resettar variablerna
      //Backspace kan tryckas mitt i en låt för att komma till titelskärmen
      if(nowtime>songtime+5000+3000+300 || key[KEY_BACKSPACE])
      {
      free(noter);
      FSOUND_Stream_Close(handle);
      
      clear_bitmap(runonce);
      
      songstart=true;
      process=true;
      ver=true;
      
      storlek=0;
      filnamn[0]='\0';
      }

   }

//Avslutar och friar lite minne
destroy_bitmap(buffer);   
destroy_bitmap(runonce);   
FSOUND_Close();
return(0);
}

