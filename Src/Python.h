//*******************************************************************
/*!
\file   Python.h
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   15.11.2024

License: See file "LICENSE"
*/

//*******************************************************************
#ifndef PYTHON_H
#define PYTHON_H

//*******************************************************************
int execPython(char *file, int arg);
int stopPython();
bool isPythonRunning();

#endif // MAIN_H
