//*******************************************************************
/*!
\file   FlashDialog.cpp
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   25.11.2023

License: See file "LICENSE"
*/

//*******************************************************************
#include "FlashDialog.h"
#include "Flash.h"

//*******************************************************************
//(*InternalHeaders(FlashDialog)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/settings.h>
#include <wx/string.h>
//*)
//*******************************************************************

//*******************************************************************
//(*IdInit(FlashDialog)
const long FlashDialog::ID_STATICTEXT1 = wxNewId();
const long FlashDialog::ID_STATICTEXT2 = wxNewId();
const long FlashDialog::ID_STATICTEXT3 = wxNewId();
const long FlashDialog::ID_STATICTEXT4 = wxNewId();
const long FlashDialog::ID_TIMER1      = wxNewId();
//*)
//*******************************************************************

//*******************************************************************
BEGIN_EVENT_TABLE(FlashDialog,wxDialog)
  //(*EventTable(FlashDialog)
  //*)
END_EVENT_TABLE()
//*******************************************************************

//-------------------------------------------------------------------
FlashDialog::FlashDialog( char       *fileProg,
                          cISC       &ipcIn,
                          wxWindow   *parent,
                          wxWindowID  id )
: flashTool( ipcIn )
{
  //*****************************************************************
  //(*Initialize(FlashDialog)
  Create(parent, id, _("Flash"), wxDefaultPosition, wxDefaultSize, wxSTAY_ON_TOP|wxBORDER_DOUBLE|wxBORDER_RAISED, _T("id"));
  SetClientSize(wxSize(547,151));
  Move(wxDefaultPosition);
  SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_INACTIVECAPTION));
  StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Label"), wxPoint(32,64), wxSize(224,16), 0, _T("ID_STATICTEXT1"));
  wxFont StaticText1Font(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
  StaticText1->SetFont(StaticText1Font);
  StaticText_Status = new wxStaticText(this, ID_STATICTEXT2, _("Label"), wxPoint(32,104), wxSize(224,13), 0, _T("ID_STATICTEXT2"));
  wxFont StaticText_StatusFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
  StaticText_Status->SetFont(StaticText_StatusFont);
  StaticText_File = new wxStaticText(this, ID_STATICTEXT3, _("Label"), wxPoint(8,32), wxSize(528,13), 0, _T("ID_STATICTEXT3"));
  StaticText2 = new wxStaticText(this, ID_STATICTEXT4, _("Download to ORB:"), wxPoint(8,8), wxSize(256,16), 0, _T("ID_STATICTEXT4"));
  Timer1.SetOwner(this, ID_TIMER1);
  Timer1.Start(10, false);

  Connect(ID_TIMER1,wxEVT_TIMER,(wxObjectEventFunction)&FlashDialog::OnTimer1Trigger);
  Connect(wxID_ANY,wxEVT_INIT_DIALOG,(wxObjectEventFunction)&FlashDialog::OnInit);
  //*)
  //*****************************************************************

  isDownload = false;
  strcpy( fileNameProg, fileProg );
  isPythonScriptFlag = isPythonScript(fileNameProg);
  fileId = 0;
}

//-------------------------------------------------------------------
FlashDialog::~FlashDialog()
{
  //(*Destroy(FlashDialog)
  //*)
}

//-------------------------------------------------------------------
void FlashDialog::run( int id )
{
  if( id < 0 )
    return;

  fileId = id;

  /// PlaySoundW(TEXT("FlashRunning.wav"), NULL, SND_ASYNC|SND_LOOP|SND_FILENAME);
  ShowModal();
}

//-------------------------------------------------------------------
static DWORD __stdcall func( void *ptr )
{
  FlashDialog *flashDialog = (FlashDialog *)ptr;

  int result = 0;
  if( flashDialog->fileId == 0)
  {
    flashDialog->StaticText_File->SetLabel( flashDialog->fileNameProg );
    result = Flash( flashDialog->flashTool, flashDialog->fileNameProg, flashDialog->fileId );
  }
  else
  {
  }
  flashDialog->isDownload = false;
  if(result == EXIT_SUCCESS)
  {
///      PlaySoundW( TEXT("FlashOK.wav"), NULL, SND_FILENAME );
  }
  else
  {
///      PlaySoundW( TEXT("FlashError.wav"), NULL, SND_FILENAME );

    Sleep(2000);
  }
  return( 0 );
}

//-------------------------------------------------------------------
void FlashDialog::OnInit( wxInitDialogEvent& event )
{
  isDownload = true;
  flashTool.info.status = FlashTool::Info::NONE;

  Timer1.Start( 100, false );

  DWORD threadID=0;
  CreateThread( NULL,
                0,            //stack size
                func,         //MyThreadFunction,
                (void *)this, // argument to thread function
                0,            // creation flags
                &threadID );
}

//-------------------------------------------------------------------
void FlashDialog::OnTimer1Trigger( wxTimerEvent& event )
{
    char txt[60];
    sprintf(txt,"%d %% of %u Byte",flashTool.info.percent,flashTool.info.size );
    StaticText1->SetLabel(txt);

    switch(flashTool.info.status)
    {
        case FlashTool::Info::NONE:        StaticText_Status->SetLabel("");               break;
        case FlashTool::Info::CONNECTING:  StaticText_Status->SetLabel("connecting");     break;
        case FlashTool::Info::RUNNING:     StaticText_Status->SetLabel("running");        break;
        case FlashTool::Info::READY:       StaticText_Status->SetLabel("ready");          break;
        case FlashTool::Info::ERR_TIMEOUT: StaticText_Status->SetLabel("ERROR: timeout"); break;
        case FlashTool::Info::ERR_DATA:    StaticText_Status->SetLabel("ERROR: data");    break;
        case FlashTool::Info::ERR_CRC:     StaticText_Status->SetLabel("ERROR: CRC");     break;
        default:                           StaticText_Status->SetLabel("ERROR: unknown"); break;
    }

    if(flashTool.info.status >= FlashTool::Info::READY )
    {
        Timer1.Stop();
        Sleep(2000);
        EndDialog(2);
    }
}

//EOF
