//*******************************************************************
/*!
\file   SettingsDialog.h
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   25.11.2023

License: See file "LICENSE"
*/

//*******************************************************************
#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

//*******************************************************************
#include "ComPort.h"
#include "FlashDialog.h"
#include "SettingsDialog.h"
#include "Flash.h"
#include "Daten.h"

//(*Headers(SettingsDialog)
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/dialog.h>
#include <wx/spinctrl.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

//*******************************************************************
/*!
\class   SettingsDialog

*/
class SettingsDialog: public wxDialog
{
  public:

    SettingsDialog( Daten      &daten,
                    wxWindow   *parent,
                    wxWindowID  id = wxID_ANY );

    virtual ~SettingsDialog();

    void run( void  );

    void refresh();

    //(*Declarations(SettingsDialog)
    wxButton* Button_Send;
    wxButton* Button_Close;
    wxCheckBox* CheckBox_ClearMemory;
    wxSpinCtrlDouble* SpinCtrl_VccOK;
    wxSpinCtrlDouble* SpinCtrl_VccLow;
    wxStaticText* StaticText1;
    wxStaticText* StaticText2;
    wxStaticText* StaticText3;
    wxStaticText* StaticText4;
    wxStaticText* StaticText5;
    wxStaticText* StaticText6;
    wxStaticText* StaticText7;
    wxStaticText* StaticText8;
    wxStaticText* StaticText_Board;
    wxStaticText* StaticText_ORB_Version;
    wxStaticText* StaticText_Version;
    wxTextCtrl* TextCtrl_Name;
    //*)

  protected:

    //(*Identifiers(SettingsDialog)
    static const long ID_BUTTON_CLOSE;
    static const long ID_BUTTON_SEND;
    static const long ID_TEXTCTRL1;
    static const long ID_STATICTEXT1;
    static const long ID_STATICTEXT2;
    static const long ID_STATICTEXT3;
    static const long ID_STATICTEXT4;
    static const long ID_STATICTEXT6;
    static const long ID_STATICTEXT7;
    static const long ID_STATICTEXT5;
    static const long ID_STATICTEXT8;
    static const long ID_CHECKBOX1;
    static const long ID_SPINCTRL_VCC_OK;
    static const long ID_SPINCTRL_VCC_LOW;
    static const long ID_STATICTEXT9;
    static const long ID_STATICTEXT10;
    static const long ID_STATICTEXT11;
    //*)

  private:

    //(*Handlers(SettingsDialog)
    void OnClose(wxCloseEvent& event);
    void OnButton_Send(wxCommandEvent& event);
    void OnButton_Close(wxCommandEvent& event);
    void OnTextCtrl_Enter(wxCommandEvent& event);
    void OnSpinCtrlChange_VccOK(wxSpinDoubleEvent& event);
    void OnSpinCtrlChange_VccLow(wxSpinDoubleEvent& event);
    //*)

    Daten &daten;

    Daten::SettingsToORB::Data loc;
    DECLARE_EVENT_TABLE()
};

#endif
