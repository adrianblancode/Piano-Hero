#include "huvud.h"

//Denna funktion hanterar midi input, samt spelar upp ljud och ritar grafik till input
//Detta är en callback funktion som endast kallas när en tangent på midikeyboardet trycks ner
//Jag har inte lyckats få denna funktion att ta emot värden, så den är isolerad

void CALLBACK midiCallback(HMIDIIN handle, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
{   
unsigned long int on, off;
	
BITMAP* midipress = create_bitmap(800, 95);
BITMAP *piano = load_bitmap( "resources/piano.bmp", NULL);

draw_sprite(midipress, piano, 35, 0);
rectfill(midipress, 0, 0, 35, 95, makecol(0, 0, 0));
rectfill(midipress, 765, 0, 800, 95, makecol(0, 0, 0));
	
//När midi devicen väljs skickas alltid en kontrollsignal som har dwParam1 som 0
	
   if(dwParam1==0)
   {
   printf("\nMidi input starting");                   
   }
   
   //När dwParam1 hamnar i detta intervall brukar noten ha släppts
   else if(dwParam1<4230000 && dwParam1>4200000)
   {
   off = 1+((dwParam1-144)%(256*256))/256;
   }
    
   //Annars kan vi anta att den slogs på
   else
   {
   BITMAP *keyleft = load_bitmap("resources/keyleftf.bmp", NULL);
   BITMAP *keyright = load_bitmap("resources/keyrightf.bmp", NULL);
   BITMAP *keymiddle = load_bitmap("resources/keymiddlef.bmp", NULL);
   BITMAP *keyblack = load_bitmap("resources/keyblackf.bmp", NULL);
   
   FSOUND_STREAM* music;
   char fil[11]="nox/00.wav";
   fil[10]='\0';
         
   on = ((dwParam1-144)%(256*256))/256;
   //printf("\nOn: %ld", on);
   
   textprintf_ex(midipress, font, 10, 0, makecol(255, 255, 255), -1, "%d", on);
   
   fil[4]=(on/10)+'0';
   fil[5]=(on%10)+'0';

   //Noternas placering förklaras mer ingående i drawnotes.c
    
   //A
   if(on%12==9%12)draw_sprite(midipress, keymiddle,35+(((7*floor((on-21)/12))+0)*730/52),12);
    
   //B
   else if(on%12==11%12)draw_sprite(midipress, keyright,35+(((7*floor((on-21)/12))+1)*730/52),12);
   
   //C
   else if(on%12==0)draw_sprite(midipress, keyleft,35+(((7*floor((on-21)/12))+2)*730/52),12);
    
   //D
   else if(on%12==2%12)draw_sprite(midipress, keymiddle,35+(((7*floor((on-21)/12))+3)*730/52),12);
    
   //E
   else if(on%12==4%12)draw_sprite(midipress, keyright,35+(((7*floor((on-21)/12))+4)*730/52),12);
    
   //F
   else if(on%12==5%12)draw_sprite(midipress, keyleft,35+(((7*floor((on-21)/12))+5)*730/52),12);
    
   //G
   else if(on%12==7%12)draw_sprite(midipress, keymiddle,35+(((7*floor((on-21)/12))+6)*730/52),12);
     
     
   //A#
   else if(on%12==10%12)draw_sprite(midipress, keyblack,10+35+98*floor((on-21)/12),12);
    
   //C#
   else if(on%12==1%12)draw_sprite(midipress, keyblack,38+35+98*floor((on-21)/12),12);
    
   //D#
   else if(on%12==3%12)draw_sprite(midipress, keyblack,52+35+98*floor((on-21)/12),12);
    
   //F#
   else if(on%12==6%12)draw_sprite(midipress, keyblack,80+35+98*floor((on-21)/12),12);
    
   //G#
   else if(on%12==8%12)draw_sprite(midipress, keyblack,94+35+98*floor((on-21)/12),12);
   
   //Spelar en ljudfil av noten som slogs
   music=FSOUND_Sample_Load(FSOUND_FREE,fil,0,0,0);
   FSOUND_PlaySound (FSOUND_FREE, music);
   
   //Det går inte att fria minnet till music
   //eftersom ljudfilen inte spelats klart när funktionen slutar,
   //det blir extra svårt av att funktionen är isolerad vilket leder till att
   //programmet läcker ungefär 500kb minne per slagen not (storleken av ljudfilen)
   
   destroy_bitmap(keyleft);   
   destroy_bitmap(keymiddle);   
   destroy_bitmap(keyright);   
   destroy_bitmap(keyblack);   
    
   }

blit(midipress, screen, 0, 0, 0, 505, 800, 95);
destroy_bitmap(midipress);   
destroy_bitmap(piano);   
}
