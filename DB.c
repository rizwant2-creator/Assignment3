/* DB.c
 *
 * TODO: Provide a high-level description of what is contained
 * in this file.
 *
 * Author: Taha Rizwan,Mark Seme,Rebecca Ngyuen
 * Lab instructor: Hanan Saleh
 * Lecture instructor: Dara Wagh
 */

#include "DB.h"       /* Import the public database header. */
#include "DB_impl.h"  /* Import the private database header */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

DataBase *Db = NULL;

void importDB(char *fileName){
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL){
        fprintf(stderr, "Could not open file %s\n", fileName);
        return;
    }

    Db = malloc(sizeof(DataBase)); //allocate database
    if (Db == NULL){
        fclose(fp);
        return;
    }

    Db->tableTypeTable = createTable();
    Db->surfaceMaterialTable = createTable();
    Db->structuralMaterialTable = createTable();
    Db->neighborhoodTable = createNeighbourhoodTable();
    Db->picnicTableTable = createPicnicTable();

    //read csv
    

}

void exportDB(char *fileName){
    int i;
    if (Db == NULL){
        return;
    }

    FILE *fp = fopen(fileName, "w");
    if (fp == NULL){
        fprintf(stderr, "Could not write file %s\n", fileName);
        return;
    }

    //csv header line
    fprintf(fp, "Id,Table Type,Surface Material,Structural Material,Street / Avenue,Neighbourhood Id,Neighbourhood Name,Ward,Latitude,Longitude,Location\n");
    for (i = 0; i < Db->picnicTableTable->size; i++){
        fprintf(fp, "%d,%s,%s,%s,%s,%d,%s,%s,%s,%s,%s\n",
            Db->picnicTableTable->entries[i].siteID,
            Db->picnicTableTable->entries[i].tableTypeID,
            Db->picnicTableTable->entries[i].surfaceMaterialID,
            Db->picnicTableTable->entries[i].structuralMaterialID,
            Db->picnicTableTable->entries[i].street,
            Db->picnicTableTable->entries[i].neighbourhoodID,
            Db->picnicTableTable->entries[i].neighborhoodName,
            Db->picnicTableTable->entries[i].ward,
            Db->picnicTableTable->entries[i].latitude,
            Db->picnicTableTable->entries[i].longitude,
            Db->picnicTableTable->entries[i].longitude);
    }
    fclose(fp);
}

void freeDB(void){
    int i;

    if (Db == NULL){
        return;
    }

    //free lookup tables, free each string, entries array, and table
    if (Db->tableTypeTable != NULL){
        for (i = 0; i < Db->tableTypeTable->size; i++){
            free(Db->tableTypeTable->entries[i].name);
        }
        free(Db->tableTypeTable->entries);
        free(Db->tableTypeTable);
    }

    if (Db->surfaceMaterialTable != NULL){
        for (i = 0; i < Db->surfaceMaterialTable->size; i++){
            free(Db->surfaceMaterialTable->entries[i].name);
        }
        free(Db->surfaceMaterialTable->entries);
        free(Db->surfaceMaterialTable);
    }

    if (Db->structuralMaterialTable != NULL){

    }

    //free neighbourhood table, free name, entries array, and neighbourhood table
    if (Db->neighborhoodTable != NULL){

    }

    //free picnic table, free each string, entries array, and picnic table
    if (Db->picnicTableTable != NULL){

    }
    free(Db);
    Db = NULL;
}