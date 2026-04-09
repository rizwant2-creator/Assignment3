/* DB_impl.h
 *
 * For any "private"  declarations that should not be visible to the public
 * users of the database, but might want to be shared across various source
 * files in database implementation.
 * 
 * It is a common convention to append "_impl" to a private implementation of
 * some public interface, so we do so here.
 *
 * Author: Taha Rizwan,Mark Seme,Rebecca Ngyuen
 * Lab instructor: Hanan Saleh
 * Lecture instructor: Dara Wagh 
 */


#ifndef DB_IMPL_H
#define DB_IMPL_H
#include "DB.h"

//table creators
Table *createTable(void);
NeighbourhoodTable *createNeighbourhoodTable(void);
PicnicTable *createPicnicTable(void);

//lookup helpers
int lookupTableID(Table *t, const char *name);
int lookupNeighbourhood(NeighbourhoodTable *nt, int id, const char *name);

//lookup by id helpers
const char *lookupTableName(Table *t, int id);
const char *lookupNeighbourhoodName(NeighbourhoodTable *nt, int id);

//insertion helpers
int insertToTable(Table *t, const char *name);
int insertToNeighbourhoodTable(NeighbourhoodTable *nt, int id, const char *name);
int insertToPicnicTable(PicnicTable *pt, PicnicTableEntry *entry);

//picnic table entry lookup by tableID
PicnicTableEntry *lookupPicnicEntry(PicnicTable *pt, int tableID);

#endif
