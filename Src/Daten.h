//*******************************************************************
/*!
\file   Daten.h
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   25.11.2023

License: See file "LICENSE"
*/

//*******************************************************************
#ifndef _DATEN_H
#define _DATEN_H

//*******************************************************************
#include "lib.h"
#include "Properties.h"
#include "Module/RtosTimer/RTOS.h"

//*******************************************************************
class Daten
{
  public:
    //---------------------------------------------------------------
    template <class T> class Set
    {
      public:
        //-------------------------------------------------------------
        T             d;
      private:
        //-------------------------------------------------------------
        cRTOS::Timer  timeout;
        bool          isNewFlag;

      public:
        //-------------------------------------------------------------
        Set()
        : timeout( 1000 )
        {
          isNewFlag = 0;
        }

        //-------------------------------------------------------------
        void setUpdate()
        {
          isNewFlag = true;
          timeout.start();
        }

        //-------------------------------------------------------------
        bool isTimeout()
        {
          return( !timeout.isRunning() );
        }

        //-------------------------------------------------------------
        bool isNew()
        {
          if( isNewFlag )
          {
            isNewFlag = false;
            return( true );
          }
          return( false );
        }

        //-------------------------------------------------------------
        void operator<<(typename T::Data &x)
        {
          d.data = x;
          isNewFlag = true;
          timeout.start();
        }

        //-------------------------------------------------------------
        void operator>>(T &x)
        {
          x = d;
        }
    };

  public:
    //***************************************************************
    class ConfigToORB
    {
      public:
        //-------------------------------------------------------------
        class Data
        {
          public:
            //-----------------------------------------------------------
            class Sensor
            {
              public:
                BYTE type;
                BYTE mode;
                WORD option;
            } sensor[4];
            //-----------------------------------------------------------
            class Motor
            {
              public:
                WORD ticsPerRotation;
                BYTE acceleration;
                BYTE Regler_Kp;
                BYTE Regler_Ki;
            } motor[4];
        } data;

      public:
        //-----------------------------------------------------------
        ConfigToORB()
        {
          memset(this,0,sizeof(ConfigToORB));
        }

        //-----------------------------------------------------------
        void update() {}

        //-----------------------------------------------------------
        void operator>>( cConfigToORB::Data &x )
        {
          for(int i=0;i<4;i++)
          {
            x.sensorConfig[i].type   = data.sensor[i].type;
            x.sensorConfig[i].mode   = data.sensor[i].mode;
            x.sensorConfig[i].option = data.sensor[i].option;
          }
          for(int i=0;i<4;i++)
          {
            x.motorConfig[i].ticsPerRotation = data.motor[i].ticsPerRotation;
            x.motorConfig[i].acceleration    = data.motor[i].acceleration;
            x.motorConfig[i].Regler_Kp       = data.motor[i].Regler_Kp;
            x.motorConfig[i].Regler_Ki       = data.motor[i].Regler_Ki;
          }
        }
    };

    //***************************************************************
    class PropToORB
    {
      public:
        //-------------------------------------------------------------
        class Data
        {
          public:
            //-----------------------------------------------------------
            class Motor
            {
              public:
                BYTE  mmode;
                short speed;
                int   pos;
            } motor[4];

            //-----------------------------------------------------------
            class ModelServo
            {
              public:
                BYTE sspeed;
                BYTE spos;
            } modelServo[2];
        } data;

      public:
        //-----------------------------------------------------------
        PropToORB()
        {
          memset(this,0,sizeof(PropToORB));
        }

        //-----------------------------------------------------------
        void update() {}

        //-----------------------------------------------------------
        void operator>>( cPropToORB::Data &x )
        {
          for(int i=0;i<4;i++)
          {
            x.motor[i].mmode = data.motor[i].mmode;
            x.motor[i].speed = data.motor[i].speed;
            x.motor[i].pos   = data.motor[i].pos;
          }
          for(int i=0;i<2;i++)
          {
            x.modelServo[i].sspeed = data.modelServo[i].sspeed;
            x.modelServo[i].spos  = data.modelServo[i].spos;
          }
        }
    };

    //***************************************************************
    class PropFromORB
    {
      public:
        //-------------------------------------------------------------
        class Data
        {
          public:
            //-----------------------------------------------------------
            class Motor
            {
              public:
                char  pwr;
                short speed;
                int   pos;
            } motor[4];

            //-----------------------------------------------------------
            class Sensor
            {
              public:
                unsigned int   value[2];
                BYTE           type;
                BYTE           descriptor;
                BYTE           option;
                bool           valid;
            } sensor[4];

            //-----------------------------------------------------------
            BYTE Vcc;
            BYTE status;
            bool taster[2];
      } data;

      private:
        //-----------------------------------------------------------
        DWORD sensorValue[4][2];

      public:
        //-----------------------------------------------------------
        PropFromORB()
        {
          memset(this,0,sizeof(PropFromORB));
        }

        //-----------------------------------------------------------
        void update() {}

        //-----------------------------------------------------------
        void operator<<( cPropFromORB::Data &x )
        {
          for(int i=0;i<4;i++)
          {
            data.motor[i].pwr   = x.motor[i].pwr;
            data.motor[i].speed = x.motor[i].speed;
            data.motor[i].pos   = x.motor[i].pos;
          }

          for(int i=0;i<4;i++)
          {
            BYTE lenExp  = (x.sensor[i].descriptor>>5)&0x07;
            BYTE package = x.sensor[i].descriptor & 0x1F;

            BYTE ready = false;

            if( lenExp <= 2 && package==0) // nur ein packet
            {
              sensorValue[i][0] = x.sensor[i].value;
              sensorValue[i][1] = 0;
              ready = true;
            }
            else if( lenExp <4 && package == 0 ) // 1. von 2 packeten
            {
              sensorValue[i][0] = x.sensor[i].value;
              sensorValue[i][1] = 0;
            }
            else if( lenExp <4 && package == 1 ) // 2. von 2 packeten
            {
              sensorValue[i][1] = x.sensor[i].value;
              ready = true;
            }
            else // alle anderen
            {
             printf("error Daten.h:%d\n",__LINE__);
            }

            if( ready)
            {
              data.sensor[i].value[0]   = sensorValue[i][0];
              data.sensor[i].value[1]   = sensorValue[i][1];
              data.sensor[i].descriptor = x.sensor[i].descriptor;
              data.sensor[i].option     = x.sensor[i].option;
              data.sensor[i].type       = x.sensor[i].type&0x7F;
              data.sensor[i].valid      = (bool)(x.sensor[i].type&0x80);
            }

          }

          data.taster[0] = (bool)(x.digital & 0x01 );
          data.taster[1] = (bool)(x.digital & 0x02 );

          data.status = x.status;
          data.Vcc    = x.Vcc;

        }
    }; //PropFromORB

    //***************************************************************
    class MonitorToORB
    {
      public:
        //-------------------------------------------------------------
        class Data
        {
          public:
            //-----------------------------------------------------------
            BYTE bmode;
            BYTE parameter;
            BYTE keycode;
        } data;

      public:
        //-----------------------------------------------------------
        MonitorToORB()
        {
          data.bmode     = 0;
          data.parameter = 0;
          data.keycode   = 0;
        }

        //-----------------------------------------------------------
        void update() {}

        //-----------------------------------------------------------
        void operator>>( cMonitorToORB::Data &x )
        {
          x.bmode = data.bmode;
          x.parameter = data.parameter;
          x.keycode = data.keycode;
        }

    }; //MonitorToORB

    //***************************************************************
    class MonitorFromORB
    {
      public:
        //-------------------------------------------------------------
        class Data
        {
          public:
            //-----------------------------------------------------------
            char text[4][30+1];
        } data;

      public:
        //-----------------------------------------------------------
        MonitorFromORB()
        {
          memset( data.text, 0, 4*31 );
        }

        //-----------------------------------------------------------
        void update() {}

        //-----------------------------------------------------------
        void operator<<( cMonitorFromORB::Data &x )
        {
          if( 0 <= x.line && x.line < 4)
          {
            strncpy(data.text[x.line],x.text,30);
          }
        }
    };

    //***************************************************************
    class SettingsFromORB
    {
      public:
        //-------------------------------------------------------------
        class Data
        {
          public:
            //---------------------------------------------------------------
            WORD version[2];
            WORD board[2];
            char name[21];
            BYTE VCC_ok;
            BYTE VCC_low;
        } data;

      public:
        //-----------------------------------------------------------
        SettingsFromORB()
        {
          strncpy(data.name,"---",20);
          data.version[0] = 0;
          data.version[1] = 0;
          data.board[0]   = 0;
          data.board[1]   = 0;
          data.VCC_ok  = 0;
          data.VCC_low = 0;
        }

        //-----------------------------------------------------------
        void update() {}

        //-----------------------------------------------------------
        void operator<<( cSettingsFromORB::Data &x )
        {
          data.version[0] = x.version[0];
          data.version[1] = x.version[1];
          data.board[0]   = x.board[0];
          data.board[1]   = x.board[1];
          strncpy(data.name,x.name,20);
          data.VCC_ok = x.VCC_ok;
          data.VCC_low = x.VCC_low;
        }
    }; //

    //***************************************************************
    class SettingsToORB
    {
      public:
        //-------------------------------------------------------------
        class Data
        {
          public:
            //---------------------------------------------------------------
            BYTE command;
            char name[21];
            BYTE VCC_ok;
            BYTE VCC_low;
        } data;

      public:
        //-----------------------------------------------------------
        SettingsToORB()
        {
          data.command  = 0;
          strncpy(data.name,"---",20);
          data.VCC_ok   = 78;
          data.VCC_low  = 72;
        }

        //-----------------------------------------------------------
        void operator>>( cSettingsToORB::Data &x )
        {
          x.command = data.command;
          strncpy(x.name,data.name,20);
          x.VCC_ok = data.VCC_ok;
          x.VCC_low = data.VCC_low;
        }



      }; //

  //*******************************************************************
  //
  //*******************************************************************
  public:
    //-----------------------------------------------------------------
    Set<ConfigToORB>     config;
    Set<PropToORB>       control;
    Set<PropFromORB>     mess;
    Set<MonitorToORB>    monitorToORB;
    Set<MonitorFromORB>  monitorFromORB;
    Set<SettingsFromORB> settingsFromORB;
    Set<SettingsToORB>   settingsToORB;

  public:
    //-----------------------------------------------------------------
    Daten()
    {
    }

    //-----------------------------------------------------------------
    void operator>>( cConfigToORB::Data &x )
    {
      config.d >> x;
    }

    //-----------------------------------------------------------------
    void operator>>( cPropToORB::Data &x )
    {
      control.d >> x;
    }

    //-----------------------------------------------------------------
    void operator>>( cSettingsToORB::Data &x )
    {
      settingsToORB.d >> x;
    }

    //-----------------------------------------------------------------
    void operator>>( cMonitorToORB::Data &x )
    {
      monitorToORB.d >> x;
    }

    //-----------------------------------------------------------------
    void operator<<( cPropFromORB::Data &x )
    {
      mess.d << x;
      mess.setUpdate();
    }

    //-----------------------------------------------------------------
    void operator<< ( cMonitorFromORB::Data &x )
    {
      monitorFromORB.d << x;
      monitorFromORB.setUpdate();
    }

    //-----------------------------------------------------------------
    void operator<< ( cSettingsFromORB::Data &x )
    {
      settingsFromORB.d << x;
      settingsFromORB.setUpdate();
    }

    //-----------------------------------------------------------------
    void clearCommand()
    {
      settingsToORB.d.data.command = 0;
    }

    //-----------------------------------------------------------------
    bool isMessDataOK()
    {
      return( !mess.isTimeout() );
    }

    //-----------------------------------------------------------------
    bool isCtrlDataOK()
    {
      return( !control.isTimeout() );
    }

    //-----------------------------------------------------------------
    // ORB bestätigt den Erhalt von ConfigToORB im nächsten PropFromORB
    // einmalig mit gesetztem Status-Bit
    bool isConfigToORB_Ackn()
    {
      if( !mess.isTimeout() )
        return( mess.d.data.status & 0x02 );
      else
        return( false );
    }

    //-----------------------------------------------------------------
    bool isLocalControl()
    {
      return( mess.d.data.status & 0x01 );
    }

    //*****************************************************************
    //*****************************************************************
    //-----------------------------------------------------------------
    const char *getMonitorText( BYTE id )
    {
      if( id >= 4 )
        return( "???" );

      return( monitorFromORB.d.data.text[id] );
    }

    //---------------------------------------------------------------
    const char* getSensorByString( unsigned id )
    {
      if( id >= 4 )
        return( "???" );

      static char str[32];

      switch( mess.d.data.sensor[id].type & 0x7F )
      {
        default:
        {
          sprintf(str, "%u (%x): 0x%08x,0x%08x",
                  mess.d.data.sensor[id].type,
                  mess.d.data.sensor[id].valid,
                  mess.d.data.sensor[id].value[0],
                  mess.d.data.sensor[id].value[1]);
          break;
        }

        case   cConfigToORB::Data::SensorConfig::UART:
        {

          if( (mess.d.data.sensor[id].descriptor >> 5)>2)
            sprintf(str, "UART (%u,%x): 0x%08x,0x%08x",
                    mess.d.data.sensor[id].option,
                    mess.d.data.sensor[id].valid,
                    mess.d.data.sensor[id].value[0],
                    mess.d.data.sensor[id].value[1]);
          else

            sprintf(str, "UART (%u,%x): %u",
                    mess.d.data.sensor[id].option,
                    mess.d.data.sensor[id].valid,
                    mess.d.data.sensor[id].value[0]);
          break;
        }

        case   cConfigToORB::Data::SensorConfig::ANALOG:
        {
          WORD analog1 = (mess.d.data.sensor[id].value[0]      )&0x0FFF;
          WORD analog2 = (mess.d.data.sensor[id].value[0] >> 12)&0x0FFF;
          BYTE pin6    = (mess.d.data.sensor[id].value[0] >> 24)&0x0001;
          BYTE pin5    = (mess.d.data.sensor[id].value[0] >> 25)&0x0001;

          sprintf(str, "ANALOG D5:%c D1:%c A1:%5u   A2:%5u",
                  pin5?'I':'o',
                  pin6?'I':'o',
                  analog1,
                  analog2 );
          break;
        }

      }

      return( str );
    }

    //---------------------------------------------------------------
    const char* getDigitalByString( unsigned id )
    {
      if( id >= 2 )
        return( "???" );

      static char str[32];
      sprintf(str, "T%d: %c", id+1, mess.d.data.taster[id]?'I':'0' );
      return( str );
    }

    //---------------------------------------------------------------
    const char* getMotorByString( unsigned id )
    {
      if( id >= 4 )
        return( "???" );

      static char str[32];
      sprintf( str, "%5d  %5d %11d", (int)mess.d.data.motor[id].pwr,
                                     (int)mess.d.data.motor[id].speed,
                                     (int)mess.d.data.motor[id].pos );
      return( str );
    }

    //-----------------------------------------------------------------
    char *getVccByString( void )
    {
      static char str[32];
      sprintf(str, "Vcc: %.1f V", 0.1*mess.d.data.Vcc );
      return( str );
    }

    //-----------------------------------------------------------------
    char *getLabelByString( void )
    {
      static char str[32];
      sprintf(str, "%s", settingsFromORB.d.data.name );
      return( str );
    }

};

#endif
