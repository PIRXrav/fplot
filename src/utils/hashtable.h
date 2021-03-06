/*
 * hashtable.h
 *
 *  Created on: 26/06/2020
 *      Author: pirx
 */

#ifndef _hashtable_H_
#define _hashtable_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <stdint.h>
#include <stdio.h>

/*******************************************************************************
 * Macros
 ******************************************************************************/

/*******************************************************************************
 * Types
 ******************************************************************************/

typedef struct HashTable HashTable;

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

HashTable *HT_Init(void);
HashTable *HT_Insert(HashTable *ht, char *str, void *dat);
// get ht[str]. NULL if none
void *HT_Get(HashTable *ht, char *str);
void HT_FPrintRaw(FILE *pf, HashTable *ht);
void HT_FPrintKeys(FILE *pf, HashTable *ht, char *delimitor);
void HF_fprintFormat(FILE *pf, HashTable *ht,
                     void (*fprintelem)(FILE *, char *name, void *));
void TU_HashTable(void);

#endif /* _hashtable_H_ */
