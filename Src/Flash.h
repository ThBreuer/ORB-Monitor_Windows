//*******************************************************************
/*!
\file   Flash.h
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   25.11.2023

License: See file "LICENSE"
*/

//*******************************************************************
#ifndef _FLASH
#define _FLASH

//*******************************************************************
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "lib.h"
#include "Module/ISC.h"

#include <wx/chartype.h>

//*******************************************************************
using namespace std;

//*******************************************************************
class Image
{
  public:
    //---------------------------------------------------------------
    Image( const char    *fileNameIn,
           unsigned long  memIndexIn = 0 )
    {
      memIndex     = memIndexIn;
      memFlashSize = 0;
      const char *flag;

      if( strlen(fileNameIn) > 0 )
      {
        fileName = fileNameIn;
        flag     = "rb";
      }
      else
      {
        fileName = "~image.bin";
        flag     = "wb+";
      }
      if( (fp = fopen(fileName,flag)) > 0 )
      {
        fseek( fp, 0, SEEK_END );
        memFlashSize = 32L*((ftell(fp)+31)/32);
      }
      else
      {
        fp = NULL;
      }
    }

    //---------------------------------------------------------------
    ~Image( void )
    {
      if( fp != NULL )
      {
        fclose( fp );
      }
    }

    //---------------------------------------------------------------
    void setIndex( WORD index )
    {
      memIndex = index;
    }

    //---------------------------------------------------------------
    DWORD getIndex()
    {
      return(memIndex);
    }

    //---------------------------------------------------------------
    DWORD getSize()
    {
      return(memFlashSize);
    }

    //---------------------------------------------------------------
    void write( unsigned long addr, BYTE data )
    {
      if( fp )
      {
        fseek( fp, addr, SEEK_SET );
        fwrite( &data, 1, 1, fp );
        fseek( fp, 0, SEEK_END );
        memFlashSize = 32L*((ftell(fp)+31)/32);
      }
    }

    //---------------------------------------------------------------
    BYTE read( unsigned long addr )
    {
      char data = 0;
      if( fp )
      {
        fseek( fp, addr, SEEK_SET );
        fread( &data, 1, 1, fp );
      }
      return( data );
    }

  private:
    //---------------------------------------------------------------
    FILE *fp;
    const char *fileName;
    unsigned long memIndex;
    unsigned long memFlashSize;
};

//*******************************************************************
class DownloadData
{
  public:
    //---------------------------------------------------------------
    #pragma pack(1)
    class Data
    {
      public:
        Data() {}
        WORD  index;
        WORD  option;
        DWORD numOfBlocks;
        DWORD blockId;
        BYTE  payload[32];
    } data;
    #pragma pack()

    //---------------------------------------------------------------
    DownloadData() {}

    //---------------------------------------------------------------
    virtual void update()
    {
    }
};
//*******************************************************************

//*******************************************************************
class DownloadReply
{
  public:
    //---------------------------------------------------------------
    #pragma pack(1)
    class Data
    {
      public:
        Data() {}
        WORD  error;
        WORD  crc;
        DWORD length;
        BYTE payload[32];
    } data;
    #pragma pack()

    //---------------------------------------------------------------
    DownloadReply() {}

    //---------------------------------------------------------------
    virtual void update()
    {
    }
};
//*******************************************************************

//*******************************************************************
class DownloadTool
{
  public:
    //---------------------------------------------------------------
    enum
    {
      RECORD_MARK = 0,
      RECLEN,
      LOAD_OFFSET,
      RECTYP,
      DATA,
      CHECKSUM
    };

  private:
    //---------------------------------------------------------------
    BYTE checkSum;

    int state;

    unsigned int id;
    unsigned long len;
    unsigned long loadoffset;
    unsigned long rectyp;

    unsigned char pos;
    unsigned long xdata;
    unsigned long x;
    unsigned long addr;
    unsigned long extSegm;

    bool firstRec;
    FILE *fp;

  public:
    //---------------------------------------------------------------
    unsigned char err;

  public:
    //---------------------------------------------------------------
    DownloadTool(  )
    {
      state = RECORD_MARK;
      pos = 0;
      checkSum = 0;
      err = 0;
    }

    //---------------------------------------------------------------
    bool open( const char *name)
    {
      state    = RECORD_MARK;
      pos      = 0;
      checkSum = 0;
      err      = 0;
      addr     = 0;
      extSegm  = 0;
      firstRec = true;

      if((fp = fopen(name,"rb+"))>0)
      {
        return( true );
      }
      return( false );
    }

    //---------------------------------------------------------------
    bool readImage( Image &image )
    {
      char c;
      while( fread( &c, 1, 1, fp ) == 1 )
      {
        if( !execute( c, image ) )
        {
          printf("\n\nERROR %d\n\n",err);
          return( false );
        }
      }
      return( true );
    }

    //---------------------------------------------------------------
    bool close()
    {
      fclose( fp );
      return( true );
    }

    //---------------------------------------------------------------
    bool readValue( unsigned long &value,
                    unsigned char  size,
                    unsigned char &pos,
                    char           c )
    {
      if( pos == 0 ) // first char of value?
      {
        value = 0;
      }

      if( pos < size )
      {
        pos++;
        unsigned long x = 0;
        if( c >= '0' && c <= '9' )
          x = c-'0';
        else if( c >= 'A' && c<='F')
          x = c-'A'+10;
        else if( c >= 'a' && c<='f')
          x = c-'a'+10;
        else
          x = 0; // ERROR ???
        value |= x << 4*(size-pos);
      }

      if( pos >= size )
      {
        checkSum += value&0xFF;
        if( size > 1 )
        {
          checkSum += (value>> 8)&0xFF;
          checkSum += (value>>16)&0xFF;
          checkSum += (value>>24)&0xFF;
        }

        pos = 0;
        return( true ); // ready ?
      }
      else
      {
        return( false );
      }
    }

    //---------------------------------------------------------------
    bool execute( char c, Image &image )
    {
      switch( state )
      {
        default:
          break;

        case RECORD_MARK:
          if( c == ':' )
          {
            state = RECLEN;
            pos = 0;
            checkSum = 0;
           }
           break;

        case RECLEN:
          if( readValue( len, 2, pos, c ) )
          {
            state = LOAD_OFFSET;
          }
          break;

        case LOAD_OFFSET:
          if( readValue( loadoffset, 4, pos, c ) )
          {
            state = RECTYP;
          }
          break;

        case RECTYP:
          if( readValue( rectyp, 2, pos, c ) )
          {
            state = (len>0)?DATA:CHECKSUM;
            addr = extSegm*0x10000 + loadoffset;
            if( rectyp == 0 && firstRec )
            {
              firstRec=false;
            }
            id=0;
            xdata = 0;
          }
          break;

        case DATA:
          if( rectyp!=0 && len <= 4 )
          {
            if( readValue( xdata, 2*len, pos, c ) )
            {
              state = CHECKSUM;
            }
          }
          else
          {
            if( readValue( x, 2, pos, c ) )
            {
               id++;
               unsigned long j = (addr++)-extSegm*0x10000;
               image.write(j,x);

              if(id>=len)
              {
                state = CHECKSUM;
              }
            }
          }
          break;

        case CHECKSUM:
          if( readValue( x, 2, pos, c ) )
          {
            state = RECORD_MARK;
            if( checkSum != 0 )
            {
                //++++++++++
                err= 2; //
                printf( "ERROR  %02x  %02lx\n\r",checkSum,x);
                return( false ); //exit(-1);
                //++++++++++
            }

            switch(rectyp)
            {
              case 0:
                //printf("nutzdaten\n");
                break;
              case 1:
                //printf("ende\n");
                break;
              case 2:
                //printf("extended segment %x\n",xdata);
                extSegm = xdata;
                addr    = extSegm*0x10000;
                break;
              case 3:
                //printf("start segment\n");
                break;
              case 4:
                //printf("extended linear %x\n",xdata);
                extSegm = xdata;
                addr    = extSegm*0x10000;
               break;
              case 5:
                //printf("start linear %x\n",xdata);
                break;
            }
          }
          break;
        }
        return( true );
      }
};

//*******************************************************************
class FlashTool
{
  private:
    //---------------------------------------------------------------
    cISC &ipc;
    cISC::Data<DownloadData, 254>  out;
    cISC::Data<DownloadReply, 255> in;

  public:
    class Info
    {
      public:
          typedef enum
          {
            NONE = 0,
            CONNECTING,
            RUNNING,
            READY,
            ERR_TIMEOUT,
            ERR_DATA,
            ERR_CRC,
            ERR_FILE,
          } Status;

          Info()
          {
              percent = 0;
              size = 0;
              status = NONE;
          }
        int percent;
        unsigned size;
        Status status;
    } info;

  public:
    //---------------------------------------------------------------
    FlashTool( cISC &ipcIn  )

    : ipc( ipcIn ),
      out( ipc ),
      in( ipc )
    {

    }

    //---------------------------------------------------------------
    bool sendImage( Image &image, WORD option = 0 )
    {
      unsigned numOfBlocks = (image.getSize()+31)/32;

      Crc  crcCalulator_Fast ( Crc::FAST  );

      printf("Index   = %#lx\n",image.getIndex());
      printf("FlashSize   = %ld\n",image.getSize());
      printf("NumOfBlocks = %d\n",numOfBlocks);

      out.data.index   = image.getIndex();
      out.data.numOfBlocks = numOfBlocks;
      out.data.option  = option;

     // WORD error = 0;

      info.size = image.getSize();
      info.status = Info::CONNECTING;


      for( unsigned i=0;i<numOfBlocks;i++)
      {
        info.percent = ((i+1)*100)/numOfBlocks;

        out.data.blockId    = i;

        printf("send %d   \r", i);
        for( unsigned j = 0; j<32; j++ )
        {
          out.data.payload[j] = image.read(32L*i+j);
          crcCalulator_Fast(out.data.payload[j]);
        }

        //out.write();

        WORD cnt = 1000;
        do
        {
            // try again
            if( (cnt % 200) == 0 ) // == 200 )
            {
              out.write();
            }
          Sleep(1);
          ipc.update();
        } while( --cnt && !in.isNew() );

        if( cnt == 0 )
        {
          printf("\n\nTIMEOUT\n\n");
          info.status = Info::ERR_TIMEOUT;
          return( false );
        }

        info.status = Info::RUNNING;

        if(  in.data.error )
        {
          printf("\nERROR = %#x\n", in.data.error );
          info.status = Info::ERR_DATA;
          return( false );
        }
      }

      if(numOfBlocks)
      {
        printf("\nCRC (local) = %#04x",     crcCalulator_Fast.get() );
        printf("\nCRC (flash) = %#04x\n\n", in.data.crc             );

        if( crcCalulator_Fast.get() != in.data.crc )
        {
          printf("CRC error\n");
          info.status = Info::ERR_CRC;
          return( false );
        }
        //out.data.state = 1;

        info.status = Info::READY;
        return( true );
      }
      else // clear only
      {

        out.data.numOfBlocks = 0;
        out.data.blockId    = 0;
        out.data.option  = option;
        out.write();

        //printf("OPTION:%d\n",out.data.option);
        WORD cnt = 200;
        do
        {
          Sleep(10);
          ipc.update();
        } while( --cnt && !in.isNew() );

        if( cnt == 0 )
        {
          printf("\n\nTIMEOUT\n\n");
          info.status = Info::ERR_TIMEOUT;
          return( false );
        }
        return( true );
      }
    }
};

//*******************************************************************
// \todo Why this?
int Flash( FlashTool &flashTool, char *file, int id);
#endif
