#ifndef MOTORDIALOG_H
#define MOTORDIALOG_H

#include "Daten.h"

//(*Headers(MotorDialog)
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/choice.h>
#include <wx/dialog.h>
#include <wx/spinctrl.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/timer.h>
//*)

class MotorDialog: public wxDialog
{
	public:

		MotorDialog( Daten      &daten,
                 wxWindow* parent,
                wxWindowID id=wxID_ANY);
		virtual ~MotorDialog();

    void run( void  );

    bool isConnectedFlag = false;
    bool sendConfigReq = false;
    void setIsConnected( bool flag )
    {
      if( !isConnectedFlag && flag )
      {
        sendConfigReq = true;
      }
      isConnectedFlag = flag;
    }

    void printAll(bool enable);
    void setMotorConfig( Daten::ConfigToORB::Data &config, int id, int type );
    void setMotorProp( Daten::PropToORB::Data &prop,int id, int mode, int speed );
    void setServoProp( Daten::PropToORB::Data &prop,int id, int speed, int pos );

		//(*Declarations(MotorDialog)
		wxButton* Button1;
		wxCheckBox* CheckBox_Enable;
		wxChoice* Choice1;
		wxChoice* Choice_MotorMode_1;
		wxChoice* Choice_MotorMode_2;
		wxChoice* Choice_MotorMode_3;
		wxChoice* Choice_MotorMode_4;
		wxChoice* Choice_MotorType_1;
		wxChoice* Choice_MotorType_2;
		wxChoice* Choice_MotorType_3;
		wxChoice* Choice_MotorType_4;
		wxSpinCtrl* SpinCtrl_MotorSpeed_1;
		wxSpinCtrl* SpinCtrl_MotorSpeed_2;
		wxSpinCtrl* SpinCtrl_MotorSpeed_3;
		wxSpinCtrl* SpinCtrl_MotorSpeed_4;
		wxSpinCtrl* SpinCtrl_PosServo1;
		wxSpinCtrl* SpinCtrl_PosServo2;
		wxSpinCtrl* SpinCtrl_SpeedServo1;
		wxSpinCtrl* SpinCtrl_SpeedServo2;
		wxStaticBox* StaticBox1;
		wxStaticBox* StaticBox2;
		wxStaticBox* StaticBox3;
		wxStaticBox* StaticBox4;
		wxStaticBox* StaticBox5;
		wxStaticBox* StaticBox6;
		wxStaticText* StaticText1;
		wxStaticText* StaticText2;
		wxStaticText* StaticText3;
		wxStaticText* StaticText4;
		wxStaticText* StaticText5;
		wxTimer Timer1;
		//*)

	protected:

		//(*Identifiers(MotorDialog)
		static const long ID_STATICBOX1;
		static const long ID_STATICBOX2;
		static const long ID_STATICBOX3;
		static const long ID_STATICBOX4;
		static const long ID_CHOICE_TYPE_M1;
		static const long ID_CHOICE_TYPE_M2;
		static const long ID_CHOICE_TYPE_M3;
		static const long ID_CHOICE_TYPE_M4;
		static const long ID_CHOICE_MODE_M1;
		static const long ID_CHOICE_MODE_M2;
		static const long ID_CHOICE_MODE_M3;
		static const long ID_CHOICE_MODE_M4;
		static const long ID_SPINCTRL_SPEED_M1;
		static const long ID_SPINCTRL_SPEED_M2;
		static const long ID_SPINCTRL_SPEED_M3;
		static const long ID_SPINCTRL_SPEED_M4;
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT2;
		static const long ID_STATICTEXT3;
		static const long ID_BUTTON1;
		static const long ID_STATICBOX5;
		static const long ID_STATICBOX6;
		static const long ID_STATICTEXT4;
		static const long ID_STATICTEXT5;
		static const long ID_CHOICE1;
		static const long ID_SPINCTRL1;
		static const long ID_SPINCTRL2;
		static const long ID_SPINCTRL3;
		static const long ID_SPINCTRL4;
		static const long ID_CHECKBOX1;
		static const long ID_TIMER1;
		//*)

	private:

		//(*Handlers(MotorDialog)
		void OnChoice1Select(wxCommandEvent& event);
		void OnChoice2Select(wxCommandEvent& event);
		void OnSpinCtrl1Change(wxSpinEvent& event);
		void OnSpinCtrl_MotorSpeed_2Change(wxSpinEvent& event);
		void OnButton2Click(wxCommandEvent& event);
		void OnInit(wxInitDialogEvent& event);
		void OnChoice_Config(wxCommandEvent& event);
		void OnChoice_MotorSetting(wxCommandEvent& event);
		void OnChoice_MotorConfig(wxCommandEvent& event);
		void OnSpinCtrl_MotorSetting(wxSpinEvent& event);
		void OnMouseEnter(wxMouseEvent& event);
		void OnMouseLeave(wxMouseEvent& event);
		void OnClose(wxCloseEvent& event);
		void OnButton_Close(wxCommandEvent& event);
		void OnButton_Stop(wxCommandEvent& event);
		void OnButton_Run(wxCommandEvent& event);
		void OnTimer1Trigger(wxTimerEvent& event);
		//*)

		DECLARE_EVENT_TABLE()

		Daten &daten;
};

#endif
