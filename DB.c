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
    if (fp == NULL){
        fprintf(stderr, "Could not open file %s\n", fileName);
        return;
    }

    Db = malloc(sizeof(DataBase)); //allocate database
    if (Db == NULL){
        fclose(fp);
        return;
    }

    //allocate lookup tables

    //initialize tables

    //initialize neighbourhood table

    //initialize picnic table

    //read csv

}

void exportDB(char *fileName){
    if (Db == NULL){
        return;
    }

    FILE *fp = fopen(fileName, "w");
    if (fp == NULL){
        fprintf(stderr, "Could not write file %s\n", fileName);
        return;
    }
}

void freeDB(void){
    if (Db == NULL){
        return;
    }

    //free lookup tables

    //free neighbourhood table

    //free picnic table
}