#ifdef DOS
#include "..\include\globals.h"
#include "..\include\extern.h"
#endif

#ifdef UNIX
#include "../include/globals.h"
#include "../include/extern.h"
#endif

void Rip_SuperCruncher27 ( void )
{
  /* PW_l is still the whole size */

  Uchar * Amiga_EXE_Header_Block;

  OutputSize = PW_l;

  /*  printf ( "\b\b\b\b\b\b\b\bSuper Cruncher 2.7 Exe-file found at %ld !. its size is : %ld\n" , PW_Start_Address , OutputSize );*/
  /*  OutName[1] = Extensions[SuperCruncher][0];
  OutName[2] = Extensions[SuperCruncher][1];
  OutName[3] = Extensions[SuperCruncher][2];*/

  CONVERT = BAD;

  if ( Amiga_EXE_Header == BAD )
  {
    OutputSize -= 36;
    Amiga_EXE_Header_Block = (Uchar *) malloc ( 36 );
    BZERO ( Amiga_EXE_Header_Block , 36 );
    Amiga_EXE_Header_Block[2]  = Amiga_EXE_Header_Block[30] = 0x03;
    Amiga_EXE_Header_Block[3]  = 0xF3;
    Amiga_EXE_Header_Block[11] = 0x02;
    Amiga_EXE_Header_Block[19] = 0x01;
    Amiga_EXE_Header_Block[23] = Amiga_EXE_Header_Block[35] = 0xA8;
    Amiga_EXE_Header_Block[31] = 0xE9;

    Amiga_EXE_Header_Block[24] = in_data[PW_Start_Address+680];
    Amiga_EXE_Header_Block[25] = in_data[PW_Start_Address+681];
    Amiga_EXE_Header_Block[26] = in_data[PW_Start_Address+682];
    Amiga_EXE_Header_Block[27] = in_data[PW_Start_Address+683];

    /* also the last 4 bytes are 'removed' frequently ... Here they are */
    in_data[PW_Start_Address+OutputSize-4]  = 0x00;
    in_data[PW_Start_Address+OutputSize-3]  = 0x00;
    in_data[PW_Start_Address+OutputSize-2]  = 0x03;
    in_data[PW_Start_Address+OutputSize-1]  = 0xF2;

    Save_Rip_Special ( "Super Cruncher 2.7 Exe-file", SuperCruncher, Amiga_EXE_Header_Block , 36 );
    free ( Amiga_EXE_Header_Block );
  }
  else
  {
    PW_Start_Address -= 36;
    Save_Rip ( "Super Cruncher 2.7 Exe-file", SuperCruncher );
  }
  
  if ( Save_Status == GOOD )
    PW_i += (OutputSize - 40);  /* 36 should do but call it "just to be sure" :) */
}
