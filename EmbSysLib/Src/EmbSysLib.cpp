//*******************************************************************
/*!
\file   EmbSysLib.cpp
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   23.03.2016

License: See file "LICENSE"

\brief Summary of complete library code
*/

//*******************************************************************
#include "EmbSysLib.h"

//*******************************************************************
#include "System.cpp"

//===================================================================
// MCU
//===================================================================
#include "Mcu.cpp"

//===================================================================
// Std
//===================================================================
#include "Std/Std.cpp"
#include "Std/CRC.cpp"
#include "Std/List.cpp"
#include "Std/DataPointer.cpp"
#include "Std/Fifo.cpp"
#include "Std/Sequence.cpp"
#include "Std/Report.cpp"
#include "Std/Flag.cpp"
#include "Std/Timer.cpp"
#include "Std/SharedMem.cpp"

//===================================================================
// Hardware/Common
//===================================================================
#include "Hardware/Common/Analog/Adc.cpp"
#include "Hardware/Common/Analog/Dac.cpp"
#include "Hardware/Common/Display/Type/Font.cpp"
#include "Hardware/Common/Display/Type/Bitmap.cpp"
#include "Hardware/Common/Display/DisplayChar.cpp"
#include "Hardware/Common/Display/DisplayGraphic.cpp"
#include "Hardware/Common/I2C/I2Cmaster.cpp"
#include "Hardware/Common/I2C/I2Cmaster_Emul.cpp"
#include "Hardware/Common/Memory/Memory.cpp"
#include "Hardware/Common/Memory/MemoryImage.cpp"
#include "Hardware/Common/Port/Port.cpp"
#include "Hardware/Common/Port/ExtInt.cpp"
#include "Hardware/Common/Rtc/Rtc.cpp"
#include "Hardware/Common/SPI/SPImaster.cpp"
#include "Hardware/Common/Timer/Timer.cpp"
#include "Hardware/Common/Timer/Encoder.cpp"
#include "Hardware/Common/Display/Touch.cpp"
#include "Hardware/Common/Uart/Uart.cpp"
#include "Hardware/Common/USB/USBdevice.cpp"
#include "Hardware/Common/USB/USBdevice/USBcontrol.cpp"
#include "Hardware/Common/USB/USBdevice/USBdescriptor.cpp"
#include "Hardware/Common/USB/USBdevice/USBendpoint.cpp"
#include "Hardware/Common/USB/USBdevice/USBinterface.cpp"
#include "Hardware/Common/USB/USBhost.cpp"

//===================================================================
// Device/Digital
//===================================================================
//*******************************************************************
// Device/Analog
//*****************************************************************
#include "Device/Analog/devAnalog.cpp"
#include "Device/Analog/devAnalogIn.cpp"
#include "Device/Analog/devAnalogInADC.cpp"
#include "Device/Analog/devAnalogOut.cpp"
#include "Device/Analog/devAnalogOutDAC.cpp"
#include "Device/Analog/devAnalogOutPWM.cpp"

//*******************************************************************
// DEVICE/MEMORY
//*******************************************************************
#include "Device/Memory/devMemory.cpp"

//*******************************************************************
// DEVICE/MOTOR
//*******************************************************************
#include "Device/Motor/devMotor.cpp"
#include "Device/Motor/devMotorDirection.cpp"
#include "Device/Motor/devMotorBipolar.cpp"



#include "Device/Digital/Digital.cpp"
#include "Device/Screen/ScreenChar.cpp"
#include "Device/Screen/ScreenGraphic.cpp"
#include "Device/Pointer/Pointer.cpp"
#include "Device/Task/TaskManager.cpp"
#include "Device/Terminal/Terminal.cpp"

//===================================================================
// Control
//===================================================================
#include "Control/DigitalButton.cpp"
#include "Control/DigitalEncoder.cpp"
#include "Control/DigitalEncoderJoystick.cpp"
#include "Control/DigitalEncoderRotaryknob.cpp"
#include "Control/DigitalIndicator.cpp"

//===================================================================
