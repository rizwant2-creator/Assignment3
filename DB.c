/* DB.c
 *
 * TODO: Provide a high-level description of what is contained
 * in this file.
 *
 * Author: Taha Rizwan,Marc Seme,Rebecca Ngyuen
 * Lab instructor: Hanan Saleh
 * Lecture instructor: Dara Wagh
 */

#include "DB.h"       // Import the public database header. 
#include "DB_impl.h"  // Import the private database header 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

DataBase *Db = NULL;




// Parse one CSV field from src into buffer
static char *fieldParser(char *src, char *buffer, int buffSize) {
    int i = 0;
    if (*src == '"') { // if field starts with a quote, read until closing quote
        src++; // skip opening quote
        while (*src && *src != '"') {
            if (i < buffSize - 1) buffer[i++] = *src;
            src++;
        }
        if (*src == '"') src++; // skip closing quote
        if (*src == ',') src++; // skip comma separator
    } else {
        while (*src && *src != ',' && *src != '\n' && *src != '\r') {
            if (i < buffSize - 1) buffer[i++] = *src;
            src++;
        }
        if (*src == ',') src++; // skip comma separator
    }
    buffer[i] = '\0';
    return src;
}

void importDB(char *fileName) {
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL) {
        fprintf(stderr, "Could not open file %s\n", fileName);
        return;
    }

    Db = malloc(sizeof(DataBase));
    if (Db == NULL) {
        fclose(fp);
        return;
    }

    Db->tableTypeTable = createTable();
    Db->surfaceMaterialTable = createTable();
    Db->structuralMaterialTable = createTable();
    Db->neighborhoodTable = createNeighbourhoodTable();
    Db->picnicTableTable = createPicnicTable();
    Db->lineEnding = NULL;

    char line[1000];
    int picTableID = 0; // to be incremented for picnic table entries

    while (fgets(line, sizeof(line), fp) != NULL) {
        
        if (strncmp(line, "Id,", 3) == 0) continue; // if line = header, skip it

        char siteIDStr[45], type[45], surface[45], structural[45];
        char street[100], nhoodIDStr[45], neighborhoodName[100];
        char ward[45], latitude[45], longitude[45], location[200];

        char *ptr = line;
        ptr = fieldParser(ptr, siteIDStr,        sizeof(siteIDStr));
        ptr = fieldParser(ptr, type,             sizeof(type));
        ptr = fieldParser(ptr, surface,          sizeof(surface));
        ptr = fieldParser(ptr, structural,       sizeof(structural));
        ptr = fieldParser(ptr, street,           sizeof(street));
        ptr = fieldParser(ptr, nhoodIDStr,       sizeof(nhoodIDStr));
        ptr = fieldParser(ptr, neighborhoodName, sizeof(neighborhoodName));
        ptr = fieldParser(ptr, ward,             sizeof(ward));
        ptr = fieldParser(ptr, latitude,         sizeof(latitude));
        ptr = fieldParser(ptr, longitude,        sizeof(longitude));
        ptr = fieldParser(ptr, location,         sizeof(location));

        // inserts into lookup tables
        int tableTypeID = lookupTableID(Db->tableTypeTable, type);
        if (tableTypeID == -1) {
            tableTypeID = insertToTable(Db->tableTypeTable, type);
        }

        int surfaceMaterialID = lookupTableID(Db->surfaceMaterialTable, surface);
        if (surfaceMaterialID == -1) {
            surfaceMaterialID = insertToTable(Db->surfaceMaterialTable, surface);
        }

        int structuralMaterialID = lookupTableID(Db->structuralMaterialTable, structural);
        if (structuralMaterialID == -1) {
            structuralMaterialID = insertToTable(Db->structuralMaterialTable, structural);
        }

        int nhoodID = atoi(nhoodIDStr);
        int neighbourhoodID = lookupNeighbourhood(Db->neighborhoodTable, nhoodID, neighborhoodName);
        if (neighbourhoodID == -1) {
            neighbourhoodID = insertToNeighbourhoodTable(Db->neighborhoodTable, nhoodID, neighborhoodName);
        }

        PicnicTableEntry entry;
        entry.tableID              = picTableID++;      
        entry.siteID               = atoi(siteIDStr); // CSV Id column
        entry.tableTypeID          = tableTypeID;
        entry.surfaceMaterialID    = surfaceMaterialID;
        entry.structuralMaterialID = structuralMaterialID;
        entry.neighbourhoodID      = nhoodID;

        entry.neighborhoodName = malloc(strlen(neighborhoodName) + 1);
        if (entry.neighborhoodName == NULL) { fclose(fp); return; }
        strcpy(entry.neighborhoodName, neighborhoodName);

        entry.ward = malloc(strlen(ward) + 1);
        if (entry.ward == NULL) { fclose(fp); return; }
        strcpy(entry.ward, ward);

        entry.latitude = malloc(strlen(latitude) + 1);
        if (entry.latitude == NULL) { fclose(fp); return; }
        strcpy(entry.latitude, latitude);

        entry.longitude = malloc(strlen(longitude) + 1);
        if (entry.longitude == NULL) { fclose(fp); return; }
        strcpy(entry.longitude, longitude);

        entry.location = malloc(strlen(location) + 1);
        if (entry.location == NULL) { fclose(fp); return; }
        strcpy(entry.location, location);

        entry.street = malloc(strlen(street) + 1);
        if (entry.street == NULL) { fclose(fp); return; }
        strcpy(entry.street, street);

        if (insertToPicnicTable(Db->picnicTableTable, &entry) == -1) {
            printf("Failed to insert picnic table entry\n");
            fclose(fp);
            return;
        }
    }

    fclose(fp);
}

void exportDB(char *fileName) {
    int i;
    FILE *fp = fopen(fileName, "wb"); // binary mode to preserve
    if (fp == NULL) {
        printf("Could not write to file \n");
        return;
    }

    fprintf(fp, "Id,Table Type,Surface Material,Structural Material,Street / Avenue,Neighbourhood Id,Neighbourhood Name,Ward,Latitude,Longitude,Location\r\n");

    for (i = 0; i < Db->picnicTableTable->size; i++) {
        PicnicTableEntry *exp = &Db->picnicTableTable->entries[i];
        const char *tableType          = lookupTableName(Db->tableTypeTable,           exp->tableTypeID);
        const char *surfaceMaterial    = lookupTableName(Db->surfaceMaterialTable,     exp->surfaceMaterialID);
        const char *structuralMaterial = lookupTableName(Db->structuralMaterialTable,  exp->structuralMaterialID);

        fprintf(fp, "%d,%s,%s,%s,%s,%d,%s,%s,%s,%s,\"%s\"\r\n",
            exp->siteID,
            tableType          ? tableType          : "", // if NULL
            surfaceMaterial    ? surfaceMaterial    : "", // print empty
            structuralMaterial ? structuralMaterial : "", // string instead
            exp->street,
            exp->neighbourhoodID,
            exp->neighborhoodName,
            exp->ward,
            exp->latitude,
            exp->longitude,
            exp->location);
    }
    fclose(fp);
}

int countEntries(char *memberName, char * value){
    int i;
    int count = 0;
    int id;

    if (strcmp(memberName, "table type") == 0){
        id = lookupTableID(Db->tableTypeTable, value); //convert text value to lookup table id
        for (i = 0; i < Db->picnicTableTable->size; i++){
            if (Db->picnicTableTable->entries[i].tableTypeID == id){
                count++;
            }
        }
    }
    else if (strcmp(memberName, "surface material") == 0){
        id = lookupTableID(Db->surfaceMaterialTable, value);
        for (i = 0; i < Db->picnicTableTable->size; i++){
            if (Db->picnicTableTable->entries[i].surfaceMaterialID == id){
                count++;
            }
        }
    }
    else if (strcmp(memberName, "structural material") == 0){
        id = lookupTableID(Db->structuralMaterialTable, value);
        for (i = 0; i < Db->picnicTableTable->size; i++){
            if (Db->picnicTableTable->entries[i].structuralMaterialID == id){
                 count++;
            }
        }
    }
    else if (strcmp(memberName, "neighbourhood id") == 0){
        id = atoi(value); //convert string value to integer id
        for (i = 0; i < Db->picnicTableTable->size; i++){
            if (Db->picnicTableTable->entries[i].neighbourhoodID == id){
                count++;
            }
        }
    }
    else if (strcmp(memberName, "neighbourhood name") == 0){
        for (i = 0; i < Db->picnicTableTable->size; i++){
            if (strcmp(Db->picnicTableTable->entries[i].neighborhoodName, value) == 0){
                count++;
            }
        }
    }
    else if (strcmp(memberName, "ward") == 0){
        for (i = 0; i < Db->picnicTableTable->size; i++){
            if(strcmp(Db->picnicTableTable->entries[i].ward, value) == 0){ //compare ward string directly
                count++;
            }
        }
    }
    return count;
}

void editTableEntry(int siteID, char *memberName, char *value) {
    if (Db == NULL) return;

    PicnicTableEntry *entry = lookupPicnicTBySiteID(Db->picnicTableTable, siteID);
    if (entry == NULL) {
        printf("No entry found for site ID %d\n", siteID);
        return;
    }

    if (strcmp(memberName, "table type") == 0) {
        int id = lookupTableID(Db->tableTypeTable, value);
        if (id == -1) {
            id = insertToTable(Db->tableTypeTable, value);
        }
        entry->tableTypeID = id;
    }
    else if (strcmp(memberName, "surface material") == 0) {
        int id = lookupTableID(Db->surfaceMaterialTable, value);
        if (id == -1) {
            id = insertToTable(Db->surfaceMaterialTable, value);
        }
        entry->surfaceMaterialID = id;
    }
    else if (strcmp(memberName, "structural material") == 0) {
        int id = lookupTableID(Db->structuralMaterialTable, value);
        if (id == -1) {
            id = insertToTable(Db->structuralMaterialTable, value);
        }
        entry->structuralMaterialID = id;
    }
}

// Comparison function for qsort
static int compare(const void *a, const void *b) {
    return strcmp((const char *)a, (const char *)b);
}

void reportByNeighbourhood() {
    int i, j;
    int n = Db->picnicTableTable->size;
    char nhoods[500][100]; // assuming (max) 500 unique neighbourhoods & 100 chars for each name
    int unique_nhoods = 0;

    for (i = 0; i < n; i++) {
        char *name = Db->picnicTableTable->entries[i].neighborhoodName;
        for (j = 0; j < unique_nhoods; j++) {
            if (strcmp(nhoods[j], name) == 0) {
                break;
            }
        }
        // if we reached the end of nhoods without a match
        if (j == unique_nhoods) {
            strncpy(nhoods[unique_nhoods], name, 99);
            unique_nhoods++;}
    }

    // sorts the array (in ascending order by neighborhood name)
    qsort(nhoods, unique_nhoods, sizeof(nhoods[0]), compare);

    for (i = 0; i < unique_nhoods; i++) {
        printf("%s\n", nhoods[i]);
        for (j = 0; j < n; j++) {
            PicnicTableEntry *e = &Db->picnicTableTable->entries[j];
            if (strcmp(e->neighborhoodName, nhoods[i]) == 0) {
                printf("%d,%s,%s,%s,%s,%d,%s,%s,%s,%s,%s\n\n",
                    e->siteID,
                    lookupTableName(Db->tableTypeTable, e->tableTypeID),
                    lookupTableName(Db->surfaceMaterialTable, e->surfaceMaterialID),
                    lookupTableName(Db->structuralMaterialTable, e->structuralMaterialID),
                    e->street, e->neighbourhoodID, e->neighborhoodName,
                    e->ward, e->latitude, e->longitude, e->location);}  
        }
    }
}

void reportByWard() {
    int i, j;
    int n = Db->picnicTableTable->size;
    char all_wards[500][100];
    int unique_wards = 0;

    for (i = 0; i < n; i++) {
        char *ward = Db->picnicTableTable->entries[i].ward;
        for (j = 0; j < unique_wards; j++) {
            if (strcmp(all_wards[j], ward) == 0) {
                break; }
        }
        // if we reached the end of all_wards without a match
        if (j == unique_wards) {
            strncpy(all_wards[unique_wards], ward, 99);
            unique_wards++;
        }
    }

    // sorts the array (in ascending order by ward name)
    qsort(all_wards, unique_wards, sizeof(all_wards[0]), compare);

    for (i = 0; i < unique_wards; i++) {
        printf("%s\n", all_wards[i]);
        for (j = 0; j < n; j++) {
            PicnicTableEntry *e = &Db->picnicTableTable->entries[j];
            if (strcmp(e->ward, all_wards[i]) == 0) {
                printf("%d,%s,%s,%s,%s,%d,%s,%s,%s,%s,%s\n\n",
                    e->siteID,
                    lookupTableName(Db->tableTypeTable, e->tableTypeID),
                    lookupTableName(Db->surfaceMaterialTable, e->surfaceMaterialID),
                    lookupTableName(Db->structuralMaterialTable, e->structuralMaterialID),
                    e->street, e->neighbourhoodID, e->neighborhoodName,
                    e->ward, e->latitude, e->longitude, e->location);}  
        }
    }
}

void sortByMember(char *memberName)
{
    PicnicTableEntry key;
    PicnicTableEntry *left;
    int compare;
    if (Db == NULL)
    {
        return;
    }
    else
    {
        if (Db->picnicTableTable == NULL)
        {
            return;
        }
        if (memberName == NULL)
        {
            return;
        }
        for (int i = 1; i< Db->picnicTableTable->size; i++)
        {
            key = Db->picnicTableTable->entries[i];
            int j= i-1;
            while (j>=0)
            {
                left = &Db->picnicTableTable->entries[j];
                if (strcmp(memberName,"TT")== 0)
                {
                    compare = strcmp(lookupTableName(Db->tableTypeTable,left->tableTypeID),lookupTableName(Db->tableTypeTable,key.tableTypeID));

                }
                else if (strcmp(memberName,"SM")==0)
                {
                    compare = strcmp(lookupTableName(Db->surfaceMaterialTable,left->surfaceMaterialID),lookupTableName(Db->surfaceMaterialTable,key.surfaceMaterialID));

                }
                else if (strcmp(memberName,"StM")== 0)
                {
                    compare = strcmp(lookupTableName(Db->structuralMaterialTable,left->structuralMaterialID),lookupTableName(Db->structuralMaterialTable,key.structuralMaterialID));


                }
                else if (strcmp(memberName,"NID")== 0)
                {
                    if (left->neighbourhoodID<key.neighbourhoodID)
                    {
                        compare =-1;
                    }
                    else if (left->neighbourhoodID>key.neighbourhoodID)
                    {
                        compare =1;
                    }


                }
                else if(strcmp(memberName,"NN")==0)
                {
                   compare = strcmp(lookupNeighbourhoodName(Db->neighborhoodTable,left->neighbourhoodID),lookupNeighbourhoodName(Db->neighborhoodTable,key.neighbourhoodID));

                }
                else if (strcmp(memberName,"W")== 0)
                {
                    compare = strcmp(left->ward,key.ward);
                }
                if (compare<=0)
                {
                    break;
                }
                Db->picnicTableTable->entries[j+1] = Db->picnicTableTable->entries[j];
                j--;
            }
            Db->picnicTableTable->entries[j+1] = key;
        }
    }
}

void freeDB(void) {
    int i;

    if (Db == NULL) return;

    if (Db->tableTypeTable != NULL) {
        for (i = 0; i < Db->tableTypeTable->size; i++) {
            free(Db->tableTypeTable->entries[i].type);
        }
        free(Db->tableTypeTable->entries);
        free(Db->tableTypeTable);
    }

    if (Db->surfaceMaterialTable != NULL) {
        for (i = 0; i < Db->surfaceMaterialTable->size; i++) {
            free(Db->surfaceMaterialTable->entries[i].type);
        }
        free(Db->surfaceMaterialTable->entries);
        free(Db->surfaceMaterialTable);
    }

    if (Db->structuralMaterialTable != NULL) {
        for (i = 0; i < Db->structuralMaterialTable->size; i++) {
            free(Db->structuralMaterialTable->entries[i].type);
        }
        free(Db->structuralMaterialTable->entries);
        free(Db->structuralMaterialTable);
    }

    if (Db->neighborhoodTable != NULL) {
        for (i = 0; i < Db->neighborhoodTable->size; i++) {
            free(Db->neighborhoodTable->entries[i].nname);
        }
        free(Db->neighborhoodTable->entries);
        free(Db->neighborhoodTable);
    }

    if (Db->picnicTableTable != NULL) {
        for (i = 0; i < Db->picnicTableTable->size; i++) {
            free(Db->picnicTableTable->entries[i].neighborhoodName);
            free(Db->picnicTableTable->entries[i].ward);
            free(Db->picnicTableTable->entries[i].latitude);
            free(Db->picnicTableTable->entries[i].longitude);
            free(Db->picnicTableTable->entries[i].location);
            free(Db->picnicTableTable->entries[i].street);
        }
        free(Db->picnicTableTable->entries);
        free(Db->picnicTableTable);
    }

    free(Db);
    Db = NULL;
}
