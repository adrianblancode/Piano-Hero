#include "huvud.h"

void initmidi()
{

//F�ljande kod g�r igenom antalet midi-devices, inte min kod
unsigned long    iNumDevs;
int i, device=0;

//V�rden som anv�nds till midi
MIDIINCAPS     mic;       
HMIDIIN      inhandle;

iNumDevs = midiInGetNumDevs();  /* Get the number of MIDI In devices in this computer */
/* Go through all of those devices, displaying their names */

   for (i = 0; i < iNumDevs; i++)
   {
      /* Get info about the next device */
      if (!midiInGetDevCaps(i, &mic, sizeof(MIDIINCAPS)))
      {
      /* Display its Device ID and name */
      printf("Device ID #%u: %s\r\n", i, mic.szPname);
            
      //Letar efter ifall det finns en nanokey inkopplad (m�rket p� mitt midipiano)
      //Ifall det finns en nanokey inkopplad anv�nds den
      //annars anv�nds vad som �n finns p� ID #0
      if(strstr(mic.szPname, "nanoKEY") != NULL) device=i;
      }
   }

if(device!=0) printf("\nnanoKEY found at #%d\n", device);

   //Midi aktiveras inte ifall devicen �r Fast Track Pro MIDI
   //Eftersom det kan bli fel med att st�nga av den
   if(strstr(mic.szPname, "Fast Track Pro MIDI") == NULL)
   {

   //Startar midi input
   //Om inte midi input fungerar, �ndra parameter 2 till den device du vill anv�nda
   midiInOpen(&inhandle, device, (DWORD)midiCallback, 0, CALLBACK_FUNCTION);
   midiInStart(inhandle);
   }
}
