#include "ViewDialog.h"

//(*InternalHeaders(ViewDialog)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/settings.h>
#include <wx/string.h>
//*)

//(*IdInit(ViewDialog)
const long ViewDialog::ID_STATICBOX4 = wxNewId();
const long ViewDialog::ID_STATICBOX3 = wxNewId();
const long ViewDialog::ID_STATICBOX2 = wxNewId();
const long ViewDialog::ID_STATICBOX1 = wxNewId();
const long ViewDialog::ID_STATICTEXT1 = wxNewId();
const long ViewDialog::ID_STATICTEXT2 = wxNewId();
const long ViewDialog::ID_STATICTEXT3 = wxNewId();
const long ViewDialog::ID_STATICTEXT4 = wxNewId();
const long ViewDialog::ID_STATICTEXT5 = wxNewId();
const long ViewDialog::ID_STATICTEXT6 = wxNewId();
const long ViewDialog::ID_STATICTEXT7 = wxNewId();
const long ViewDialog::ID_STATICTEXT8 = wxNewId();
const long ViewDialog::ID_STATICTEXT9 = wxNewId();
const long ViewDialog::ID_STATICTEXT10 = wxNewId();
const long ViewDialog::ID_STATICTEXT11 = wxNewId();
const long ViewDialog::ID_STATICTEXT12 = wxNewId();
const long ViewDialog::ID_STATICTEXT13 = wxNewId();
const long ViewDialog::ID_STATICTEXT14 = wxNewId();
const long ViewDialog::ID_STATICTEXT15 = wxNewId();
const long ViewDialog::ID_STATICBOX5 = wxNewId();
const long ViewDialog::ID_STATICTEXT16 = wxNewId();
const long ViewDialog::ID_STATICTEXT17 = wxNewId();
const long ViewDialog::ID_STATICBOX6 = wxNewId();
const long ViewDialog::ID_CHECKBOX1 = wxNewId();
const long ViewDialog::ID_CHECKBOX2 = wxNewId();
const long ViewDialog::ID_STATICBOX7 = wxNewId();
const long ViewDialog::ID_STATICBOX8 = wxNewId();
const long ViewDialog::ID_STATICBOX9 = wxNewId();
const long ViewDialog::ID_STATICTEXT18 = wxNewId();
const long ViewDialog::ID_STATICTEXT19 = wxNewId();
const long ViewDialog::ID_STATICTEXT20 = wxNewId();
const long ViewDialog::ID_STATICTEXT21 = wxNewId();
const long ViewDialog::ID_STATICTEXT22 = wxNewId();
const long ViewDialog::ID_STATICTEXT23 = wxNewId();
const long ViewDialog::ID_STATICTEXT24 = wxNewId();
const long ViewDialog::ID_STATICTEXT25 = wxNewId();
const long ViewDialog::ID_TIMER1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(ViewDialog,wxDialog)
	//(*EventTable(ViewDialog)
	//*)
END_EVENT_TABLE()

//-------------------------------------------------------------------
ViewDialog::ViewDialog( Daten &daten,
                        wxWindow* parent,
                        wxWindowID id,
                        const wxPoint& pos,
                        const wxSize& size )
: daten( daten )
{
	//(*Initialize(ViewDialog)
	Create(parent, id, _("ORB-Monitor - View Raw Data"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxMINIMIZE_BOX, _T("id"));
	SetClientSize(wxSize(552,304));
	Move(wxDefaultPosition);
	SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
	StaticBox4 = new wxStaticBox(this, ID_STATICBOX4, _("M4"), wxPoint(424,8), wxSize(120,104), 0, _T("ID_STATICBOX4"));
	StaticBox3 = new wxStaticBox(this, ID_STATICBOX3, _("M3"), wxPoint(304,8), wxSize(120,104), 0, _T("ID_STATICBOX3"));
	StaticBox2 = new wxStaticBox(this, ID_STATICBOX2, _("M2"), wxPoint(184,8), wxSize(120,104), 0, _T("ID_STATICBOX2"));
	StaticBox1 = new wxStaticBox(this, ID_STATICBOX1, _("M1"), wxPoint(64,8), wxSize(120,104), 0, _T("ID_STATICBOX1"));
	StaticText_SpeedM1 = new wxStaticText(this, ID_STATICTEXT1, _("---"), wxPoint(72,56), wxSize(104,24), 0, _T("ID_STATICTEXT1"));
	wxFont StaticText_SpeedM1Font(10,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
	StaticText_SpeedM1->SetFont(StaticText_SpeedM1Font);
	StaticText_PowerM1 = new wxStaticText(this, ID_STATICTEXT2, _("---"), wxPoint(72,32), wxSize(104,24), 0, _T("ID_STATICTEXT2"));
	wxFont StaticText_PowerM1Font(10,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
	StaticText_PowerM1->SetFont(StaticText_PowerM1Font);
	StaticText_PosM1 = new wxStaticText(this, ID_STATICTEXT3, _("---"), wxPoint(72,80), wxSize(104,24), 0, _T("ID_STATICTEXT3"));
	wxFont StaticText_PosM1Font(10,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
	StaticText_PosM1->SetFont(StaticText_PosM1Font);
	StaticText_PowerM2 = new wxStaticText(this, ID_STATICTEXT4, _("---"), wxPoint(192,32), wxSize(104,24), 0, _T("ID_STATICTEXT4"));
	wxFont StaticText_PowerM2Font(10,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
	StaticText_PowerM2->SetFont(StaticText_PowerM2Font);
	StaticText_PowerM3 = new wxStaticText(this, ID_STATICTEXT5, _("---"), wxPoint(312,32), wxSize(104,24), 0, _T("ID_STATICTEXT5"));
	wxFont StaticText_PowerM3Font(10,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
	StaticText_PowerM3->SetFont(StaticText_PowerM3Font);
	StaticText_PowerM4 = new wxStaticText(this, ID_STATICTEXT6, _("---"), wxPoint(432,32), wxSize(104,24), 0, _T("ID_STATICTEXT6"));
	wxFont StaticText_PowerM4Font(10,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
	StaticText_PowerM4->SetFont(StaticText_PowerM4Font);
	StaticText_SpeedM2 = new wxStaticText(this, ID_STATICTEXT7, _("---"), wxPoint(192,56), wxSize(104,24), 0, _T("ID_STATICTEXT7"));
	wxFont StaticText_SpeedM2Font(10,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
	StaticText_SpeedM2->SetFont(StaticText_SpeedM2Font);
	StaticText_SpeedM3 = new wxStaticText(this, ID_STATICTEXT8, _("---"), wxPoint(312,56), wxSize(104,24), 0, _T("ID_STATICTEXT8"));
	wxFont StaticText_SpeedM3Font(10,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
	StaticText_SpeedM3->SetFont(StaticText_SpeedM3Font);
	StaticText_SpeedM4 = new wxStaticText(this, ID_STATICTEXT9, _("---"), wxPoint(432,56), wxSize(104,24), 0, _T("ID_STATICTEXT9"));
	wxFont StaticText_SpeedM4Font(10,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
	StaticText_SpeedM4->SetFont(StaticText_SpeedM4Font);
	StaticText_PosM2 = new wxStaticText(this, ID_STATICTEXT10, _("---"), wxPoint(192,80), wxSize(104,24), 0, _T("ID_STATICTEXT10"));
	wxFont StaticText_PosM2Font(10,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
	StaticText_PosM2->SetFont(StaticText_PosM2Font);
	StaticText_PosM3 = new wxStaticText(this, ID_STATICTEXT11, _("---"), wxPoint(312,80), wxSize(104,24), 0, _T("ID_STATICTEXT11"));
	wxFont StaticText_PosM3Font(10,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
	StaticText_PosM3->SetFont(StaticText_PosM3Font);
	StaticText_PosM4 = new wxStaticText(this, ID_STATICTEXT12, _("---"), wxPoint(432,80), wxSize(104,24), 0, _T("ID_STATICTEXT12"));
	wxFont StaticText_PosM4Font(10,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
	StaticText_PosM4->SetFont(StaticText_PosM4Font);
	StaticText13 = new wxStaticText(this, ID_STATICTEXT13, _("Power"), wxPoint(8,32), wxDefaultSize, 0, _T("ID_STATICTEXT13"));
	StaticText14 = new wxStaticText(this, ID_STATICTEXT14, _("Speed"), wxPoint(8,56), wxDefaultSize, 0, _T("ID_STATICTEXT14"));
	StaticText15 = new wxStaticText(this, ID_STATICTEXT15, _("Position"), wxPoint(8,80), wxDefaultSize, 0, _T("ID_STATICTEXT15"));
	StaticBox5 = new wxStaticBox(this, ID_STATICBOX5, _("S1"), wxPoint(64,120), wxSize(120,104), 0, _T("ID_STATICBOX5"));
	StaticText_ValueS1 = new wxStaticText(this, ID_STATICTEXT16, _("---"), wxPoint(72,168), wxSize(104,24), 0, _T("ID_STATICTEXT16"));
	wxFont StaticText_ValueS1Font(10,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
	StaticText_ValueS1->SetFont(StaticText_ValueS1Font);
	StaticText17 = new wxStaticText(this, ID_STATICTEXT17, _("Value"), wxPoint(8,168), wxDefaultSize, 0, _T("ID_STATICTEXT17"));
	StaticBox6 = new wxStaticBox(this, ID_STATICBOX6, _("Digital"), wxPoint(64,232), wxSize(120,64), 0, _T("ID_STATICBOX6"));
	CheckBox_D1 = new wxCheckBox(this, ID_CHECKBOX1, _("D1   "), wxPoint(88,256), wxSize(48,15), wxALIGN_RIGHT, wxDefaultValidator, _T("ID_CHECKBOX1"));
	CheckBox_D1->SetValue(false);
	CheckBox_D2 = new wxCheckBox(this, ID_CHECKBOX2, _("D2   "), wxPoint(88,272), wxSize(48,15), wxCHK_3STATE|wxALIGN_RIGHT, wxDefaultValidator, _T("ID_CHECKBOX2"));
	CheckBox_D2->SetValue(false);
	StaticBox7 = new wxStaticBox(this, ID_STATICBOX7, _("S2"), wxPoint(184,120), wxSize(120,104), 0, _T("ID_STATICBOX7"));
	StaticBox8 = new wxStaticBox(this, ID_STATICBOX8, _("S3"), wxPoint(304,120), wxSize(120,104), 0, _T("ID_STATICBOX8"));
	StaticBox9 = new wxStaticBox(this, ID_STATICBOX9, _("S4"), wxPoint(424,120), wxSize(120,104), 0, _T("ID_STATICBOX9"));
	StaticText_ValueS2 = new wxStaticText(this, ID_STATICTEXT18, _("---"), wxPoint(192,168), wxSize(104,24), 0, _T("ID_STATICTEXT18"));
	wxFont StaticText_ValueS2Font(10,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
	StaticText_ValueS2->SetFont(StaticText_ValueS2Font);
	StaticText_ValueS3 = new wxStaticText(this, ID_STATICTEXT19, _("---"), wxPoint(312,168), wxSize(104,24), 0, _T("ID_STATICTEXT19"));
	wxFont StaticText_ValueS3Font(10,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
	StaticText_ValueS3->SetFont(StaticText_ValueS3Font);
	StaticText_ValueS4 = new wxStaticText(this, ID_STATICTEXT20, _("---"), wxPoint(432,168), wxSize(104,24), 0, _T("ID_STATICTEXT20"));
	wxFont StaticText_ValueS4Font(10,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
	StaticText_ValueS4->SetFont(StaticText_ValueS4Font);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT21, _("Info"), wxPoint(8,144), wxDefaultSize, 0, _T("ID_STATICTEXT21"));
	StaticText_InfoS1 = new wxStaticText(this, ID_STATICTEXT22, _("Label"), wxPoint(72,144), wxSize(104,16), 0, _T("ID_STATICTEXT22"));
	StaticText_InfoS2 = new wxStaticText(this, ID_STATICTEXT23, _("Label"), wxPoint(192,144), wxSize(104,16), 0, _T("ID_STATICTEXT23"));
	StaticText_InfoS3 = new wxStaticText(this, ID_STATICTEXT24, _("Label"), wxPoint(312,144), wxSize(104,16), 0, _T("ID_STATICTEXT24"));
	StaticText_InfoS4 = new wxStaticText(this, ID_STATICTEXT25, _("Label"), wxPoint(432,144), wxSize(104,16), 0, _T("ID_STATICTEXT25"));
	Timer1.SetOwner(this, ID_TIMER1);
	Timer1.Start(100, false);

	Connect(ID_TIMER1,wxEVT_TIMER,(wxObjectEventFunction)&ViewDialog::OnTimer1Trigger);
	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&ViewDialog::OnClose);
	//*)

	Timer1.Stop();
}

//-------------------------------------------------------------------
ViewDialog::~ViewDialog()
{
	//(*Destroy(ViewDialog)
	//*)
}

//-------------------------------------------------------------------
void ViewDialog::run( void )
{
  Timer1.Start();
 if( !Show() )
 {
  Raise();
  Restore();
 }
}

//-------------------------------------------------------------------
void ViewDialog::OnTimer1Trigger(wxTimerEvent& event)
{
  StaticText_PowerM1->SetLabel( daten.getMotorPowerByString(0) );
  StaticText_PowerM2->SetLabel( daten.getMotorPowerByString(1) );
  StaticText_PowerM3->SetLabel( daten.getMotorPowerByString(2) );
  StaticText_PowerM4->SetLabel( daten.getMotorPowerByString(3) );

  StaticText_SpeedM1->SetLabel( daten.getMotorSpeedByString(0) );
  StaticText_SpeedM2->SetLabel( daten.getMotorSpeedByString(1) );
  StaticText_SpeedM3->SetLabel( daten.getMotorSpeedByString(2) );
  StaticText_SpeedM4->SetLabel( daten.getMotorSpeedByString(3) );

  StaticText_PosM1->SetLabel( daten.getMotorPosByString(0) );
  StaticText_PosM2->SetLabel( daten.getMotorPosByString(1) );
  StaticText_PosM3->SetLabel( daten.getMotorPosByString(2) );
  StaticText_PosM4->SetLabel( daten.getMotorPosByString(3) );

  StaticText_ValueS1->SetLabel( daten.getSensorValueByString(0));
  StaticText_ValueS2->SetLabel( daten.getSensorValueByString(1));
  StaticText_ValueS3->SetLabel( daten.getSensorValueByString(2));
  StaticText_ValueS4->SetLabel( daten.getSensorValueByString(3));

  StaticText_InfoS1->SetLabel( daten.getSensorInfoByString(0));
  StaticText_InfoS2->SetLabel( daten.getSensorInfoByString(1));
  StaticText_InfoS3->SetLabel( daten.getSensorInfoByString(2));
  StaticText_InfoS4->SetLabel( daten.getSensorInfoByString(3));

  CheckBox_D1->SetValue(daten.mess.d.data.taster[0]);
  CheckBox_D2->SetValue(daten.mess.d.data.taster[1]);
}

//-------------------------------------------------------------------
void ViewDialog::OnClose(wxCloseEvent& event)
{
  Timer1.Stop();
  EndDialog(0);
}

//EOF
