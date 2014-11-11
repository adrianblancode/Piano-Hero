#include "huvud.h"

void initmidi()
{

//Följande kod går igenom antalet midi-devices, inte min kod
unsigned long    iNumDevs;
int i, device=0;

//Värden som används till midi
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
            
      //Letar efter ifall det finns en nanokey inkopplad (märket på mitt midipiano)
      //Ifall det finns en nanokey inkopplad används den
      //annars används vad som än finns på ID #0
      if(strstr(mic.szPname, "nanoKEY") != NULL) device=i;
      }
   }

if(device!=0) printf("\nnanoKEY found at #%d\n", device);

   //Midi aktiveras inte ifall devicen är Fast Track Pro MIDI
   //Eftersom det kan bli fel med att stänga av den
   if(strstr(mic.szPname, "Fast Track Pro MIDI") == NULL)
   {

   //Startar midi input
   //Om inte midi input fungerar, ändra parameter 2 till den device du vill använda
   midiInOpen(&inhandle, device, (DWORD)midiCallback, 0, CALLBACK_FUNCTION);
   midiInStart(inhandle);
   }
}
