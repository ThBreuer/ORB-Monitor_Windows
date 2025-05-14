//*******************************************************************
/*!
\file   Main.h
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   25.11.2023

License: See file "LICENSE"
*/

//*******************************************************************
#ifndef MAIN_H
#define MAIN_H

//*******************************************************************
#include <wx/timer.h>

//*******************************************************************
#include "ComPort.h"
#include "FlashDialog.h"
#include "SettingsDialog.h"
#include "MotorDialog.h"
#include "SensorDialog.h"
#include "ViewDialog.h"
#include "ConsoleDialog.h"
#include "Flash.h"
#include "Daten.h"

#include "lib.h"
#include "Sys/UDPclient.h"
#include "Sys/UDPserver.h"

#include "ORB_Monitor.h"

#include "Command.h"

//*******************************************************************
//(*Headers(MainFrame)
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/choice.h>
#include <wx/filedlg.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/snglinst.h>
#include <wx/statbox.h>
#include <wx/statline.h>
#include <wx/stattext.h>
#include <wx/statusbr.h>
#include <wx/timer.h>
#include <wx/utils.h>
//*)

class App;

//*******************************************************************
//
// MainFrame
//
//*******************************************************************
class MainFrame: public wxFrame
{
  public:
    //---------------------------------------------------------------
    MainFrame(App &appIn, wxWindow* parent,wxWindowID id = -1);

    //---------------------------------------------------------------
    virtual ~MainFrame();

  private:
    //---------------------------------------------------------------
    //(*Handlers(MainFrame)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnTimer1Trigger(wxTimerEvent& event);
    void OnMenu_COMport_Selected(wxCommandEvent& event);
    void OnButtonClick_Download(wxCommandEvent& event);
    void OnMenuFlashDialog_Selected(wxCommandEvent& event);
    void OnButton_StartRobo_Click(wxCommandEvent& event);
    void OnButton_StopRobo_Click(wxCommandEvent& event);
    void OnMenuQuitt(wxCommandEvent& event);
    void OnMenuQuit(wxCommandEvent& event);
    void OnClose(wxCloseEvent& event);
    void OnButtonClick_DownloadData(wxCommandEvent& event);
    void OnButtonClick_DownloadProgram(wxCommandEvent& event);
    void OnChoicePortSelect(wxCommandEvent& event);
    void OnButton5Click(wxCommandEvent& event);
    void OnButton7Click(wxCommandEvent& event);
    void OnButton9Click(wxCommandEvent& event);
    void OnButton9Click1(wxCommandEvent& event);
    void OnButton_StartKalib_Click(wxCommandEvent& event);
    void OnButton_ESCClick(wxCommandEvent& event);
    void OnButton_PlusClick(wxCommandEvent& event);
    void OnButton_MinusClick(wxCommandEvent& event);
    void OnButton_OKClick(wxCommandEvent& event);
    void OnButton2Click(wxCommandEvent& event);
    void OnTextCtrl_NameTextEnter(wxCommandEvent& event);
    void OnButton13Click(wxCommandEvent& event);
    void OnButton9Click2(wxCommandEvent& event);
    void OnButton11Click(wxCommandEvent& event);
    void OnButton16Click(wxCommandEvent& event);
    void OnButton8Click(wxCommandEvent& event);
    void OnButton_PlusClick1(wxCommandEvent& event);
    void OnMenu_Settings(wxCommandEvent& event);
    void OnButton_B3Click(wxCommandEvent& event);
    void OnButton_B5Click(wxCommandEvent& event);
    void OnTimerFastTrigger(wxTimerEvent& event);
    void OnTimerSlowTrigger(wxTimerEvent& event);
    void OnButton_ESCClick1(wxCommandEvent& event);
    void OnButton_ESCClick2(wxCommandEvent& event);
    void OnButton_ESCClick3(wxCommandEvent& event);
    void OnButton_MinusClick1(wxCommandEvent& event);
    void OnButton_OKClick1(wxCommandEvent& event);
    void OnButton_OKClick2(wxCommandEvent& event);
    void OnMenuMotorTest(wxCommandEvent& event);
    void OnMenu_MotorTest(wxCommandEvent& event);
    void OnMenuFirmwareUpdate(wxCommandEvent& event);
    void OnMenu_FirmwareUpdate(wxCommandEvent& event);
    void OnMenu_SensorTest(wxCommandEvent& event);
    void OnMenu_ViewDialog(wxCommandEvent& event);
    void OnMenu_Layout(wxCommandEvent& event);
    void OnCheckBox1Click(wxCommandEvent& event);
    void OnCheckBox_RunPythonLocalClick(wxCommandEvent& event);
    void OnMenuItem_PythonConsole(wxCommandEvent& event);
    void OnMenuItem_Doc_Cpp(wxCommandEvent& event);
    void OnMenuItem_Doc_MicroPython(wxCommandEvent& event);
    //*)

    //(*Identifiers(MainFrame)
    static const long ID_STATICBOX10;
    static const long ID_BUTTON14;
    static const long ID_BUTTON7;
    static const long ID_BUTTON3;
    static const long ID_STATICTEXT7;
    static const long ID_STATICTEXT24;
    static const long ID_STATICTEXT28;
    static const long ID_STATICTEXT32;
    static const long ID_BUTTON4;
    static const long ID_BUTTON5;
    static const long ID_CHOICE1;
    static const long ID_BUTTON9;
    static const long ID_STATICTEXT_INFO;
    static const long ID_BUTTON8;
    static const long ID_BUTTON11;
    static const long ID_BUTTON12;
    static const long ID_BUTTON13;
    static const long ID_BUTTON15;
    static const long ID_BUTTON16;
    static const long ID_BUTTON17;
    static const long ID_BUTTON18;
    static const long ID_BUTTON19;
    static const long ID_BUTTON20;
    static const long ID_BUTTON21;
    static const long ID_BUTTON22;
    static const long ID_BUTTON_PLUS;
    static const long ID_BUTTON_MINUS;
    static const long ID_BUTTON6;
    static const long ID_BUTTON2;
    static const long ID_BUTTON_ESC;
    static const long ID_BUTTON_OK;
    static const long ID_BUTTON23;
    static const long ID_STATICTEXT_VCC;
    static const long ID_STATICLINE1;
    static const long ID_STATICLINE2;
    static const long ID_CHECKBOX1;
    static const long ID_STATICTEXT1;
    static const long ID_STATICTEXT2;
    static const long ID_MENU_LAYOUT;
    static const long ID_MENU_SETTINGS;
    static const long ID_MENUITEM1;
    static const long ID_MENUITEM2;
    static const long ID_MENU_MOTORTEST;
    static const long ID_MENUITEM4;
    static const long ID_MENUITEM3;
    static const long ID_MENU_PYTHON_CONSOLE;
    static const long ID_MENUITEM5;
    static const long ID_MENUITEM6;
    static const long ID_STATUSBAR;
    static const long ID_TIMER2;
    //*)

    //(*Declarations(MainFrame)
    wxButton* Button2;
    wxButton* Button3;
    wxButton* Button4;
    wxButton* Button5;
    wxButton* Button_B10;
    wxButton* Button_B11;
    wxButton* Button_B12;
    wxButton* Button_B1;
    wxButton* Button_B2;
    wxButton* Button_B3;
    wxButton* Button_B4;
    wxButton* Button_B5;
    wxButton* Button_B6;
    wxButton* Button_B7;
    wxButton* Button_B8;
    wxButton* Button_B9;
    wxButton* Button_C1;
    wxButton* Button_DownloadProg;
    wxButton* Button_ESC;
    wxButton* Button_Minus;
    wxButton* Button_OK;
    wxButton* Button_Plus;
    wxButton* Button_Start_0;
    wxButton* Button_Start_1;
    wxButton* Button_Stop;
    wxCheckBox* CheckBox_RunPythonLocal;
    wxChoice* ChoicePort;
    wxFileDialog* FileDialog1;
    wxMenu* Menu3;
    wxMenu* Menu4;
    wxMenu* Menu5;
    wxMenu* Menu6;
    wxMenuBar* MenuBar1;
    wxMenuItem* Menu1;
    wxMenuItem* Menu2;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem3;
    wxMenuItem* MenuItem4;
    wxMenuItem* MenuItem5;
    wxMenuItem* MenuItem6;
    wxMenuItem* MenuItem7;
    wxMenuItem* MenuItem8;
    wxSingleInstanceChecker SingleInstanceChecker1;
    wxStaticBox* StaticBox10;
    wxStaticLine* StaticLine1;
    wxStaticLine* StaticLine2;
    wxStaticText* StaticText1;
    wxStaticText* StaticText_Info;
    wxStaticText* StaticText_ProgFile;
    wxStaticText* StaticText_Vcc;
    wxStaticText* debugText0;
    wxStaticText* debugText1;
    wxStaticText* debugText2;
    wxStaticText* debugText3;
    wxStatusBar* StatusBar;
    wxTimer TimerSlow;
    //*)

    DECLARE_EVENT_TABLE()

    //***************************************************************
    class ButtonExt
    {
      public:
        //-----------------------------------------------------------
        ButtonExt( wxButton *btnIn,
                   void (MainFrame::*method)(wxMouseEvent &),
                   MainFrame *eventHandler )
        {
          btn = btnIn;
          btn->Bind(wxEVT_LEFT_DOWN, method, eventHandler);
          btn->Bind(wxEVT_LEFT_UP,   method, eventHandler);
          strncpy(name,btn->GetLabel(),30);
        }

        //-----------------------------------------------------------
        void setLabel(char *txt)
        {
          int cnt=0;
          char txt2[100];

          txt2[0]=0;
          unsigned unicode = 8598;

          while( *txt != 0 )
          {
            cnt++;
            if( *txt == '&' && *(txt+1) == '#')
            {
              txt += 2;
              char tmp[10+1] = {0};
              int  pos = 0;
              while( pos < 10 && *txt != ';' && *txt != 0 )
              {
                tmp[pos++]=*txt;
                tmp[pos]=0;
                txt++;
              }
              unicode = atoi(tmp);
            }
            else
            {
              unicode = *txt;
            }
            txt++;

            char utxt[16];
            if( unicode <= 0x7F )
            {
              utxt[0]=unicode;
              utxt[1]=0;
            }
            else if( unicode <= 0x7FF)
            {
              utxt[0] = 0xC0 | ((unicode>>6)&0x1F);
              utxt[1] = 0x80 | ((unicode>>0)&0x3F);
              utxt[2] = 0;
            }
            else if( unicode <= 0xFFFF )
            {
              utxt[0] = 0xE0 | ((unicode>>12)&0x1F);
              utxt[1] = 0x80 | ((unicode>>6)&0x3F);
              utxt[2] = 0x80 | ((unicode>>0)&0x3F);
              utxt[3] = 0;
            }
            else if( unicode <= 0x10FFFF)
            {
              utxt[0] = 0xF0 | ((unicode>>18)&0x1F);
              utxt[1] = 0x80 | ((unicode>>12)&0x3F);
              utxt[2] = 0x80 | ((unicode>> 6)&0x3F);
              utxt[3] = 0x80 | ((unicode>> 0)&0x3F);
              utxt[4] = 0;
            }
            else
            {
              utxt[1] = '?';
              utxt[2] = 0;
            }
            strcat(txt2,utxt);
          }
          if( strlen(txt2) > 0 )
          {
            btn->SetLabel(wxString::FromUTF8(txt2));
            if( cnt == 1 )
            {
              wxFont font(18, wxFONTFAMILY_DEFAULT, wxNORMAL, wxNORMAL);
              btn->SetFont(font);
            }
            else
            {
              wxFont font(10, wxFONTFAMILY_DEFAULT, wxNORMAL, wxNORMAL);
              btn->SetFont(font);
            }
            btn->Show();
          }
          else
            btn->Hide();
        }

        //-----------------------------------------------------------
        unsigned long getId()
        {
          return( btn->GetId() );
        }

        //-----------------------------------------------------------
        char *getName()
        {
          return( name );
        }

        wxButton *btn;
        char name[32];

    }; //class ButtonExt
    //***************************************************************

    //---------------------------------------------------------------
    void OnMouseEvent(wxMouseEvent& event);

    //---------------------------------------------------------------
    void CloseFrame( void );

    //---------------------------------------------------------------
    void setKeyLayout( const char *file );


        //---------------------------------------------------------------
        char *getReducedProgFileName( char *str , int len)
        {
          static char ret[1024]; //len+6+1];

          if( len <= 6 )
            len = 6;
          if( strlen(str)>len )
          {  // str=12, len=8, 8-6=2 frei => idx = 10,11
            int idx = strlen(str)-(len-6);
            sprintf(ret,"%.3s...%s",&str[0],&str[idx ] );

            return( ret );
          }

          else
          {
            return( str );
          }

        }

  private:
    //---------------------------------------------------------------
    App              &app;
    ORB_Monitor       orbMonitor;
    UDPserver         udp;
    Command::Handler  commandHandler;

    ComPort      *comPort;
    ButtonExt    *btn[23];
    char          layoutFileName[1024];

  public:
    FlashDialog    *dlgFlash     = NULL;
    SettingsDialog *dlgSettings;
    MotorDialog *dlgMotorTest;
    SensorDialog *dlgSensorTest;
    ViewDialog   *dlgView;

    bool isInit = false;

}; //class MainFrame

// \todo Why included here ?
#include "FlashDialog.h"

#endif // MAIN_H
