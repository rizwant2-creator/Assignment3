/*
 * dashboard.c
 *
 * TODO: Provide a high-level description of what is contained
 * in this file.
 *
 * Author: <TODO: Group Member Names>
 * Lab instructor: <TODO: Your lab instructor's name here>
 * Lecture instructor: <TODO: Your lecture instructor's name here>
*/

//You may include other original headers as you see fit
#include "DB.h"
#include "DB_impl.h"
#include "DB.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){

    importDB("PicnicTableSmall.csv");

    if (Db == NULL){
        fprintf(stderr, "importDB failed: Db is NULL\n");
        return 1;
    }

    // printf("importDB succeeded\n");
    // printf("  picnic table entries = %d\n", Db->picnicTableTable->size);
    // printf("  table types = %d\n", Db->tableTypeTable->size);
    // printf("  surface materials = %d\n", Db->surfaceMaterialTable->size);
    // printf("  structural materials = %d\n", Db->structuralMaterialTable->size);
    // printf("  neighbourhood entries = %d\n", Db->neighborhoodTable->size);

    // freeDB();
    return 0;
}
