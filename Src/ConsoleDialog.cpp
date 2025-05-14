#include "lib.h"
#include "ConsoleDialog.h"
#include "Daten.h"


//(*InternalHeaders(ConsoleDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(ConsoleDialog)
const long ConsoleDialog::ID_TEXTCTRL1 = wxNewId();
const long ConsoleDialog::ID_BUTTON1 = wxNewId();
const long ConsoleDialog::ID_TIMER1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(ConsoleDialog,wxDialog)
	//(*EventTable(ConsoleDialog)
	//*)
END_EVENT_TABLE()

//-------------------------------------------------------------------
ConsoleDialog::ConsoleDialog(/*Fifo<char> &fifo,*/ wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
//: fifo( fifo)
{
	//(*Initialize(ConsoleDialog)
	Create(parent, id, _("Python Console"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxSYSTEM_MENU|wxRESIZE_BORDER|wxCLOSE_BOX|wxDIALOG_NO_PARENT|wxMINIMIZE_BOX, _T("id"));
	SetClientSize(wxSize(621,417));
	Move(wxDefaultPosition);
	TextCtrl_Console = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxPoint(8,8), wxSize(608,376), wxTE_MULTILINE|wxTE_READONLY|wxTE_RICH|wxTE_CHARWRAP|wxTE_WORDWRAP|wxBORDER_NONE|wxFULL_REPAINT_ON_RESIZE, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	TextCtrl_Console->SetMinSize(wxSize(-1,-1));
	TextCtrl_Console->SetMaxSize(wxSize(0,0));
	Button1 = new wxButton(this, ID_BUTTON1, _("Clear"), wxPoint(544,392), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	Timer1.SetOwner(this, ID_TIMER1);
	Timer1.Start(20, false);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ConsoleDialog::OnButton1_ClearClick);
	Connect(ID_TIMER1,wxEVT_TIMER,(wxObjectEventFunction)&ConsoleDialog::OnTimer1Trigger);
	//*)

}

//-------------------------------------------------------------------
ConsoleDialog::~ConsoleDialog()
{
	//(*Destroy(ConsoleDialog)
	//*)
}

//-------------------------------------------------------------------
void ConsoleDialog::run( void )
{
  if( !Show() )
  {
    Raise();
    Restore();
  }
}

//-------------------------------------------------------------------
void ConsoleDialog::print(char *str)
{
  while( *str )
  {
    Daten::fifo<<*str;
    str++;
  }
  Sleep(20);
}

//-------------------------------------------------------------------
void ConsoleDialog::OnTimer1Trigger(wxTimerEvent& event)
{
  char c;

  while( Daten::fifo >> c )
  {

    switch( c )
    {
      case 1: TextCtrl_Console->SetDefaultStyle(wxTextAttr(*wxBLACK)); break;
      case 2: TextCtrl_Console->SetDefaultStyle(wxTextAttr(*wxRED  )); break;
      case 3: TextCtrl_Console->SetDefaultStyle(wxTextAttr(*wxBLUE )); break;
      case 4: TextCtrl_Console->SetDefaultStyle(wxTextAttr(*wxGREEN)); break;
      case '\n':
      case '\r':
        // todo oder immer machen?
        while( TextCtrl_Console->GetNumberOfLines() > 500 )
        {
          long lineLen;
          lineLen = TextCtrl_Console->GetLineLength(0);
          TextCtrl_Console->Remove(0,lineLen+1);
        }

        TextCtrl_Console->SetDefaultStyle(wxTextAttr(*wxBLACK));
        // no break

      default:
        TextCtrl_Console->AppendText(c);
        break;
    }
  }

}

//-------------------------------------------------------------------
void ConsoleDialog::OnButton1_ClearClick(wxCommandEvent& event)
{
  TextCtrl_Console->Clear();
}
