//*******************************************************************
/*!
\file   Module/ISC_USBhost.h
\author Thomas Breuer
\date   11.12.2014

\brief
*/

//*******************************************************************
#ifndef _ISC_USB_HOST_H
#define _ISC_USB_HOST_H

//*******************************************************************
#include "lib.h"
//#ifdef USB_ON
#include "Src/USBhost_MCU.h"
//#endif
#include "Module/ISC.h"

//*******************************************************************
/*!
\class cISC_USBhost

\brief ...

*/
class cISC_USBhost : public cISC
{
  private:
    //---------------------------------------------------------------
    #pragma pack(1)
    class DATA
    {
      public:
        static const WORD maxLength = 60;

        WORD crcValue;
        BYTE id;
        BYTE reserved;
        BYTE data[ maxLength ];

    };
    #pragma pack()

  public:
    //---------------------------------------------------------------
    /*! ...
    */
    cISC_USBhost( USBhost &usb, BYTE interfId, Crc::MODE crcMode = Crc::FAST);

    //---------------------------------------------------------------
    /*! ...
    */
    virtual void update( void );

    //---------------------------------------------------------------
    /*! ...
    */
    virtual void writeStream( BYTE id, BYTE *data, BYTE size, WORD crc );

    public:
    //---------------------------------------------------------------
    USBhost  &usb;
    DATA   rec;

}; //cISC_USBhost

#endif
