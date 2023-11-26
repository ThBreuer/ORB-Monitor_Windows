//*******************************************************************
/*!
\file   ComPort.cpp
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   25.11.2023

License: See file "LICENSE"
*/

//*******************************************************************
#include "ComPort.h"

#include <wx/stattext.h>
#include <wx/choice.h>
#include <wx/button.h>
#include <wx/dialog.h>

#include <Setupapi.h>

#include <windows.h>
#include <initguid.h>
#include <devguid.h>
#include <setupapi.h>

//*******************************************************************
//-------------------------------------------------------------------
void char2wchar(wchar_t *out, char *in)
{
    unsigned i=0;
    for(i=0;in != NULL && i<strlen(in);i++)
    {
         out[i] = in[i];
    }
    out[i] = 0;
}


//*******************************************************************
//
// cRegistry
//
//*******************************************************************
/*
  "Dazu wird der Schlüssel zuerst mittels Externer Link!RegOpenKeyEx geöffnet.
  Mittels Externer Link!RegQueryInfoKey kann die Anzahl der vorhanden Einträge sowie
  die maximale Länge des Schlüsselnamens (in Zeichen) und des Schlüsselwertes(in Bytes) ermittelt werden.
  Mit diesen Informationen kann mittels Externer Link!RegEnumValue über die einzelnen Einträge iteriert werden.
  Der Schlüsselname bezeichnet das Gerät, das den Port zur Verfügung stellt.
  Der Schlüsselwert bezeichnet den COM-Port selbst.
  Nachdem der Schlüssel ausgelesen wurde, muss dieser mittels Externer Link!RegCloseKey geschlossen werden."

  see: http://www.freebasic-portal.de/code-beispiele/system/serielle-schnittstellen-com-ports-unter-windows-ermitteln-248.html
*/
//-------------------------------------------------------------------
class cRegistry
{
  private:
    //---------------------------------------------------------------
    HKEY hKey;
    int idx;
    wchar_t subKey    [1024];

  public:
    //---------------------------------------------------------------
    cRegistry( const wchar_t *subKeyIn, const wchar_t *xKey, REGSAM samDesired )
    {
      wcscpy( subKey, subKeyIn);
      wcscat( subKey, xKey);

     //int err =
      RegOpenKeyEx( HKEY_LOCAL_MACHINE,
                    subKey,
                    0,
                    KEY_READ,
                    &hKey );
      idx = 0;
    }

    //---------------------------------------------------------------
    wchar_t *getNextSubKey()
    {
      static wchar_t key[1024];

      wchar_t rSubKey[1024];

      if( RegEnumKeyW( hKey, idx++, rSubKey, 1024 ) == 0 )
      {
        wcscpy(key,subKey);
        wcscat(key,L"\\");
        wcscat(key,rSubKey);
        return( key );
      }
      return( NULL );
    }

    //---------------------------------------------------------------
    BYTE *getNextValue()
    {
      static BYTE val[1024];

      wchar_t key[1024];
      long unsigned type   = REG_SZ;
      long unsigned keyLen = 1024;
      long unsigned  valLen = 1024;

      if( RegEnumValue( hKey,
                        idx++,
                        key,
                        &keyLen,
                        0 ,
                        &type,
                        val,
                        &valLen) == 0 )
      {
       return( val );
      }
      return( NULL );
    }

    //---------------------------------------------------------------
    BYTE *getValue( const wchar_t *name )
    {
      static BYTE val[1024];

      wchar_t key[1024];

      int idx = 0;
      while(1)
      {
        long unsigned type   = REG_SZ;
        long unsigned  keyLen = 1024;
        long unsigned  valLen = 1024;

        if( RegEnumValue( hKey,
                          idx++,
                          key,
                          &keyLen,
                          0 ,
                          &type,
                          (unsigned char*)val,
                          &valLen) )
        {
           break;
        }
        else
        {
          if( wcscmp(key,name) == 0 )
          {
            return(val);
          }
        }
      }
      return( NULL );
    }

    //---------------------------------------------------------------
    ~cRegistry()
    {
       RegCloseKey( hKey );
    }
};


//*******************************************************************
//
// ComPort
//
//*******************************************************************
//-------------------------------------------------------------------
ComPort::ComPort( wxChoice* ChoiceIn, const char *defPortName  )
{
  Choice = ChoiceIn;

  Choice->Clear       ( );
  Choice->Append      ( _(" no port") );
  Choice->Append      ( _("USB") );
  Choice->SetSelection( 0 );

  GetPortList();

  for( unsigned i=0;i<Choice->GetCount();i++)
  {
    if( strnicmp( Choice->GetString(i), defPortName, strlen(defPortName)) == 0 )
    {
      Choice->SetSelection( i );
      break;
    }
  }
}

//-------------------------------------------------------------------
ComPort::~ComPort()
{
}

//-------------------------------------------------------------------
void ComPort::GetPortList()
{
  cRegistry r(L"HARDWARE\\DEVICEMAP\\SERIALCOMM",L"",KEY_QUERY_VALUE);

  while( true )
  {
    WCHAR comPort[32];
    WCHAR *val = (wchar_t*)r.getNextValue();
    if( val == NULL )
    {
      break;
    }
    swprintf(comPort,L"%-5ls | %-20ls", val, getFriendlyName( val ));
    Choice->Append(comPort);
  }
}

//-------------------------------------------------------------------
const wchar_t *ComPort::getFriendlyName(wchar_t *portIn)
{
  static wchar_t friendlyName[1024];
  wcscpy(friendlyName,L"");

  wchar_t port[1024];
  wcscpy(port,portIn);

  SP_DEVINFO_DATA devInfoData = {};
  devInfoData.cbSize = sizeof(devInfoData);

  // get the tree containing the info for the ports
  HDEVINFO hDeviceInfo = SetupDiGetClassDevs(&GUID_DEVCLASS_PORTS,
                                             0,
                                             NULL,
                                             DIGCF_PRESENT );
  if (hDeviceInfo == INVALID_HANDLE_VALUE)
  {
      return(L"");
  }

  // iterate over all the devices in the tree
  int nDevice = 0;
  while (SetupDiEnumDeviceInfo(hDeviceInfo,            // Our device tree
                               nDevice++,            // The member to look for
                               &devInfoData))
  {
    DWORD regDataType;
    WCHAR text[1024];
    DWORD  len=0;

    if (SetupDiGetDeviceRegistryProperty(hDeviceInfo, &devInfoData, SPDRP_HARDWAREID, &regDataType, (PBYTE)text, 1024, &len))
    {
      wchar_t subKey[1024];

      //swprintf(subKey,L"SYSTEM\\CurrentControlSet\\Enum\\%s",text);
      wcscpy( subKey, L"SYSTEM\\CurrentControlSet\\Enum\\");
      wcscat( subKey, text);

      cRegistry r0(subKey,L"",KEY_ENUMERATE_SUB_KEYS);

      wchar_t *key;

      while( (key = r0.getNextSubKey()) != NULL )
      {
        cRegistry r1( key,L"\\Device Parameters", KEY_QUERY_VALUE);

        if( wcscmp(port,(wchar_t*)r1.getValue(L"PortName")) == 0 )
        {
          wchar_t *btid = (wchar_t*)r1.getValue(L"Bluetooth_UniqueID");
          if( btid != NULL )
          {
            wchar_t str[1024];

            wcstok(btid,L"#");
            //swscanf(wcstok(NULL,L"#"),L"%[^_]",str);
            wcscpy(str,wcstok(NULL,L"'"));
            wcstok(str,L"_");

            cRegistry r2(L"SYSTEM\\CurrentControlSet\\Services\\BTHPORT\\Parameters\\Devices\\",str,KEY_QUERY_VALUE);

            char2wchar(friendlyName,(char*)r2.getValue(L"Name"));
            return(friendlyName);
          }
        }
      }
    }
  }
  return(L"");
}

//-------------------------------------------------------------------
const char *ComPort::getPort()
{
   port = Choice->GetString( Choice->GetSelection() );
   return( port.GetData().AsChar() );
}
