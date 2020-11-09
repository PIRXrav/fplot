/*
 * mem_prgm.c
 *
 *  Created on: 23/06/2020
 *      Author: pirx
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "mem_prgm.h"
#include <assert.h>

/*******************************************************************************
 * Macros
 ******************************************************************************/

/*******************************************************************************
 * Types
 ******************************************************************************/

/*******************************************************************************
 * Internal function declaration
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

size_t memmainsize;
size_t *memsubsizes;

PCODE ***memprgm = NULL;

/*******************************************************************************
 * Public function
 ******************************************************************************/

void MEMPRGM_Init(PCODE ***prgm, size_t mainsize, size_t *subsizes) {
  memprgm = prgm;
  memmainsize = mainsize;
  memsubsizes = subsizes;
}

PCODE *MEMPRGM_Get(size_t i) { // ONLY ENTRY POINT TODO /!\//
  if (i >= memsubsizes[0])
    return NULL;        // EOP
  return memprgm[0][i]; // TODO;
}

void MEMPRGM_Print(void) {
  printf("***     MEM-PRGM(%ld)     ***\n", memsubsizes[0]);
  for (size_t i = 0; i < memsubsizes[0]; i++) {
    printf("[%.5ld] ", i);
    PC_Print(memprgm[0][i]);
    printf("\n");
  }
}
/*******************************************************************************
 * Internal function
 ******************************************************************************/
