//*******************************************************************
/*!
\file   Main.cpp
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   25.11.2023

License: See file "LICENSE"
*/

//*******************************************************************
#include <wx/msgdlg.h>
#include "wx/cshelp.h"
#include <wx/snglinst.h>

//*******************************************************************
#include "lib.h"
#include "Main.h"
#include "ComPort.h"
#include "Flash.h"
#include "Daten.h"

#include "LayoutFile.h"

//*******************************************************************
System           sys;
Daten            daten;
Uart_Serial      bluetooth(Uart_Serial::BR_307200);
USBhost_Mcu      usb;
cIPC_Repository  ipc( bluetooth, usb );

//*******************************************************************
#include "ReportHandler.h"
#include "App.h"
#include "Windows.h"

//*******************************************************************
//(*InternalHeaders(Frame)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/settings.h>
#include <wx/string.h>
//*)

//*******************************************************************
//helper functions
enum wxbuildinfoformat
{
  short_f,
  long_f
};

//*******************************************************************
wxString wxbuildinfo( wxbuildinfoformat format )
{
  wxString wxbuild( wxVERSION_STRING );

  if (format == long_f )
  {
    #if defined(__WXMSW__)
            wxbuild << _T("-Windows");
    #elif defined(__UNIX__)
            wxbuild << _T("-Linux");
    #endif

    #if wxUSE_UNICODE
            wxbuild << _T("-Unicode build");
    #else
            wxbuild << _T("-ANSI build");
    #endif // wxUSE_UNICODE
  }
  return wxbuild;
}

//*******************************************************************
//(*IdInit(Frame)
const long Frame::ID_STATICBOX10 = wxNewId();
const long Frame::ID_BUTTON14 = wxNewId();
const long Frame::ID_BUTTON7 = wxNewId();
const long Frame::ID_BUTTON3 = wxNewId();
const long Frame::ID_STATICTEXT7 = wxNewId();
const long Frame::ID_STATICTEXT24 = wxNewId();
const long Frame::ID_STATICTEXT28 = wxNewId();
const long Frame::ID_STATICTEXT32 = wxNewId();
const long Frame::ID_BUTTON4 = wxNewId();
const long Frame::ID_BUTTON5 = wxNewId();
const long Frame::ID_CHOICE1 = wxNewId();
const long Frame::ID_BUTTON9 = wxNewId();
const long Frame::ID_STATICTEXT_INFO = wxNewId();
const long Frame::ID_BUTTON8 = wxNewId();
const long Frame::ID_BUTTON11 = wxNewId();
const long Frame::ID_BUTTON12 = wxNewId();
const long Frame::ID_BUTTON13 = wxNewId();
const long Frame::ID_BUTTON15 = wxNewId();
const long Frame::ID_BUTTON16 = wxNewId();
const long Frame::ID_BUTTON17 = wxNewId();
const long Frame::ID_BUTTON18 = wxNewId();
const long Frame::ID_BUTTON19 = wxNewId();
const long Frame::ID_BUTTON20 = wxNewId();
const long Frame::ID_BUTTON21 = wxNewId();
const long Frame::ID_BUTTON22 = wxNewId();
const long Frame::ID_BUTTON_PLUS = wxNewId();
const long Frame::ID_BUTTON_MINUS = wxNewId();
const long Frame::ID_BUTTON6 = wxNewId();
const long Frame::ID_BUTTON2 = wxNewId();
const long Frame::ID_BUTTON_ESC = wxNewId();
const long Frame::ID_BUTTON_OK = wxNewId();
const long Frame::ID_BUTTON23 = wxNewId();
const long Frame::ID_STATICTEXT_VCC = wxNewId();
const long Frame::ID_STATICLINE1 = wxNewId();
const long Frame::ID_STATICLINE2 = wxNewId();
const long Frame::ID_MENUITEM2 = wxNewId();
const long Frame::ID_MENU_SETTINGS = wxNewId();
const long Frame::ID_STATUSBAR = wxNewId();
const long Frame::ID_TIMER2 = wxNewId();
//*)

//*******************************************************************
BEGIN_EVENT_TABLE(Frame,wxFrame)
    //(*EventTable(Frame)
    //*)
END_EVENT_TABLE()

//*******************************************************************
//
// Frame
//
//*******************************************************************
//*******************************************************************
Frame::Frame( App &appIn, wxWindow* parent, wxWindowID id )

: app(appIn),
  orbMonitor( ipc, daten ),
  udp( 2000 /*port*/),
  commandHandler(udp)
{
    isInit = false;

    //---------------------------------------------------------------
    //(*Initialize(Frame)
    Create(parent, wxID_ANY, _("ORB-Monitor"), wxDefaultPosition, wxDefaultSize, wxCAPTION|wxDEFAULT_FRAME_STYLE|wxSYSTEM_MENU|wxCLOSE_BOX|wxFRAME_SHAPED, _T("wxID_ANY"));
    SetClientSize(wxSize(530,368));
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
    wxFont thisFont(8,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    SetFont(thisFont);
    SetExtraStyle( GetExtraStyle() | wxFRAME_EX_METAL );
    StaticBox10 = new wxStaticBox(this, ID_STATICBOX10, wxEmptyString, wxPoint(16,48), wxSize(320,136), wxALWAYS_SHOW_SB, _T("ID_STATICBOX10"));
    Button_B4 = new wxButton(this, ID_BUTTON14, _("B4"), wxPoint(344,88), wxSize(56,32), 0, wxDefaultValidator, _T("ID_BUTTON14"));
    Button_B4->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    Button4 = new wxButton(this, ID_BUTTON7, _("A7"), wxPoint(176,224), wxSize(80,32), 0, wxDefaultValidator, _T("ID_BUTTON7"));
    Button4->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    Button_DownloadProg = new wxButton(this, ID_BUTTON3, _("Download Program"), wxPoint(16,280), wxSize(136,32), 0, wxDefaultValidator, _T("ID_BUTTON3"));
    Button_DownloadProg->SetBackgroundColour(wxColour(0,255,255));
    wxFont Button_DownloadProgFont(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    Button_DownloadProg->SetFont(Button_DownloadProgFont);
    debugText0 = new wxStaticText(this, ID_STATICTEXT7, _("123456789012345678901234567890"), wxPoint(24,72), wxSize(192,13), 0, _T("ID_STATICTEXT7"));
    debugText0->SetMinSize(wxSize(192,13));
    wxFont debugText0Font(10,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
    debugText0->SetFont(debugText0Font);
    debugText1 = new wxStaticText(this, ID_STATICTEXT24, _("2"), wxPoint(24,96), wxSize(192,13), 0, _T("ID_STATICTEXT24"));
    wxFont debugText1Font(10,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
    debugText1->SetFont(debugText1Font);
    debugText2 = new wxStaticText(this, ID_STATICTEXT28, _("3"), wxPoint(24,120), wxSize(192,13), 0, _T("ID_STATICTEXT28"));
    wxFont debugText2Font(10,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
    debugText2->SetFont(debugText2Font);
    debugText3 = new wxStaticText(this, ID_STATICTEXT32, _("4"), wxPoint(24,144), wxSize(192,13), 0, _T("ID_STATICTEXT32"));
    wxFont debugText3Font(10,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
    debugText3->SetFont(debugText3Font);
    Button_Start_0 = new wxButton(this, ID_BUTTON4, _("S0"), wxPoint(184,280), wxSize(96,32), 0, wxDefaultValidator, _T("ID_BUTTON4"));
    Button_Start_0->SetBackgroundColour(wxColour(0,255,0));
    Button_Stop = new wxButton(this, ID_BUTTON5, _("Stop"), wxPoint(392,280), wxSize(120,32), 0, wxDefaultValidator, _T("ID_BUTTON5"));
    Button_Stop->SetBackgroundColour(wxColour(255,0,0));
    ChoicePort = new wxChoice(this, ID_CHOICE1, wxPoint(16,8), wxSize(176,28), 0, 0, wxCB_SORT|wxBORDER_DOUBLE|wxTRANSPARENT_WINDOW, wxDefaultValidator, _T("ID_CHOICE1"));
    wxFont ChoicePortFont(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
    ChoicePort->SetFont(ChoicePortFont);
    Button_Start_1 = new wxButton(this, ID_BUTTON9, _("S1"), wxPoint(288,280), wxSize(96,32), 0, wxDefaultValidator, _T("ID_BUTTON9"));
    Button_Start_1->SetBackgroundColour(wxColour(255,255,0));
    StaticText_Info = new wxStaticText(this, ID_STATICTEXT_INFO, _("---"), wxPoint(224,8), wxSize(152,32), wxST_NO_AUTORESIZE, _T("ID_STATICTEXT_INFO"));
    wxFont StaticText_InfoFont(11,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    StaticText_Info->SetFont(StaticText_InfoFont);
    Button5 = new wxButton(this, ID_BUTTON8, _("A8"), wxPoint(256,224), wxSize(80,32), 0, wxDefaultValidator, _T("ID_BUTTON8"));
    Button5->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    Button_B1 = new wxButton(this, ID_BUTTON11, _("B1"), wxPoint(344,56), wxSize(56,32), 0, wxDefaultValidator, _T("ID_BUTTON11"));
    Button_B1->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    Button_B2 = new wxButton(this, ID_BUTTON12, _("B2"), wxPoint(400,56), wxSize(56,32), 0, wxDefaultValidator, _T("ID_BUTTON12"));
    Button_B2->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    Button_B3 = new wxButton(this, ID_BUTTON13, _("B3"), wxPoint(456,56), wxSize(56,32), 0, wxDefaultValidator, _T("ID_BUTTON13"));
    Button_B3->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    Button_B5 = new wxButton(this, ID_BUTTON15, _("B5"), wxPoint(400,88), wxSize(56,32), 0, wxDefaultValidator, _T("ID_BUTTON15"));
    Button_B5->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    Button_B6 = new wxButton(this, ID_BUTTON16, _("B6"), wxPoint(456,88), wxSize(56,32), 0, wxDefaultValidator, _T("ID_BUTTON16"));
    Button_B6->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    Button_B7 = new wxButton(this, ID_BUTTON17, _("B7"), wxPoint(344,120), wxSize(56,32), 0, wxDefaultValidator, _T("ID_BUTTON17"));
    Button_B7->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    Button_B8 = new wxButton(this, ID_BUTTON18, _("B8"), wxPoint(400,120), wxSize(56,32), 0, wxDefaultValidator, _T("ID_BUTTON18"));
    Button_B8->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    Button_B9 = new wxButton(this, ID_BUTTON19, _("B9"), wxPoint(456,120), wxSize(56,32), 0, wxDefaultValidator, _T("ID_BUTTON19"));
    Button_B9->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    Button_B10 = new wxButton(this, ID_BUTTON20, _("B10"), wxPoint(344,152), wxSize(56,32), 0, wxDefaultValidator, _T("ID_BUTTON20"));
    Button_B10->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    Button_B11 = new wxButton(this, ID_BUTTON21, _("B11"), wxPoint(400,152), wxSize(56,32), 0, wxDefaultValidator, _T("ID_BUTTON21"));
    Button_B11->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    Button_B12 = new wxButton(this, ID_BUTTON22, _("B12"), wxPoint(456,152), wxSize(56,32), 0, wxDefaultValidator, _T("ID_BUTTON22"));
    Button_B12->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    Button_Plus = new wxButton(this, ID_BUTTON_PLUS, _("A2"), wxPoint(96,192), wxSize(80,32), 0, wxDefaultValidator, _T("ID_BUTTON_PLUS"));
    Button_Plus->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    Button_Minus = new wxButton(this, ID_BUTTON_MINUS, _("A3"), wxPoint(176,192), wxSize(80,32), 0, wxDefaultValidator, _T("ID_BUTTON_MINUS"));
    Button_Minus->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    Button3 = new wxButton(this, ID_BUTTON6, _("A6"), wxPoint(96,224), wxSize(80,32), 0, wxDefaultValidator, _T("ID_BUTTON6"));
    Button3->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    Button2 = new wxButton(this, ID_BUTTON2, _("A5"), wxPoint(16,224), wxSize(80,32), 0, wxDefaultValidator, _T("ID_BUTTON2"));
    Button2->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    Button_ESC = new wxButton(this, ID_BUTTON_ESC, _("A1"), wxPoint(16,192), wxSize(80,32), 0, wxDefaultValidator, _T("ID_BUTTON_ESC"));
    Button_ESC->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    Button_OK = new wxButton(this, ID_BUTTON_OK, _("A4"), wxPoint(256,192), wxSize(80,32), 0, wxDefaultValidator, _T("ID_BUTTON_OK"));
    Button_OK->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    Button_C1 = new wxButton(this, ID_BUTTON23, _("C1"), wxPoint(384,200), wxSize(88,40), 0, wxDefaultValidator, _T("ID_BUTTON23"));
    Button_C1->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    StaticText_Vcc = new wxStaticText(this, ID_STATICTEXT_VCC, _("Vcc"), wxPoint(416,8), wxSize(96,24), wxST_NO_AUTORESIZE|wxALIGN_RIGHT, _T("ID_STATICTEXT_VCC"));
    wxFont StaticText_VccFont(11,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    StaticText_Vcc->SetFont(StaticText_VccFont);
    StaticLine1 = new wxStaticLine(this, ID_STATICLINE1, wxPoint(16,272), wxSize(488,0), wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
    StaticLine2 = new wxStaticLine(this, ID_STATICLINE2, wxPoint(16,264), wxSize(496,1), wxLI_HORIZONTAL, _T("ID_STATICLINE2"));
    MenuBar1 = new wxMenuBar();
    Menu3 = new wxMenu();
    Menu2 = new wxMenuItem(Menu3, ID_MENUITEM2, _("Quit"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(Menu2);
    Menu1 = new wxMenuItem(Menu3, ID_MENU_SETTINGS, _("Settings"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(Menu1);
    MenuBar1->Append(Menu3, _("File"));
    SetMenuBar(MenuBar1);
    StatusBar = new wxStatusBar(this, ID_STATUSBAR, 0, _T("ID_STATUSBAR"));
    int __wxStatusBarWidths_1[3] = { -12, -12, -5 };
    int __wxStatusBarStyles_1[3] = { wxSB_NORMAL, wxSB_NORMAL, wxSB_NORMAL };
    StatusBar->SetFieldsCount(3,__wxStatusBarWidths_1);
    StatusBar->SetStatusStyles(3,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar);
    TimerSlow.SetOwner(this, ID_TIMER2);
    TimerSlow.Start(10, false);
    SingleInstanceChecker1.Create(_T("ORB-Monitor_") + wxGetUserId() + _T("_Guard"));

    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Frame::OnButtonClick_DownloadProgram);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Frame::OnButton_StartRobo_Click);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Frame::OnButton_StopRobo_Click);
    Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&Frame::OnChoicePortSelect);
    Connect(ID_BUTTON9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Frame::OnButton_StartKalib_Click);
    Connect(ID_MENUITEM2,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&Frame::OnMenuQuit);
    Connect(ID_MENU_SETTINGS,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&Frame::OnMenu_Settings);
    Connect(ID_TIMER2,wxEVT_TIMER,(wxObjectEventFunction)&Frame::OnTimerSlowTrigger);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&Frame::OnClose);
    //*)
    //---------------------------------------------------------------


    SetTitle(wxString("ORB-Monitor   ")+(char*)app.title);
    SetIcon(wxICON(aaaa));

    btn[0] = new ButtonExt(Button_ESC,  &Frame::OnMouseEvent, this);
    btn[1] = new ButtonExt(Button_Plus, &Frame::OnMouseEvent, this);
    btn[2] = new ButtonExt(Button_Minus,&Frame::OnMouseEvent, this);
    btn[3] = new ButtonExt(Button_OK,   &Frame::OnMouseEvent, this);

    btn[4] = new ButtonExt(Button2,&Frame::OnMouseEvent, this);
    btn[5] = new ButtonExt(Button3,&Frame::OnMouseEvent, this);
    btn[6] = new ButtonExt(Button4,&Frame::OnMouseEvent, this);
    btn[7] = new ButtonExt(Button5,&Frame::OnMouseEvent, this);

    btn[ 8] = new ButtonExt(Button_B1, &Frame::OnMouseEvent, this);
    btn[ 9] = new ButtonExt(Button_B2, &Frame::OnMouseEvent, this);
    btn[10] = new ButtonExt(Button_B3, &Frame::OnMouseEvent, this);
    btn[11] = new ButtonExt(Button_B4, &Frame::OnMouseEvent, this);
    btn[12] = new ButtonExt(Button_B5, &Frame::OnMouseEvent, this);
    btn[13] = new ButtonExt(Button_B6, &Frame::OnMouseEvent, this);
    btn[14] = new ButtonExt(Button_B7, &Frame::OnMouseEvent, this);
    btn[15] = new ButtonExt(Button_B8, &Frame::OnMouseEvent, this);
    btn[16] = new ButtonExt(Button_B9, &Frame::OnMouseEvent, this);
    btn[17] = new ButtonExt(Button_B10,&Frame::OnMouseEvent, this);
    btn[18] = new ButtonExt(Button_B11,&Frame::OnMouseEvent, this);
    btn[19] = new ButtonExt(Button_B12,&Frame::OnMouseEvent, this);

    btn[20] = new ButtonExt(Button_C1,&Frame::OnMouseEvent, this);
    btn[21] = new ButtonExt(Button_Start_0,&Frame::OnMouseEvent, this);
    btn[22] = new ButtonExt(Button_Start_1,&Frame::OnMouseEvent, this);

    setKeyLayout((char*)app.fileNameKeys);

    comPort  = new ComPort(ChoicePort, app.portName);
    orbMonitor.selectPort( comPort->getPort() );

    dlgFlash = new FlashDialog(app.fileNameProg, /*app.fileNameData,*/ ipc, this);

    dlgSettings = new SettingsDialog( daten, this);

    wxHelpProvider::Set( new wxSimpleHelpProvider );

  isInit = true;

} //constructor

//*******************************************************************
Frame::~Frame()
{
  orbMonitor.close();
}

//*******************************************************************
void Frame::CloseFrame()
{
  orbMonitor.close();
}

//*******************************************************************
void Frame::OnAbout( wxCommandEvent& event )
{
  wxString msg = wxbuildinfo(long_f);
  wxMessageBox(msg, _("Welcome to..."));
  wxContextHelp contextHelp(this);
}

//*******************************************************************
void Frame::OnTimerSlowTrigger(wxTimerEvent& event)
{
  if( !isInit )
     return;

  udp.run();
  if( commandHandler.isEvent() )
  {
      // set monitor keys
      setKeyLayout((char*)commandHandler.data.keys);

      orbMonitor.setDownloadRequest(0);
      strncpy(dlgFlash->fileNameProg,commandHandler.data.prog,512);
  }
  //======================
  if( dlgFlash != NULL )
  {
    orbMonitor.update( dlgFlash->isDownload /*|| orbMonitor.downloadProgReq*/);
    dlgFlash->run( orbMonitor.getDownloadRequest() );
      if( dlgFlash->isDownload )
        return;
  }


  //======================
  // Anzeige aktualisieren
  //======================
  //----------------------
  // Monitor-Display
  //----------------------
  if( daten.monitorFromORB.isTimeout() )
  {
    debugText0->SetLabel( "" );
    debugText1->SetLabel( "" );
    debugText2->SetLabel( "" );
    debugText3->SetLabel( "" );
  }
  else if( daten.monitorFromORB.isNew() )
  {
    debugText0->SetLabel( daten.getMonitorText(0) );
    debugText1->SetLabel( daten.getMonitorText(1) );
    debugText2->SetLabel( daten.getMonitorText(2) );
    debugText3->SetLabel( daten.getMonitorText(3) );
  }

  //----------------------
  // Name
  //----------------------
  if( daten.mess.isTimeout() ) // vorläufig !
  {
    StaticText_Info->SetForegroundColour(0x0000FF);
    StaticText_Info->SetLabel( "not connected" );
  //  dlgSettings->refresh();
  }
  else if( daten.settingsFromORB.isNew() )
  {
    StaticText_Info->SetForegroundColour(0x008F00);
    StaticText_Info->SetLabel( daten.getLabelByString() );
    dlgSettings->refresh();
  }

  //----------------------
  // Mess-Daten
  //----------------------
  if( daten.mess.isTimeout() )
  {
    StaticText_Vcc->SetLabel( "---" );
  }
  else if( daten.mess.isNew() )
  {
    StaticText_Vcc->SetLabel( daten.getVccByString() );
  }

  //----------------------
  // Status
  //----------------------
  StatusBar->SetStatusText( orbMonitor.getConnectionStr(), 0 );
  StatusBar->SetStatusText( orbMonitor.getControlStr()   , 1 );
  StatusBar->SetStatusText( orbMonitor.getKeyCode()      , 2 );

  //======================
  //
  //======================
  if( dlgFlash != NULL )
  {
    orbMonitor.update( dlgFlash->isDownload /*|| orbMonitor.downloadProgReq*/);
    dlgFlash->run( orbMonitor.getDownloadRequest() );
  }
} // end of Frame::OnTimer1Trigger()

//*******************************************************************
void Frame::OnButtonClick_DownloadProgram(wxCommandEvent& event)
{
  orbMonitor.setDownloadRequest(0);
}

//*******************************************************************
void Frame::OnButton_StartRobo_Click(wxCommandEvent& event)
{
  orbMonitor.startLocalControl(0);
}

//*******************************************************************
void Frame::OnButton_StartKalib_Click(wxCommandEvent& event)
{
  orbMonitor.startLocalControl(1);
}

//*******************************************************************
void Frame::OnButton_StopRobo_Click(wxCommandEvent& event)
{
  orbMonitor.stopLocalControl();
}

//*******************************************************************
void Frame::OnMenuQuit(wxCommandEvent& event)
{
  isInit = false;
  CloseFrame();
  this->Destroy();
}

//*******************************************************************
void Frame::OnClose(wxCloseEvent& event)
{
  isInit = false;
  CloseFrame();
  this->Destroy();
}

//*******************************************************************
void Frame::OnChoicePortSelect(wxCommandEvent& event)
{
  orbMonitor.selectPort( comPort->getPort() );
}

//*******************************************************************
void Frame::OnMouseEvent(wxMouseEvent& event)
{
  BYTE key = 0;

  if( event.LeftDown() )
  {
    for(int i=0;i<21;i++)
    {
      if( event.GetId() == btn[i]->btn->GetId() )
      {
        key = i+1;
      }
    }
  }

  orbMonitor.setKeyCode( key );
  event.Skip();
}

//*******************************************************************
void Frame::OnMenu_Settings(wxCommandEvent& event)
{
  dlgSettings->run();
}

//*******************************************************************
void Frame::setKeyLayout( char *file )
{
    LayoutFile layout( file );
    for(int i=0;i<23;i++)
    {
      btn[i]->setLabel(  layout.getLabel( btn[i]->getName() ) );
    }
}

//EOF
