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
#include <stdbool.h>

DataBase *Db = NULL;

void importDB(char *fileName){
    FILE *fp = fopen(fileName, "r");
    const char *source;
    char line[10000];
    char* collums[11];
    int siteID,tableTypeID,surfaceMaterialID,neighbourhoodID,parsedFields;
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

    size_t length = strlen("\n");
    Db->lineEnding = malloc(length+1);
    
    if (Db->lineEnding!=NULL)
    {
        memcpy(Db->lineEnding,"\n",length+1);

    }
    //read csv
    if (fgets(line,sizeof(line),fp)==NULL)
    {
        fclose(fp);
        return;
    }
    free (Db->lineEnding);
    if (strstr(line,"\r\n")!=NULL)
    {
        source = "\r\n";
    }
    else
    {
        source = "\n"
    }
    length = strlen(source);
    Db->lineEnding = malloc(length+1);
    memcpy(Db->lineEnding,source,length+1);

    while (fgets(line,sizeof(line),fp)!=NULL)
    {
        //parse this line on the basis of comma
        parsedFields = parseLine(line,collums,11);//parse line function will give us 11
        if (parsedFields!=11)
        {
            for (int i=0;i<parsedFields;i++)
            {
                free(collums[i]);

            }
            continue;

        }
        //fetched collums r 11
        siteID = atoi(collums[0]);
        
    }

}
int parseLine(const char* line,char** collums,int numOfCol)
{
    size_t length = strlen(line);
    int count = 0, j = 0;
    char* dupLine = malloc(length+1);
    char ch;
    bool isQuote = false;
    int length;

    if (dupLine==NULL)
    {
        return 0;
    }
    for (int i =0;i<length;i++)
    {
        ch = line[i];
        if (ch=='"')
        {
            isQuote = !isQuote;
            continue;

        }
        if (ch == ','&& isQuote == false)
        {
            dupLine[j]='\0';
            if (count< numOfCol)
            {
                length = strlen(dupLine);
                collums[count]=malloc(length+1);
                memcpy(collums[count],dupLine,length+1);
                count++;
                
            }
            j = 0;
            continue;
        }
        if ((ch =='\n'|| ch =='\r')&& isQuote== false)
        {
            continue;
        }
        dupLine[j] = ch;
        j++;

    }
    dupLine[j]='\0';
    if (count<numOfCol)
    {
        length = strlen(dupLine);
        collums[count]=malloc(length+1);
        memcpy(collums[count],dupLine,length+1);
        count++;


    }
    free(dupLine);
    return count;

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


