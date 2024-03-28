#ifndef SENSORDIALOG_H
#define SENSORDIALOG_H


#include "Daten.h"


//(*Headers(SensorDialog)
#include <wx/button.h>
#include <wx/choice.h>
#include <wx/dialog.h>
#include <wx/spinctrl.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/timer.h>
//*)

class SensorDialog: public wxDialog
{
	public:

		SensorDialog(Daten      &daten,
                 wxWindow* parent,wxWindowID id=wxID_ANY);
		virtual ~SensorDialog();

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



		//(*Declarations(SensorDialog)
		wxButton* Button1;
		wxChoice* Choice_TypeS1;
		wxChoice* Choice_TypeS2;
		wxChoice* Choice_TypeS3;
		wxChoice* Choice_TypeS4;
		wxSpinCtrl* SpinCtrl_ModeS1;
		wxSpinCtrl* SpinCtrl_ModeS2;
		wxSpinCtrl* SpinCtrl_ModeS3;
		wxSpinCtrl* SpinCtrl_ModeS4;
		wxStaticBox* StaticBox1;
		wxStaticBox* StaticBox2;
		wxStaticBox* StaticBox4;
		wxStaticBox* StaticBox5;
		wxStaticText* StaticText1;
		wxStaticText* StaticText2;
		wxTimer Timer1;
		//*)

	protected:

		//(*Identifiers(SensorDialog)
		static const long ID_STATICBOX1;
		static const long ID_STATICBOX2;
		static const long ID_STATICTEXT1;
		static const long ID_CHOICE1;
		static const long ID_STATICTEXT2;
		static const long ID_BUTTON1;
		static const long ID_STATICBOX4;
		static const long ID_STATICBOX5;
		static const long ID_CHOICE3;
		static const long ID_CHOICE5;
		static const long ID_CHOICE7;
		static const long ID_SPINCTRL1;
		static const long ID_SPINCTRL2;
		static const long ID_SPINCTRL3;
		static const long ID_SPINCTRL4;
		static const long ID_TIMER1;
		//*)

	private:

		//(*Handlers(SensorDialog)
		void OnButton1Click(wxCommandEvent& event);
		void OnButton_Close(wxCommandEvent& event);
		void OnClose(wxCloseEvent& event);
		void OnTimer1Trigger(wxTimerEvent& event);
		void OnChoice_SensorConfig(wxCommandEvent& event);
		void OnSpinCtrl_ModeS1Change(wxSpinEvent& event);
		void OnSpinCtrl_SensorConfig(wxSpinEvent& event);
		//*)

		DECLARE_EVENT_TABLE()

		Daten &daten;

		void setSensorConfig( Daten::ConfigToORB::Data &config, int id, int type, int mode );
		void configAllSensor();
};
#endif
