/*
 * po_objstack.c
 *
 *  Created on: 23/06/2020
 *      Author: pirx
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "po_objstack.h"
#include <assert.h>

/*******************************************************************************
 * Macros
 ******************************************************************************/

#define STACK_SIZE 1024

/*******************************************************************************
 * Types
 ******************************************************************************/

/*******************************************************************************
 * Internal function declaration
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

static OBJ *stack[STACK_SIZE];
static size_t i_stack = 0; // Point sur un case vide

/*******************************************************************************
 * Public function
 ******************************************************************************/

void PO_OBJSTACK_Push(OBJ *obj) {
  assert(i_stack < STACK_SIZE - 1);
  stack[i_stack++] = obj;
}

OBJ *PO_OBJSTACK_Pop(void) {
  assert(i_stack > 0);
  return stack[i_stack-- - 1];
}

void PO_OBJSTACK_Print(void) {
  for (size_t i = 0; i < i_stack; i++) {
    printf("OBJSTACK[%.5ld]:", i);
    OBJ_Print(stack[i]);
    printf("\n");
  }
}

void PO_OBJSTACK_PrintDebugOBJ(FILE *f, size_t offset) {
  OBJ_FPrint(f, stack[i_stack - offset - 1]);
}

/*******************************************************************************
 * Internal function
 ******************************************************************************/
