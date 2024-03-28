#include "MotorDialog.h"

//(*InternalHeaders(MotorDialog)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/settings.h>
#include <wx/string.h>
//*)

//(*IdInit(MotorDialog)
const long MotorDialog::ID_STATICBOX1 = wxNewId();
const long MotorDialog::ID_STATICBOX2 = wxNewId();
const long MotorDialog::ID_STATICBOX3 = wxNewId();
const long MotorDialog::ID_STATICBOX4 = wxNewId();
const long MotorDialog::ID_CHOICE_TYPE_M1 = wxNewId();
const long MotorDialog::ID_CHOICE_TYPE_M2 = wxNewId();
const long MotorDialog::ID_CHOICE_TYPE_M3 = wxNewId();
const long MotorDialog::ID_CHOICE_TYPE_M4 = wxNewId();
const long MotorDialog::ID_CHOICE_MODE_M1 = wxNewId();
const long MotorDialog::ID_CHOICE_MODE_M2 = wxNewId();
const long MotorDialog::ID_CHOICE_MODE_M3 = wxNewId();
const long MotorDialog::ID_CHOICE_MODE_M4 = wxNewId();
const long MotorDialog::ID_SPINCTRL_SPEED_M1 = wxNewId();
const long MotorDialog::ID_SPINCTRL_SPEED_M2 = wxNewId();
const long MotorDialog::ID_SPINCTRL_SPEED_M3 = wxNewId();
const long MotorDialog::ID_SPINCTRL_SPEED_M4 = wxNewId();
const long MotorDialog::ID_STATICTEXT1 = wxNewId();
const long MotorDialog::ID_STATICTEXT2 = wxNewId();
const long MotorDialog::ID_STATICTEXT3 = wxNewId();
const long MotorDialog::ID_BUTTON1 = wxNewId();
const long MotorDialog::ID_STATICBOX5 = wxNewId();
const long MotorDialog::ID_STATICBOX6 = wxNewId();
const long MotorDialog::ID_STATICTEXT4 = wxNewId();
const long MotorDialog::ID_STATICTEXT5 = wxNewId();
const long MotorDialog::ID_CHOICE1 = wxNewId();
const long MotorDialog::ID_SPINCTRL1 = wxNewId();
const long MotorDialog::ID_SPINCTRL2 = wxNewId();
const long MotorDialog::ID_SPINCTRL3 = wxNewId();
const long MotorDialog::ID_SPINCTRL4 = wxNewId();
const long MotorDialog::ID_CHECKBOX1 = wxNewId();
const long MotorDialog::ID_TIMER1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(MotorDialog,wxDialog)
	//(*EventTable(MotorDialog)
	//*)
END_EVENT_TABLE()

//-------------------------------------------------------------------
MotorDialog::MotorDialog( Daten &daten,
                          wxWindow* parent,
                          wxWindowID id )
: daten( daten )
{
	//(*Initialize(MotorDialog)
	Create(parent, wxID_ANY, _("ORB-Monitor - Motor Configuration and Setting"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxMINIMIZE_BOX, _T("wxID_ANY"));
	SetClientSize(wxSize(552,232));
	SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
	StaticBox1 = new wxStaticBox(this, ID_STATICBOX1, _("M1"), wxPoint(56,8), wxSize(120,120), 0, _T("ID_STATICBOX1"));
	StaticBox2 = new wxStaticBox(this, ID_STATICBOX2, _("M2"), wxPoint(176,8), wxSize(120,120), 0, _T("ID_STATICBOX2"));
	StaticBox3 = new wxStaticBox(this, ID_STATICBOX3, _("M3"), wxPoint(296,8), wxSize(120,120), 0, _T("ID_STATICBOX3"));
	StaticBox4 = new wxStaticBox(this, ID_STATICBOX4, _("M4"), wxPoint(416,8), wxSize(120,120), 0, _T("ID_STATICBOX4"));
	Choice_MotorType_1 = new wxChoice(this, ID_CHOICE_TYPE_M1, wxPoint(64,32), wxSize(104,23), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE_TYPE_M1"));
	Choice_MotorType_1->SetSelection( Choice_MotorType_1->Append(_("LEGO")) );
	Choice_MotorType_1->Append(_("Makeblock"));
	Choice_MotorType_2 = new wxChoice(this, ID_CHOICE_TYPE_M2, wxPoint(184,32), wxSize(104,23), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE_TYPE_M2"));
	Choice_MotorType_2->SetSelection( Choice_MotorType_2->Append(_("LEGO")) );
	Choice_MotorType_2->Append(_("Makeblock"));
	Choice_MotorType_3 = new wxChoice(this, ID_CHOICE_TYPE_M3, wxPoint(304,32), wxSize(104,23), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE_TYPE_M3"));
	Choice_MotorType_3->SetSelection( Choice_MotorType_3->Append(_("LEGO")) );
	Choice_MotorType_3->Append(_("Makeblock"));
	Choice_MotorType_4 = new wxChoice(this, ID_CHOICE_TYPE_M4, wxPoint(424,32), wxSize(104,23), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE_TYPE_M4"));
	Choice_MotorType_4->SetSelection( Choice_MotorType_4->Append(_("LEGO")) );
	Choice_MotorType_4->Append(_("Makeblock"));
	Choice_MotorMode_1 = new wxChoice(this, ID_CHOICE_MODE_M1, wxPoint(64,64), wxSize(104,23), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE_MODE_M1"));
	Choice_MotorMode_1->SetSelection( Choice_MotorMode_1->Append(_("Off")) );
	Choice_MotorMode_1->Append(_("Power"));
	Choice_MotorMode_1->Append(_("Brake"));
	Choice_MotorMode_1->Append(_("Speed"));
	Choice_MotorMode_2 = new wxChoice(this, ID_CHOICE_MODE_M2, wxPoint(184,64), wxSize(104,23), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE_MODE_M2"));
	Choice_MotorMode_2->SetSelection( Choice_MotorMode_2->Append(_("Off")) );
	Choice_MotorMode_2->Append(_("Power"));
	Choice_MotorMode_2->Append(_("Brake"));
	Choice_MotorMode_2->Append(_("Speed"));
	Choice_MotorMode_3 = new wxChoice(this, ID_CHOICE_MODE_M3, wxPoint(304,64), wxSize(104,23), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE_MODE_M3"));
	Choice_MotorMode_3->SetSelection( Choice_MotorMode_3->Append(_("Off")) );
	Choice_MotorMode_3->Append(_("Power"));
	Choice_MotorMode_3->Append(_("Brake"));
	Choice_MotorMode_3->Append(_("Speed"));
	Choice_MotorMode_4 = new wxChoice(this, ID_CHOICE_MODE_M4, wxPoint(424,64), wxSize(104,23), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE_MODE_M4"));
	Choice_MotorMode_4->SetSelection( Choice_MotorMode_4->Append(_("Off")) );
	Choice_MotorMode_4->Append(_("Power"));
	Choice_MotorMode_4->Append(_("Brake"));
	Choice_MotorMode_4->Append(_("Speed"));
	SpinCtrl_MotorSpeed_1 = new wxSpinCtrl(this, ID_SPINCTRL_SPEED_M1, _T("0"), wxPoint(64,96), wxSize(106,23), wxSP_ARROW_KEYS, -100, 100, 0, _T("ID_SPINCTRL_SPEED_M1"));
	SpinCtrl_MotorSpeed_1->SetValue(_T("0"));
	SpinCtrl_MotorSpeed_2 = new wxSpinCtrl(this, ID_SPINCTRL_SPEED_M2, _T("0"), wxPoint(184,96), wxSize(106,23), 0, -100, 100, 0, _T("ID_SPINCTRL_SPEED_M2"));
	SpinCtrl_MotorSpeed_2->SetValue(_T("0"));
	SpinCtrl_MotorSpeed_3 = new wxSpinCtrl(this, ID_SPINCTRL_SPEED_M3, _T("0"), wxPoint(304,96), wxSize(106,23), 0, -100, 100, 0, _T("ID_SPINCTRL_SPEED_M3"));
	SpinCtrl_MotorSpeed_3->SetValue(_T("0"));
	SpinCtrl_MotorSpeed_4 = new wxSpinCtrl(this, ID_SPINCTRL_SPEED_M4, _T("0"), wxPoint(424,96), wxSize(106,23), 0, -100, 100, 0, _T("ID_SPINCTRL_SPEED_M4"));
	SpinCtrl_MotorSpeed_4->SetValue(_T("0"));
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Mode"), wxPoint(8,64), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Type"), wxPoint(8,32), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Speed\nPower"), wxPoint(8,96), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	Button1 = new wxButton(this, ID_BUTTON1, _("Close"), wxPoint(456,192), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	StaticBox5 = new wxStaticBox(this, ID_STATICBOX5, _("Servo 1"), wxPoint(56,136), wxSize(120,88), 0, _T("ID_STATICBOX5"));
	StaticBox6 = new wxStaticBox(this, ID_STATICBOX6, _("Servo 2"), wxPoint(176,136), wxSize(120,88), 0, _T("ID_STATICBOX6"));
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Speed"), wxPoint(8,160), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Position"), wxPoint(8,192), wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	Choice1 = new wxChoice(this, ID_CHOICE1, wxPoint(344,376), wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
	SpinCtrl_SpeedServo1 = new wxSpinCtrl(this, ID_SPINCTRL1, _T("0"), wxPoint(64,160), wxSize(106,23), 0, 0, 100, 0, _T("ID_SPINCTRL1"));
	SpinCtrl_SpeedServo1->SetValue(_T("0"));
	SpinCtrl_SpeedServo2 = new wxSpinCtrl(this, ID_SPINCTRL2, _T("0"), wxPoint(184,160), wxSize(106,23), 0, 0, 100, 0, _T("ID_SPINCTRL2"));
	SpinCtrl_SpeedServo2->SetValue(_T("0"));
	SpinCtrl_PosServo1 = new wxSpinCtrl(this, ID_SPINCTRL3, _T("0"), wxPoint(64,192), wxSize(106,23), 0, 0, 100, 0, _T("ID_SPINCTRL3"));
	SpinCtrl_PosServo1->SetValue(_T("0"));
	SpinCtrl_PosServo2 = new wxSpinCtrl(this, ID_SPINCTRL4, _T("0"), wxPoint(184,192), wxSize(106,23), 0, 0, 100, 0, _T("ID_SPINCTRL4"));
	SpinCtrl_PosServo2->SetValue(_T("0"));
	CheckBox_Enable = new wxCheckBox(this, ID_CHECKBOX1, _("Enable"), wxPoint(464,152), wxSize(72,15), 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	CheckBox_Enable->SetValue(false);
	wxFont CheckBox_EnableFont(12,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Arial"),wxFONTENCODING_DEFAULT);
	CheckBox_Enable->SetFont(CheckBox_EnableFont);
	Timer1.SetOwner(this, ID_TIMER1);
	Timer1.Start(100, false);

	Connect(ID_CHOICE_TYPE_M1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&MotorDialog::OnChoice_MotorConfig);
	Connect(ID_CHOICE_TYPE_M2,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&MotorDialog::OnChoice_MotorConfig);
	Connect(ID_CHOICE_TYPE_M3,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&MotorDialog::OnChoice_MotorConfig);
	Connect(ID_CHOICE_TYPE_M4,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&MotorDialog::OnChoice_MotorConfig);
	Connect(ID_CHOICE_MODE_M1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&MotorDialog::OnChoice_MotorSetting);
	Connect(ID_CHOICE_MODE_M2,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&MotorDialog::OnChoice_MotorSetting);
	Connect(ID_CHOICE_MODE_M3,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&MotorDialog::OnChoice_MotorSetting);
	Connect(ID_CHOICE_MODE_M4,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&MotorDialog::OnChoice_MotorSetting);
	Connect(ID_SPINCTRL_SPEED_M1,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&MotorDialog::OnSpinCtrl_MotorSetting);
	Connect(ID_SPINCTRL_SPEED_M2,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&MotorDialog::OnSpinCtrl_MotorSetting);
	Connect(ID_SPINCTRL_SPEED_M3,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&MotorDialog::OnSpinCtrl_MotorSetting);
	Connect(ID_SPINCTRL_SPEED_M4,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&MotorDialog::OnSpinCtrl_MotorSetting);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MotorDialog::OnButton_Close);
	Connect(ID_TIMER1,wxEVT_TIMER,(wxObjectEventFunction)&MotorDialog::OnTimer1Trigger);
	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&MotorDialog::OnClose);
	//*)

	Timer1.Stop();
}

//-------------------------------------------------------------------
MotorDialog::~MotorDialog()
{
	//(*Destroy(MotorDialog)
	//*)
}

//-------------------------------------------------------------------
void MotorDialog::setMotorConfig( Daten::ConfigToORB::Data &config, int id, int type )
{
  switch( type )
  {
    case 0:
      config.motor[id].ticsPerRotation = 72;
      config.motor[id].acceleration    = 25;
      config.motor[id].Regler_Kp       = 50;
      config.motor[id].Regler_Ki       = 30;
      break;
    case 1:
      config.motor[id].ticsPerRotation = 144;
      config.motor[id].acceleration    = 50;
      config.motor[id].Regler_Kp       = 50;
      config.motor[id].Regler_Ki       = 30;
      break;
  }
}

//-------------------------------------------------------------------
void MotorDialog::setMotorProp( Daten::PropToORB::Data &prop,int id, int mode, int speed )
{
  if( mode )
  {
    prop.motor[id].mmode = mode-1;
    prop.motor[id].speed = (mode==1)? 10*speed : 50*speed;
    prop.motor[id].pos   = 0;
  }
  else
  {
    prop.motor[id].mmode = 0;
    prop.motor[id].speed = 0;
    prop.motor[id].pos   = 0;
  }
}

//-------------------------------------------------------------------
void MotorDialog::setServoProp( Daten::PropToORB::Data &prop,int id, int speed, int pos )
{
  prop.modelServo[id].sspeed = speed;
  prop.modelServo[id].spos   = pos;
}

//-------------------------------------------------------------------
void MotorDialog::printAll( bool isConfig )
{
    if( isConfig || sendConfigReq )
    {
      sendConfigReq = false;
      Daten::ConfigToORB::Data &config = daten.config.d.data;
      //config << daten.config;
      setMotorConfig( config, 0,Choice_MotorType_1->GetSelection() );
      setMotorConfig( config, 1,Choice_MotorType_2->GetSelection() );
      setMotorConfig( config, 2,Choice_MotorType_3->GetSelection() );
      setMotorConfig( config, 3,Choice_MotorType_4->GetSelection() );
      daten.config << config;
    }

  if( CheckBox_Enable->GetValue() )
  {
    Daten::PropToORB::Data prop;
    setMotorProp( prop, 0, Choice_MotorMode_1->GetSelection(), SpinCtrl_MotorSpeed_1->GetValue() );
    setMotorProp( prop, 1, Choice_MotorMode_2->GetSelection(), SpinCtrl_MotorSpeed_2->GetValue() );
    setMotorProp( prop, 2, Choice_MotorMode_3->GetSelection(), SpinCtrl_MotorSpeed_3->GetValue() );
    setMotorProp( prop, 3, Choice_MotorMode_4->GetSelection(), SpinCtrl_MotorSpeed_4->GetValue() );

    setServoProp( prop, 0, SpinCtrl_SpeedServo1->GetValue(), SpinCtrl_PosServo1->GetValue());
    setServoProp( prop, 1, SpinCtrl_SpeedServo2->GetValue(), SpinCtrl_PosServo2->GetValue());

    daten.control << prop;

  }
  else
  {
    Daten::PropToORB::Data prop;
    setMotorProp( prop, 0, 0, 0 );
    setMotorProp( prop, 1, 0, 0 );
    setMotorProp( prop, 2, 0, 0 );
    setMotorProp( prop, 3, 0, 0 );

    setServoProp( prop, 0, 0, 0);
    setServoProp( prop, 1, 0, 0);

    daten.control << prop;
  }
}

//-------------------------------------------------------------------
void MotorDialog::run( void )
{
   isConnectedFlag = false;
   if( !Show() )
   {
    Raise();
  //  Maximize();
    Restore();
   }
   else
   {
     CheckBox_Enable->SetValue(false);
     printAll( true );
     Timer1.Start();
   }
}

//-------------------------------------------------------------------
void MotorDialog::OnChoice_MotorConfig(wxCommandEvent& event)
{
  printAll( true );
}

//-------------------------------------------------------------------
void MotorDialog::OnChoice_MotorSetting(wxCommandEvent& event)
{
  printAll( false );
}

//-------------------------------------------------------------------
void MotorDialog::OnSpinCtrl_MotorSetting(wxSpinEvent& event)
{
}

//-------------------------------------------------------------------
void MotorDialog::OnClose(wxCloseEvent& event)
{
  // Motoren ausschalten
  Timer1.Stop();
  CheckBox_Enable->SetValue(false);
  printAll( false );
  EndDialog(0);
}

//-------------------------------------------------------------------
void MotorDialog::OnButton_Close(wxCommandEvent& event)
{
  Close();
}

//-------------------------------------------------------------------
void MotorDialog::OnTimer1Trigger(wxTimerEvent& event)
{
  printAll( false );
}

//EOF
