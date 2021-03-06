/*
 * po_ctxstack.h
 *
 *  Created on: 20/12/2020
 */

#ifndef _PO_CTXSTACK_H_
#define _PO_CTXSTACK_H_

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

extern FILE *stdout_po_ctx;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void CTX_Init(void);

void CTX_enter();
void CTX_leave();

void CTX_printCur();

OBJ *CTX_setObj(char *name, OBJ *o);
OBJ *CTX_getObj(char *name);

void CTX_PC_Set(size_t npc);
void CTX_PC_Inc(void);
size_t CTX_PC_Get(void);
void CTX_PC_Add(size_t dpc);

void CTX_PC_setMainPc(size_t value);
size_t CTX_PC_getMainPc();

#endif /* _PO_CTXSTACK_H_ */
