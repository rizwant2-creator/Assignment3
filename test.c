#include <stdio.h>

int main(void) {

    FILE *fp = fopen("PicnicTableSmall.csv", "r");
    if (fp == NULL) {
        printf("Could not open file\n");
        return 1;
    }

    char line[1024];
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
    }

    fclose(fp);
    // printf("===== Testing importDB Function =====\n\n");

    // // Test 1: Import the small CSV file
    // printf("Test 1: Importing PicnicTableSmall.csv...\n");
    // importDB("PicnicTableSmall.csv");
    // printf("✓ importDB executed successfully\n\n");

    // // Test 2: Verify data was imported using DB_impl functions
    // printf("Test 2: Verifying imported data using DB_impl functions...\n");

    // // Check that we have the expected number of entries (9 from CSV)
    // if (Db == NULL) {
    //     printf("✗ Database is NULL - importDB failed\n");
    //     return 1;
    // }

    // printf("Number of picnic table entries: %d\n", Db->picnicTableTable->size);
    // if (Db->picnicTableTable->size == 11) {
    //     printf("✓ Correct number of entries imported\n");
    // } else {
    //     printf("✗ Expected 9 entries, got %d\n", Db->picnicTableTable->size);
    // }

    // // Test lookup functions
    // printf("\nTesting lookup functions:\n");

    // // Test table type lookup
    // int tableTypeID = lookupTableID(Db->tableTypeTable, "Square Picnic Table");
    // if (tableTypeID > 0) {
    //     printf("✓ Found 'Square Picnic Table' with ID: %d\n", tableTypeID);
    // } else {
    //     printf("✗ Could not find 'Square Picnic Table'\n");
    // }

    // // Test surface material lookup
    // int surfaceID = lookupTableID(Db->surfaceMaterialTable, "Wood");
    // if (surfaceID >= 0) {
    //     printf("✓ Found 'Wood' surface material with ID: %d\n", surfaceID);
    // } else {
    //     printf("✗ Could not find 'Wood' surface material\n");
    // }

    // // Test structural material lookup
    // int structuralID = lookupTableID(Db->structuralMaterialTable, "Metal");
    // if (structuralID > 0) {
    //     printf("✓ Found 'Metal' structural material with ID: %d\n", structuralID);
    // } else {
    //     printf("✗ Could not find 'Metal' structural material\n");
    // }

    // // Test neighborhood lookup
    // int neighborhoodID = lookupNeighbourhood(Db->neighborhoodTable, 1200, "RIVER VALLEY VICTORIA");
    // if (neighborhoodID > 0) {
    //     printf("✓ Found neighborhood 'RIVER VALLEY VICTORIA' with ID: %d\n", neighborhoodID);
    // } else {
    //     printf("✗ Could not find neighborhood 'RIVER VALLEY VICTORIA'\n");
    // }

    // // Test reverse lookups (ID to name)
    // printf("\nTesting reverse lookups (ID to name):\n");

    // const char *tableName = lookupTableName(Db->tableTypeTable, 1);
    // if (tableName != NULL) {
    //     printf("✓ Table type ID 1 corresponds to: %s\n", tableName);
    // } else {
    //     printf("✗ Could not find name for table type ID 1\n");
    // }

    // const char *neighborhoodName = lookupNeighbourhoodName(Db->neighborhoodTable, 1200);
    // if (neighborhoodName != NULL) {
    //     printf("✓ Neighborhood ID 1200 corresponds to: %s\n", neighborhoodName);
    // } else {
    //     printf("✗ Could not find name for neighborhood ID 1200\n");
    // }

    // printf("\n===== Test Complete =====\n");
    return 0;
}
    // printf("  Tables in Downtown: %d\n", count4);
    // if (count4 >= 0) {
    //     printf("  ✓ Completed lookup for Downtown neighborhood\n");
    // }

    // // Count entries by Ward
    // printf("\nCounting entries by Ward:\n");
    // int count5 = countEntries("Ward", "Ward 1");
    // printf("  Tables in Ward 1: %d\n", count5);
    // if (count5 >= 0) {
    //     printf("  ✓ Completed lookup for Ward 1\n");
    // }

    // // Test 3: Generate a report
    // printf("\n\nTest 3: Generating report by neighborhood...\n");
    // printf("===== Report by Neighbourhood =====\n");
    // reportByNeighbourhood();
    // printf("\n===== End Report =====\n");

    // Cleanup
    // printf("\n\nCleaning up...\n");
    // freeDB();
    // printf("✓ Database freed successfully\n");

    // printf("\n===== All tests completed =====\n");
    // return 0;