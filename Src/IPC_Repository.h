//*******************************************************************
/*!
\file   IPC_Repository.h
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   25.11.2023

License: See file "LICENSE"
*/

//*******************************************************************
#ifndef _IPC_REPOSITORY_H
#define _IPC_REPOSITORY_H

//*******************************************************************
// \todo Define VID/PID not here
#define VID 0x0023
#define PID 0x2000

//*******************************************************************
class cIPC_Repository : public cISC
{
  public:
    //---------------------------------------------------------------
    cIPC_Repository( Uart_Serial &uartIn, USBhost &usbIn )

    : cISC(Crc::FAST),
      uart( uartIn),
      usb(usbIn),
      ipcUart(uart),
      ipcUsb( usb, 0)
    {
      ipc = NULL;
      port = 0;
    }

    //---------------------------------------------------------------
    void setNoPort()
    {
      port = 0;
      close();
      ipc = NULL;
    }

    //---------------------------------------------------------------
    void setUart()
    {
      ipcUart.list = list;
      uart.open(portNameShort);
      ipc = &ipcUart;
      port = 1;
      usb.close();
    }

    //---------------------------------------------------------------
    void setUsb()
    {
      ipcUsb.list = list;
      usb.open(VID,PID,0);
      ipc = &ipcUsb;
      port = 2;
      uart.close();
    }

    //---------------------------------------------------------------
    void update()
    {
      if( ipc )
      {
          ipc->update();
      }
    }

    //---------------------------------------------------------------
    void writeStream( BYTE id, BYTE *data, BYTE size, WORD crc )
    {
      if( ipc )
      {
          ipc->writeStream( id, data, size, crc );
          // \todo Check Sleep
          Sleep(3);
      }
    }

    //---------------------------------------------------------------
    BYTE open()
    {
      close();
      switch( port )
      {
        case 1: uart.open( portNameShort ); break;
        case 2: usb.open ( VID, PID, 0 );   break;
      }
      return(0);
    }

    //---------------------------------------------------------------
    BYTE isOpen()
    {
      switch( port )
      {
        case 1: return( uart.isOpen() );
        case 2: return( usb.isConnected() );
      }
      return( false );
    }

    //---------------------------------------------------------------
    void close()
    {
//      printf("close ipc\r\n");
      if( uart.isOpen() )
        uart.close();
      if( usb.isConnected() )
        usb.close();
    //  ipc = NULL;
    }

    //---------------------------------------------------------------
    void setPortName(const char *portNameIn)
    {
      if( portNameIn == 0 || strlen(portNameIn) == 0)
      {
        return;
      }
      else
      {
        strncpy( portName, portNameIn, 32);
        sscanf( portName,"%s",portNameShort);
      }
    }

    //---------------------------------------------------------------
    char *getPortName()
    {
      return(  portName );
    }

  public:
    //---------------------------------------------------------------
    char portName[33];
    char portNameShort[33];

    Uart_Serial  &uart;
    USBhost      &usb;
    cISC_UART     ipcUart;
    cISC_USBhost  ipcUsb;
    cISC         *ipc;
    BYTE          port;
};

#endif
