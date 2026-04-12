#include <stdio.h>
#include <string.h>
#include "../DB.h"
#include "../DB_impl.h"

int main(void) 
{
    int count;
    importDB("./PicnicTableSmall.csv");
    if (Db ==NULL)
    {
        printf("importDB failed\n");
    }
    else
    {
        printf("import DB passed\n");
    }
    printf("total picnic tables = %d\n",Db->picnicTableTable->size);
    
    count = countEntries("ward","Ward 1");
    if (count>0)
    {
        printf("count by ward = %d\n",count);
        printf("count entry by ward passed\n");
    }

    count = countEntries("neighbourhood name","RIVER VALLEY VICTORIA");
    if (count>0)
    {
        printf("count by neighbourhood name  = %d\n",count);
        printf("count entry by neighbourhood name passed\n");
    }

    count = countEntries("table type","Square Picnic Table");
    if (count>0)
    {
        printf("count by table type = %d\n",count);
        printf("count entry by table type passed\n");
    }

    sortByMember("W");
    printf("first entry after sort by ward =%s\n",Db->picnicTableTable->entries[0].ward);

    exportDB("output.csv");
    printf("export db passed\n");
    freeDB();
    if (Db == NULL)
    {
        printf("free db passed\n");
    }
}


    