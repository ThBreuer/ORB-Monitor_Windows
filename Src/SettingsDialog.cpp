//*******************************************************************
/*!
\file   SettingsDialog.cpp
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   25.11.2023

License: See file "LICENSE"
*/

//*******************************************************************
#include "SettingsDialog.h"

//(*InternalHeaders(SettingsDialog)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//*******************************************************************
//(*IdInit(SettingsDialog)
const long SettingsDialog::ID_BUTTON_CLOSE = wxNewId();
const long SettingsDialog::ID_BUTTON_SEND = wxNewId();
const long SettingsDialog::ID_TEXTCTRL1 = wxNewId();
const long SettingsDialog::ID_STATICTEXT1 = wxNewId();
const long SettingsDialog::ID_STATICTEXT2 = wxNewId();
const long SettingsDialog::ID_STATICTEXT3 = wxNewId();
const long SettingsDialog::ID_STATICTEXT4 = wxNewId();
const long SettingsDialog::ID_STATICTEXT6 = wxNewId();
const long SettingsDialog::ID_STATICTEXT7 = wxNewId();
const long SettingsDialog::ID_STATICTEXT5 = wxNewId();
const long SettingsDialog::ID_STATICTEXT8 = wxNewId();
const long SettingsDialog::ID_CHECKBOX1 = wxNewId();
const long SettingsDialog::ID_SPINCTRL_VCC_OK = wxNewId();
const long SettingsDialog::ID_SPINCTRL_VCC_LOW = wxNewId();
const long SettingsDialog::ID_STATICTEXT9 = wxNewId();
const long SettingsDialog::ID_STATICTEXT10 = wxNewId();
const long SettingsDialog::ID_STATICTEXT11 = wxNewId();
//*)

//*******************************************************************
BEGIN_EVENT_TABLE(SettingsDialog,wxDialog)
  //(*EventTable(SettingsDialog)
  //*)
END_EVENT_TABLE()

//-------------------------------------------------------------------
SettingsDialog::SettingsDialog( Daten &daten,
                                wxWindow   *parent,
                                wxWindowID  id )

: daten( daten )
{
  //(*Initialize(SettingsDialog)
  Create(parent, wxID_ANY, _("Settings"), wxDefaultPosition, wxDefaultSize, wxSTAY_ON_TOP|wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
  SetClientSize(wxSize(402,388));
  Button_Close = new wxButton(this, ID_BUTTON_CLOSE, _("close"), wxPoint(160,344), wxSize(80,24), 0, wxDefaultValidator, _T("ID_BUTTON_CLOSE"));
  Button_Send = new wxButton(this, ID_BUTTON_SEND, _("send"), wxPoint(32,344), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_SEND"));
  TextCtrl_Name = new wxTextCtrl(this, ID_TEXTCTRL1, _("12345678901234567890"), wxPoint(128,32), wxSize(208,21), wxTE_PROCESS_ENTER|wxTE_PROCESS_TAB, wxDefaultValidator, _T("ID_TEXTCTRL1"));
  TextCtrl_Name->SetMaxLength(20);
  TextCtrl_Name->SetFocus();
  wxFont TextCtrl_NameFont(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
  TextCtrl_Name->SetFont(TextCtrl_NameFont);
  StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Name"), wxPoint(32,32), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
  StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Firmware"), wxPoint(32,168), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
  StaticText_Version = new wxStaticText(this, ID_STATICTEXT3, _("---"), wxPoint(128,192), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
  wxFont StaticText_VersionFont(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
  StaticText_Version->SetFont(StaticText_VersionFont);
  StaticText_Board = new wxStaticText(this, ID_STATICTEXT4, _("---"), wxPoint(128,216), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
  wxFont StaticText_BoardFont(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
  StaticText_Board->SetFont(StaticText_BoardFont);
  StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("Batterie OK über"), wxPoint(32,80), wxDefaultSize, 0, _T("ID_STATICTEXT6"));
  StaticText7 = new wxStaticText(this, ID_STATICTEXT7, _("Batterie leer unter"), wxPoint(32,120), wxDefaultSize, 0, _T("ID_STATICTEXT7"));
  StaticText3 = new wxStaticText(this, ID_STATICTEXT5, _("Version"), wxPoint(56,192), wxDefaultSize, 0, _T("ID_STATICTEXT5"));
  StaticText4 = new wxStaticText(this, ID_STATICTEXT8, _("Board"), wxPoint(56,216), wxDefaultSize, 0, _T("ID_STATICTEXT8"));
  CheckBox_ClearMemory = new wxCheckBox(this, ID_CHECKBOX1, _("Speicher löschen"), wxPoint(240,80), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
  CheckBox_ClearMemory->SetValue(false);
  SpinCtrl_VccOK = new wxSpinCtrlDouble(this, ID_SPINCTRL_VCC_OK, _T("7.5"), wxPoint(136,80), wxSize(72,23), 0, 6, 8, 6, 0.1, _T("ID_SPINCTRL_VCC_OK"));
  SpinCtrl_VccOK->SetValue(_T("7.5"));
  SpinCtrl_VccLow = new wxSpinCtrlDouble(this, ID_SPINCTRL_VCC_LOW, _T("7.2"), wxPoint(136,120), wxSize(72,23), 0, 6, 8, 7.2, 0.1, _T("ID_SPINCTRL_VCC_LOW"));
  SpinCtrl_VccLow->SetValue(_T("7.2"));
  StaticText5 = new wxStaticText(this, ID_STATICTEXT9, _("ORB-Monitor:"), wxPoint(32,256), wxDefaultSize, 0, _T("ID_STATICTEXT9"));
  StaticText8 = new wxStaticText(this, ID_STATICTEXT10, _("Version"), wxPoint(56,280), wxDefaultSize, 0, _T("ID_STATICTEXT10"));
  StaticText_ORB_Version = new wxStaticText(this, ID_STATICTEXT11, _("---"), wxPoint(128,280), wxDefaultSize, 0, _T("ID_STATICTEXT11"));
  wxFont StaticText_ORB_VersionFont(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Arial"),wxFONTENCODING_DEFAULT);
  StaticText_ORB_Version->SetFont(StaticText_ORB_VersionFont);

  Connect(ID_BUTTON_CLOSE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SettingsDialog::OnButton_Close);
  Connect(ID_BUTTON_SEND,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SettingsDialog::OnButton_Send);
  Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&SettingsDialog::OnTextCtrl_Enter);
  Connect(ID_SPINCTRL_VCC_OK,wxEVT_SPINCTRLDOUBLE,(wxObjectEventFunction)&SettingsDialog::OnSpinCtrlChange_VccOK);
  Connect(ID_SPINCTRL_VCC_LOW,wxEVT_SPINCTRLDOUBLE,(wxObjectEventFunction)&SettingsDialog::OnSpinCtrlChange_VccLow);
  Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&SettingsDialog::OnClose);
  //*)
}

//-------------------------------------------------------------------
SettingsDialog::~SettingsDialog()
{
  //(*Destroy(SettingsDialog)
  //*)
}

//-------------------------------------------------------------------
void SettingsDialog::refresh( void )
{
  char txt[20];
  Daten::SettingsFromORB::Data &in = daten.settingsFromORB.d.data;

  TextCtrl_Name->SetLabelText(in.name);

  sprintf(txt,"%.1f", 0.1*in.VCC_ok);
  SpinCtrl_VccOK->SetValue(txt);

  sprintf(txt,"%.1f", 0.1*in.VCC_low);
  SpinCtrl_VccLow->SetValue(txt);

  sprintf(txt,"%02u.%02u",in.version[0],in.version[1]);
  StaticText_Version->SetLabelText(txt);

  sprintf(txt,"%02u.%02u",in.board[0],in.board[1]);
  StaticText_Board  ->SetLabelText(txt);

  sprintf(txt,"%02u.%02u",VERSION_MAIN,VERSION_SUB);
  StaticText_ORB_Version->SetLabelText(txt);

  strncpy( loc.name, in.name, 20);
  loc.VCC_ok  = in.VCC_ok;
  loc.VCC_low = in.VCC_low;
}

//-------------------------------------------------------------------
void SettingsDialog::run( void )
{
  refresh();
  CheckBox_ClearMemory->SetValue(false);
  ShowModal();
}

//-------------------------------------------------------------------
void SettingsDialog::OnClose(wxCloseEvent& event)
{
  EndDialog(0);
}

//-------------------------------------------------------------------
void SettingsDialog::OnButton_Close(wxCommandEvent& event)
{
  Close();
}

//-------------------------------------------------------------------
void SettingsDialog::OnButton_Send(wxCommandEvent& event)
{
   loc.command = 0x01;
   if( CheckBox_ClearMemory->GetValue() )
   {
     loc.command |= 0x02;
   }
   strncpy(loc.name,TextCtrl_Name->GetLineText(0),20);

   daten.settingsToORB << loc;

   EndDialog(0);
}

//-------------------------------------------------------------------
void SettingsDialog::OnTextCtrl_Enter(wxCommandEvent& event)
{
}

//-------------------------------------------------------------------
void SettingsDialog::OnSpinCtrlChange_VccOK(wxSpinDoubleEvent& event)
{
  loc.VCC_ok = 10*SpinCtrl_VccOK->GetValue();
}

//-------------------------------------------------------------------
void SettingsDialog::OnSpinCtrlChange_VccLow(wxSpinDoubleEvent& event)
{
  loc.VCC_low = 10*SpinCtrl_VccLow->GetValue();
}
