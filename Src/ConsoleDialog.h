#ifndef CONSOLEDIALOG_H
#define CONSOLEDIALOG_H

//(*Headers(ConsoleDialog)
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/textctrl.h>
#include <wx/timer.h>
//*)


#include "lib.h"

//*******************************************************************
class ConsoleDialog: public wxDialog
{
	public:
    //---------------------------------------------------------------
		ConsoleDialog( wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~ConsoleDialog();

		void run( void  );
		void print(char *str);

		//(*Declarations(ConsoleDialog)
		wxButton* Button1;
		wxTextCtrl* TextCtrl_Console;
		wxTimer Timer1;
		//*)

	protected:

		//(*Identifiers(ConsoleDialog)
		static const long ID_TEXTCTRL1;
		static const long ID_BUTTON1;
		static const long ID_TIMER1;
		//*)

	private:

		//(*Handlers(ConsoleDialog)
		void OnTextCtrl_ConsoleText(wxCommandEvent& event);
		void OnTimer1Trigger(wxTimerEvent& event);
		void OnButton1_ClearClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
