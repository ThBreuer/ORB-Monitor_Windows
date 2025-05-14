//*******************************************************************
/*!
\file   ORB_Monitor.h
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   25.11.2023

License: See file "LICENSE"
*/

//*******************************************************************
#ifndef _ORB_MONITOR_H
#define _ORB_MONITOR_H

//*******************************************************************
#include "lib.h"
#include "Module/ISC.h"

#include "IPC_Repository.h"
#include "Daten.h"
///#include "Module/Rtos/RTOS.h"

//*******************************************************************
/*!
\class
\brief
*/
class ORB_Monitor
{
  private:
    //---------------------------------------------------------------
    Daten            &daten;
    cIPC_Repository  &ipc;

    cISC::Data<cConfigToORB,     0> ORBconfigOut ;
    cISC::Data<cPropToORB,       1> ORBpropOut;
    cISC::Data<cPropFromORB,     2> orbPropFromORB;
    cISC::Data<cMonitorToORB,    3> ORBmonitorOut;
    cISC::Data<cMonitorFromORB,  4> orbMonitorFromORB;
    cISC::Data<cSettingsFromORB, 5> orbSettingsFromORB;
    cISC::Data<cSettingsToORB,   6> ORBsettingsOut;

    Rtos::Clock  timeoutTimer;

    bool startReq;
    bool stopReq;
    BYTE startParam;
    bool isORBconnected;
    bool isSettingsOK;
    bool isCloseReq;
    bool isDownload;
    BYTE keyCode;

    bool downloadProgReq;
    bool downloadDataReq;
    bool configSendReq;
    int  downloadDataMemId;

    char controlStr[32];
    char connection[32];
    char port[32];

  public:
    //---------------------------------------------------------------
    ORB_Monitor( cIPC_Repository  &ipcIn,
                 Daten            &datenIn )

    : daten              ( datenIn )
    , ipc                ( ipcIn )
    , ORBconfigOut       ( ipc )
    , ORBpropOut         ( ipc )
    , orbPropFromORB     ( ipc )
    , ORBmonitorOut      ( ipc )
    , orbMonitorFromORB  ( ipc )
    , orbSettingsFromORB ( ipc )
    , ORBsettingsOut     ( ipc )

    , timeoutTimer( 3000/*ms*/)

    {
      isORBconnected    = false;
      isSettingsOK      = false;
      startReq          = false;
      stopReq           = false;
      keyCode           = 0;
      downloadDataMemId = 0;
      isCloseReq        = false;
      isDownload        = false;
      downloadProgReq   = false;
      downloadDataReq   = false;
      configSendReq     = false;
    }

    //---------------------------------------------------------------
    ~ORB_Monitor()
    {
      ipc.close();
    }

    //---------------------------------------------------------------
    void close()
    {
      ipc.close();
    }

    //---------------------------------------------------------------
    void startLocalControl( BYTE para )
    {
      startReq = true;
      startParam = para;
    }

    //---------------------------------------------------------------
    void stopLocalControl()
    {
      stopReq = true;
    }

    //---------------------------------------------------------------
    void setKeyCode( BYTE key )
    {
      keyCode = key;
    }

    //---------------------------------------------------------------
    char *getKeyCode(  )
    {
      static char key[4];

      if( 0<keyCode && keyCode<=8)
      {
        sprintf(key,"A%-2d",keyCode);
      }
      else if( 8<keyCode && keyCode<=20)
      {
        sprintf(key,"B%-2d",keyCode-8);
      }
      else if( keyCode==21)
      {
        sprintf(key,"C%-2d",keyCode-20);
      }
      else
      {
        sprintf(key,"--");
      }
      return( key );
    }

    //---------------------------------------------------------------
    void setDownloadRequest( BYTE id )
    {
      startReq = false;
      stopReq  = true;

      if( id == 0 )
        downloadProgReq = true;
      else
      {
        downloadDataReq = true;
        downloadDataMemId = id;
      }
    }

    //---------------------------------------------------------------
    const char* getControlStr()
    {
      return( controlStr );
    }

    //---------------------------------------------------------------
    const char* getConnectionStr()
    {
      return( connection );
    }

    //---------------------------------------------------------------
    int getDownloadRequest()
    {
      if( downloadProgReq )
      {
        ipc.update();
        ipc.update();
        ipc.update();
        Sleep(500);

        downloadProgReq = false;
        return( 0 );
      }

      if( downloadDataReq )
      {
        downloadDataReq = false;
        return( downloadDataMemId );
      }
      return( -1 );
    }

int cnt=0;
    //---------------------------------------------------------------
    void update( bool isDownloadRunning)
    {
      if( isDownloadRunning )
      {
        return;
      }

      ipc.update();

      isORBconnected = daten.isMessDataOK();

      if( !isORBconnected )
        isSettingsOK = false;

      //-----------------------
      // local control auslesen
      //-----------------------
      if( !daten.isConfigToORB_Ackn() && daten.config.isNew() )
      {
        configSendReq = true;
      }

      if( orbPropFromORB.isNew() )
      {
        daten << orbPropFromORB.data;

        if( configSendReq && daten.isConfigToORB_Ackn() )
        {
          configSendReq = false;
        }
      }

      if( orbMonitorFromORB.isNew() )
      {
        if( daten.isLocalControl() )
        {
          daten << orbMonitorFromORB.data; // read line 0 to 3
        }
      }

      if( orbSettingsFromORB.isNew() )
      {
        daten << orbSettingsFromORB.data;

        isSettingsOK = true;
      }

      if( (cnt++)%3 )
      {

        if( stopReq )
        {
          stopReq                    = false;
          startReq                   = false;
          ORBmonitorOut.data.bmode   = 2;
          ORBmonitorOut.data.keycode = 0;
        }
        else if( startReq )
        {
          startReq                     = false;
          ORBmonitorOut.data.bmode     = 1;
          ORBmonitorOut.data.parameter = startParam;
        }
        else if(   ((ORBmonitorOut.data.bmode & 0x01) && daten.isLocalControl())
                || ((ORBmonitorOut.data.bmode & 0x02) && !daten.isLocalControl()) )
        {
          ORBmonitorOut.data.bmode = 0;
        }
        else
        {
          ORBmonitorOut.data.keycode = keyCode;
        }
        ORBmonitorOut.write();
      }

      // todo create and use methode
      daten.monitorToORB.d.data.keycode = keyCode;


      if( isORBconnected )
      {
        if(!isSettingsOK || daten.settingsToORB.isNew() )
        {
          daten >> ORBsettingsOut.data;
          ORBsettingsOut.write();

          daten.clearCommand();
        }
      }
      else
      {
        startReq = false;
        ORBmonitorOut.data.bmode = 0;
      }

      if( daten.isCtrlDataOK()  )
      {
        daten >> ORBpropOut.data;
        ORBpropOut.write();
      }

//      if( (cnt++)%5 == 0 )
//      {
////long tt = GetSysTimeMicroSec();
//        ORBmonitorOut.write();
////printf("delta %ld\n", tt-GetSysTimeMicroSec());
////
//        Sleep(2);
//
//      }

      if( configSendReq )
      {
        daten >> ORBconfigOut.data;
        ORBconfigOut.write();
      }

      //------------------------
      // Check connection to ORB
      //------------------------
      if( daten.isMessDataOK() )
      {
        timeoutTimer.start();
      }

      if( isCloseReq  || timeoutTimer.trigger() )
      {

        ipc.close();

        if( !isCloseReq )
        {
          ipc.open();
          timeoutTimer.start();
        }
        isCloseReq = false;
      }

      //-------------------------
      if( daten.isLocalControl() )
      {
         strcpy( controlStr, "local control");
      }
      else if( ORBmonitorOut.data.bmode == 3 || daten.isCtrlDataOK() )
      {
         strcpy( controlStr, "remote control");
      }
      else
      {
         strcpy( controlStr, "monitoring");
      }

      if( ipc.isOpen() )
      {
         strcpy( connection, ipc.getPortName());
      }
      else
      {
        strcpy( connection, "no port");
      }

      if( strlen(port)>0 &&  strcmp(port,ipc.getPortName()) )
      {
        selectPort( port );
        strcpy( port, "" );
      }
    }

    //---------------------------------------------------------------
    void selectPort(const char *port )
    {
     ipc.setPortName( port );

      if( strcmp(port,"USB")==0)
      {
        ipc.setUsb();
      }
      else if( strncmp(port,"COM",3)==0)
      {
        ipc.setUart();
      }
      else
      {
        ipc.setNoPort();
        isCloseReq = true;
      }
    }

    //---------------------------------------------------------------
};

#endif // _ORB_MONITOR_H
