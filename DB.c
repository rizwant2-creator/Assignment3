/* DB.c
 *
 * TODO: Provide a high-level description of what is contained
 * in this file.
 *
 * Author: Taha Rizwan,Marc Seme,Rebecca Ngyuen
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
    char line[10000];
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
    if (fgets(line,sizeof(line),fp)==NULL)
    {
        fclose(fp);
        return;
    }
    while (fgets(line,sizeof(line),fp)!=NULL)
    {
        //parse this line on the basis of commas 
    }

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

void freeDB()
{
    if (Db==NULL)
    {
        return;
    }
    if (Db->tableTypeTable!=NULL)
    {
        if (Db->tableTypeTable->entries!=NULL)
        {
            for (int i=0;i<Db->tableTypeTable->size;i++)
            {
               free(Db->tableTypeTable->entries[i].name);
            }
            free(Db->tableTypeTable->entries);
        }
        free(Db->tableTypeTable);
    }
    if (Db->surfaceMaterialTable!=NULL)
    {
        if (Db->surfaceMaterialTable->entries!=NULL)
        {
            for (int i=0;i<Db->surfaceMaterialTable->size;i++)
            {
                free(Db->surfaceMaterialTable->entries[i].name);
            }
            free(Db->surfaceMaterialTable->entries);
        }
        free(Db->surfaceMaterialTable);
    }
    if (Db->structuralMaterialTable!=NULL)
    {
        if (Db->structuralMaterialTable->entries!=NULL)
        {
            for (int i=0;i<Db->structuralMaterialTable->size;i++)
            {
                free(Db->structuralMaterialTable->entries[i].name);
            }
            free(Db->structuralMaterialTable->entries);
        }
        free(Db->structuralMaterialTable);
    }
    if (Db->structuralMaterialTable!=NULL)
    {
        if (Db->neighborhoodTable->entries!=NULL)
        {
            for (int i=0;i<Db->neighborhoodTable->size;i++)
            {
                free(Db->neighborhoodTable->entries[i].name);
            }
        free(Db->neighborhoodTable->entries);
        }
        free(Db->neighborhoodTable);
    }
    if (Db->picnicTableTable!=NULL)
    {
        if(Db->picnicTableTable->entries!=NULL)
        {
            for (int i=0;i<Db->picnicTableTable->size;i++)
            {
                free(Db->picnicTableTable->entries[i].ward);
                free(Db->picnicTableTable->entries[i].latitude);
                free(Db->picnicTableTable->entries[i].longlitude);
                free(Db->picnicTableTable->entries[i].location);
                free(Db->picnicTableTable->entries[i].street);

            }
            free(Db->picnicTableTable->entries);
        }
        free(Db->picnicTableTable);
    }
    free(Db->lineEnding);
    free(Db);
    Db=NULL;


}


