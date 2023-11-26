//*******************************************************************
/*!
\file   App.cpp
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   25.11.2023

License: See file "LICENSE"
*/

//*******************************************************************
#include "App.h"
#include <wx/msgdlg.h>

//*******************************************************************
//(*AppHeaders
#include "Main.h"
#include <wx/image.h>
//*)
//*******************************************************************

//*******************************************************************
IMPLEMENT_APP(App);

//*******************************************************************
bool App::OnInit()
{
    m_checker = new wxSingleInstanceChecker;
    if ( m_checker->IsAnotherRunning() )
    {
      Command cmd("localhost:2000");
      cmd.sendCmd(fileNameProg, fileNameKeys);

      /// wxLogError(_("Another program instance is already running, aborting."));
      delete m_checker; // OnExit() won't be called if we return false
      m_checker = NULL;
      return false;
    }
    
    //***************************************************************
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
      Frame* frame = new Frame(*this,0);
      frame->Show();
      SetTopWindow(frame);
    }
    //*)
    //***************************************************************

    return wxsOK;
}

//*******************************************************************
int App::OnExit()
{
    delete m_checker;
    return 0;
}

//EOF
