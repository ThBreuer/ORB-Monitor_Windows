#ifndef VIEWDIALOG_H
#define VIEWDIALOG_H

#include "Daten.h"

//(*Headers(ViewDialog)
#include <wx/checkbox.h>
#include <wx/dialog.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/timer.h>
//*)

class ViewDialog: public wxDialog
{
	public:

		ViewDialog(Daten &daten, wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~ViewDialog();

		void run( void  );

		//(*Declarations(ViewDialog)
		wxCheckBox* CheckBox_D1;
		wxCheckBox* CheckBox_D2;
		wxStaticBox* StaticBox1;
		wxStaticBox* StaticBox2;
		wxStaticBox* StaticBox3;
		wxStaticBox* StaticBox4;
		wxStaticBox* StaticBox5;
		wxStaticBox* StaticBox6;
		wxStaticBox* StaticBox7;
		wxStaticBox* StaticBox8;
		wxStaticBox* StaticBox9;
		wxStaticText* StaticText13;
		wxStaticText* StaticText14;
		wxStaticText* StaticText15;
		wxStaticText* StaticText17;
		wxStaticText* StaticText1;
		wxStaticText* StaticText_InfoS1;
		wxStaticText* StaticText_InfoS2;
		wxStaticText* StaticText_InfoS3;
		wxStaticText* StaticText_InfoS4;
		wxStaticText* StaticText_PosM1;
		wxStaticText* StaticText_PosM2;
		wxStaticText* StaticText_PosM3;
		wxStaticText* StaticText_PosM4;
		wxStaticText* StaticText_PowerM1;
		wxStaticText* StaticText_PowerM2;
		wxStaticText* StaticText_PowerM3;
		wxStaticText* StaticText_PowerM4;
		wxStaticText* StaticText_SpeedM1;
		wxStaticText* StaticText_SpeedM2;
		wxStaticText* StaticText_SpeedM3;
		wxStaticText* StaticText_SpeedM4;
		wxStaticText* StaticText_ValueS1;
		wxStaticText* StaticText_ValueS2;
		wxStaticText* StaticText_ValueS3;
		wxStaticText* StaticText_ValueS4;
		wxTimer Timer1;
		//*)

	protected:

		//(*Identifiers(ViewDialog)
		static const long ID_STATICBOX4;
		static const long ID_STATICBOX3;
		static const long ID_STATICBOX2;
		static const long ID_STATICBOX1;
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT2;
		static const long ID_STATICTEXT3;
		static const long ID_STATICTEXT4;
		static const long ID_STATICTEXT5;
		static const long ID_STATICTEXT6;
		static const long ID_STATICTEXT7;
		static const long ID_STATICTEXT8;
		static const long ID_STATICTEXT9;
		static const long ID_STATICTEXT10;
		static const long ID_STATICTEXT11;
		static const long ID_STATICTEXT12;
		static const long ID_STATICTEXT13;
		static const long ID_STATICTEXT14;
		static const long ID_STATICTEXT15;
		static const long ID_STATICBOX5;
		static const long ID_STATICTEXT16;
		static const long ID_STATICTEXT17;
		static const long ID_STATICBOX6;
		static const long ID_CHECKBOX1;
		static const long ID_CHECKBOX2;
		static const long ID_STATICBOX7;
		static const long ID_STATICBOX8;
		static const long ID_STATICBOX9;
		static const long ID_STATICTEXT18;
		static const long ID_STATICTEXT19;
		static const long ID_STATICTEXT20;
		static const long ID_STATICTEXT21;
		static const long ID_STATICTEXT22;
		static const long ID_STATICTEXT23;
		static const long ID_STATICTEXT24;
		static const long ID_STATICTEXT25;
		static const long ID_TIMER1;
		//*)

	private:

		//(*Handlers(ViewDialog)
		void OnButton1Click(wxCommandEvent& event);
		void OnTimer1Trigger(wxTimerEvent& event);
		void OnClose(wxCloseEvent& event);
		//*)

		DECLARE_EVENT_TABLE()

		Daten &daten;
};

#endif
