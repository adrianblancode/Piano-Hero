#include "huvud.h"

void intro(char * filnamn, long * caret, BITMAP * buffer, FONT * myfont, FONT *bigfont)
{

//Det finns ingen enkel motsvarighet till fscan i allegro, detta �r det n�rmaste jag hittade
//Denna funktion ritar upp text p� introsk�rmen efter input
//Inte min kod

   if(keypressed())
   {
   clear(buffer);
   int  newkey   = readkey();
   char ASCII    = newkey & 0xff;
   char scancode = newkey >> 8;

   //a character key was pressed; add it to the string
      if(ASCII >= 32 && ASCII <= 126)
      {
         if(*caret < 150 - 1)
         {
         filnamn[*caret] = ASCII;
         (*caret)++;
         filnamn[*caret] = '\0';
         }
      }
          
          else if(scancode == KEY_BACKSPACE)
          {
          if (*caret > 0) (*caret)--;
          filnamn[*caret] = '\0';
          }
   }
            
//Ritande av grafik introsk�rm
textout_ex(buffer, bigfont, "Piano Hero", 400 - text_length(bigfont, "PIANO HERO")/2, 30, WHITE,1);
textout_ex(buffer, myfont, "Choose your song:", 330, 220, WHITE,1);
textout_ex(buffer, myfont, filnamn, 330, 240, WHITE,1);
vline(buffer, 335 + *caret * 9, 245, 255, WHITE);
blit(buffer, screen, 0, 0, 0, 0, 800, 600);

}
