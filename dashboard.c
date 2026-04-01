/*
 * dashboard.c
 *
 * TODO: Provide a high-level description of what is contained
 * in this file.
 *
 * Author: <TODO: Group Member Names>
 * Lab instructor: <TODO: Your lab instructor's name here>
 * Lecture instructor: <TODO: Your lecture instructor's name here>
*/

//You may include other original headers as you see fit
#include "DB.h"
#include "DB_impl.h"

int main(int argc, char *argv[]){

    if (argc !=3)
    {
        printf("command should be as follows:\n");
        printf("%s -c <csv file name>\n",argv[0]);
        printf("%s -b <binary file name>\n",argv[0]);
        return 1;
    }
    //with having a correct command
    if (strcmp(argv[1],"-c")==0)
    {
        // read the csv file here
        importDB(argv[2]);

    }
    else if(strcmp(argv[1],"-b")==0)
    {
        // read the binary file
        importDBBinary(argv[2]);
    }   
    else
    {
        printf("invalid mode. use -c or -b\n")
    }
    return 0;
}
