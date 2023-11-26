//*******************************************************************
/*!
\file   FlashDialog.h
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   25.11.2023

License: See file "LICENSE"
*/

//*******************************************************************
#ifndef FLASHDIALOG_H
#define FLASHDIALOG_H

//*******************************************************************
//(*Headers(FlashDialog)
#include <wx/dialog.h>
#include <wx/stattext.h>
#include <wx/timer.h>
//*)
//*******************************************************************

//*******************************************************************
#include "Flash.h"

//*******************************************************************
//
// FlashDialog
//
//*******************************************************************
class FlashDialog: public wxDialog
{
  public:
    //---------------------------------------------------------------
    FlashDialog( char       *fileProg,
                 cISC       &ipcIn,
                 wxWindow   *parent,
                 wxWindowID  id = wxID_ANY );

    //---------------------------------------------------------------
    virtual ~FlashDialog();

    //---------------------------------------------------------------
    void run( int id  );

    //***************************************************************
    //(*Declarations(FlashDialog)
    wxStaticText* StaticText1;
    wxStaticText* StaticText2;
    wxStaticText* StaticText_File;
    wxStaticText* StaticText_Status;
    wxTimer Timer1;
    //*)
    //***************************************************************

  public:
    //---------------------------------------------------------------
    bool        isDownload;
    FlashTool   flashTool;
    char        fileNameProg[512];
    int         fileId;

  protected:
    //***************************************************************
    //(*Identifiers(FlashDialog)
    static const long ID_STATICTEXT1;
    static const long ID_STATICTEXT2;
    static const long ID_STATICTEXT3;
    static const long ID_STATICTEXT4;
    static const long ID_TIMER1;
    //*)
    //***************************************************************

  private:
    //***************************************************************
    //(*Handlers(FlashDialog)
    void OnTimer1Trigger(wxTimerEvent& event);
    void OnTimer1Trigger1(wxTimerEvent& event);
    void OnInit(wxInitDialogEvent& event);
    void OnTimer2Trigger(wxTimerEvent& event);
    void OnButton1Click(wxCommandEvent& event);
    void OnClose(wxCloseEvent& event);
    void OnCloseSettings(wxCloseEvent& event);
    //*)
    //***************************************************************

    DECLARE_EVENT_TABLE()
};

#endif
