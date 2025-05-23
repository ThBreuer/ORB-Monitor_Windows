//*******************************************************************
/*!
\file   devMotorDirection.h
\author Thomas Breuer
\date   22.02.2019
*/

//*******************************************************************
#ifndef _DEV_MOTOR_DIRECTION_H
#define _DEV_MOTOR_DIRECTION_H

//*******************************************************************
using namespace EmbSysLib::Dev;

//*******************************************************************
/*!
\class   cDevMotorDirection


\example
*/
class cDevMotorDirection : public cDevMotor
{
  private:
    //---------------------------------------------------------------
    Digital    &cw;
    Digital    &ccw;
    AnalogOut  &pwm;

  public:
    //---------------------------------------------------------------
    // Konstruktor
    //
    cDevMotorDirection( Digital    &cw,
                        Digital    &ccw,
                        AnalogOut  &pwm );

  public:
    //---------------------------------------------------------------
    /*!
    */
    virtual void run( float power );

    //---------------------------------------------------------------
    /*!
    */
 	  virtual void brake( void );

};

#endif
