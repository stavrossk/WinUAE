#ifdef DOS
#include "..\include\globals.h"
#include "..\include\extern.h"
#endif

#ifdef UNIX
#include "../include/globals.h"
#include "../include/extern.h"
#endif

short testJamCracker ( void )
{
  PW_Start_Address = PW_i;

  /* number of samples */
  PW_j = in_data[PW_Start_Address+5];
  if ( (PW_j == 0) || (PW_j > 0x1f) )
  {
/*printf ( "#1 (start:%ld) (number of samples:%ld)\n" , PW_Start_Address , PW_j);*/
    return BAD;
  }

  /* sample sizes */
  /* PW_j is the number of sample */
  PW_WholeSampleSize = 0;
  for ( PW_k=0 ; PW_k<PW_j ; PW_k++ )
  {
    PW_l =((in_data[PW_Start_Address+38+PW_k*40]*256*256*256)+
           (in_data[PW_Start_Address+39+PW_k*40]*256*256)+
           (in_data[PW_Start_Address+40+PW_k*40]*256)+
            in_data[PW_Start_Address+41+PW_k*40] );
    if ( PW_l == 0 )
    {
/*printf ( "#2 (Start:%ld) (sample:%ld) (size:%ld)\n" , PW_Start_Address , PW_k , PW_l );*/
      return BAD;
    }
    PW_WholeSampleSize += PW_l;
  }

  /* number of pattern saved */
  /* PW_j is the number of sample */
  /* PW_WholeSampleSize is the whole sample size :) */
  PW_l = in_data[PW_Start_Address+(PW_j*40)+7];
  /* test if more than FF patterns */
  if ( in_data[PW_Start_Address+(PW_j*40)+6] != 0 )
  {
/*printf ( "#3 (Start:%ld) (number of pattern : %d,%ld)\n" , PW_Start_Address , in_data[PW_Start_Address+(PW_j*40)+6] , PW_l );*/
    return BAD;
  }

  /* size of pattern list */
  /* PW_j is the number of sample */
  /* PW_WholeSampleSize is the whole sample size :) */
  /* PW_l is the number of pattern saved */
  PW_m = in_data[PW_Start_Address+(PW_j*40)+9+(PW_l*6)];
  PW_n = in_data[PW_Start_Address+(PW_j*40)+8+(PW_l*6)];
  /* test if more than FF patterns */
  if ( PW_n != 0 )
  {
/*printf ( "#4 (Start:%ld) (number of pattern : %ld,%ld)\n" , PW_Start_Address , PW_n , PW_m );*/
    return BAD;
  }


  /* PW_j is the number of sample */
  /* PW_WholeSampleSize is the whole sample size :) */
  /* PW_l is the number of pattern saved */
  /* PW_m is the size of the pattern list */
  return GOOD;
}
