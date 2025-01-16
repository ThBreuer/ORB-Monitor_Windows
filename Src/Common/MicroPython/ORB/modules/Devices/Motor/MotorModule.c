//*******************************************************************
/*!
\author Nils Hoffmann
\date   12.10.2024
*/

#include "py/obj.h"
#include "py/mphal.h"
#include "py/runtime.h"
#include "MotorModule.h"
#include "Motor_C_Interface.h"
#include "helper.h"
#include <stdio.h>

const mp_obj_type_t motor_type;

typedef struct _motor_obj_t {
    mp_obj_base_t base;
    uint8_t port;
    uint16_t ticks;
    uint8_t acc;
    uint8_t kp;
    uint8_t ki;
    uint8_t mode;
    int speed;
    int position;
} motor_obj_t;

motor_obj_t motor_obj_list[4];

void init_motor_representations() {
    motor_obj_list[0] = (motor_obj_t){ .base = { .type = &motor_type }, .port = M1, .ticks = 72, .acc = 25, .kp = 50, .ki = 30, .mode = 0, .speed = 0, .position = 0 };
    motor_obj_list[1] = (motor_obj_t){ .base = { .type = &motor_type }, .port = M2, .ticks = 72, .acc = 25, .kp = 50, .ki = 30, .mode = 0, .speed = 0, .position = 0 };
    motor_obj_list[2] = (motor_obj_t){ .base = { .type = &motor_type }, .port = M3, .ticks = 72, .acc = 25, .kp = 50, .ki = 30, .mode = 0, .speed = 0, .position = 0 };
    motor_obj_list[3] = (motor_obj_t){ .base = { .type = &motor_type }, .port = M4, .ticks = 72, .acc = 25, .kp = 50, .ki = 30, .mode = 0, .speed = 0, .position = 0 };
}

static void mp_motor_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    motor_obj_t *self = MP_OBJ_TO_PTR(self_in);
    mp_printf(print, "Motor(%d)", self->port);
}

static mp_obj_t mp_motor_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *all_args) {
    enum { ARG_port, ARG_ticks, ARG_acc, ARG_kp, ARG_ki};
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_port,         MP_ARG_REQUIRED | MP_ARG_INT, {.u_int = -1 } },
        { MP_QSTR_ticks,        MP_ARG_OBJ, {.u_obj  = MP_OBJ_NULL  } },
        { MP_QSTR_acc,          MP_ARG_OBJ, {.u_obj  = MP_OBJ_NULL  } },
        { MP_QSTR_kp,           MP_ARG_OBJ, {.u_obj  = MP_OBJ_NULL  } },
        { MP_QSTR_ki,           MP_ARG_OBJ, {.u_obj  = MP_OBJ_NULL  } },
    };
    PARSE_KW_ARGS_CONSTRUCTOR(n_args, n_kw, all_args, allowed_args);

    int port = ACCEPT_PORT(ARG_port, motor_obj_list);

    motor_obj_t *self = &motor_obj_list[port];

    ACCEPT_KW_ARG(ARG_ticks, self->ticks, MP_OBJ_GET_NUMBER_VALUE);
    ACCEPT_KW_ARG(ARG_acc, self->acc, MP_OBJ_GET_NUMBER_VALUE);
    ACCEPT_KW_ARG(ARG_kp , self->kp, MP_OBJ_GET_NUMBER_VALUE);
    ACCEPT_KW_ARG(ARG_ki  , self->ki, MP_OBJ_GET_NUMBER_VALUE);

    UPDATE_MOTOR_SETTINGS(self);

    return MP_OBJ_FROM_PTR(self);
}

static mp_obj_t config(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args){
    enum { ARG_ticks, ARG_acc, ARG_kp, ARG_ki};

    // Define the allowed arguments
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_ticks,        MP_ARG_OBJ, {.u_obj  = MP_OBJ_NULL  } },
        { MP_QSTR_acc,          MP_ARG_OBJ, {.u_obj  = MP_OBJ_NULL  } },
        { MP_QSTR_kp,           MP_ARG_OBJ, {.u_obj  = MP_OBJ_NULL  } },
        { MP_QSTR_ki,           MP_ARG_OBJ, {.u_obj  = MP_OBJ_NULL  } },
    };

    PARSE_KW_ARGS_INSTANCE_FUNCTION(n_args, pos_args, kw_args, allowed_args);

    motor_obj_t *self = MP_OBJ_TO_PTR(pos_args[0]);

    ACCEPT_KW_ARG(ARG_ticks, self->ticks, MP_OBJ_GET_NUMBER_VALUE);
    ACCEPT_KW_ARG(ARG_acc, self->acc , MP_OBJ_GET_NUMBER_VALUE);
    ACCEPT_KW_ARG(ARG_kp, self->kp , MP_OBJ_GET_NUMBER_VALUE);
    ACCEPT_KW_ARG(ARG_ki, self->ki , MP_OBJ_GET_NUMBER_VALUE);

    UPDATE_MOTOR_SETTINGS(self);

    return MP_OBJ_FROM_PTR(self);
}
static MP_DEFINE_CONST_FUN_OBJ_KW(config_obj, 0, config);

static mp_obj_t set(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args){
    enum { ARG_mode, ARG_speed, ARG_position};

    // Define the allowed arguments
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_mode,              MP_ARG_OBJ, {.u_obj  = MP_OBJ_NULL  } },
        { MP_QSTR_speed,             MP_ARG_OBJ, {.u_obj  = MP_OBJ_NULL  } },
        { MP_QSTR_position,          MP_ARG_OBJ, {.u_obj  = MP_OBJ_NULL  } },
    };
    PARSE_KW_ARGS_INSTANCE_FUNCTION(n_args, pos_args, kw_args, allowed_args);

    motor_obj_t *self = MP_OBJ_TO_PTR(pos_args[0]);

    ACCEPT_KW_ARG(ARG_mode, self->mode, MP_OBJ_GET_NUMBER_VALUE);
    ACCEPT_KW_ARG(ARG_speed, self->speed, MP_OBJ_GET_NUMBER_VALUE);
    ACCEPT_KW_ARG(ARG_position, self->position , MP_OBJ_GET_NUMBER_VALUE);

    SET_MOTOR(self);

    return MP_OBJ_FROM_PTR(self);
}
static MP_DEFINE_CONST_FUN_OBJ_KW(set_obj, 1, set);

static mp_obj_t get(mp_obj_t self_in){
    motor_obj_t *self = MP_OBJ_TO_PTR(self_in);
    motor_return_values ret;
    getMotor(self->port, &ret);

    mp_obj_t dict = mp_obj_new_dict(3);

    mp_obj_dict_store(dict, mp_obj_new_str("speed", 5), mp_obj_new_int(ret.speed));
    mp_obj_dict_store(dict, mp_obj_new_str("position", 8), mp_obj_new_int(ret.pos));
    mp_obj_dict_store(dict, mp_obj_new_str("power", 5), mp_obj_new_int(ret.pwr));

    return dict;
}
static MP_DEFINE_CONST_FUN_OBJ_1(get_obj , get);

static const mp_rom_map_elem_t motor_local_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_M1), MP_ROM_INT(M1) },
    { MP_ROM_QSTR(MP_QSTR_M2), MP_ROM_INT(M2) },
    { MP_ROM_QSTR(MP_QSTR_M3), MP_ROM_INT(M3) },
    { MP_ROM_QSTR(MP_QSTR_M4), MP_ROM_INT(M4) },

    { MP_ROM_QSTR(MP_QSTR_POWER_MODE), MP_ROM_INT(POWER_MODE) },
    { MP_ROM_QSTR(MP_QSTR_BRAKE_MODE), MP_ROM_INT(BRAKE_MODE) },
    { MP_ROM_QSTR(MP_QSTR_SPEED_MODE), MP_ROM_INT(SPEED_MODE) },
    { MP_ROM_QSTR(MP_QSTR_MOVETO_MODE), MP_ROM_INT(MOVETO_MODE) },

    { MP_ROM_QSTR(MP_QSTR_config), MP_ROM_PTR(&config_obj) },
    { MP_ROM_QSTR(MP_QSTR_set), MP_ROM_PTR(&set_obj) },
    { MP_ROM_QSTR(MP_QSTR_get), MP_ROM_PTR(&get_obj) },

};
static MP_DEFINE_CONST_DICT(motor_local, motor_local_dict_table);

MP_DEFINE_CONST_OBJ_TYPE(
    motor_type,
    MP_QSTR_motor,
    MP_TYPE_FLAG_NONE,
    make_new, mp_motor_make_new,
    print, mp_motor_print,
    locals_dict, &motor_local
    );

