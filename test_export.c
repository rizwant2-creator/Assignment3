#include <stdio.h>
#include "DB.h"
#include "DB_impl.h"

int main(void) {
    importDB("PicnicTableSmall.csv");
    if (Db == NULL) { printf("importDB failed\n"); return 1; }
    exportDB("out.csv");
    printf("Export done.\n");
    freeDB();
    return 0;
}
