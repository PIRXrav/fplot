/*
 * po_pc.h
 *
 *  Created on: 25/06/2020
 *      Author: pirx
 */

#ifndef _po_pc_H_
#define _po_pc_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

/*******************************************************************************
 * Macros
 ******************************************************************************/

/*******************************************************************************
 * Types
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

extern FILE *stdout_po_pc;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

void PO_PC_Init(void);
void PO_PC_Set(size_t npc);
void PO_PC_Inc(void);
size_t PO_PC_Get(void);

#endif /* _po_pc_H_ */
