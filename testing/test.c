#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../DB.h"
#include "../DB_impl.h"

int main (void){
   importDB("PicnicTableSmall.csv");
    
    if (Db == NULL) {
        printf("FAIL\n");
        return 1;
    } else {
        printf("PASS\n");
    }

    // Test Create tables 
    printf("createTable Test\n");
    Table *table = createTable();
    if (table->capacity == INIT_SIZE && table->entries != NULL && table->size == 0){
        printf("PASS\n");
    } else{
        printf("FAIL\n");
    }

    printf("createNeighbourhoodTable Test\n");
    NeighbourhoodTable *nt = createNeighbourhoodTable();
    if (nt->capacity == INIT_SIZE && nt->entries != NULL && nt->size == 0){
        printf("PASS\n");
    } else{
        printf("FAIL\n");
    }

    printf("createPicnicTable Test\n");
    PicnicTable *pt = createPicnicTable();
    if (pt->capacity == INIT_SIZE && pt->entries != NULL && pt->size == 0){
        printf("PASS\n");
    } else{
        printf("FAIL\n");
    }

    free(table->entries);
    free(table);
    free(nt->entries);
    free(nt);
    free(pt->entries);
    free(pt);

    // Test lookupTableName
    const char *tableName;
    const char *neighbourhoodName;
    int id;
    
    id = lookupTableID(Db->tableTypeTable, "Round Picnic Table");

    printf("lookupTableName Test: Matching id\n");
    tableName = lookupTableName(Db->tableTypeTable, id);
    if (tableName != NULL && strcmp(tableName, "Round Picnic Table") == 0) {
        printf("PASS\n");
    } else {
        printf("FAIL\n");
    }

    printf("lookupTableName Test: Non-matching id\n");
    tableName = lookupTableName(Db->tableTypeTable, 999999);
    if (tableName == NULL) {
        printf("PASS\n");
    } else {
        printf("FAIL\n");
    }

    printf("lookupNeighbourhoodName Test: Matching id\n");
    neighbourhoodName = lookupNeighbourhoodName(Db->neighborhoodTable, 5130);
    if (neighbourhoodName != NULL && strcmp(neighbourhoodName, "CARTER CREST") == 0) {
        printf("PASS\n");
    } else {
        printf("FAIL\n");
    }

    printf("lookupNeighbourhoodName Test: Non-matching id\n");
    neighbourhoodName = lookupNeighbourhoodName(Db->neighborhoodTable, 999999);
    if (neighbourhoodName == NULL) {
        printf("PASS\n");
    } else {
        printf("FAIL\n");
    }

    // Test countEntries 
    int result;
    printf("countEntries Test: Matching name\n");
    result = countEntries("neighbourhood name", "CARTER CREST");
    if (result == 1) {
        printf("PASS\n");
    } else{
        printf("FAIL\n");
    }

    printf("countEntries Test: Non-matching name\n");
    result = countEntries("neighbourhood name", "fake neighbourhood");
    if (result == 0) {
        printf("PASS\n");
    } else{
        printf("FAIL\n");
    }

    printf("countEntries Test: Matching id\n");
    result = countEntries("neighbourhood id", "5130");
    if (result == 1) {
        printf("PASS\n");
    } else{
        printf("FAIL\n");
    }

    printf("countEntries Test: Non-matching id\n");
    result = countEntries("neighbourhood id", "999999999");
    if (result == 0) {
        printf("PASS\n");
    } else{
        printf("FAIL\n");
    }

    printf("countEntries Test: Case sensitivity\n");
    result = countEntries("neighbourhood name", "RoSEnThaL");
    if (result == 0) {
        printf("PASS\n");
    } else{
        printf("FAIL\n");
    }

    printf("countEntries Test: Negative id\n");
    result = countEntries("neighbourhood id", "-20");
    if (result == 0) {
        printf("PASS\n");
    } else{
        printf("FAIL\n");
    }

    // Test lookupPicnicEntry
    int firstID = Db->picnicTableTable->entries[0].tableID;
    PicnicTableEntry *entry;

    printf("lookupPicnicEntry Test: Matching tableID\n");
    entry = lookupPicnicEntry(Db->picnicTableTable, firstID);
    if (entry != NULL && entry->tableID == firstID) {
        printf("PASS\n");
    } else {
        printf("FAIL\n");
    }

    printf("lookupPicnicEntry Test: Non-matching tableID\n");
    entry = lookupPicnicEntry(Db->picnicTableTable, 999999);
    if (entry == NULL) {
        printf("PASS\n");
    } else {
        printf("FAIL\n");
    }

    // Test editTableEntry
    printf("editTableEntry Test: Valid table type edit\n");
    editTableEntry(firstID, "table type", "Steel Picnic Table");
    entry = lookupPicnicEntry(Db->picnicTableTable, firstID);
    const char *newType = lookupTableName(Db->tableTypeTable, entry->tableTypeID);
    if (newType != NULL && strcmp(newType, "Steel Picnic Table") == 0) {
        printf("PASS\n");
    } else {
        printf("FAIL\n");
    }

    printf("editTableEntry Test: New value not in table gets inserted\n");
    editTableEntry(firstID, "table type", "Completely New Type");
    entry = lookupPicnicEntry(Db->picnicTableTable, firstID);
    newType = lookupTableName(Db->tableTypeTable, entry->tableTypeID);
    if (newType != NULL && strcmp(newType, "Completely New Type") == 0) {
        printf("PASS\n");
    } else {
        printf("FAIL\n");
    }

    printf("editTableEntry Test: Invalid tableID does not crash\n");
    editTableEntry(999999, "table type", "Wood Picnic Table");
    printf("PASS\n");

    printf("editTableEntry Test: Invalid member name does not crash\n");
    editTableEntry(firstID, "fake member", "some value");
    printf("PASS\n");

    // Test reportByNeighbourhood and reportByWard
    printf("reportByNeighbourhood Test: Runs without crashing\n");
    reportByNeighbourhood();
    printf("PASS\n");

    printf("reportByWard Test: Runs without crashing\n");
    reportByWard();
    printf("PASS\n");

    freeDB();
    return 0;
}