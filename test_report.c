#include <stdio.h>
#include "DB.h"

int main(void) {
    importDB("PicnicTableSmall.csv");
    if (Db == NULL) { printf("importDB failed\n"); return 1; }

    printf("=== Report By Neighbourhood ===\n");
    reportByNeighbourhood();

    printf("\n=== Report By Ward ===\n");
    reportByWard();

    freeDB();
    return 0;
}
