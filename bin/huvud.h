#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "allegro.h"
#include "winalleg.h"
#include "fmod.h"
#include <time.h>
#include <math.h>
//#include <mmsystem.h>

#define WHITE makecol(255, 255, 255)
#define RED makecol(255,0,0)

enum element{track=0, start_time, pitch, duration, dynamic};

void initmidi();
void intro(char [], long *, BITMAP*, FONT*, FONT*);

int filelenght(char[]);
void las(long int[][], long, char[]);
void sort(long int[][], long int);
void skriv(long int[][], long int, char[]);
bool verify(long int[][], long int);

void debugg(long int[][], long int);
void initnotes(long int[][], long int, long int, float*);
void drawnotes(long int[][], BITMAP*, float, long int, long int);

void CALLBACK midiCallback(HMIDIIN, UINT, DWORD, DWORD, DWORD);
