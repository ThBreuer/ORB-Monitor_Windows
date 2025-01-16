//*******************************************************************
/*!
\author Nils Hoffmann
\date   12.10.2024
*/

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <thread>
#include <chrono>
#include <cstring>
#include <string>
#include <direct.h>

#include "lib.h"

#include "ConsoleDialog.h"

extern "C"{
    #include "python-vm.h"

}
char *name = "program\\program.bin";

extern ConsoleDialog   *dlgPythonConsole;

extern "C"{
  void printConsole(const char* format,...)
  {
   static char str[1024+1];
    va_list argzeiger;

    va_start ( argzeiger, format );
    vsnprintf( str, 1024, format, argzeiger );
    va_end   ( argzeiger );

    if( dlgPythonConsole )
    {
      dlgPythonConsole->print( str );
    }
  }
}
uint8_t buffer[128*1024];

uint8_t* loadFile() {
    std::ifstream file(name, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << name << std::endl;
        printConsole("\2Error: \3Failed to open file: %s\n",name);
        return nullptr;
    }

    file.seekg(0,std::ios::end );

    long int length = file.tellg()-1;
    file.seekg(0,std::ios::beg );

    file.ignore(1);

    std::vector<uint8_t> byteArray(length);

    file.read(reinterpret_cast<char*>(byteArray.data()), length);

    if (!file) {
        std::cerr << "Error reading file." << std::endl;
        printConsole("\2Error: \3Failed to read file: %s\n",name);
        return nullptr;
    }

    file.close();

   // uint8_t* result = (uint8_t*)malloc(byteArray.size() * sizeof(uint8_t));
    std::copy(byteArray.begin(), byteArray.end(), buffer);

    return buffer;
}

PythonVM vm;
int arg = 0;

void startProgramThread()
{
    vm.run(loadFile, arg);
///    conPrintf("2Exit: %d\n", vm.getExitStatus());
///    conPrintf("Exit Type: %s", vm.getExitInfo());
    printConsole("\2Exit: \3(%d) ",vm.getExitStatus());
    printConsole(vm.getExitInfo());
    printConsole("\n");
}

std::thread *programThread = NULL;

int execPython(char *_name, int para)
{
  arg = para;
  name = _name;

  if(vm.isRunning())
  {
    return 0;
  }

  std::thread *programThread = new std::thread(startProgramThread);

  printConsole("\2Start: \3%s\n",name);

  return 0;
}

void stopPython()
{
  if(vm.isRunning())
  {
    vm.stopProgram();

    Sleep(100);

    if( programThread )
    {
      delete programThread;
      programThread = nullptr;
    }
  }
}

bool isPythonRunning()
{
  if( vm.isRunning() )
    return( true );
  return( false );
}
