#include "SensorDialog.h"

//(*InternalHeaders(SensorDialog)
#include <wx/intl.h>
#include <wx/settings.h>
#include <wx/string.h>
//*)

//(*IdInit(SensorDialog)
const long SensorDialog::ID_STATICBOX1 = wxNewId();
const long SensorDialog::ID_STATICBOX2 = wxNewId();
const long SensorDialog::ID_STATICTEXT1 = wxNewId();
const long SensorDialog::ID_CHOICE1 = wxNewId();
const long SensorDialog::ID_STATICTEXT2 = wxNewId();
const long SensorDialog::ID_BUTTON1 = wxNewId();
const long SensorDialog::ID_STATICBOX4 = wxNewId();
const long SensorDialog::ID_STATICBOX5 = wxNewId();
const long SensorDialog::ID_CHOICE3 = wxNewId();
const long SensorDialog::ID_CHOICE5 = wxNewId();
const long SensorDialog::ID_CHOICE7 = wxNewId();
const long SensorDialog::ID_SPINCTRL1 = wxNewId();
const long SensorDialog::ID_SPINCTRL2 = wxNewId();
const long SensorDialog::ID_SPINCTRL3 = wxNewId();
const long SensorDialog::ID_SPINCTRL4 = wxNewId();
const long SensorDialog::ID_TIMER1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(SensorDialog,wxDialog)
	//(*EventTable(SensorDialog)
	//*)
END_EVENT_TABLE()

//-------------------------------------------------------------------
SensorDialog::SensorDialog( Daten &daten,
                            wxWindow* parent,
                            wxWindowID id )
: daten( daten )
{
	//(*Initialize(SensorDialog)
	Create(parent, wxID_ANY, _("ORB-Monitor - Sensor Configuration"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxMINIMIZE_BOX, _T("wxID_ANY"));
	SetClientSize(wxSize(552,136));
	SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
	StaticBox1 = new wxStaticBox(this, ID_STATICBOX1, _("S1"), wxPoint(56,8), wxSize(120,88), 0, _T("ID_STATICBOX1"));
	StaticBox2 = new wxStaticBox(this, ID_STATICBOX2, _("S2"), wxPoint(176,8), wxSize(120,88), 0, _T("ID_STATICBOX2"));
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Type"), wxPoint(8,32), wxSize(40,24), 0, _T("ID_STATICTEXT1"));
	Choice_TypeS1 = new wxChoice(this, ID_CHOICE1, wxPoint(64,32), wxSize(104,23), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
	Choice_TypeS1->SetSelection( Choice_TypeS1->Append(_("Raw")) );
	Choice_TypeS1->Append(_("EV3/UART"));
	Choice_TypeS1->Append(_("MB-Linefollower"));
	Choice_TypeS1->Append(_("MB-Ultrasonic"));
	Choice_TypeS1->Append(_("NXT-Light"));
	Choice_TypeS1->Append(_("NXT-Ultrasonic"));
	Choice_TypeS1->Append(_("NXT/EV3-Touch"));
	Choice_TypeS1->Append(_("TCS34xx-Color"));
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Mode"), wxPoint(8,64), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	Button1 = new wxButton(this, ID_BUTTON1, _("Close"), wxPoint(464,104), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	StaticBox4 = new wxStaticBox(this, ID_STATICBOX4, _("S3"), wxPoint(296,8), wxSize(120,88), 0, _T("ID_STATICBOX4"));
	StaticBox5 = new wxStaticBox(this, ID_STATICBOX5, _("S4"), wxPoint(416,8), wxSize(120,88), 0, _T("ID_STATICBOX5"));
	Choice_TypeS2 = new wxChoice(this, ID_CHOICE3, wxPoint(184,32), wxSize(104,23), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE3"));
	Choice_TypeS2->SetSelection( Choice_TypeS2->Append(_("Raw")) );
	Choice_TypeS2->Append(_("EV3/UART"));
	Choice_TypeS2->Append(_("MB-Linefollower"));
	Choice_TypeS2->Append(_("MB-Ultrasonic"));
	Choice_TypeS2->Append(_("NXT-Light"));
	Choice_TypeS2->Append(_("NXT-Ultrasonic"));
	Choice_TypeS2->Append(_("NXT/EV3-Touch"));
	Choice_TypeS2->Append(_("TCS34xx-Color"));
	Choice_TypeS3 = new wxChoice(this, ID_CHOICE5, wxPoint(304,32), wxSize(104,23), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE5"));
	Choice_TypeS3->SetSelection( Choice_TypeS3->Append(_("Raw")) );
	Choice_TypeS3->Append(_("EV3/UART"));
	Choice_TypeS3->Append(_("MB-Linefollower"));
	Choice_TypeS3->Append(_("MB-Ultrasonic"));
	Choice_TypeS3->Append(_("NXT-Light"));
	Choice_TypeS3->Append(_("NXT-Ultrasonic"));
	Choice_TypeS3->Append(_("NXT/EV3-Touch"));
	Choice_TypeS3->Append(_("TCS34xx-Color"));
	Choice_TypeS4 = new wxChoice(this, ID_CHOICE7, wxPoint(424,32), wxSize(104,23), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE7"));
	Choice_TypeS4->SetSelection( Choice_TypeS4->Append(_("Raw")) );
	Choice_TypeS4->Append(_("EV3/UART"));
	Choice_TypeS4->Append(_("MB-Linefollower"));
	Choice_TypeS4->Append(_("MB-Ultrasonic"));
	Choice_TypeS4->Append(_("NXT-Light"));
	Choice_TypeS4->Append(_("NXT-Ultrasonic"));
	Choice_TypeS4->Append(_("NXT/EV3-Touch"));
	Choice_TypeS4->Append(_("TCS34xx-Color"));
	SpinCtrl_ModeS1 = new wxSpinCtrl(this, ID_SPINCTRL1, _T("0"), wxPoint(64,64), wxSize(104,23), 0, 0, 2, 0, _T("ID_SPINCTRL1"));
	SpinCtrl_ModeS1->SetValue(_T("0"));
	SpinCtrl_ModeS2 = new wxSpinCtrl(this, ID_SPINCTRL2, _T("0"), wxPoint(184,64), wxSize(106,23), 0, 0, 2, 0, _T("ID_SPINCTRL2"));
	SpinCtrl_ModeS2->SetValue(_T("0"));
	SpinCtrl_ModeS3 = new wxSpinCtrl(this, ID_SPINCTRL3, _T("0"), wxPoint(304,64), wxSize(106,23), 0, 0, 2, 0, _T("ID_SPINCTRL3"));
	SpinCtrl_ModeS3->SetValue(_T("0"));
	SpinCtrl_ModeS4 = new wxSpinCtrl(this, ID_SPINCTRL4, _T("0"), wxPoint(424,64), wxSize(106,23), 0, 0, 2, 0, _T("ID_SPINCTRL4"));
	SpinCtrl_ModeS4->SetValue(_T("0"));
	Timer1.SetOwner(this, ID_TIMER1);
	Timer1.Start(50, false);

	Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&SensorDialog::OnChoice_SensorConfig);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SensorDialog::OnButton_Close);
	Connect(ID_CHOICE3,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&SensorDialog::OnChoice_SensorConfig);
	Connect(ID_CHOICE5,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&SensorDialog::OnChoice_SensorConfig);
	Connect(ID_CHOICE7,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&SensorDialog::OnChoice_SensorConfig);
	Connect(ID_SPINCTRL1,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&SensorDialog::OnSpinCtrl_SensorConfig);
	Connect(ID_SPINCTRL2,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&SensorDialog::OnSpinCtrl_SensorConfig);
	Connect(ID_SPINCTRL3,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&SensorDialog::OnSpinCtrl_SensorConfig);
	Connect(ID_SPINCTRL4,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&SensorDialog::OnSpinCtrl_SensorConfig);
	Connect(ID_TIMER1,wxEVT_TIMER,(wxObjectEventFunction)&SensorDialog::OnTimer1Trigger);
	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&SensorDialog::OnClose);
	//*)

	Timer1.Stop();
}

//-------------------------------------------------------------------
SensorDialog::~SensorDialog()
{
	//(*Destroy(SensorDialog)
	//*)
}

//-------------------------------------------------------------------
void SensorDialog::run( void )
{
  isConnectedFlag = false;
  configAllSensor();
  Timer1.Start();
  if( !Show() )
  {
    Raise();
    Restore();
  }
}

//-------------------------------------------------------------------
void SensorDialog::OnClose(wxCloseEvent& event)
{
  Timer1.Stop();
  EndDialog(0);
}

//-------------------------------------------------------------------
void SensorDialog::OnButton_Close(wxCommandEvent& event)
{
  Close();
}

//-------------------------------------------------------------------
void SensorDialog::OnTimer1Trigger(wxTimerEvent& event)
{
//  StaticText_ValueS1->SetLabel( daten.getSensorValueByString(0));
//  StaticText_ValueS2->SetLabel( daten.getSensorValueByString(1));
//  StaticText_ValueS3->SetLabel( daten.getSensorValueByString(2));
//  StaticText_ValueS4->SetLabel( daten.getSensorValueByString(3));
  if( sendConfigReq )
  {
    sendConfigReq = false;
    configAllSensor();
  }

}


void SensorDialog::setSensorConfig( Daten::ConfigToORB::Data &config, int id, int type, int mode )
{
  switch( type )
  {
    default:
    case 0: //Raw
      config.sensor[id].type   = 0;
      config.sensor[id].mode   = 0;
      config.sensor[id].option = (2<<8)&(2<<12);
      break;

    case 1: //EV3/UART
      config.sensor[id].type   = 1;
      config.sensor[id].mode   = mode;
      config.sensor[id].option = 0;
      break;

    case 2: //MB-Linefollower
      config.sensor[id].type   = 0;
      config.sensor[id].mode   = 0;
      config.sensor[id].option = 0x2222;
      break;

    case 3: //MB-Ultrasonic
      config.sensor[id].type   = 3;
      config.sensor[id].mode   = 0;
      config.sensor[id].option = 0;
      break;

    case 4: //NXT-Light
      config.sensor[id].type   = 0;
      config.sensor[id].mode   = 0;
      config.sensor[id].option = mode?(0xF<<8):(0x7<<8);
      break;

    case 5: //NXT-Ultrasonic
      config.sensor[id].type   = 2;
      config.sensor[id].mode   = 0;
      config.sensor[id].option = 0;
      break;

    case 6: //NXT/EV3-Touch
      config.sensor[id].type   = 4;
      config.sensor[id].mode   = 0;
      config.sensor[id].option = 0;
      break;

    case 7: //TCS34xx-Color
      config.sensor[id].type   = 2;
      config.sensor[id].mode   = 1;
      config.sensor[id].option = 0;
      break;


  }
}

void SensorDialog::configAllSensor()
{
  Daten::ConfigToORB::Data &config = daten.config.d.data;
  setSensorConfig( config, 0, Choice_TypeS1->GetSelection(), SpinCtrl_ModeS1->GetValue() );
  setSensorConfig( config, 1, Choice_TypeS2->GetSelection(), SpinCtrl_ModeS2->GetValue() );
  setSensorConfig( config, 2, Choice_TypeS3->GetSelection(), SpinCtrl_ModeS3->GetValue() );
  setSensorConfig( config, 3, Choice_TypeS4->GetSelection(), SpinCtrl_ModeS4->GetValue() );
  daten.config << config;
}

//-------------------------------------------------------------------
void SensorDialog::OnChoice_SensorConfig(wxCommandEvent& event)
{
  configAllSensor();
}

//-------------------------------------------------------------------
void SensorDialog::OnSpinCtrl_SensorConfig(wxSpinEvent& event)
{
  configAllSensor();
}

//EOF
