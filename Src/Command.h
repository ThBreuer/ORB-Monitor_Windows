//*******************************************************************
/*!
\file   Command.h
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   25.11.2023

License: See file "LICENSE"
*/

//*******************************************************************
#ifndef COMMAND_H
#define COMMAND_H

//*******************************************************************
#include "lib.h"
#include "Sys/UDPclient.h"
#include "Sys/UDPserver.h"

//*******************************************************************
/*!
\class Command

*/
class Command
{
  private:
    //---------------------------------------------------------------
    class Data
    {
      public:
        UDP_MsgHeader header;
        char prog[1024+1];
        char keys[1024+1];

        Data()
        : header( 0 /* ID */, 0 )
        {
        }
    };

  public:
    //*************************************************************
    /*!
    \class Handler

    \brief Interface to handle a request, must be derived by server
    */
    class Handler : public UDPserver::Handler
    {
      public:
        bool flag;
        Data data;

      public:
        //---------------------------------------------------------
        Handler( UDPserver &server )
        : UDPserver::Handler( server )
        {
          flag = false;
        }

        bool isEvent()
        {
          bool ret = flag;
          flag = false;
          return( ret );
        }

        //---------------------------------------------------------
        virtual bool update( BYTE *data, WORD plen )
        {
          BYTE mode = data[0];

          if( plen <= sizeof(Data) )
            memcpy(&(this->data),data,plen);

        if( mode == 0 )
        {
          flag = true;
          return true;
        }
        return false;
      }
    }; //class Handler

  public:
    //---------------------------------------------------------------
    /*! Initialize the ADC hardware
        \param server Name of the server
        \param timer Reference to a timer object
    */
    Command( const char *server)
    : client( server )
    {
    }

  public:
    //----------------------------------------
    virtual void sendCmd(char *prog, char *keys)
    {
      data.header.cmd = 0;

      strncpy(data.prog, prog, 1024);
      strncpy(data.keys, keys, 1024);
      client.send((BYTE*)&data, sizeof(Data));
    }

  public:
    //----------------------------------------
    Data       data;
    UDPclient  client;

}; //class ...

#endif // COMMAND_H
