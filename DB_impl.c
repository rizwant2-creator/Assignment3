/* DB_impl.c
 *
 * TODO: Provide a high-level description of what is contained
 * in this file.
 *
 * Author: Taha Rizwan,Marc Seme,Rebecca Ngyuen
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

//lookup by name helpers for Table. 
//Returns the id of the entry with the given name, or 0 if not found.
int lookupTableID(Table *t, const char *name){
    int i;
    for (i = 0; i < t->size; i++){
        if (strcmp(t->entries[i].type, name) == 0){
            return t->entries[i].id;
        }
    }
    return -1;
}

//lookup by id and name helpers for NeighbourhoodTable
int lookupNeighbourhood(NeighbourhoodTable *nt, int id, const char *name){
    int i;
    for (i = 0; i < nt->size; i++){
        if (nt->entries[i].id == id && strcmp(nt->entries[i].nname, name) == 0){
            return id;
        }
    }
    return -1;
}

//lookup by id helpers returns Table name given id
const char *lookupTableName(Table *t, int id){
    int i;
    for (i = 0; i < t->size; i++){
        if (t->entries[i].id == id){
            return t->entries[i].type;
        }
    }
    return NULL;
}

//lookup by id helpers returns Neighbourhood name given id
const char *lookupNeighbourhoodName(NeighbourhoodTable *nt, int id){
    int i;
    for (i = 0; i < nt->size; i++){
        if (nt->entries[i].id == id){
            return nt->entries[i].nname;
        }
    }
    return NULL;
}

//insertion helpers for Table. Returns the id of the inserted entry, or -1 on failure.
int insertToTable(Table *t, const char *name){

    if (t->size >= t->capacity){
        t->capacity *= 2;
        t->entries = realloc(t->entries, sizeof(TableEntry) * t->capacity);
        if (t->entries == NULL){
            printf("Memory allocation failed for table entries\n");
            return -1;
        }
    }

    int newEntryid = t->size; //id starts at 0
    t->entries[t->size].id = newEntryid;
    t->entries[t->size].type = malloc(strlen(name) + 1);
    if (t->entries[t->size].type == NULL){
        printf("Memory allocation failed for entry name\n");
        return -1;
    }

    strcpy(t->entries[t->size].type, name);
    t->size++;
    return newEntryid;
}

//insertion helpers for NeighbourhoodTable. Returns the id of the inserted entry, or -1 on failure.
int insertToNeighbourhoodTable(NeighbourhoodTable *nt, int id, const char *name){

    if (nt->size >= nt->capacity){
        nt->capacity *= 2;
        nt->entries = realloc(nt->entries, sizeof(NeighbourhoodEntry) * nt->capacity);
        if (nt->entries == NULL){
            return -1;
        }
    }

    nt->entries[nt->size].id = id;
    nt->entries[nt->size].nname = malloc(strlen(name) + 1);
    if (nt->entries[nt->size].nname == NULL){
        printf("Memory allocation failed for entry name\n");
        return -1;
    }
    strcpy(nt->entries[nt->size].nname, name);
    nt->size++;
    return id;
}

//lookup picnic entry by tableID. Returns pointer to entry, or NULL if not found.
PicnicTableEntry *lookupPicnicEntry(PicnicTable *pt, int tableID){
    int i;
    for (i = 0; i < pt->size; i++){
        if (pt->entries[i].tableID == tableID){
            return &pt->entries[i];
        }
    }
    return NULL;
}

//insertion helpers for PicnicTable. Returns the id of the inserted entry, or -1 on failure.
int insertToPicnicTable(PicnicTable *pt, PicnicTableEntry *entry){

    if (pt->size >= pt->capacity){
        pt->capacity *= 2;
        pt->entries = realloc(pt->entries, sizeof(PicnicTableEntry) * pt->capacity);
        if (pt->entries == NULL){
            printf("Memory allocation failed for picnic table entries\n");
            return -1;
        }
    }
    pt->entries[pt->size] = *entry; //copy entry to table
    pt->size++;
    return entry->tableID;
}