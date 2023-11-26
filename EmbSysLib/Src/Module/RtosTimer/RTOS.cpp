//*******************************************************************
/*!
\file   Module/RTOS/RTOS.cpp
\author Thomas Breuer
\date   14.02.2011, 09.03.2016
*/

//*******************************************************************
#include "RTOS.h"

//*******************************************************************


//*******************************************************************
//
// cRTOS::Timer
//
//*******************************************************************
//-------------------------------------------------------------------
cRTOS::Timer::Timer( WORD timeToWait_msec )
{
  set( timeToWait_msec ); // Don't use cTimer constructor
}

//-------------------------------------------------------------------
DWORD cRTOS::Timer::getTics( void )
{
  return( (unsigned long)GetSysTimeMilliSec() );
}

//-------------------------------------------------------------------
DWORD cRTOS::Timer::getTimeOfTic( void )
{
  return( 1000/*us*/ );
}



//EOF
