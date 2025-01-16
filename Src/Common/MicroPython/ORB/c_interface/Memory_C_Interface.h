//*******************************************************************
/*!
\author Nils Hoffmann
\date   12.10.2024
*/

#ifndef MEMORY_MOCKUP_H
#define MEMORY_MOCKUP_H
#include <stdio.h>
#include "stdint.h"
#include "stddef.h"

#ifdef __cplusplus
extern "C" {
#endif

void clearMemory();

void setMemory(uint32_t addr, uint8_t *data, uint32_t data_size);

void getMemory(uint32_t addr, uint8_t* data, uint32_t data_size);

#ifdef __cplusplus
}
#endif

#endif
