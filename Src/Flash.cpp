//*******************************************************************
/*!
\file   Flash.cpp
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   25.11.2023

License: See file "LICENSE"
*/

//*******************************************************************
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "EmbSysLib.h"
#include "Module/ISC.h"

#include "Flash.h"

//*******************************************************************
int Flash( FlashTool &flashTool, char *file, int id )
{
  Image  *image = NULL;

  DownloadTool   download;

  if( 1 ) //strlen(fileNameBin) == 0 && strlen(fileNameHex) > 0 )
  {
    if( id == 0 )
    {
      if( !download.open( file ) )
      {
        printf("ERROR: Can not open HEX-File\n");
        flashTool.info.status = FlashTool::Info::ERR_FILE;
        return 1;
      }
      image = new Image( "", 0 );

      if( !download.readImage( *image ) )
      {
        printf("ERROR: can not read image\n");
        flashTool.info.status = FlashTool::Info::ERR_FILE;
        delete image;
        return 1;
      }

      download.close();
    }
    else
    {
      image = new Image( file, id );
    }

    if( image == NULL )
    {
      printf("ERROR: can not read image\n");
      flashTool.info.status = FlashTool::Info::ERR_FILE;
      return 1;
    }
  }

  WORD option = 0;

  // printf("OPTION:%d\n", option);

  if( !flashTool.sendImage( *image, option ) )
  {
    printf("ERROR: can not send image\n");
    delete image;
    return 1;
  }
  Sleep(1000);

  delete image;

  return EXIT_SUCCESS;
}

//EOF
