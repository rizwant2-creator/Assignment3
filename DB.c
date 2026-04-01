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
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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

void initalizeDB()
{
    
}

void importDB(char *fileName)
{
    FILE* file;
    char line[1000];
    char* fields[11]; //they are total 11 fields in the .csv file
    if (fileName==NULL)
    {
        return;
    }
    //free the old DB
    freeDB();
    // we will initalize all the variables
    initalizeDB(); //this function dinamically allocate memory to all the pointers of database


}