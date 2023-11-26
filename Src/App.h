//*******************************************************************
/*!
\file   App.h
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   25.11.2023

License: See file "LICENSE"
*/

//*******************************************************************
#ifndef APP_H
#define APP_H

//*******************************************************************
#include <wx/app.h>
#include <wx/snglinst.h>

#include "Module/Option.h"
#include "Command.h"

//*******************************************************************
class App : public wxApp
{
  public:
    //---------------------------------------------------------------
    Option fileNameProg;
    Option portName;
    Option title;
    Option fileNameKeys;

     wxSingleInstanceChecker *m_checker;

    public:
    //---------------------------------------------------------------
    virtual bool Initialize(int& argc, wxChar **argv)
    {
      if( wxApp::Initialize(argc, argv) )
      {
          fileNameProg.scan(argc,argv,"prog","Bin\\main.hex");
          fileNameKeys.scan(argc,argv,"k","Src\\ORB-Monitor-Tasten.txt");
          portName    .scan(argc,argv,"port","no port");
          title       .scan(argc,argv,"t","");
          return(true);
      }
      return( false );
    }

    //---------------------------------------------------------------
    virtual bool OnInit();

    //---------------------------------------------------------------
    virtual int OnExit();
};

#endif // APP_H
