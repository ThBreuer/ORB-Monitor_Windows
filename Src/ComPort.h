//*******************************************************************
/*!
\file   ComPort.h
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   25.11.2023

License: See file "LICENSE"
*/

//*******************************************************************
#ifndef COMPORT_H
#define COMPORT_H

//*******************************************************************
#include <wx/choice.h>

//*******************************************************************
//
// ComPort
//
//*******************************************************************
class ComPort
{
  public:
    //---------------------------------------------------------------
    ComPort( wxChoice* Choice , const char *defPortName );

    //---------------------------------------------------------------
    virtual ~ComPort();

    //---------------------------------------------------------------
    const char *getPort();

  private:
    //---------------------------------------------------------------
    void GetPortList();

   const wchar_t *getFriendlyName( wchar_t *portIn );

  private:
    //---------------------------------------------------------------
    wxChoice* Choice;
    wxString  port;
};

#endif
