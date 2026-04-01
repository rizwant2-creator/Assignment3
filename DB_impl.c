/* DB_impl.c
 *
 * TODO: Provide a high-level description of what is contained
 * in this file.
 *
 * Author: Taha Rizwan,Mark Seme,Rebecca Ngyuen
 * Lab instructor: Hanan Saleh
 * Lecture instructor: Dara Wagh
 */

#include "DB.h"      /* Import the public database header. */
#include "DB_impl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Table *createTable(void){ //create empty lookup table
    Table *t = malloc(sizeof(Table));
    if (t == NULL){
        return NULL;
    }

    t->entries = malloc(sizeof(TableEntry) * INIT_SIZE);
    if (t->entries == NULL){
        free(t);
        return NULL;
    }

    t->size = 0;
    t->capacity = INIT_SIZE;
    return t;
}

NeighbourhoodTable *createNeighbourhoodTable(void){ //create empty neighbourhood table
    NeighbourhoodTable *nt = malloc(sizeof(NeighbourhoodTable));
    if (nt == NULL){
        return NULL;
    }
    
    nt->entries = malloc(sizeof(NeighbourhoodEntry) * INIT_SIZE);
    if (nt->entries == NULL){
        free(nt);
        return NULL;
    }

    nt->size = 0;
    nt->capacity = INIT_SIZE;
    return nt;
}

PicnicTable *createPicnicTable(void){ //create empty picnic table
    PicnicTable *pt = malloc(sizeof(PicnicTable));
    if (pt == NULL){
        return NULL;
    }

    pt->entries = malloc(sizeof(PicnicTableEntry) * INIT_SIZE);
    if (pt->entries == NULL){
        free(pt);
        return NULL;
    }

    pt->size = 0;
    pt->capacity = INIT_SIZE;
    return pt;
}