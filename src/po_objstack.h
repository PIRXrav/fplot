/*
 * po_objstack.h
 *
 *  Created on: 23/06/2020
 *      Author: pirx
 */

#ifndef _po_objstack_H_
#define _po_objstack_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "obj_handler.h"

/*******************************************************************************
 * Macros
 ******************************************************************************/

/*******************************************************************************
 * Types
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

void PO_OBJSTACK_Push(OBJ *obj);
OBJ *PO_OBJSTACK_Pop(void);
void PO_OBJSTACK_Print(void);

void PO_OBJSTACK_PrintDebugOBJ(FILE *f, size_t offset);

#endif /* _po_objstack_H_ */
