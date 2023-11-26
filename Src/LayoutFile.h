//*******************************************************************
/*!
\file   LayoutFile.h
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   25.11.2023

License: See file "LICENSE"
*/

//**************************************************************************************
#ifndef _LAYOUT_FILE_H
#define _LAYOUT_FILE_H

#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>

//**************************************************************************************
class LayoutFile
{
  public:
    FILE *fp;

    //---------------------------------------------------------------
    LayoutFile( const char *fileName )
    {
      fp = fopen( fileName, "r" );
      err = (fp == NULL )?true:false;
    }

    //---------------------------------------------------------------
    ~LayoutFile()
    {
      fclose(fp);
    }

    //---------------------------------------------------------------
    char *getLabel( const char *name )
    {
      static char ret[32];
      char l[32];
      char n[32];

      strncpy( ret, " ", 30 );
      fseek( fp, 0, SEEK_SET );

      while( !err )
      {
        strncpy( l, "", 30 );
        int e = fscanf( fp, "%30s : \"%30[^\"]\"\n", n, l);
        if( e >= 1 )
        {
          if( strcmp( name, n ) == 0)
          {
            strncpy( ret, l, 30 );
            break;
         }
       }
       else if( e < 0 )
       {
         break;
       }
     }
     return( ret );
   }

  public:
    //---------------------------------------------------------------
    int err;
};

#endif //
