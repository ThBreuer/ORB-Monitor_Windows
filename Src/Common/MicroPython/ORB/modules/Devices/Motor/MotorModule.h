//*******************************************************************
/*!
\author Nils Hoffmann
\date   12.10.2024
*/

#include "py/obj.h"
#include "py/runtime.h"
#include "py/mphal.h"
#include "py/runtime.h"
#include "py/objstr.h"
#include "py/stackctrl.h"

#define SET_MOTOR(self) \
    setMotor((self)->port, \
             (self)->mode, \
             (self)->speed, \
             (self)->position )

#define UPDATE_MOTOR_SETTINGS(self) \
    SET_MOTOR(self);\
    motorSettings((self)->port, (self)->ticks, (self)->acc, (self)->kp, (self)->ki)

extern const mp_obj_type_t motor_type;

void init_motor_representations();
