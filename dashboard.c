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
#include <stdio.h>
#include <string.h>


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
        // importDBBinary(argv[2]);
    }   
    else
    {
        printf("invalid mode. use -c or -b\n");
        printf("\n");
        return 1;
    }

    int option;
    int memberCode;
    int total;
    char fileName[256];
    char value[256];
    char memberName[100];

    do{
        printf("1. Export Database\n");
        printf("2. Count Entries\n");
        printf("3. Sort By\n");
        printf("4. Edit Entry\n");
        printf("5. Report\n");
        printf("6. Compress database\n");
        printf("7. Exit\n");
        printf("option: ");
        scanf("%d", &option);
        getchar();

        if (option == 1){
            printf("Enter a filename: ");
            fgets(fileName, sizeof(fileName), stdin);
            if (fileName[strlen(fileName) - 1] == '\n'){
                fileName[strlen(fileName) - 1] = '\0';
            }
            exportDB(fileName);
        }
        else if (option == 2){
            printf("Enter member code (1.TT 2.SM 3.StM 4.NID 5.NN 6.W): ");
            scanf("%d", &memberCode);
            getchar();

            if (memberCode == 1){
                strcpy(memberName, "table type");
            } 
            else if (memberCode == 2){
                strcpy(memberName, "surface material");
            } 
            else if (memberCode == 3){
                strcpy(memberName, "structural material");
            }
            else if (memberCode == 4){
                strcpy(memberName, "neighbourhood id");
            }
            else if (memberCode == 5){
                strcpy(memberName, "neighbourhood name");
            }
            else if (memberCode == 6){
                strcpy(memberName, "ward");
            }
            else {
                printf("Invalid member code\n");
                continue;
            }

            printf("Enter Value: ");
            fgets(value, sizeof(value), stdin);
            if (value[strlen(value) - 1] == '\n'){
                value[strlen(value) - 1] = '\0';
            }
            total = countEntries(memberName, value);
            printf("%s <%s> appeared in the table %d time(s)\n", memberName, value, total);
        }
        else if (option == 3){ //sort by
            printf("Enter a criteria to sort by (1.TT 2.SM 3.StM 4.NID 5.NN 6.W): ");
            scanf("%d", &memberCode);
            getchar();

            if (memberCode == 1){
                sortByMember("TT");//sort by table type
                exportDB("table_type.csv");
            }
            else if (memberCode == 2){
                sortByMember("SM");//sort by surface material
                exportDB("surface_material.csv");
            }
            else if (memberCode == 3){
                sortByMember("StM");//sort by structural material
                exportDB("structural_material.csv");
            }
            else if (memberCode == 4){
                sortByMember("NID");//sort by neighbourhood id
                exportDB("neighbourhood_id.csv");
            }
            else if (memberCode == 5){
                sortByMember("NN");//sort by neighbourhood name
                exportDB("neighbourhood_name.csv");
            }
            else if (memberCode == 6){
                sortByMember("W");//sort by ward
                exportDB("ward.csv");
            }
            else{
                printf("Invalid member code\n");
            }

        }
        else if (option == 4){ //edit entry
            int tableID;
            printf("Enter a numerical table entry to edit: ");
            scanf("%d", &tableID);
            getchar();

            printf("Enter member code (1.TT 2.SM 3.StM: ");
            scanf("%d", &memberCode);
            getchar();

            printf("Enter Value: ");
            fgets(value, sizeof(value), stdin);
            if (value[strlen(value) - 1] == '\n'){
                value[strlen(value) - 1] = '\0';
            }     
        }
        else if (option == 5){ //report
            int criteria;
            printf("Enter a criteria to report by (1. Neighborhood 2. Ward): ");
            scanf("%d", &criteria);
            getchar();

            if (criteria == 1){
                reportByNeighbourhood();//neighbourhood report
            }
            else if (criteria == 2){
               reportByWard(); //ward report
            }
            else {
                printf("Invalid option\n");
            }
        }
        else if (option == 6){ //compress
            printf("Enter filename: ");
            fgets(fileName, sizeof(fileName), stdin);
             if (fileName[strlen(fileName) - 1] == '\n'){
                fileName[strlen(fileName) - 1] = '\0';
            }

            compressDB(fileName);//compress database
        }
        else if (option != 7){
            printf("Invalid option\n");
        }
    } while (option != 7);

    freeDB();
    return 0;

}
